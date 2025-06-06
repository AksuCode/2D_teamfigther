#ifndef WORLD
#define WORLD

#include <cstdint>

#include "config.hpp"

// *** All of these should be power of 2 ***
#define CHUNK_DIMENSION 32          // 2^5 = 32

#define BATCH_DIMENSION 64          // 2^6 = 64

#define WORLD_BATCH_WIDTH 8
#define WORLD_BATCH_HEIGHT 4

#define WORLD_CHUNK_WIDTH 512
#define WORLD_CHUNK_HEIGHT 256

#define WORLD_BLOCK_HEIGHT (CHUNK_DIMENSION * WORLD_CHUNK_HEIGHT)
// *** ***

#define getChunkRowSolidity(chunk_measurement, i) (((chunk_measurement) >> (i)) & 1)

struct solid_block_chunk {
    uint32_t data[CHUNK_DIMENSION];

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

struct solid_world {
    solid_block_chunk world[WORLD_CHUNK_WIDTH][WORLD_CHUNK_HEIGHT];

    void worldGenerate() {
        for (int w = 0; w < WORLD_CHUNK_WIDTH; w++) {
            for (int h = 0; h < WORLD_CHUNK_HEIGHT; h++) {
                solid_block_chunk & block_chunk = world[w][h];
                uint32_t * block_data = block_chunk.data;
                for (int j = 0; j < CHUNK_DIMENSION; j++) {
                    block_data[j] = 0;
                    if (h < WORLD_CHUNK_HEIGHT / 2) {
                        if (1 < j && j < 30) {
                            block_data[j] = 0x3FFFFFFC;
                        }
                    }
                }
            }
        }

        world[0][255].data[31] = 0xFFFFFF0F;

    }

};

struct block_type_chunk {
    uint16_t data[32][32];
};

struct type_world {
    block_type_chunk world[WORLD_CHUNK_WIDTH][WORLD_CHUNK_HEIGHT];
};

#endif