#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>

#include <SDL2/SDL.h>

#include "MGL/include/event_handler.hpp"
#include "MGL/include/action.hpp"
#include "MGL/include/game_window.hpp"
#include "MGL/include/mgl_time.hpp"

#include "./world.hpp"

#include "renderer/renderer.hpp"

#include "ecs/core/coordinator.hpp"

#include "ecs/components/physics/gravity.hpp"
#include "ecs/components/physics/motion.hpp"
#include "ecs/components/physics/rotation.hpp"
#include "ecs/components/physics/scale.hpp"
#include "ecs/components/physics/thrust.hpp"
#include "ecs/components/physics/weight.hpp"
#include "ecs/components/physics/gravity.hpp"

#include "ecs/components/actor/creature.hpp"
#include "ecs/components/actor/player.hpp"
#include "ecs/components/actor/main_player.hpp"
#include "ecs/components/actor/player/wizard.hpp"

#include "ecs/components/render/r_player.hpp"

#include "ecs/systems/control/main_player_control_system.hpp"
#include "ecs/systems/control/main_player_position_getter_system.hpp"

#include "ecs/systems/render/player_render_system.hpp"

class Game {
    public:
        Game(SDL_LogOutputFunction sdl_logOutputFunction);
        ~Game();
        void gameLoop();

    private:
        EventHandler * game_eventhandler_;
        Action * game_action_;
        GameWindow * game_window_;

        World * world_;
        Renderer * renderer_;
};

#endif