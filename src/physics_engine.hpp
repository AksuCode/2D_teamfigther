#ifndef PHYSICS_ENGINE_HPP
#define PHYSICS_ENGINE_HPP

#include <utility>

#include "./world.hpp"

class PhysicsEngine{
    public:
        PhysicsEngine(const double deltaTime);
    private:
        const double deltaTime_;
};

#endif