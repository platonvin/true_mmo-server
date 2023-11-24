#pragma once

#include <enet/enet.h>
#include <structs.h>

void net_init  (server_t* server);
void net_deinit(server_t* server);

void net_update(server_t* server);
