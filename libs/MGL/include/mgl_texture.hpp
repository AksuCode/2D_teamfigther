#ifndef MGL_GENERAL_RENDER_HPP
#define MGL_GENERAL_RENDER_HPP

#include <utility>

#include <SDL2/SDL.h>

#include "./game_window.hpp"

class MGL_Texture {
    public:
        // SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND) | SDL_BLENDMODE_NONE SDL_BLENDMODE_BLEND SDL_BLENDMODE_ADD SDL_BLENDMODE_MOD
        // SDL_SetTextureAlphaMod
        // SDL_SetTextureColorMod

        
        MGL_Texture(GameWindow * gw);
        ~MGL_Texture();

        // https://wiki.libsdl.org/SDL2/SDL_CreateTexture
        int load(Uint32 format, int access, int w, int h);

        int unload();

        /*
        *  Pixel data must be the size of w_ * h_. It consists of h_ * rows of Uint32 values of length w_.
        */
        int drawTextureWithPixelStream(Uint32* pixel_data);

        /*
        * Makes generated sprites transparent in the scale from 0-255.
        * Parameters:
        * transparency - Scale of transparency (0-255). 0 fully transparent. 255 fully opaque.
        */
        int setTextureTransparency(Uint8 transparency);

        /*
        * Sprites are generated normally. No transparency etc.
        */
        int setTextureToDefaultMode();

        int renderTexture(const std::pair<int, int> & dst_pos);

        int renderTextureEx(const double & angle, const int & flip);
        
        int renderTextureScaled(const float & scalar);

        int renderTextureExScaled(const float & scalar, const double & angle, const int & flip);

    private:
        GameWindow * gw_;
        SDL_Texture * texture_;
        int w_;
        int h_;

        SDL_Rect src_rect_;
        SDL_Rect dst_rect_;
        SDL_FRect dst_frect_;
};

#endif