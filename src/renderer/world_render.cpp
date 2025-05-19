#include "./world_render.hpp"

ChunkRender::~ChunkRender() {
    delete chunk_texture_;
}

void ChunkRender::load(GameWindow * gw, solid_block_chunk * sbc, const std::pair<int, int> chunk_pos) {
    sbc_ = sbc;
    update_chunk_ = true;
    chunk_pos_ = chunk_pos;
    chunk_texture_ = new MGL_Texture(gw);
    if(chunk_texture_->load(SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 32, 32) != 0) {exit(-1);}
}

void ChunkRender::updateChunk() {
    if (update_chunk_) {
        const uint32_t * data_32 = sbc_->data;
        int k = 0;
        for (int i = 0; i < 32; i++) {
            uint32_t row = data_32[i];
            for (int j = 0; j < 32; j++) {
                uint32_t mask = 1 << j;
                uint32_t bit_value = (row & mask) >> j;
                pixel_data_[k] = 0x00FF00FF * bit_value;
                k++;
            }
        }
        chunk_texture_->drawTextureWithPixelStream(static_cast<Uint32*>(pixel_data_));
    }
    update_chunk_ = false;
}

void ChunkRender::renderChunk() {
    chunk_texture_->renderTexture(chunk_pos_);
}

WorldRender::WorldRender(GameWindow * gw, solid_world * sw) : gw_(gw), sw_(sw) {}

WorldRender::~WorldRender() {}

void WorldRender::initWorldRender() {
    for (int w = 0; w < WORLD_CHUNK_WIDTH; w++) {
        for (int h = 0; h < WORLD_CHUNK_HEIGHT; h++) {
            const std::pair<int, int> position = {w * CHUNK_WIDTH, h * CHUNK_HEIGHT};
            solid_block_chunk * sbc = &sw_->world[w][h];
            crs_[w * WORLD_CHUNK_HEIGHT + h].load(gw_, sbc, position);
        }
    }
}

void WorldRender::updateWorldRender() {
    for (int k = 0; k < WORLD_CHUNK_WIDTH * WORLD_CHUNK_HEIGHT; k++) {
        crs_[k].updateChunk();
    }
}

void WorldRender::renderWorld() {
        for (int k = 0; k < WORLD_CHUNK_WIDTH * WORLD_CHUNK_HEIGHT; k++) {
        crs_[k].renderChunk();
    }
}