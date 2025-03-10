#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>
#include <array>

// Actors
#include "./entities/actor/actor.hpp"

class World {
    public:
        World();
        ~World();
        std::vector<Actor *> & getActors();
        std::array<std::array<unsigned short int, 5000>, 2000> & getBlocks();
    private:
        std::vector<Actor *> actors_;
        std::array<std::array<unsigned short int, 5000>, 2000> blocks_;       // unsigned short int corresponds to the block id.
};

#endif