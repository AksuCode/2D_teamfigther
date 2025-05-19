#include <cstdint>
#include <utility>


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

// For now lets load the entire world to memory:
struct solid_tile_world {
    solid_block_chunk_batch world[WORLD_BATCH_WIDTH][WORLD_BATCH_HEIGHT];

    void worldGenerate() {
        for(int w = 0; w < WORLD_BATCH_WIDTH; w++) {
            for (int h = WORLD_BATCH_HEIGHT / 2; h < WORLD_BATCH_HEIGHT; h++) {
                solid_block_chunk_batch & chunk_batch = world[w][h];
                solid_block_chunk & chunk_batch_data = chunk_batch.batch;
                for (int j = 0; j < BATCH_DIMENSION; j++) {
                    for (int i = 0; i < BATCH_DIMENSION; i++) {
                        solid_block_chunk & block_chunk = chunk_batch_data[j][i];
                        uint32_t & block_chunk_data = block_chunk.data
                        for (int k = 0; k < 32; k++) {
                            data[k] = UINT32_MAX;
                        }
                        block_chunk.measureChunkSolidity();
                    }
                }
                chunk_batch.measureBatchSolidity();
            }
        }
    }

    // Returns uint_8 which is a bit mask. If the bit mask is NOT 0, there is a collision.
    // If the least significant bit is 1 there is collision on top.
    // Second bit means collision on right. Third means bottom. Fourth means left.
    // end_position gives the position when collision occures.
    /*
    static uint8_t collisionResolution( const std::pair<double, double> starting_position,
                                        const std::pair<double, double> hitbox,
                                        const std::pair<double, double> movement_vector,
                                        std::pair<double, double> & end_position 
                                    ) {
        const double half_width = hitbox.first / 2;
        const double half_height = hitbox.second / 2;

        //const std::pair<double, double> top_right = {starting_position.first + half_width, starting_position.second + half_height};
        //const std::pair<double, double> bot_right = {starting_position.first + half_width, starting_position.second - half_height};
        //const std::pair<double, double> bot_left = {starting_position.first - half_width, starting_position.second - half_height};
        //const std::pair<double, double> top_left = {starting_position.first - half_width, starting_position.second + half_height};

        if (movement_vector.first > 0 && movement_vector.second > 0) {
            const std::pair<double, double> top_right = {starting_position.first + half_width, starting_position.second + half_height};
            const std::pair<double, double> candidate_end_position = {top_right.first + movement_vector.first, top_right.second + movement_vector.second};

            // Linear equation:
            const double A = top_right.second - candidate_end_position.second;
            const double B = candidate_end_position.first - top_right.first;
            const double C = top_right.first * candidate_end_position.second - candidate_end_position.first * top_right.second;

            // Horizontal:

        }

        
    }
    */
}

// Block type chunk is 32 x 32 bytemap, where a byte is an id of the type of block. So there is a limit of 256 block types.
struct block_type_chunk {
    uint8_t data[32][32];
}

// A batch of block type chunks
struct block_type_chunk_batch {
    block_type_chunk batch[BATCH_DIMENSION][BATCH_DIMENSION];
}

struct type_tile_world {
    block_type_chunk_batch world[WORLD_BATCH_WIDTH][WORLD_BATCH_HEIGHT];
}