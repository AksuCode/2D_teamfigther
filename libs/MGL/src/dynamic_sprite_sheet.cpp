#include "../include/dynamic_sprite_sheet.hpp"

DynamicSpriteSheet::DynamicSpriteSheet(const char * bmp_file_path) : bmp_file_path_(bmp_file_path), sprite_sheet_(nullptr) {
    asyncLoadSurface(bmp_file_path_, sprite_sheet_);
}

DynamicSpriteSheet::~DynamicSpriteSheet() {SDL_FreeSurface(sprite_sheet_);}

void DynamicSpriteSheet::refresh() {
    SDL_FreeSurface(sprite_sheet_);
    asyncLoadSurface(bmp_file_path_, sprite_sheet_);
}

sprite_sheet DynamicSpriteSheet::getSpriteSheet() {
    if (!sprite_sheet_) {
        throw std::ios_base::failure("Failed to load BMP file: " + bmp_file_path_);
    }
    return (sprite_sheet) sprite_sheet_;
}

int DynamicSpriteSheet::layerSpriteSheetWithAnother(sprite_sheet src_sprite_sheet,
                                                    int src_rect_copy_w,
                                                    int src_rect_copy_h,
                                                    int src_rect_copy_pos_x,
                                                    int src_rect_copy_pos_y,
                                                    int dst_rect_copy_w,
                                                    int dst_rect_copy_h,
                                                    int dst_rect_copy_pos_x,
                                                    int dst_rect_copy_pos_y) {
    // Use in some way to add transparency of the new added layer SDL_SetSurfaceAlphaMod.
    const SDL_Rect src = {src_rect_copy_w, src_rect_copy_h, src_rect_copy_pos_x, src_rect_copy_pos_y};
    const SDL_Rect dst = {dst_rect_copy_w, dst_rect_copy_h, dst_rect_copy_pos_x, dst_rect_copy_pos_y};
    return SDL_BlitSurface((SDL_Surface) src_sprite_sheet, &src, sprite_sheet_, &dst);
}

SDL_Surface * DynamicSpriteSheet::loadBMP(const char * bmp_file_path) {
    SDL_Surface * surface = SDL_LoadBMP(bmp_file_path);
    if (!surface) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Loading sprite sheet (path: %s) failed: %s\n", bmp_file_path, SDL_GetError());
        return nullptr;
    }
    return surface;
}

void DynamicSpriteSheet::loadSurfaceThread(const char * bmp_file_path, SDL_Surface * destination) {
    destination = loadBMPAsync(bmp_file_path);
}

void DynamicSpriteSheet::asyncLoadSurface(const char * bmp_file_path, SDL_Surface * destination) {
    loadSurfaceThread(bmp_file_path, destination); // !!!!!!!!!!!!!!! EXECUTE THIS FUNCTION WITH MY THREAD POOL THREAD. NEED TO IMPLEMENT THREAD POOL FIRST.
}