#include "../include/sprite_sheet.hpp"

SpriteSheet::SpriteSheet(std::string bmp_path) : bmp_path_(bmp_path), loaded_(false), surface_(nullptr) {}

SpriteSheet::~SpriteSheet() {
    loaded_ = false;
    SDL_FreeSurface(surface_);
}

int SpriteSheet::load() {
    const char * c_bmp_path = bmp_path_.c_str();
    surface_ = SDL_LoadBMP(c_bmp_path);
    if (surface_ == NULL) {return -1;}
    loaded_ = true;
    return 0;
}

void SpriteSheet::unload() {
    loaded_ = false;
    SDL_FreeSurface(surface_);
}

int SpriteSheet::refresh() {
    unload();
    return load();
}

SpriteSheet::Sprite_s SpriteSheet::getSpriteSheet() {
    return (Sprite_s) surface_;
}

int SpriteSheet::layerSpriteSheetWithAnother(Sprite_s src_sprite_sheet,
                                                    int src_rect_copy_w,
                                                    int src_rect_copy_h,
                                                    int src_rect_copy_pos_x,
                                                    int src_rect_copy_pos_y,
                                                    int dst_rect_copy_w,
                                                    int dst_rect_copy_h,
                                                    int dst_rect_copy_pos_x,
                                                    int dst_rect_copy_pos_y) {
    // SDL_SetSurfaceAlphaMod: Use in some way to add transparency of the new added layer.
    const SDL_Rect src = {src_rect_copy_w, src_rect_copy_h, src_rect_copy_pos_x, src_rect_copy_pos_y};
    SDL_Rect dst = {dst_rect_copy_w, dst_rect_copy_h, dst_rect_copy_pos_x, dst_rect_copy_pos_y};
    return SDL_BlitSurface((SDL_Surface *) src_sprite_sheet, &src, surface_, &dst);
}