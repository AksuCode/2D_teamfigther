#include "./game.hpp"

// ECS
Coordinator gCoordinator;
//

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

    renderer_ = new Renderer(game_window_);

    // ECS
    gCoordinator.Init();
    gCoordinator.RegisterComponent<Gravity>();
    gCoordinator.RegisterComponent<Motion>();
    gCoordinator.RegisterComponent<Rotation>();
    gCoordinator.RegisterComponent<Scale>();
    gCoordinator.RegisterComponent<Thrust>();
    gCoordinator.RegisterComponent<Weight>();
    gCoordinator.RegisterComponent<Player>();
    gCoordinator.RegisterComponent<MainPlayer>();
    gCoordinator.RegisterComponent<Creature>();
    gCoordinator.RegisterComponent<Wizard>();
    gCoordinator.RegisterComponent<R_Player>();
    //
}

Game::~Game() {
    delete game_eventhandler_;
    delete game_action_;
    delete game_window_;
    delete renderer_;
    SDL_Quit();
}

void Game::gameLoop() {

    // Jotain kivaa.
    MGL_Timing * gamelogic_timer = new MGL_Timing();
    MGL_SchedulerMs * animation_scheduler = new MGL_SchedulerMs(15);
    //

    game_window_->createOrUpdateWindow(false, 1000, 1000);

    // ECS
    auto main_player_control_system = gCoordinator.RegisterSystem<MainPlayerControlSystem>();
    {
        Signature signature;
		signature.set(gCoordinator.GetComponentType<MainPlayer>());
        signature.set(gCoordinator.GetComponentType<Motion>());
        gCoordinator.SetSystemSignature<MainPlayerControlSystem>(signature);
    }
    main_player_control_system->Init();

    auto main_player_position_getter_system = gCoordinator.RegisterSystem<MainPlayerPositionGetterSystem>();
    {
        Signature signature;
		signature.set(gCoordinator.GetComponentType<MainPlayer>());
        signature.set(gCoordinator.GetComponentType<Motion>());
        gCoordinator.SetSystemSignature<MainPlayerPositionGetterSystem>(signature);
    }
    main_player_position_getter_system->Init();

    auto player_render_system = gCoordinator.RegisterSystem<PlayerRenderSystem>();
    {
        Signature signature;
		signature.set(gCoordinator.GetComponentType<R_Player>());
        signature.set(gCoordinator.GetComponentType<Motion>());
        gCoordinator.SetSystemSignature<MainPlayerPositionGetterSystem>(signature);
    }
    player_render_system->Init(renderer_);

    Entity main_player = gCoordinator.CreateEntity();
    gCoordinator.AddComponent(main_player, MainPlayer{});
    gCoordinator.AddComponent(
        main_player,
        Motion{
            .position = {500.0, 500.0},
            .velocity = {0.0,0.0},
            .acceleration = {0.0, 0.0}}
    );
    gCoordinator.AddComponent(main_player, R_Player{});



    player_render_system->CreatePlayerRenders();
    player_render_system->LoadPlayerRenders();
    //


    while (true) {

        if (gamelogic_timer->computeNextLogic()) {
            // Steps 1 - 4 get evaluated at the beginnig of a chosen tick timer. But ignored until next game tick.

            // 1. system takes external input
            game_eventhandler_->pollEvent();
            //

            // 2. External input converted to player actions that create a cause to the world
            // Turn inputs to player actions with player actions class which in turn somewhow changes player state
            // Maybe pass reference to player actions object to gamestate class ro something
            auto current_action = game_action_->getActions(game_eventhandler_->getKeyboardState(), game_eventhandler_->getMouseKeyState());
            std::pair<int, int> current_mouse_position = game_eventhandler_->getMousePosition();

            //


            // ECS
            main_player_control_system->Update(current_action);
            //

            // 3. Other actors do their actions that also create a cause

            //

            // 4. world state and cause are evaluated against game logic and new world state generated as effect

            //

            std::cout << "Game logic" << std::endl;
        }

        gamelogic_timer->startFrameRenderTimer();
        if (animation_scheduler->executeOnSchedule()) {
            // 5. World state is rendered as image + animations (actions in effect)
            //world_render_->renderWorld();
            player_render_system->Render();
            game_window_->updateWindow();
            auto res = main_player_position_getter_system->get();
            std::cout << "Movement tester: (x: " << res.first << ", y: " << res.second << ")" << std::endl; 
            //
        }
        gamelogic_timer->endFrameRenderTimer();
    }

}