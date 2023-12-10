#include <stdio.h>
#include <string.h>
#include <assert.h>
// #include <windows.h>
// #include <timeapi.h>
#include <time.h>
// #include <sys/time.h>
// #include <enet/enet.h>
// #include <hasht/khash.h>


// #include <sqlite3.h>
#include <entities/entity.h>
#include <net/net.h>
#include <macros.h>

#include <timer.c>
#include <structs.h>

#define CALL(x) \
do{ \
printf("called   %s\n", #x); \
x; \
printf("returned %s\n", #x); \
}while(0)


void time_update(server_t* s)
{
    double current_time = ns() / 1e9;
    s->time_elapsed = current_time - s->last_tick;
    s->last_tick = current_time;
}

int main()
{
    server_t server = {0};
    // used for id generation
    srand(time(NULL));
    server.last_tick = ns() / 1e9;
    
    //creating managers
    CALL(net_init(&server));
    CALL(entity_manager_create(&server));
    entity_t bm={0}, wm={0};
    bm.type_id = 2; bm.state = STATE_IDLE;
    wm.type_id = 3; wm.state = STATE_IDLE;
    entity_create(&server, bm);
    entity_create(&server, wm);

    while (1) 
    {
        time_update(&server);
        entities_update(&server);
        // printf("server loop\n");
        net_update(&server);

        Sleep(1000);
    }

    //destroying managers
    net_deinit(&server);
    entity_manager_destroy(&server);

    printf("MANAGERS DESTROYED\n");

    return 0;
}