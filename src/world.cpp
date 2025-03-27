#include "./world.hpp"

World::World(int width, int heigth) : width_(width), heigth_(heigth) {
    block_world_ = new BlockWorld(width_, heigth_);
}

World::~World() {
    delete block_world_;
    for (auto it = actors_.begin(); it != actors_.end(); it++) {
        delete (*it);
    }
}

int World::getWidth() {
    return width_;
}

int World::getHeigth() {
    return heigth_;
}

BlockWorld * World::getBlockWorld() {
    return *block_world_;
}

std::vector<Actor *> & World::getActors() { return actors_; }