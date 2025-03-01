#ifndef ACTOR_RENDER_HPP
#define ACTOR_RENDER_HPP

#include "MGL/include/sprite_render.hpp"

class ActorRender {
    public:
        ActorRender();

        // Loading
        void loadSpriteSheet();
        void unloadSpriteSheet();
        void loadSpriteRender();
        void unloadSpriteRender();

        bool spriteSheetLoaded();
        bool spriteRenderLoaded();
        //

        void setAction(int action);
        void setDestination(const std::pair<int, int> & destination_position);

    private:
       SpriteSheet * ss_;
       bool ss_loaded_;
       SpriteRender * sr_;
       bool sr_loaded_;
       int action_;
       int action_sprite_counter_;
       float scaling_;
       std::pair<int, int> destination_position_;
};

#endif