#include "../include/game.hpp"

Game::Game(SDL_LogOutputFunction sdl_logOFunction) {
    // Initialize SDL library
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Video initialization error: %s\n", SDL_GetError());
        exit(-1);
    }
    // Configure logging
    if (sdl_logOFunction != NULL) {
        SDL_LogSetOutputFunction(sdl_logOFunction, NULL);
        SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);
    }

    game_window_ = new Window(NULL);
    game_inputhandler_ = new InputHandler();
}

Game::~Game() {
    delete game_window_;
    SDL_Quit();
}