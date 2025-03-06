#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>

#include <SDL2/SDL.h>

#include "MGL/include/event_handler.hpp"
#include "MGL/include/action.hpp"
#include "MGL/include/game_window.hpp"

#include "./world.hpp"
#include "./world_render.hpp"

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
        WorldRender * world_render_;
};

#endif