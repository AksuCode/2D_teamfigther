#ifndef WORLD_HPP
#define WORLD_HPP

// Actors
#include "./entities/actor/actor.hpp"
#include "./entities/actor/player/wizard/wizard.hpp"

class World {
    public:
        World();
        ~World();
    private:
        Actor * main_player_;
};

#endif