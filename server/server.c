#include <stdio.h>
#include <string.h>
#include <assert.h>
// #include <enet/enet.h>
#include <hasht/khash.h>


// #define LIBRG_IMPLEMENTATION
#include <sqlite3.h>
#include <net/net.h>

// void update

KHASH_MAP_INIT_INT(ht, double)
int main()
{
    // server_t server;



    // net_init(&server);

    // while (1) 
    // {
    //     printf("server loop\n");
    //     net_handle(&server);
        
    // }
    // net_deinit(&server);
    int retcode;
    khiter_t iterator;

    khash_t(ht)* hashtable = kh_init(ht);
    kh_put(ht, hashtable, 777, &retcode);
    kh_put(ht, hashtable, 222, &retcode);
    kh_put(ht, hashtable, 666, &retcode);

    iterator = kh_get(ht, hashtable, 777);
    kh_value(hashtable, iterator) = 17.0;
    iterator = kh_get(ht, hashtable, 222);
    kh_value(hashtable, iterator) = 12.0;
    iterator = kh_get(ht, hashtable, 666);
    kh_value(hashtable, iterator) = 16.0;

    for (iterator = kh_begin(hashtable); iterator != kh_end(hashtable); iterator++)
    {
        if (kh_exist(hashtable, iterator)) 
        {
            // kh_value(h, k) = 1;
            printf("%lf ", kh_value(hashtable, iterator));
        }
    }
}