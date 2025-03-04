#include "./world.hpp"

World::World() {
    main_player_ = new Wizard();
}

World::~World() {
    delete main_player_;
}