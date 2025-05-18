#ifndef MGL_SPRITE_SHEET_HPP
#define MGL_SPRITE_SHEET_HPP

#include <string>
#include <cstring>
#include <utility>

#include <SDL2/SDL.h>

class SpriteSheet {
    public:
        SpriteSheet(const std::string bmp_path, const int sprite_sheet_dimensions, const std::pair<int, int> sprite_dimensions);
        ~SpriteSheet();
        int load();
        void unload();
        int refresh();
        bool isLoaded();
        int getSheetDimensions();
        std::pair<int,int> getSpriteDimensions();
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
        char c_str_bmp_path_[50];
        bool loaded_;
        SDL_Surface * surface_;

        int sprite_sheet_dimensions_;
        const std::pair<int, int> sprite_dimensions_;
};

#endif