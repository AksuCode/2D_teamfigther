#include "./physics_engine.hpp"

PhysicsEngine::PhysicsEngine(const double deltaTime) : deltaTime_(deltaTime) {}

void PhysicsEngine::applyPhysics(std::array<std::array<unsigned short int, 5000>, 2000> blocks, std::vector<Actor *> & actors) {
    for (auto it = actors.begin(); it != actors.end(); it++) {
        std::pair<double, double> position = (*it)->getPosition();
        std::pair<double, double> velocity = (*it)->getVelocity();
        std::pair<double, double> acceleration = (*it)->getAcceleration();

        velocity.first += acceleration.first * deltaTime_;
        velocity.second += acceleration.second * deltaTime_;

        position.first += velocity.first * deltaTime_;
        position.second += velocity.second * deltaTime_;

        // Collision detection
        
    }
}