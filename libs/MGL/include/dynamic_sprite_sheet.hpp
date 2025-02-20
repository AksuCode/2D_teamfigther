#ifndef MGL_DYNAMIC_SPRITE_SHEET_HPP
#define MGL_DYNAMIC_SPRITE_SHEET_HPP

#include <SDL2/SDL.h>

#include <stdexcept>

class DynamicSpriteSheet {
    public:
        DynamicSpriteSheet(const char * bmp_file_path);
        ~DynamicSpriteSheet();
        int refresh();
        typedef SDL_Surface* sprite_sheet;
        sprite_sheet getSpriteSheet();
        int layerSpriteSheetWithAnother(sprite_sheet src_sprite_sheet,
                                        int src_rect_copy_w,
                                        int src_rect_copy_h,
                                        int src_rect_copy_pos_x,
                                        int src_rect_copy_pos_y,
                                        int dst_rect_copy_w,
                                        int dst_rect_copy_h,
                                        int dst_rect_copy_pos_x,
                                        int dst_rect_copy_pos_y);
    private:
        const char * bmp_file_path_;
        SDL_Surface * sprite_sheet_;

        SDL_Surface * loadBMP(const char * bmp_file_path);
        void loadSurfaceThread(const char * bmp_file_path, SDL_Surface * destination);
        void asyncLoadSurface(const char * bmp_file_path, SDL_Surface * destination);
};

#endif