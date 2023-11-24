#pragma once

#include <vec.h>


typedef struct entity_t
{
    int type_id;
    int id;

    vec3d pos;    
    vec3d vel;

    int collider;
    int ai;

    int stats;

    int state; //armor
    int effects; //
    
    int inventory;

} entity_t;
