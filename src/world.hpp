#ifndef WORLD_HPP
#define WORLD_HPP

#include <utility>
#include <vector>
#include <array>
#include <cstdlib>

// Actors
#include "./block_world.hpp"

class World {
    public:
        World(int width, int heigth);
        ~World();

        int getWidth();

        int getHeigth();

        BlockWorld * getBlockWorld();

    private:
        const int width_;
        const int heigth_;

        BlockWorld * block_world_;
};

#endif