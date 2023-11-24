#include "net.h"

void net_init(server_t* server)
{
    assert(enet_initialize()==0);

    ENetAddress adress;
    ENetHost* server_host;

    adress.host = ENET_HOST_ANY;
    adress.port = 8800;

    server_host = enet_host_create(&adress, 1024, 2, 0, 0);
    assert (server_host != 0);

    server->net.host = server_host;
}

void net_deinit(server_t* server)
{
    enet_host_destroy(server->net.host);
    enet_deinitialize();
}

static void handle_event(ENetEvent event)
{
    switch (event.type) 
    {
        case ENET_EVENT_TYPE_CONNECT:
            printf("client connected\n");
            break;

        case ENET_EVENT_TYPE_RECEIVE:
            printf("smth received\n");
            break;

        case ENET_EVENT_TYPE_DISCONNECT:
            printf("client disconnected\n");
            break;

        default:
            printf("Tick tock   \n");
            break;
    }
}

void net_update(server_t* server)
{
    ENetEvent event;
    ENetPacket* packet;    

    //trying to fastly go through all the packets and process data
    while (enet_host_service(server->net.host, &event, 0) > 0) 
    {
        handle_event(event);
    }
}