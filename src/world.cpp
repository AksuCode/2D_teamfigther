#include "./world.hpp"

World::World(int width, int heigth) : width_(width), heigth_(heigth) {
    block_matrix_ = new BlockMatrix(heigth_, width_);
}

World::~World() {
    delete block_matrix_;
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

BlockMatrix & World::getBlockMatrix() {
    return *block_matrix_;
}

std::vector<Actor *> & World::getActors() { return actors_; }