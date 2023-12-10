#include "entity.h"

void entity_manager_create(server_t* s)
{
    s->em.htable = kh_init(ent);
    s->em.qtree  = kvad_tree_create(0,0, 1000, 1000, 255, 4);
}
void entity_manager_destroy(server_t* s)
{
    kh_destroy(ent, s->em.htable);
    kvad_tree_release(s->em.qtree);
}

entity_t* entity_get_by_id(khash_t(ent)* ht, int ID)
{
    entity_t* entity;
    khiter_t  iter = kh_get(ent, ht, ID);
    entity = &kh_val(ht, iter);

    return entity;
}

//WARNING: returned ID considered USED
static int get_new_id(entity_manager_t* em)
{
    int newID = 1;
    int iter = 0;
    for(int i=0; i<1000; i++)
    {
        newID = rand();
        iter = kh_get(ent, em->htable, newID);

        if (iter == kh_end(em->htable))
        {
            return newID;
        }
    }
    printf("random FAILED\n\n");
    exit(17213);
}

int entity_create(server_t* s, entity_t entity)
{
    int newID = get_new_id(&s->em);
    entity.id = newID;

    int retcode = 0;
    int iter = kh_put(ent, s->em.htable, newID, &retcode);
    kh_val(s->em.htable, iter) = entity;
    assert(retcode > 0);
    //writes ID into pointer, but its fine (i hope)
    kvad_tree_insert(s->em.qtree, entity.pos.x, entity.pos.y, (void*)((long)newID));

    return newID;
}

void entity_destroy(server_t* s, int type_id, int id)
{
    int iter = kh_get(ent, s->em.htable, id);
    kh_del(ent, s->em.htable, iter);
    //maybe does not work well with no coords, idk
    assert(kvad_tree_remove_payload(s->em.qtree, 0, 0, (void*)((long)id)) == 1);
}

static void entity_ai(server_t* s, entity_t* ent)
{
    switch (ent->type_id)
    {
    case 1: //player
        break;
    case 2: //black mushroom
        ent->vel.x += 0.01 * s->time_elapsed;
        if (ent->pos.x > 10) ent->pos.x = 0;
        break;
    case 3: //white mushroom
        ent->vel.y += 0.01 * s->time_elapsed;
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

    printf("pos %.2f %.2f %.2f\nvel %.2f %.2f %.2f\nid %d type %d\n", ent->pos.x, ent->pos.y, ent->pos.z, ent->vel.x, ent->vel.y, ent->vel.z,ent->id, ent->type_id);

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
        // else printf("does not exist\n");
    }
    printf("\n");
}