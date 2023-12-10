#include "net.h"


void net_init(server_t* server)
{
    assert(enet_initialize()==0);

    ENetAddress adress;
    ENetHost* server_host;

    adress.host = ENET_HOST_ANY;
    adress.port = 8800;

    server_host = enet_host_create(&adress, 8, 2, 0, 0);
    assert (server_host != 0);

    server->net.host = server_host;


    printf("peerCount %d\n", server->net.host->peerCount);
}

void net_deinit(server_t* server)
{
    enet_host_destroy(server->net.host);
    enet_deinitialize();
}


// void on_player_connect
// void on_player_disconnect
// void o
static void handle_event(server_t* s, ENetEvent* event)
{
    switch (event->type) 
    {
        case ENET_EVENT_TYPE_CONNECT:
            printf("client connected\n");

            entity_t player_ent = {0};
            player_ent.type_id = 1;
            // player_ent.
            // add client player to map. Also write down its entity ID to do some client stuff 
            int player_entID = entity_create(s, player_ent);
            event->peer->data = (void*)((long) player_entID);
            break;

        case ENET_EVENT_TYPE_RECEIVE:
            // printf("smth received\n");
            int ID = (int)((long)(event->peer->data));
            entity_t* player = NULL;
            player = entity_get_by_id(s->em.htable, ID);
            player->pos = *(vec3d*)event->packet->data;

            break;

        case ENET_EVENT_TYPE_DISCONNECT:

            entity_destroy(s, 0, (int)((long)(event->peer->data)));
            printf("client disconnected\n");
            event->peer->data = NULL; //no id anymore
            break;

        default:
            // printf("Tick tock   \n");
            break;
    }
}

void pack_entities_for_client(double x, double y, void *payload, void *context)
{
    client_ctx *ctx = context;
    int entity_id = (int) ((long int) payload); //get our int stored in pointer;

    if(ctx->ignored_id == entity_id) return;

    entity_t* entity = entity_get_by_id(ctx->ht, entity_id);

    entity2send_t ent_for_client = {0};
    ent_for_client.pos     = entity->pos;
    ent_for_client.vel     = entity->vel;
    ent_for_client.id      = entity->id;
    ent_for_client.type_id = entity->type_id;
    ent_for_client.state   = entity->state;

    vector_add(&ctx->ents2client, ent_for_client);
}

//writing packet type, data count and data to packet
static void copy_entities(char *data, int type, entity2send_t *ents_vec)
{
    ((int*)data)[0] = type; //type of entities
    ((int*)data)[1] = vector_size(ents_vec);
    memcpy(data + sizeof(int)*2, ents_vec, vector_size(ents_vec) * sizeof(entity2send_t)); 
}

static void send_entities(server_t* s, ENetPeer* client_peer)
{
        int player_entID = (int) ((long int) client_peer->data);
        entity_t* player = entity_get_by_id(s->em.htable, player_entID);

        client_ctx context = {0}; 
        context.ht = s->em.htable;
        context.ignored_id = player_entID;
        context.ents2client = vector_create();

        //packing entities around this player
        kvad_tree_find(s->em.qtree, player->pos.x, player->pos.y, 10, 10, pack_entities_for_client, &context);

        //so now we have entities to send. Lets put packet type and entities into packet
        //allocating memory for packet
        ENetPacket* packet = enet_packet_create(NULL, sizeof(int)*2 + vector_size(context.ents2client) * sizeof(entity2send_t), ENET_PACKET_FLAG_RELIABLE);
        copy_entities(packet->data, ENTITIES_PACKET, context.ents2client);
        
        vector_free(context.ents2client);
        // vector_erase(&context.ents2client, 0, vector_size(context.ents2client));
        
        //sending the packet. Maybe should call flush, need to test
        enet_peer_send(client_peer, 0, packet);
}

void net_update(server_t* server)
{
    ENetEvent event = {0};
    // packet.

    //trying to fastly go through all the packets and process data
    while (enet_host_service(server->net.host, &event, 0) > 0) 
    {
        handle_event(server, &event);
    }

    // for (int i=0; i < server->net.host->peerCount; i++)
    // {
    //     ENetPeer* client_peer = &server->net.host->peers[i];
    //     send_entities(server, client_peer);
    //     printf("%4d ", client_peer->connectID);
    // } printf("\n");


    
    // for every client send entity updates to it
    
    for (int i=0; i < server->net.host->peerCount; i++)
    {
        // printf("lol %d\n", server->net.host->peerCount);
        ENetPeer* client_peer = &server->net.host->peers[i];
        if (client_peer->connectID != 0)
        {
            send_entities(server, client_peer);
        }
    }
}