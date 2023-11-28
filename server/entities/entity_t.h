#pragma once

#include <vec.h>
#include <hasht/khash.h>
#include <qdtree/kvad.h>
#include <vector.h>
// #include <


// int a =sizeof(entity_t);

typedef struct entity_t
{
    vec3d pos;    
    vec3d vel;
    
    void* data; //mob personal storage. Stores whatever unique mob has except effects
    void* effects; //same but for effects

    int id; //unique id for virtual memory in clients and ability to realloc
    int type_id; //collider, AI, drop,

    int state;

    /*
    stats
    owner
    drop
    */
} entity_t;

KHASH_MAP_INIT_INT(ent, entity_t)
typedef struct entity_manager_t
{
    // entity_t* entities; //reaplace with hashtable to find entities by id

    //entities stored in hash table
    khash_t(ent)* htable;
    kvad_tree*    qtree;

    // entity_t
    //use chunks to find entities by position

} entity_manager_t;
