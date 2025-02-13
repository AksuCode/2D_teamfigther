#ifndef MGL_GAME_HPP
#define MGL_GAME_HPP

#include <SDL2/SDL.h>

#include "event_handler.hpp"

#include "graphics.hpp"

class Game {
    public:
        Game(SDL_LogOutputFunction sdl_logOutputFunction);
        ~Game();
        void gameLoop();

    private:
        EventHandler * game_eventhandler_;
        InputHandler * game_inputhandler_;
        Graphics * game_graphics_;
};

#endif