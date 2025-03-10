#include "./world.hpp"

World::World() {}

World::~World() {
    for (auto it = actors_.begin(); it != actors_.end(); it++) {
        delete (*it);
    }
}

std::vector<Actor *> & World::getActors() { return actors_; }

std::array<std::array<unsigned short int, 5000>, 2000> & World::getBlocks() { return blocks_; }