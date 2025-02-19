#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>

#include "MGL/include/event_handler.hpp"
#include "MGL/include/action.hpp"
#include "MGL/include/graphics.hpp"

class Game {
    public:
        Game(SDL_LogOutputFunction sdl_logOutputFunction);
        ~Game();
        void gameLoop();

    private:
        EventHandler * game_eventhandler_;
        Action * game_action_;
        Graphics * game_graphics_;
};

#endif