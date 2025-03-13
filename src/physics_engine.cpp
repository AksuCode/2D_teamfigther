#include "./physics_engine.hpp"

PhysicsEngine::PhysicsEngine(const double deltaTime) : deltaTime_(deltaTime) {}

void PhysicsEngine::applyPhysics(BlockMatrix & block_matrix, std::vector<Actor *> & actors) {

    for (auto it = actors.begin(); it != actors.end(); it++) {
        const std::pair<double, double> position = (*it)->getPosition();
        const std::pair<double, double> velocity = (*it)->getVelocity();
        const std::pair<double, double> acceleration = (*it)->getAcceleration();

        const std::pair<double, double> new_velocity = {velocity.first + acceleration.first * deltaTime_, velocity.second + acceleration.second * deltaTime_};

        const std::pair<double, double> movement_vector = {new_velocity.first * deltaTime_, new_velocity.second * deltaTime_};

        const std::pair<double, double> candidate_position = {position.first + movement_vector.first, position.second + movement_vector.second};

        if (movement_vector.first == 0.0 && movement_vector.second == 0.0) {
            continue;
        }

        const double length_denominator = 1 / std::sqrt(movement_vector.first * movement_vector.first + movement_vector.second * movement_vector.second);
        const std::pair<double, double> movement_normalized_vector = {movement_vector.first * length_denominator, movement_vector.second * length_denominator};
        const std::pair<double, double> inverse_movement_normalized_vector = {1 / movement_normalized_vector.first, 1 / movement_normalized_vector.second};

        const std::pair<double, double> hitbox = (*it)->getHitbox();

        const double half_width = hitbox.first / 2;
        const double half_heigth = hitbox.second / 2;
        const std::pair<double, double> left_bottom = {position.first - half_width, position.second - half_heigth};
        const std::pair<double, double> right_bottom = {position.first + half_width, position.second - half_heigth};
        const std::pair<double, double> left_top = {position.first - half_width, position.second + half_heigth};
        const std::pair<double, double> right_top = {position.first + half_width, position.second + half_heigth};
        const std::pair<double, double> candidate_left_bottom = {candidate_position.first - half_width, candidate_position.second - half_heigth};
        const std::pair<double, double> candidate_right_bottom = {candidate_position.first + half_width, candidate_position.second - half_heigth};
        const std::pair<double, double> candidate_left_top = {candidate_position.first - half_width, candidate_position.second + half_heigth};
        const std::pair<double, double> candidate_right_top = {candidate_position.first + half_width, candidate_position.second + half_heigth};

        std::pair<int, int> closest_x_dim_collision_point;
        std::pair<int, int> closest_y_dim_collision_point;
        if (movement_vector.first > 0.0 && movement_vector.second > 0.0) {
            closest_x_dim_collision_point = {(int)candidate_right_top.first, (int)candidate_right_top.second};
            closest_y_dim_collision_point = {(int)candidate_right_top.first, (int)candidate_right_top.second};

            if (right_top.second <= candidate_right_bottom.second) {
                const int begin_j = (int)right_bottom.second;
                const int end_j = (int)right_top.second;
                const int begin_i = (int)right_bottom.first;
                int end_i;
                bool collision = false;
                for (int j = begin_j; j <= end_j; j++) {
                    const double scalar = ((double)(j - begin_j)) * inverse_movement_normalized_vector.second;
                    int end_i = (int)((double)begin_i + scalar * movement_normalized_vector.first);
                    for (int i = begin_i; i <= end_i; i++) {
                        unsigned short int block = block_matrix(j, i);
                        if (block > LAST_NON_COLLISION_BLOCK_ID) {
                            closest_x_dim_collision_point.first = i;
                            closest_x_dim_collision_point.second = j;
                            break;
                        }
                    }
                    if (end_i == begin_i) { break; }
                    if (end_i < (int)candidate_right_bottom.first) {
                        closest_x_dim_collision_point_x_cord = end_i;
                    }
                }
            } else {

            }

            int begin_j = (int)right_bottom.second;
            int end_j = (int)right_top.second;
            int begin_i = (int)right_bottom.first;
            for (int j = begin_j; j <= end_j; j++) {
                int scalar = ((double)(j - begin_j)) * inverse_movement_normalized_vector.second;
                int end_i = (int)((double)begin_i + scalar * movement_normalized_vector.first);
                for (int i = begin_i; i <= end_i; i++) {
                    unsigned short int block = block_matrix(i, j);
                    if (block > LAST_NON_COLLISION_BLOCK_ID) {
                        if (closest_x_collision_point.first > i || closest_x_collision_point.second > j) {
                            closest_x_collision_point.first = i;
                            closest_x_collision_point.second = j;
                        }
                    }
                }
            }
        } if else () {

        }





    }
}

