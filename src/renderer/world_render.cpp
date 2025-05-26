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
}

void WorldRender::InitialDraw() {
    auto solid_block_chunk_matrix = sw_->world;
    int counter = 0;
    for (int i = 0; i < WORLD_CHUNK_WIDTH; i++) {
        for (int j = 0; j < WORLD_CHUNK_HEIGHT; j++) {
            uint32_t * data = solid_block_chunk_matrix[i][j].data;
            
            Uint32* pixels;
            int pitch;

            SDL_Rect target;
            target.w = CHUNK_DIMENSION;
            target.h = CHUNK_DIMENSION;
            target.x = i * CHUNK_DIMENSION;
            target.y = (WORLD_CHUNK_HEIGHT - j - 1) * CHUNK_DIMENSION;

            // Assume texture is created with SDL_TEXTUREACCESS_STREAMING
            if (SDL_LockTexture(texture_, &target, (void**)&pixels, &pitch) != 0) {
                exit(-1);
            }

            // pitch is in bytes, so divide by 4 for 32-bit pixels (Uint32)
            int width = pitch / 4;
            for (int w = 0; w < CHUNK_DIMENSION; ++w) {
                uint32_t col = data[w];
                for (int h = 0; h < CHUNK_DIMENSION; ++h) {
                    uint32_t mask = 1 << h;
                    uint32_t bit_value = (col & mask) >> h;
                    Uint32 pixel = static_cast<Uint32>(0xB2FFFFFF);
                    if (bit_value != 0) {
                        pixel = static_cast<Uint32>(0x00FF00FF);
                    }
                    pixels[w * width + h] = pixel;
                }
            }

            SDL_UnlockTexture(texture_);
        }
        std::cout << counter << std::endl;
        counter++;
    }
}

void WorldRender::renderWorld() {
    SDL_Rect src_rect;
    
    int src_x = world_point_at_viewport_focal_point_->first;
    int src_y = world_point_at_viewport_focal_point_->second;

    SDL_Rect dst_rect;

    if (src_x < 0) {
        src_rect.w = viewport_width_ + src_x;
        src_rect.x = 0;

        dst_rect.w = viewport_width_ + src_x;
        dst_rect.x = -src_x;
    } else if (texture_width_ <= src_x + viewport_width_) {
        if (texture_width_ <= src_x) {return;}
        src_rect.w = texture_width_ - src_x;
        src_rect.x = src_x;

        dst_rect.w = texture_width_ - src_x;
        dst_rect.x = 0;
    } else {
        src_rect.w = viewport_width_;
        src_rect.x = world_point_at_viewport_focal_point_->first;

        dst_rect.w = viewport_width_;
        dst_rect.x = 0;
    }

    if (src_y < 0) {
        src_rect.h = viewport_height_ + src_y;
        src_rect.y = 0;

        dst_rect.h = viewport_height_ + src_y;
        dst_rect.y = -src_y;
    } else if (texture_height_ <= src_y + viewport_height_) {
        if (texture_height_ <= src_y) {return;}
        src_rect.y = texture_height_ - src_y;
        src_rect.y = src_y;

        dst_rect.h = texture_height_ - src_y;
        dst_rect.y = 0;
    } else {
        src_rect.h = viewport_height_;
        src_rect.y = world_point_at_viewport_focal_point_->second;

        dst_rect.h = viewport_height_;
        dst_rect.y = 0;
    }
    
    gw_->renderTexture(texture_, &src_rect, &dst_rect);
}

SDL_Texture * WorldRender::createChunkTexture() {
    SDL_Texture * res = SDL_CreateTexture(static_cast<SDL_Renderer*>(gw_->getRenderer()), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, texture_width_, texture_height_);
    return res;
}