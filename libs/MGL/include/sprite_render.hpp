#ifndef MGL_SPRITE_RENDER_HPP
#define MGL_SPRITE_RENDER_HPP

#include <utility>

#include <SDL2/SDL.h>

#include "sprite_sheet.hpp"
#include "game_window.hpp"

class SpriteRender {
    public:
        // SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND) | SDL_BLENDMODE_NONE SDL_BLENDMODE_BLEND SDL_BLENDMODE_ADD SDL_BLENDMODE_MOD
        // SDL_SetTextureAlphaMod
        // SDL_SetTextureColorMod
        SpriteRender(const GameWindow * gw, std::pair<int, int> sprite_dimensions);
        ~SpriteRender();
        int load(SpriteSheet::Sprite_s sprite_sheet);
        void unload();

        /*
        * Makes generated sprites transparent in the scale from 0-255.
        * Parameters:
        * transparency - Scale of transparency (0-255). 0 fully transparent. 255 fully opaque.
        */
        int setSpriteTransparency(Uint8 transparency);

        /*
        * Sprites are generated normally. No transparency etc.
        */
        int setSpriteToDefault();

        /*
        * Renders given sprite to the GameWindow pointed by gw_
        * Parameters:
        * sprite_index - First integer is a row in the spritesheet. Second integer is a column.
        * dst_pos - First integer is a x position of the sprite in the destination. Second integer is a corresponding y position.
        *   The poistion given should be the center position of the sprite in destination.
        */
        int renderSprite(const std::pair<int, int> & sprite_index, const std::pair<int, int> & dst_pos);

        /*
        * Renders given sprite to the GameWindow pointed by gw_
        * Parameters:
        * sprite_index - First integer is a row in the spritesheet. Second integer is a column.
        * dst_pos - First integer is a x position of the sprite in the destination. Second integer is a corresponding y position.
        *   The poistion given should be the center position of the sprite in destination.
        * angle - An angle of degrees of rotation applied to sprite around its center in clockwise direction.
        * flip - Defines the flipping action applied to sprite. No flip: 0x00000000, horizontal flip: 0x00000001 and vertical flip: 0x00000002.
        */
        int renderSpriteEx(const std::pair<int, int> & sprite_index,
                const std::pair<int, int> & dst_pos,
                const double & angle,
                const int & flip);
        
        /*
        * Renders given scaled sprite to the GameWindow pointed by gw_
        * Parameters:
        * sprite_index - First integer is a row in the spritesheet. Second integer is a column.
        * dst_pos - First integer is a x position of the sprite in the destination. Second integer is a corresponding y position.
        *   The poistion given should be the center position of the sprite in destination.
        * scalar - Scaling multiplier of the sprite.
        */
        int renderSpriteScaled(const std::pair<int, int> & sprite_index, const std::pair<int, int> & dst_pos, const float & scalar);

        /*
        * Renders given scaled sprite to the GameWindow pointed by gw_
        * Parameters:
        * sprite_index - First integer is a row in the spritesheet. Second integer is a column.
        * dst_pos - First integer is a x position of the sprite in the destination. Second integer is a corresponding y position.
        *   The poistion given should be the center position of the sprite in destination.
        * scalar - Scaling multiplier of the sprite.
        * angle - An angle of degrees of rotation applied to sprite around its center in clockwise direction.
        * flip - Defines the flipping action applied to sprite. No flip: 0x00000000, horizontal flip: 0x00000001 and vertical flip: 0x00000002.
        */
        int renderSpriteExScaled(const std::pair<int, int> & sprite_index,
                const std::pair<int, int> & dst_pos,
                const float & scalar,
                const double & angle,
                const int & flip);

    private:
        const GameWindow * gw_;
        const std::pair<int, int> sprite_dimensions_;
        const SDL_Point sprite_center_point_;
        SDL_Texture * texture_;
        bool loaded_;
        SDL_Rect src_rect_;
        SDL_Rect dst_rect_;
        SDL_FRect dst_frect_;
};

#endif