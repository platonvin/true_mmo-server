#pragma once

#include <vec.h>
#include <qdtree/kvad.h>
#include <vector.h>
#include <hasht/khash.h>
// #include <

// int a =sizeof(entity_t);

enum state_e
{
    STATE_UNDEF = 0,
    STATE_IDLE = 1,
    STATE_MOVING = 2,
    STATE_ATTACKING = 3,
};

enum mobs_e
{
    MOB_UNDEF = 0,
    MOB_PLAYER = 2,
    MOB_BLACK_MUSHROOM = 2,
    MOB_WHITE_MUSHROOM = 3,
};

typedef union entity_data_t
{
    struct {int   a,b,c,d};
    struct {float x,y,z,w};
    char ch[16];
} entity_data_t;

typedef struct entity_t
{
    vec3d pos;    
    vec3d vel;
    
    void* data; //mob personal storage. Stores whatever unique mob has except effects
    void* effects; //same but for effects

    int id; //unique id for virtual memory in clients and ability to realloc
    int type_id; //collider, AI, drop,

    enum state_e state;

    /*
    stats
    owner
    drop
    */
   entity_data_t data;
} entity_t;

KHASH_MAP_INIT_INT(ent, entity_t)
// typedef struct khash_t(ent) khash_t(ent);
typedef struct entity_manager_t
{
    // entity_t* entities; //reaplace with hashtable to find entities by id

    //entities stored in hash table
    khash_t(ent)* htable;
    // entity_t*  cells; //cells with entities
    // int* empty_cells;
    kvad_tree*    qtree;

    // entity_t
    //use chunks to find entities by position

} entity_manager_t;
