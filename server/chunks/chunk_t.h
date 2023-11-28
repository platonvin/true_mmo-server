#pragma once

#include <vec.h>

typedef struct block_t
{
    // float x, y, z;
    int block_num;
} block_t;

typedef struct chunk_t
{
    //those ints are in general not zero
    int block_count;
    int height;
    //ALLOCATED array of blocks. They dont change
    block_t* blocks;
} chunk_t;

//this is 2d array of chunks, some of them are empty, used like hash_table
typedef struct chunk_manager_t
{
    int height, width;
    //2d array of chunk_t
    chunk_t* chunks;
} chunk_manager_t;
