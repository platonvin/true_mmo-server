#pragma once

#include <structs.h>
#include <vector.h>
#include <hasht/khash.h>

void entity_manager_create(server_t* s);
void entity_manager_destroy(server_t* s);
//
void entity_create(server_t* s, entity_t entity);

//all of them
void entities_update(server_t* server);

void entity_destroy(server_t* s, int type_id, int id);