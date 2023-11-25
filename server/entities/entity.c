#include "entity.h"

entity_t* entity_create(server_t* s)
{
    entity_t entity = {0};

    vector_add(&s->em.entities, entity);

    return &s->em.entities[vector_size(s->em.entities) - 1];    
}

//all of them
void entities_update(server_t* server);

void entity_destroy(int type_id, int id);