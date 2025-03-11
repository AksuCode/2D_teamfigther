#ifndef PHYSICS_ENGINE_HPP
#define PHYSICS_ENGINE_HPP

#define LAST_NON_COLLISION_BLOCK_ID 10000

#include <utility>
#include <cmath>

#include "./world.hpp"

class PhysicsEngine{
    public:
        PhysicsEngine(const double deltaTime);
    private:
        const double deltaTime_;
};

#endif