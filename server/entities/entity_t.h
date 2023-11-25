#pragma once

#include <vec.h>
// #include <vector.h>
// #include <


typedef struct entity_t
{
    int type_id; //collider and AI
    int id; //unique id for virtual memory in clients and ability to realloc

    void* data; //mob personal storage. Stores whatever unique mob has except effects
    void* effects; //same but for effects

    vec3d pos;    
    vec3d vel;

} entity_t;

typedef struct entity_manager_t
{
    entity_t* entities; //reaplace with hashtable to find entities by id

    // entity_t
    //use chunks to find entities by position

} entity_manager_t;
