#pragma once

#define GLEW_STATIC

//std libs
#include <malloc.h>
#include <stdio.h>
#include <assert.h>

//structs
#include <structs.h>

//reads manager from file
void chunk_load_system(char* file_name, server_t* s);

void chunk_destroy_system(server_t* s);

chunk_t* get_chunk(server_t* s, int x, int y);

block_t get_block(server_t* s, int x, int y, int z);