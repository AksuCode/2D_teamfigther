#ifndef ACTOR_RENDER_HPP
#define ACTOR_RENDER_HPP

#include "../config.hpp"

#include "./players.hpp"

#include <utility>
#include <vector>
#include <cstring>
#include <cstdint>

#include "MGL/include/sprite_render.hpp"

class ActorRender {
    public:
        ActorRender(GameWindow * gw, uint32_t player_id, uint32_t skin_id = 0);
        ~ActorRender();

        void loadSpriteSheet();
        void unloadSpriteSheet();
        
        void loadSpriteRender();
        void unloadSpriteRender();

        bool spriteSheetLoaded();
        bool spriteRenderLoaded();
        
        int renderActor(const int action, int & action_sprite_counter, const std::pair<int, int> destination_position, const float scaling);

    private:
        SpriteSheet * ss_;
        bool ss_loaded_;
        SpriteRender * sr_;
        bool sr_loaded_;
        uint16_t sprite_sheet_dimensions_;
        std::pair<uint16_t, uint16_t> sprite_dimensions_;
        std::vector<std::pair<uint16_t, uint16_t>> & action_sprite_indexing_;
};

#endif