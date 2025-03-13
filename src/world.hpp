#ifndef WORLD_HPP
#define WORLD_HPP

#include <utility>
#include <vector>
#include <array>
#include <cstdlib>

// Actors
#include "./block_matrix.hpp"
#include "./entities/actor/actor.hpp"

class World {
    public:
        World(int width, int heigth);
        ~World();

        int getWidth();

        int getHeigth();

        /*  
        *   Column-major
        *   World coordinates are (i, j). First tells the x and second tells the y.
        */
        BlockMatrix & getBlockMatrix();

        std::vector<Actor *> & getActors();

    private:
        const int width_;
        const int heigth_;
        int stride_;
        BlockMatrix * block_matrix_;       // unsigned short int corresponds to the block id.

        std::vector<Actor *> actors_;
};

#endif