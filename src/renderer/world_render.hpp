#ifndef WORLD_RENDER_HPP
#define WORLD_RENDER_HPP

#include <cstdint>

#include <SDL2/SDL.h>

#include "../config.hpp"
#include "../world.hpp"

#include "MGL/include/mgl_texture.hpp"

class ChunkRender {
    public:

        ~ChunkRender();

        void load(GameWindow * gw, solid_block_chunk * sbc, const std::pair<int, int> chunk_pos);

        void updateChunk();

        void renderChunk();

    private:
        solid_block_chunk * sbc_; 
        std::pair<int, int> chunk_pos_;
        MGL_Texture * chunk_texture_;
        uint32_t pixel_data_[1024];      // 32 * 32 = 1024
        bool update_chunk_;
};

class WorldRender {
    public:
        WorldRender(GameWindow * gw, solid_world * sw);
        ~WorldRender();

        void initWorldRender();

        void updateWorldRender();

        void renderWorld();

    private:
        GameWindow * gw_;
        solid_world * sw_;
        ChunkRender crs_[WORLD_CHUNK_WIDTH * WORLD_CHUNK_HEIGHT];
};

#endif