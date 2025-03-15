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

std::pair<int, int> newPosition() {
    const std::pair<double, double> position = (*it)->getPosition();
    const std::pair<double, double> velocity = (*it)->getVelocity();
    const std::pair<double, double> acceleration = (*it)->getAcceleration();

    const std::pair<double, double> new_velocity = {velocity.first + acceleration.first * deltaTime_, velocity.second + acceleration.second * deltaTime_};

    const std::pair<double, double> movement_vector = {new_velocity.first * deltaTime_, new_velocity.second * deltaTime_};

    if (movement_vector.first == 0.0 && movement_vector.second == 0.0) {
        return position;
    }

    const std::pair<double, double> candidate_position = {position.first + movement_vector.first, position.second + movement_vector.second};

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

    if (movement_vector.first > 0.0 && movement_vector.second > 0.0) {
        int closest_horizontal_dim_y = (int)candidate_right_top.second + 1;
        int closest_vertical_dim_x = (int)candidate_right_top.first + 1;

        int begin_i = (int)right_bottom.first + 1;
        int end_i = (int)candidate_right_top.first;
        for (int i = begin_i; i <= end_i; i++) {
            const double scalar = ((double)(i - begin_i)) * inverse_movement_normalized_vector.first;
            int begin_j = (int)(right_bottom.second + scalar * movement_normalized_vector.second);
            int end_j = (int)(right_top.second + scalar * movement_normalized_vector.second);
            for (int j = begin_j; j <= end_j; j++) {
                unsigned short int block_id = block_matrix(i, j).id;
                if (block_id > LAST_NON_COLLISION_BLOCK_ID) {
                    closest_vertical_dim_x = i;
                    goto horizontal;
                }
            }
        }

        horizontal:
            begin_i = (int)left_top.first;
            for (int i = begin_i; i <= end_i; i++) {
                const double scalar = ((double)(i - begin_i)) * inverse_movement_normalized_vector.first;
                int begin_j;
                if (i <= (int)right_top.first) {
                    begin_j = (int)right_top.second + 1;
                } else {
                    begin_j = (int)(right_top.second + scalar * movement_normalized_vector.second);
                }
                int end_j;
                if (i > (int)candidate_left_top.first) {
                    end_j = (int)candidate_left_top.second;
                } else {
                    end_j = (int)(top_left.second + scalar * movement_normalized_vector.second);
                }
                if (end_j > closest_horizontal_dim_y) {end_j = closest_horizontal_dim_y;}
                for (int j = begin_j; j <= end_j; j++) {
                    unsigned short int block_id = block_matrix(i, j).id;
                    if (block_id > LAST_NON_COLLISION_BLOCK_ID) {
                        closest_horizontal_dim_y = j;
                        break;
                    }
                }
            }
        
        if (closest_horizontal_dim_y != (int)candidate_right_top.second + 1 && closest_vertical_dim_x != (int)candidate_right_top.first + 1) {
            const double vertical_scalar = ((double)closest_vertical_dim_x - right_top.first) * inverse_movement_normalized_vector.first;
            const double horizontal_scalar = ((double)closest_horizontal_dim_y - right_top.second) * inverse_movement_normalized_vector.second;
            const double smallest_scalar = (vertical_scalar > horizontal_scalar) ? vertical_scalar : horizontal_scalar;
            std::pair<double, double> new_position;
            new_position.first = position.first + smallest_scalar * movement_normalized_vector.first;
            new_position.second = position.second + smallest_scalar * movement_normalized_vector.second;
            return new_position;
        } else {
            return candidate_position;
        }

    } if else () {

    } if else () {

    } if else () {

    } if else () {

    } if else () {

    } if else () {

    } if else () {

    }



}

/*
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
*/