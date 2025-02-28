#ifndef MGL_SPRITE_RENDER_HPP
#define MGL_SPRITE_RENDER_HPP

#include <SDL2/SDL.h>

#include "sprite_sheet.hpp"
#include "game_window.hpp"

class SpriteRender {
    public:
        // SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND) | SDL_BLENDMODE_NONE SDL_BLENDMODE_BLEND SDL_BLENDMODE_ADD SDL_BLENDMODE_MOD
        // SDL_SetTextureAlphaMod
        // SDL_SetTextureColorMod
        SpriteRender(const GameWindow * gw);
        ~SpriteRender();
        int load(SpriteSheet::Sprite_s sprite_sheet);
        void unload();
        void renderSprite();
    private:
        const GameWindow * gw_;
        SDL_Texture * texture_;
        bool loaded_;
};

#endif