#include "./world_render.hpp"

WorldRender::WorldRender(GameWindow * gw, solid_world * sw, std::pair<double, double> * world_point_at_viewport_focal_point) : gw_(gw), sw_(sw), world_point_at_viewport_focal_point_(world_point_at_viewport_focal_point) {}

WorldRender::~WorldRender() {
    SDL_DestroyTexture(texture_);
}

void WorldRender::InitAndReconfig() {
    viewport_width_ = gw_->getWindowWidth();
    viewport_height_ = gw_->getWindowHeigth();

    texture_width_ = WORLD_CHUNK_WIDTH * CHUNK_DIMENSION;
    texture_height_ = WORLD_CHUNK_HEIGHT * CHUNK_DIMENSION;

    texture_ = createChunkTexture();
    if (texture_ == NULL) {exit(-1);}

    viewport_middle_point_ = {gw_->getWindowWidth() / 2, gw_->getWindowHeigth() / 2};
}

void WorldRender::InitialDraw() {
    auto solid_block_chunk_matrix = sw_->world;
    int counter = 0;
    for (int i = 0; i < WORLD_CHUNK_WIDTH; i++) {
        for (int j = 0; j < WORLD_CHUNK_HEIGHT; j++) {
            uint32_t * data = solid_block_chunk_matrix[i][j].data;
            for (int k = 0; k < CHUNK_DIMENSION; k++) {
                Uint32* pixels;
                int pitch;

                SDL_Rect target;
                target.w = CHUNK_DIMENSION;
                target.h = CHUNK_DIMENSION;
                target.x = i * CHUNK_DIMENSION;
                target.y = j * CHUNK_DIMENSION;

                // Assume texture is created with SDL_TEXTUREACCESS_STREAMING
                if (SDL_LockTexture(texture_, &target, (void**)&pixels, &pitch) != 0) {
                    exit(-1);
                }

                // pitch is in bytes, so divide by 4 for 32-bit pixels (Uint32)
                int width = pitch / 4;
                for (int w = 0; w < CHUNK_DIMENSION; ++w) {
                    uint32_t col = data[w];
                    for (int h = 0; h < CHUNK_DIMENSION; ++h) {
                        uint32_t mask = 1 << w;
                        uint32_t bit_value = (col & mask) >> w;
                        Uint32 pixel = static_cast<Uint32>(0xFF0064FF);
                        if (bit_value != 0) {
                            pixel = static_cast<Uint32>(0x00FF00FF);
                        }
                        pixels[w * width + h] = pixel;
                    }
                }

                SDL_UnlockTexture(texture_);
            }
        }
        std::cout << counter << std::endl;
        counter++;
    }
}

void WorldRender::renderWorld() {
    SDL_Rect src_rect;
    src_rect.w = viewport_width_;
    src_rect.h = viewport_height_;
    src_rect.x = world_point_at_viewport_focal_point_->first;
    src_rect.y = world_point_at_viewport_focal_point_->second;

    SDL_Rect dst_rect;
    dst_rect.w = viewport_width_;
    dst_rect.h = viewport_height_;
    dst_rect.x = viewport_middle_point_.first - (viewport_width_ / 2);
    dst_rect.y = viewport_middle_point_.second - (viewport_height_ / 2);

    gw_->renderTexture(texture_, &src_rect, &dst_rect);
}

SDL_Texture * WorldRender::createChunkTexture() {
    SDL_Texture * res = SDL_CreateTexture(static_cast<SDL_Renderer*>(gw_->getRenderer()), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, texture_width_, texture_height_);
    return res;
}