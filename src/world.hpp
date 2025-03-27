#ifndef WORLD_HPP
#define WORLD_HPP

#include <utility>
#include <vector>
#include <array>
#include <cstdlib>

// Actors
#include "./block_world.hpp"
#include "./entities/actor/actor.hpp"

class World {
    public:
        World(int width, int heigth);
        ~World();

        int getWidth();

        int getHeigth();

        BlockWorld * getBlockWorld();

        std::vector<Actor *> & getActors();

    private:
        const int width_;
        const int heigth_;

        BlockWorld * block_world_;

        std::vector<Actor *> actors_;
};

#endif