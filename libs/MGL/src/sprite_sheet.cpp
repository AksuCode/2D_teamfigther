#include "../include/sprite_sheet.hpp"

SpriteSheet::SpriteSheet(const std::string bmp_path, const int sprite_sheet_dimensions, const std::pair<int, int> sprite_dimensions) : sprite_sheet_dimensions_(sprite_sheet_dimensions), sprite_dimensions_(sprite_dimensions), loaded_(false), surface_(NULL) {
    std::strncpy(c_str_bmp_path_, bmp_path.c_str(), sizeof(c_str_bmp_path_));
}

SpriteSheet::~SpriteSheet() {
    loaded_ = false;
    SDL_FreeSurface(surface_);
}

int SpriteSheet::load() {
    surface_ = SDL_LoadBMP(c_str_bmp_path_);
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

bool SpriteSheet::isLoaded() {
    return loaded_;
}

int SpriteSheet::getSheetDimensions() {
    return sprite_sheet_dimensions_;
}

std::pair<int,int> SpriteSheet::getSpriteDimensions() {
    return sprite_dimensions_;
}

SpriteSheet::Sprite_s SpriteSheet::getSpriteSheet() {
    return static_cast<Sprite_s>(surface_);
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
    return SDL_BlitSurface(static_cast<SDL_Surface *>(src_sprite_sheet), &src, surface_, &dst);
}