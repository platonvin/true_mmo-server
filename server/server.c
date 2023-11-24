#include <stdio.h>
#include <string.h>
#include <assert.h>
// #include <enet/enet.h>


// #define LIBRG_IMPLEMENTATION
#include <librg/librg.h>
#include <sqlite3.h>
#include <net/net.h>

// void update

int main()
{
    server_t server;

    librg_world *world = librg_world_create();

    /* create our world configuration */
    librg_config_chunksize_set(world, 16, 16, 16);
    librg_config_chunkamount_set(world, 100, 100, 100);
    librg_config_chunkoffset_set(world, LIBRG_OFFSET_MID, LIBRG_OFFSET_MID, LIBRG_OFFSET_MID);


    net_init(&server);

    while (1) 
    {
        // printf("server loop\n");
        net_handle(&server);
        
    }
    net_deinit(&server);
}