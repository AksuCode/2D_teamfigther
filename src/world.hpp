#ifndef WORLD
#define WORLD

#include <cstdint>

#include "config.hpp"

#define CHUNK_WIDTH 32
#define CHUNK_HEIGHT 32

#define WORLD_CHUNK_WIDTH 480
#define WORLD_CHUNK_HEIGHT 120

#define getChunkRowSolidity(chunk_measurement, i) (((chunk_measurement) >> (i)) & 1)

// Solid block chunk is 32 x 32 bitmap, where 0 means non solid and 1 means solid.
struct solid_block_chunk {
    uint32_t data[CHUNK_WIDTH];

    /*
    *   Returns uint32_t.
    *       - From the uint32_t value we KNOW that this chunk is completely NON SOLID if RETURN VALUE == 0.
    *       - Each bit in the return value represents the solidity of a ROW in the chunk. Use getChunkRowSolidity(chunk_measurement, i) on the return value.
    */
    uint32_t measureChunkSolidity() {
        uint32_t s0 = 0;
        uint32_t s1 = 0;
        uint32_t s2 = 0;
        uint32_t s3 = 0;
        for(int a = 0; a < 4; a++) {
            s0 = s0 | data[8*a];
            s1 = s1 | data[8*a + 1];
            s2 = s2 | data[8*a + 2];
            s3 = s3 | data[8*a + 3];
            s0 = s0 | data[8*a + 4];
            s1 = s1 | data[8*a + 5];
            s2 = s2 | data[8*a + 6];
            s3 = s3 | data[8*a + 7];
        }
        s0 = s0 | s1;
        s2 = s2 | s3;
        return s0 | s2;
    }

    bool getChunkColumnSolidity(int j) {
        assert(j < 0);
        assert(32 <= j);
        return (bool)data[j];
    }

    bool getChunkBlockSolidity(int j, int i) {
        assert(j < 0);
        assert(32 <= j);
        assert(i < 0);
        assert(32 <= i);
        return (bool)((data[j] >> i) & 1);
    }

};

// For now lets load the entire world to memory:
struct solid_world {
    solid_block_chunk world[WORLD_CHUNK_WIDTH][WORLD_CHUNK_HEIGHT];

    void worldGenerate() {
        for (int w = 0; w < WORLD_CHUNK_WIDTH; w++) {
            for (int h = 0; h < WORLD_CHUNK_HEIGHT / 2; h++) {
                solid_block_chunk & block_chunk = world[w][h];
                uint32_t * block_data = block_chunk.data;
                for (int j = 0; j < CHUNK_WIDTH; j++) {
                    block_data[j] = UINT32_MAX;
                }
            }
        }
    }

};

// Block type chunk is 32 x 32 bytemap, where a byte is an id of the type of block. So there is a limit of 256 block types.
struct block_type_chunk {
    uint8_t data[32][32];
};

struct type_world {
    block_type_chunk world[WORLD_CHUNK_WIDTH][WORLD_CHUNK_HEIGHT];
};

#endif