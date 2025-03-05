#ifndef ACTOR_RENDER_HPP
#define ACTOR_RENDER_HPP

#include <utility>

#include "MGL/include/sprite_render.hpp"

class ActorRender {
    public:
        ActorRender();
        ~ActorRender();

        // Loading
        void loadSpriteSheet();
        void unloadSpriteSheet();
        void loadSpriteRender();
        void unloadSpriteRender();

        bool spriteSheetLoaded();
        bool spriteRenderLoaded();
        //

        std::pair<int, int> getSpriteDimensions();
        void renderActor(int action, int & action_sprite_counter, std::pair<int, int> destination_position, float scaling);

    protected:
       SpriteSheet * ss_;
       bool ss_loaded_;
       SpriteRender * sr_;
       bool sr_loaded_;
       int * sprite_amount_per_action_mapping_;
       std::pair<int, int> sprite_dimensions_;
};

#endif