#pragma once

#include <structs.h>
#include <vector.h>


//
entity_t* entity_create(server_t* s);

//all of them
void entities_update(server_t* server);

void entity_destroy(int type_id, int id);