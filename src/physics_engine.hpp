#ifndef PHYSICS_ENGINE_HPP
#define PHYSICS_ENGINE_HPP

#define LAST_NON_COLLISION_BLOCK_ID 10000

#include <utility>
#include <cmath>
#include <limits.h>
#include <algorithm>

#include "./world.hpp"

class PhysicsEngine{
    public:
        PhysicsEngine(const double deltaTime);

        bool rigidCollisionDetectionAndResolution( std::pair<double, double> & position,
                                        const std::pair<double, double> velocity,
                                        const std::pair<double, double> acceleration,
                                        const std::pair<double, double> hitbox,
                                        const SolidsColumnMajorBitmap * scmb,
                                        const SolidsRowMajorBitmap * srmb);
    private:
        const double deltaTime_;
};

#endif