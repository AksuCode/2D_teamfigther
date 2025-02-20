#ifndef MGL_SPRITE_RENDERER_HPP
#define MGL_SPRITE_RENDERER_HPP

#include <SDL2/SDL.h>

class SpriteRenderer {
    public:
        // SDL_CreateTextureFromSurface
        // SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND) | SDL_BLENDMODE_NONE SDL_BLENDMODE_BLEND SDL_BLENDMODE_ADD SDL_BLENDMODE_MOD
        // SDL_SetTextureAlphaMod
        // SDL_SetTextureColorMod
        // SDL_RenderCopyEx
        /* Resize:
            SDL_Rect dstRect = {100, 100, 200, 200}; // New size
            SDL_RenderCopy(renderer, texture, NULL, &dstRect);
        */
    private:
        //SDL_Renderer renderer_;
};

#endif