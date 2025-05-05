#ifndef MGL_SPRITE_SHEET_HPP
#define MGL_SPRITE_SHEET_HPP

#include <string>

#include <SDL2/SDL.h>

class SpriteSheet {
    public:
        SpriteSheet(std::string bmp_path);
        ~SpriteSheet();
        int load();
        void unload();
        int refresh();
        typedef SDL_Surface* Sprite_s;
        Sprite_s getSpriteSheet();
        int layerSpriteSheetWithAnother(Sprite_s src_sprite_sheet,
                                int src_rect_copy_w,
                                int src_rect_copy_h,
                                int src_rect_copy_pos_x,
                                int src_rect_copy_pos_y,
                                int dst_rect_copy_w,
                                int dst_rect_copy_h,
                                int dst_rect_copy_pos_x,
                                int dst_rect_copy_pos_y);
    private:
        std::string bmp_path_;
        bool loaded_;
        SDL_Surface * surface_;
};

#endif