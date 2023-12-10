#include "chunk.h"

// #define PRINT printf("line %d, function %s\n", __LINE__, __FUNCTION__);

#define CHUNK_SIZE 8

void chunk_load_system(char* file_name, server_t* s) 
{
    FILE* file = fopen(file_name, "rb");
    assert(file != 0);

    // Read the height and width of the 2D array of chunk_t objects from the file
    assert(fread(&s->cm.height, sizeof(int), 1, file)==1);
    assert(fread(&s->cm.width , sizeof(int), 1, file)==1);

    // Allocate memory for the height*width chunks
    s->cm.chunks = calloc(s->cm.height * s->cm.width, sizeof(chunk_t));
    assert(s->cm.chunks != NULL);
    // assert(chunk_manager->chunks != 0);

    // Read the 2D array of chunk_t objects from the file
    for (int y = 0; y < s->cm.height; y++) 
    {
        for (int x = 0; x < s->cm.width; x++) 
        {
            chunk_t* chunk = &(s->cm.chunks[x + y*s->cm.height]);

            // Read the chunk's info
            assert(fread(&chunk->height, sizeof(int), 1, file)==1);
            assert(fread(&chunk->block_count, sizeof(int), 1, file)==1);
            assert(chunk->block_count == chunk->height * CHUNK_SIZE * CHUNK_SIZE);
            // printf("offset:%d block_count:%d\n", chunk->offset, chunk->block_count);

            chunk->blocks = calloc(chunk->block_count, sizeof(block_t));
            assert(chunk->blocks != NULL);
            // Read the chunk's data
            assert(fread(chunk->blocks, sizeof(block_t), chunk->block_count, file)==1);
        }
    }

    fclose(file);
    // fclose(chunk_file  );

}

chunk_t* get_chunk(server_t* s, int x, int y)
{
    int x_in_chunks = x / 16;
    int y_in_chunks = y / 16;

    chunk_t* chunk = &s->cm.chunks[x_in_chunks + s->cm.width * y_in_chunks];
    // get
    return chunk;
}

block_t get_block(server_t* s, int x, int y, int z)
{
    block_t block;
    chunk_t* chunk = get_chunk(s, x, y);

    block = chunk->blocks[x + y * 16 + z * 16 * 16];

    return block;
}


void chunk_destroy_manager(server_t* s) 
{
    for (int y = 0; y < s->cm.height; y++) 
    {
        for (int x = 0; x < s->cm.width; x++) 
        {
            chunk_t* chunk = &(s->cm.chunks[x + y*s->cm.height]);

            free(chunk->blocks);
        }
    }
    free(s->cm.chunks);
    return;
}