void PhysicsEngine::applyPhysics(BlockMatrix & block_matrix, std::vector<Actor *> & actors) {

    for (auto it = actors.begin(); it != actors.end(); it++) {
        const std::pair<double, double> position = (*it)->getPosition();
        const std::pair<double, double> velocity = (*it)->getVelocity();
        const std::pair<double, double> acceleration = (*it)->getAcceleration();

        const std::pair<double, double> new_velocity = {velocity.first + acceleration.first * deltaTime_, velocity.second + acceleration.second * deltaTime_};

        const std::pair<double, double> movement_vector = {new_velocity.first * deltaTime_, new_velocity.second * deltaTime_};

        const std::pair<double, double> candidate_position = {position.first + movement_vector.first, position.second + movement_vector.second};

        if (movement_vector.first == 0.0 && movement_vector.second == 0.0) {
            continue;
        }

        const double length_denominator = 1 / std::sqrt(movement_vector.first * movement_vector.first + movement_vector.second * movement_vector.second);
        const std::pair<double, double> movement_normalized_vector = {movement_vector.first * length_denominator, movement_vector.second * length_denominator};
        const std::pair<double, double> inverse_movement_normalized_vector = {1 / movement_normalized_vector.first, 1 / movement_normalized_vector.second};

        const std::pair<double, double> hitbox = (*it)->getHitbox();

        const double half_width = hitbox.first / 2;
        const double half_heigth = hitbox.second / 2;
        const std::pair<double, double> left_bottom = {position.first - half_width, position.second - half_heigth};
        const std::pair<double, double> right_bottom = {position.first + half_width, position.second - half_heigth};
        const std::pair<double, double> left_top = {position.first - half_width, position.second + half_heigth};
        const std::pair<double, double> right_top = {position.first + half_width, position.second + half_heigth};
        const std::pair<double, double> candidate_left_bottom = {candidate_position.first - half_width, candidate_position.second - half_heigth};
        const std::pair<double, double> candidate_right_bottom = {candidate_position.first + half_width, candidate_position.second - half_heigth};
        const std::pair<double, double> candidate_left_top = {candidate_position.first - half_width, candidate_position.second + half_heigth};
        const std::pair<double, double> candidate_right_top = {candidate_position.first + half_width, candidate_position.second + half_heigth};

        std::pair<int, int> closest_x_dim_collision_point;
        std::pair<int, int> closest_y_dim_collision_point;
        if (movement_vector.first > 0.0 && movement_vector.second > 0.0) {
            closest_x_dim_collision_point = {(int)candidate_right_top.first, (int)candidate_right_top.second};
            closest_y_dim_collision_point = {(int)candidate_right_top.first, (int)candidate_right_top.second};

            if (right_top.second <= candidate_right_bottom.second) {
                const int begin_j = (int)right_bottom.second;
                const int end_j = (int)right_top.second;
                const int begin_i = (int)right_bottom.first;
                int end_i;
                bool collision = false;
                for (int j = begin_j; j <= end_j; j++) {
                    const double scalar = ((double)(j - begin_j)) * inverse_movement_normalized_vector.second;
                    int end_i = (int)((double)begin_i + scalar * movement_normalized_vector.first);
                    for (int i = begin_i; i <= end_i; i++) {
                        unsigned short int block = block_matrix(j, i);
                        if (block > LAST_NON_COLLISION_BLOCK_ID) {
                            closest_x_dim_collision_point.first = i;
                            closest_x_dim_collision_point.second = j;
                            break;
                        }
                    }
                    if (end_i == begin_i) { break; }
                    if (end_i < (int)candidate_right_bottom.first) {
                        closest_x_dim_collision_point_x_cord = end_i;
                    }
                }
            } else {

            }

            int begin_j = (int)right_bottom.second;
            int end_j = (int)right_top.second;
            int begin_i = (int)right_bottom.first;
            for (int j = begin_j; j <= end_j; j++) {
                int scalar = ((double)(j - begin_j)) * inverse_movement_normalized_vector.second;
                int end_i = (int)((double)begin_i + scalar * movement_normalized_vector.first);
                for (int i = begin_i; i <= end_i; i++) {
                    unsigned short int block = block_matrix(i, j);
                    if (block > LAST_NON_COLLISION_BLOCK_ID) {
                        if (closest_x_collision_point.first > i || closest_x_collision_point.second > j) {
                            closest_x_collision_point.first = i;
                            closest_x_collision_point.second = j;
                        }
                    }
                }
            }
        } if else () {

        }





    }
}