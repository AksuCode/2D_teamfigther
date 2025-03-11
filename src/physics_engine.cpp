#include "./physics_engine.hpp"

PhysicsEngine::PhysicsEngine(const double deltaTime) : deltaTime_(deltaTime) {}

void PhysicsEngine::applyPhysics(std::array<std::array<unsigned short int, 5000>, 2000> blocks, std::vector<Actor *> & actors) {

    // Movement
    for (auto it = actors.begin(); it != actors.end(); it++) {
        const std::pair<double, double> position = (*it)->getPosition();
        const std::pair<double, double> velocity = (*it)->getVelocity();
        const std::pair<double, double> acceleration = (*it)->getAcceleration();

        const std::pair<double, double> new_velocity = {velocity.first + acceleration.first * deltaTime_, velocity.second + acceleration.second * deltaTime_};

        std::pair<double, double> movement_vector = {new_velocity.first * deltaTime_, new_velocity.second * deltaTime_};

        if (movement_vector.first == 0.0 && movement_vector.second == 0.0) {
            continue;
        }

        double length_denominator = 1 / std::sqrt(movement_vector.first * movement_vector.first + movement_vector.second * movement_vector.second);
        std::pair<int, int> movement_unit_vector = {(int)(movement_vector.first * length_denominator), (int)(movement_vector.second * length_denominator)};

        const std::pair<double, double> hitbox = (*it)->getHitbox();

        std::pair<int, int> closest_x_collision_point = {position.first + movement_vector.first, position.second + movement_vector.second};
        std::pair<int, int> closest_y_collision_point = {position.first + movement_vector.first, position.second + movement_vector.second};
        // Collision:
        if (movement_vector.first > 0.0 && movement_vector.second > 0.0) {
            continue;
        }
    }
}