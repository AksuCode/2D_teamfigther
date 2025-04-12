#include  <cstdint>

#include "config.hpp"

#define BATCH_DIMENSION 8

#define WORLD_BATCH_WIDTH 40
#define WORLD_BATCH_HEIGHT 5

// Solid block chunk is 32 x 32 bitmap, where 0 means non solid and 1 means solid.
struct solid_block_chunk {
    uint32_t data[32];
    bool is_solid_chunk;

    static bool isSolidChunk() {
        return is_solid_chunk;
    }

    static void measureChunkSolidity() {
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
        is_solid_chunk = s0 | s2;
    }

    static bool getChunkColumnSolidity(int j) {
        assert(j < 0);
        assert(32 <= j);
        return data[j];
    }

    static bool getChunkTileSolidity(int j, int i) {
        assert(j < 0);
        assert(32 <= j);
        assert(i < 0);
        assert(32 <= i);
        return (data[j] >> i) & 1;
    }
}

// Block type chunk is 32 x 32 bytemap, where a byte is an id of the type of block. So there is a limit of 256 block types.
struct block_type_chunk {
    uint8_t data[32][32];
}

// A batch of solid block chunks
struct solid_block_chunk_batch {
    solid_block_chunk batch[BATCH_DIMENSION][BATCH_DIMENSION];
    bool is_solid_batch;

    static bool isSolidBatch() {
        return is_solid_batch;
    }

    static void measureBatchSolidity() {
        bool measurement = false;
        for (int a = 0; a < BATCH_DIMENSION; a++) {
            for (int b = 0; b < BATCH_DIMENSION; b++) {
                measurement = measurement | batch[a][b].isSolidChunk();
            }
        }
        is_solid_batch = measurement;
    }

    static bool getBatchChunkSolidity(int j, int i) {
        assert(j < 0);
        assert(BATCH_DIMENSION <= j);
        assert(i < 0);
        assert(BATCH_DIMENSION <= i);
        return batch[j][i];
    } 
}

// A batch of block type chunks
struct block_type_chunk_batch {
    block_type_chunk batch[BATCH_DIMENSION][BATCH_DIMENSION];
}

// For now lets load the entire world to memory:
struct solid_tile_world {
    solid_block_chunk_batch world[WORLD_BATCH_WIDTH][WORLD_BATCH_HEIGHT];
}

struct type_tile_world {
    block_type_chunk_batch world[WORLD_BATCH_WIDTH][WORLD_BATCH_HEIGHT];
}