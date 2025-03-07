#ifndef WORLD_RENDER_HPP
#define WORLD_RENDER_HPP

#include <utility>

#include "MGL/include/game_window.hpp"

// Actors
#include "./entities/actor/actor_render.hpp"
#include "./entities/actor/player/wizard/wizard_render.hpp"

class WorldRender {
    public:
        WorldRender(GameWindow * game_window);
        ~WorldRender();
        void renderWorld();
        void loadWorld();

    private:
        GameWindow * game_window_;

        WizardRender * wr_;
        int wr_action_counter = 0;

        void renderW(WizardRender * w_render, std::pair<int, int> destination_position, float scaling);
};

#endif