#include "../include/mgl_texture.hpp"

MGL_Texture::MGL_Texture(GameWindow * gw) : gw_(gw), texture_(nullptr) {}

MGL_Texture::~MGL_Texture() {
    if (texture_ != nullptr) {SDL_DestroyTexture(texture_);}
}

int MGL_Texture::load(Uint32 format, int access, int w, int h) {
    if (texture_ != nullptr) {return -1;}
    SDL_Texture * res = SDL_CreateTexture(static_cast<SDL_Renderer*>(gw_->getRenderer()), format, access, w, h);
    if (res == NULL) {return -2;} 
    texture_ = res;
    w_ = w;
    h_ = h;
    return 0;
}

int MGL_Texture::unload() {
    if (texture_ == nullptr) {return -1;}
    SDL_DestroyTexture(texture_);
    return 0;
}

int MGL_Texture::drawTextureWithPixelStream(Uint32* pixel_data) {
    Uint32* pixels;
    int pitch;

    // Assume texture is created with SDL_TEXTUREACCESS_STREAMING
    if (SDL_LockTexture(texture_, NULL, (void**)&pixels, &pitch) != 0) {
        return -1;
    }

    // pitch is in bytes, so divide by 4 for 32-bit pixels (Uint32)
    int width = pitch / 4;
    int i = 0;
    for (int y = 0; y < h_; ++y) {
        for (int x = 0; x < w_; ++x) {
            pixels[y * width + x] = pixel_data[i];
            i++;
        }
    }
    SDL_UnlockTexture(texture_);
    return 0;
}

int MGL_Texture::setTextureTransparency(Uint8 transparency) {
    if (SDL_SetTextureBlendMode(texture_, SDL_BLENDMODE_BLEND) < 0) {return -1;}
    return SDL_SetTextureAlphaMod(texture_, transparency);
}

int MGL_Texture::setTextureToDefaultMode() {
    return SDL_SetTextureBlendMode(texture_, SDL_BLENDMODE_NONE);
}

int MGL_Texture::renderTexture(const std::pair<int, int> & dst_pos) {
    dst_rect_.w = w_;
    dst_rect_.h = h_;
    dst_rect_.x = dst_pos.first;
    dst_rect_.y = dst_pos.second;
    return gw_->renderTexture(texture_, NULL, &dst_rect_);
}

int MGL_Texture::renderTextureEx(const double & angle, const int & flip) {
    return gw_->renderTextureEx(texture_, &src_rect_, &dst_rect_, angle, NULL, (SDL_RendererFlip)flip);
}

int MGL_Texture::renderTextureScaled(const float & scalar) {
    return gw_->renderTextureF(texture_, &src_rect_, &dst_frect_);
}

int MGL_Texture::renderTextureExScaled(const float & scalar, const double & angle, const int & flip) {
    return gw_->renderTextureExF(texture_, &src_rect_, &dst_frect_, angle, NULL, (SDL_RendererFlip)flip);
}