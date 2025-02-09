#ifndef MGL_GAME_HPP
#define MGL_GAME_HPP

#include <SDL2/SDL.h>

#include "window.hpp"
#include "inputhandler.hpp"

class Game {
    public:
        Game(SDL_LogOutputFunction sdl_logOFunction);
        ~Game();

    private:
        Window * game_window_;
        InputHandler * game_inputhandler_;
};

#endif