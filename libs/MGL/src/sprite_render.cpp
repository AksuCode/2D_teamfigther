#include "../include/sprite_render.hpp"

SpriteRender::SpriteRender(GameWindow * gw, const std::pair<int, int> sprite_dimensions) : gw_(gw), sprite_dimensions_(sprite_dimensions), texture_(nullptr), loaded_(false) {
    sprite_center_point_ = SDL_Point{sprite_dimensions_.first / 2, sprite_dimensions_.second / 2};
    sprite_center_fpoint_ = SDL_FPoint{(float)sprite_dimensions_.first / 2, (float)sprite_dimensions_.second / 2};
}

SpriteRender::~SpriteRender() {
    loaded_ = false;
    if (texture_ != nullptr) {SDL_DestroyTexture(texture_);}
}

int SpriteRender::load(SpriteSheet::Sprite_s sprite_sheet) {
    texture_ = SDL_CreateTextureFromSurface((SDL_Renderer *)gw_->getRenderer(), (SDL_Surface *) sprite_sheet);
    if (texture_ == NULL) {return -1;}
    loaded_ = true;
    return 0;
}

void SpriteRender::unload() {
    loaded_ = false;
    if (texture_ == nullptr) {return;}
    SDL_DestroyTexture(texture_);
}

int SpriteRender::setSpriteTransparency(Uint8 transparency) {
    if (SDL_SetTextureBlendMode(texture_, SDL_BLENDMODE_BLEND) < 0) {return -1;}
    return SDL_SetTextureAlphaMod(texture_, transparency);
}

int SpriteRender::setSpriteToDefault() {
    return SDL_SetTextureBlendMode(texture_, SDL_BLENDMODE_NONE);
}

int SpriteRender::renderSprite(const std::pair<int, int> & sprite_index,
            const std::pair<int, int> & dst_pos) {
    int src_x = sprite_dimensions_.first * sprite_index.first;
    int src_y = sprite_dimensions_.second * sprite_index.second;
    src_rect_.w = sprite_dimensions_.first;
    src_rect_.h = sprite_dimensions_.second;
    src_rect_.x = src_x;
    src_rect_.y = src_y;

    int dst_x = dst_pos.first - sprite_center_point_.x;
    int dst_y = dst_pos.second - sprite_center_point_.y;
    dst_rect_.w = sprite_dimensions_.first;
    dst_rect_.h = sprite_dimensions_.second;
    dst_rect_.x = dst_x;
    dst_rect_.y = dst_y;

    return gw_->renderTexture(texture_, &src_rect_, &dst_rect_);
}

int SpriteRender::renderSpriteEx(const std::pair<int, int> & sprite_index,
                const std::pair<int, int> & dst_pos,
                const double & angle,
                const int & flip) {
    int src_x = sprite_dimensions_.first * sprite_index.first;
    int src_y = sprite_dimensions_.second * sprite_index.second;
    src_rect_.w = sprite_dimensions_.first;
    src_rect_.h = sprite_dimensions_.second;
    src_rect_.x = src_x;
    src_rect_.y = src_y;

    int dst_x = dst_pos.first - sprite_center_point_.x;
    int dst_y = dst_pos.second - sprite_center_point_.y;
    dst_rect_.w = sprite_dimensions_.first;
    dst_rect_.h = sprite_dimensions_.second;
    dst_rect_.x = dst_x;
    dst_rect_.y = dst_y;

    return gw_->renderTextureEx(texture_, &src_rect_, &dst_rect_, angle, &sprite_center_point_, (SDL_RendererFlip)flip);
}

int SpriteRender::renderSpriteScaled(const std::pair<int, int> & sprite_index,
            const std::pair<int, int> & dst_pos,
            const float & scalar) {
    int src_x = sprite_dimensions_.first * sprite_index.first;
    int src_y = sprite_dimensions_.second * sprite_index.second;
    src_rect_.w = sprite_dimensions_.first;
    src_rect_.h = sprite_dimensions_.second;
    src_rect_.x = src_x;
    src_rect_.y = src_y;

    float dst_x = (float)dst_pos.first - scalar * (float)sprite_center_point_.x;
    float dst_y = (float)dst_pos.second - scalar * (float)sprite_center_point_.y;
    dst_frect_.w = scalar * (float)sprite_dimensions_.first;
    dst_frect_.h = scalar * (float)sprite_dimensions_.second;
    dst_frect_.x = dst_x;
    dst_frect_.y = dst_y;

    return gw_->renderTextureF(texture_, &src_rect_, &dst_frect_);
}

int SpriteRender::renderSpriteExScaled(const std::pair<int, int> & sprite_index,
                const std::pair<int, int> & dst_pos,
                const float & scalar,
                const double & angle,
                const int & flip) {
    int src_x = sprite_dimensions_.first * sprite_index.first;
    int src_y = sprite_dimensions_.second * sprite_index.second;
    src_rect_.w = sprite_dimensions_.first;
    src_rect_.h = sprite_dimensions_.second;
    src_rect_.x = src_x;
    src_rect_.y = src_y;

    float dst_x = (float)dst_pos.first - scalar * (float)sprite_center_point_.x;
    float dst_y = (float)dst_pos.second - scalar * (float)sprite_center_point_.y;
    dst_frect_.w = scalar * (float)sprite_dimensions_.first;
    dst_frect_.h = scalar * (float)sprite_dimensions_.second;
    dst_frect_.x = dst_x;
    dst_frect_.y = dst_y;

    return gw_->renderTextureExF(texture_, &src_rect_, &dst_frect_, angle, &sprite_center_fpoint_, (SDL_RendererFlip)flip);
}