#pragma once

#include <net/net_t.h>
#include <entities/entity_t.h>

typedef struct server_t
{
    net_t net;

    entity_manager_t em;
} server_t;
