#pragma once

#include <entities/entity_t.h>
#include <net/net_t.h>
#include <chunks/chunk_t.h>

typedef struct server_t
{
    double last_tick;
    double time_elapsed;

    net_t net;
    entity_manager_t em;
    chunk_manager_t  cm;
} server_t;
