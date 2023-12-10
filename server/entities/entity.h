#pragma once

#include <vector.h>
#include <hasht/khash.h>
#include <stdlib.h>
// #include <random.h>

#include <structs.h>
#include <iso646.h>

void entity_manager_create(server_t* s);
void entity_manager_destroy(server_t* s);
//
int  entity_create(server_t* s, entity_t entity);
void entity_destroy(server_t* s, int type_id, int id);

// typedef struct khash_t(ent) khash_t(ent);
entity_t* entity_get_by_id(khash_t(ent)* ht, int ID);

//all of them
void entities_update(server_t* server);
