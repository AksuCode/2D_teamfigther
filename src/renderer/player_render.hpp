#ifndef PLAYER_RENDER_HPP
#define PLAYER_RENDER_HPP

#include "../config.hpp"

#include "./players.hpp"

#include <utility>
#include <vector>
#include <cstring>
#include <cstdint>

#include "MGL/include/sprite_sheet.hpp"
#include "MGL/include/sprite_render.hpp"

class PlayerRender {
    public:
        PlayerRender(GameWindow * gw, uint32_t player_id, uint32_t skin_id);
        ~PlayerRender();

        int getReferenceCount();
        void incrementRefcount();
        void decrementRefcount();

        void loadSpriteSheet();
        void unloadSpriteSheet();
        
        void loadSpriteRender();
        void unloadSpriteRender();

        bool spriteSheetLoaded();
        bool spriteRenderLoaded();
        
        int renderPlayer(const int action, int & action_sprite_counter, const std::pair<int, int> destination_position, const float scaling);

    private:
        SpriteSheet * ss_;
        SpriteRender * sr_;

        std::vector<std::pair<uint16_t, uint16_t>> action_sprite_indexing_;

        int reference_count_;
};

#endif