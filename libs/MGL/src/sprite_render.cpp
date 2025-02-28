#include "../include/sprite_render.hpp"

SpriteRender::SpriteRender(const GameWindow * gw) : gw_(gw), texture_(nullptr), loaded_(false) {}

SpriteRender::~SpriteRender() {
    loaded_ = false;
    SDL_DestroyTexture(texture_);
}

int SpriteRender::load(SpriteSheet::Sprite_s sprite_sheet) {
    SDL_CreateTextureFromSurface(texture_, (SDL_Surface *) sprite_sheet);
    if (texture_ == NULL) {return -1;}
    loaded_ = true;
    return 0;
}

void SpriteRender::unload() {
    loaded_ = false;
    SDL_DestroyTexture(texture_);
}