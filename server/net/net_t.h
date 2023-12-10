#pragma once

#include <enet/enet.h>
#include <vec.h>
#include <hasht/khash.h>


enum packet_types
{
    ENTITIES_PACKET = 1,
};


typedef struct net_t
{
    ENetHost* host;
} net_t;

typedef struct entity2send_t
{
    vec3d pos;    
    vec3d vel;
    
    int id; //unique id for virtual memory in clients and ability to realloc
    int type_id; //collider, AI, drop,

    int state;

} entity2send_t;

typedef struct client_ctx
{
    khash_t(ent)* ht;
    entity2send_t* ents2client;
    int ignored_id;

} client_ctx;