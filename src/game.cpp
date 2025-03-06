#include "./game.hpp"

Game::Game(SDL_LogOutputFunction sdl_logOutputFunction) {
    // Initialize SDL library
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Video initialization error: %s\n", SDL_GetError());
        exit(-1);
    }
    // Configure logging
    if (sdl_logOutputFunction != NULL) {
        SDL_LogSetOutputFunction(sdl_logOutputFunction, NULL);
        SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);
    }

    game_eventhandler_ = new EventHandler();
    game_action_ = new Action();
    game_window_ = new GameWindow();

    world_ = new World();
    world_render_ = new WorldRender(game_window_);
}

Game::~Game() {
    delete game_eventhandler_;
    delete game_action_;
    delete game_window_ ;
    delete world_;
    delete world_render_;
    SDL_Quit();
}

void Game::gameLoop() {

    while (true) {
        // 1. system takes external input
        game_eventhandler_->pollEvent();
        //

        // Steps 2 - 4 get evaluated at the beginnig of a chosen tick timer. But ignored until next game tick.

        // 2. External input converted to player actions that create a cause to the world
        // Turn inputs to player actions with player actions class which in turn somewhow changes player state
        // Maybe pass reference to player actions object to gamestate class ro something
        auto current_action = game_action_->getActions(game_eventhandler_->getKeyboardState(), game_eventhandler_->getMouseKeyState());
        std::pair<int, int> current_mouse_position = game_eventhandler_->getMousePosition();

        world_render_->renderWorld();
        //

        // 3. Other actors do their actions that also create a cause

        //

        // 4. world state and cause are evaluated against game logic and new world state generated as effect

        //

        // 5. World state is rendered as image + animations (actions in effect)

        // 
    }

}