#include "entity.h"

void entity_manager_create(server_t* s)
{
    s->em.htable = kh_init(ent);
    s->em.qtree = kvad_tree_create(0,0, 1000, 1000, 255, 4);
}
void entity_manager_destroy(server_t* s)
{
    kh_destroy(ent, s->em.htable);
    kvad_tree_release(s->em.qtree);
}

void entity_create(server_t* s, entity_t entity)
{
    khiter_t iter;
    khint32_t retcode;

    iter = kh_put(ent, s->em.htable, 23123, &retcode);
    kh_value(s->em.htable, iter) = entity;
    kvad_tree_insert(s->em.qtree, entity.pos.x, entity.pos.y, )
}

static void entity_ai(server_t* s, entity_t* ent)
{
    switch (ent->type_id)
    {
    case 0: //player
        break;
    case 1: //black mushroom
        ent->vel.x += 0.01;
        if (ent->pos.x > 10) ent->pos.x = 0;
        break;
    case 2: //white mushroom
        ent->vel.y += 0.01;
        if (ent->pos.y > 10) ent->pos.y = 0;
        break;

    default:
        break;
    }
}

static void entity_move(server_t* s, entity_t* ent)
{
    ent->pos = v3dadd(ent->pos, v3dscale(ent->vel, s->time_elapsed));
}


//JUST ONE 
static void entity_update(server_t* s, entity_t* ent)
{
    /*
    depending on type_id:
    if should, move
    if should, call ai_update
    if should, update effects
    on collide either just move or damage collider
    */

    entity_move(s, ent);

    entity_ai  (s, ent);


    // (void(*)()) ai = entity_ai(ent->type_id);
    // ai();

    //update effects

    //handle collisions
}


//all of them
void entities_update(server_t* s)
{
    khint32_t iter;
	for (iter = kh_begin(s->em.htable); iter != kh_end(s->em.htable); iter++)
    {
		if (kh_exist(s->em.htable, iter)) 
        {
            entity_update(s, &kh_val(s->em.htable, iter));
        }
    }
}

void entity_destroy(server_t* s, int type_id, int id)
{
    khint32_t iter;
    iter = kh_get(ent, s->em.htable, id);
    kh_del(ent, s->em.htable, iter);
    kvad_tree
}