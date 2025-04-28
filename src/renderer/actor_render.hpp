#ifndef ACTOR_RENDER_HPP
#define ACTOR_RENDER_HPP

#include "../config.hpp"

#include <utility>
#include <vector>
#include <cstring>

#include "MGL/include/sprite_render.hpp"

class ActorRender {
    public:
        ActorRender(GameWindow * gw, const char bmp_path[], std::pair<int, int> sprite_dimensions, std::vector<std::vector<std::pair<int, int>>> sprites_per_action);
        ~ActorRender();

        void loadSpriteSheet();
        void unloadSpriteSheet();
        void loadSpriteRender();
        void unloadSpriteRender();

        bool spriteSheetLoaded();
        bool spriteRenderLoaded();
        
        int renderActor(const int action, int & action_sprite_counter, const std::pair<int, int> destination_position, const float scaling);

    protected:
        const char * bmp_path_;
        SpriteSheet * ss_;
        bool ss_loaded_;
        GameWindow * gw_;
        SpriteRender * sr_;
        bool sr_loaded_;
        std::vector<std::vector<std::pair<int, int>>> sprites_per_action_;
        std::pair<int, int> sprite_dimensions_;
};

#endif