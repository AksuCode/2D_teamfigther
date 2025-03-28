#include "./physics_engine.hpp"

PhysicsEngine::PhysicsEngine(const double deltaTime) : deltaTime_(deltaTime) {}

void PhysicsEngine::applyPhysics(BlockMatrix & block_matrix, std::vector<Actor *> & actors) {

    for (auto it = actors.begin(); it != actors.end(); it++) {
        const std::pair<double, double> position = (*it)->getPosition();
        const std::pair<double, double> velocity = (*it)->getVelocity();
        const std::pair<double, double> acceleration = (*it)->getAcceleration();
        const std::pair<double, double> hitbox = (*it)->getHitbox();
        bool collision;
        newPosition(position, velocity, acceleration, hitbox, block_matrix, collision);
    }
}

bool PhysicsEngine::rigidCollisionDetectionAndResolution(   std::pair<double, double> & position,
                                        const std::pair<double, double> velocity,
                                        const std::pair<double, double> acceleration,
                                        const std::pair<double, double> hitbox,
                                        const SolidsColumnMajorBitmap * scmb,
                                        const SolidsRowMajorBitmap * srmb
                                        ) {

    const std::pair<double, double> new_velocity = {velocity.first + acceleration.first * deltaTime_, velocity.second + acceleration.second * deltaTime_};
    const std::pair<double, double> movement_vector = {new_velocity.first * deltaTime_, new_velocity.second * deltaTime_};

    if (movement_vector.first == 0.0 && movement_vector.second == 0.0) {
        return true;
    }

    const std::pair<double, double> candidate_position = {position.first + movement_vector.first, position.second + movement_vector.second};

    const std::pair<double, double> inverse_movement_vector = {1 / movement_vector.first, 1 / movement_vector.second};

    const double half_width = hitbox.first / 2;
    const double half_height = hitbox.second / 2;

    const std::pair<double, double> corner_1_direction_vector = {half_width, half_height};
    const std::pair<double, double> corner_4_direction_vector = {half_width, - half_height};

    const double c1_mv_dot_product = corner_1_direction_vector.first * movement_vector.first + corner_1_direction_vector.second * movement_vector.second;
    const double c4_mv_dot_product = corner_4_direction_vector.first * movement_vector.first + corner_4_direction_vector.second * movement_vector.second;

    std::pair<double, double> tmp_covering_vector;
    std::pair<double, double> tmp_divisor_vector;
    if (abs(c1_mv_dot_product) < abs(c4_mv_dot_product)) {
        tmp_covering_vector = corner_1_direction_vector;
        tmp_divisor_vector = corner_4_direction_vector;
    } else {
        tmp_covering_vector = corner_4_direction_vector;
        tmp_divisor_vector = corner_1_direction_vector;
    }

    const std::pair<double, double> covering_vector = tmp_covering_vector;
    const std::pair<double, double> opposite_covering_vector = {- tmp_covering_vector.first, - tmp_covering_vector.second};

    const std::pair<double, double> divisor_vector = ((divisor_vector.first * movement_vector.first + divisor_vector.second * movement_vector.second) > 0.0) ?
                                                        tmp_divisor_vector :
                                                        {- tmp_divisor_vector.first, - tmp_divisor_vector.second};

    const std::pair<double, double> point_1 = {position.first + covering_vector.first, position.second + covering_vector.second};
    const std::pair<double, double> point_2 = {position.first + opposite_covering_vector.first, position.second + opposite_covering_vector.second};
    const std::pair<double, double> end_point_1 = {candidate_position.first + covering_vector.first, candidate_position.second + covering_vector.second};
    const std::pair<double, double> end_point_2 = {candidate_position.first + opposite_covering_vector.first, candidate_position.second + opposite_covering_vector.second};
    const std::pair<double, double> divisor = {position.first + divisor_vector.first, position.second + divisor_vector.second};
    const std::pair<double, double> end_divisor = {candidate_position.first + divisor_vector.first, candidate_position.second + divisor_vector.second};

    int closest_vertical_dim_x;
    int closest_horizontal_dim_y;
    bool collision_detected = false;
    
    {
        int begin_i = (int)point_1.first;
        int end_i = (int)end_point_1.first;
        int increment_i = 1;
        if (movement_vector.first < 0) {
            int tmp = begin_i;
            begin_i = end_i;
            end_i = tmp;
            increment_i = -1;               // Here the direction of iteration matters because we are always approaching the destination
        }
        for (int i = begin_i; i != end_i + increment_i; i+=increment_i) {
            int begin_j = (int)(point_1.second + (double)(i - (int)point_1.first) * inverse_movement_vector.first * movement_vector.second);
            int end_j = (int)(divisor.second + (double)(i - (int)divisor.first) * inverse_movement_vector.first * movement_vector.second);
            if (end_j < begin_j) {
                int tmp = begin_j;
                begin_j = end_j;
                end_j = tmp;
            }

            const int begin_n = begin_j / CHUNCK_BIT_SIZE;
            const int end_n = end_j / CHUNCK_BIT_SIZE;
            const int begin_mod = begin_j % CHUNCK_BIT_SIZE;
            const int end_mod = end_j % CHUNCK_BIT_SIZE;
            const unsigned int max_value = ~0;    // 1111111111...

            unsigned int bit_mask = max_value << begin_mod;
            const unsigned int first_chunck = SolidsColumnMajorBitmap(i, begin_n);
            if (first_chunck & bit_mask) {
                closest_vertical_dim_x = i;
                collision_detected = true;
                goto horizontal;
            }

            for (int n = begin_n + 1; n <= end_n; n++) {
                unsigned int chunck = SolidsColumnMajorBitmap(i, n);
                if (chunck) {
                    closest_vertical_dim_x = i;
                    collision_detected = true;
                    goto horizontal;
                }
            }

            if (end_mod != 0) {
                bit_mask = max_value >> (CHUNCK_BIT_SIZE - end_mod);
                const unsigned int last_chunck = SolidsColumnMajorBitmap(i, end_n + 1);
                if (last_chunck & bit_mask) {
                    closest_vertical_dim_x = i;
                    collision_detected = true;
                    goto horizontal;
                }
            }

        }
    }

    horizontal:
        {
            int begin_j = (int)point_2.second;
            int end_j = (int)end_point_2.second;
            int increment_j = 1;
            if (movement_vector.second < 0) {
                int tmp = begin_j;
                begin_j = end_j;
                end_j = tmp;
                increment_j = -1;
            }
            for (int j = begin_j; j != end_j + increment_j; j+=increment_j) {
                int begin_i = (int)(point_2.first + (double)(j - (int)point_2.second) * inverse_movement_vector.second * movement_vector.first);
                int end_i = (int)(divisor.first + (double)(j - (int)divisor.second) * inverse_movement_vector.second * movement_vector.first);
                if (movement_vector.first < 0) {
                    int tmp = begin_i;
                    begin_i = end_i;
                    end_i = tmp;
                }

                const int begin_n = begin_i / CHUNCK_BIT_SIZE;
                const int end_n = end_i / CHUNCK_BIT_SIZE;
                const int begin_mod = begin_i % CHUNCK_BIT_SIZE;
                const int end_mod = end_i % CHUNCK_BIT_SIZE;
                const unsigned int max_value = ~0;    // 1111111111...

                unsigned int bit_mask = max_value << begin_mod;
                const unsigned int first_chunck = SolidsRowMajorBitmap(j, begin_n);
                if (first_chunck & bit_mask) {
                    closest_horizontal_dim_y = j;
                    collision_detected = true;
                    goto end;
                }

                for (int n = begin_n + 1; n <= end_n; n++) {
                    unsigned int chunck = SolidsRowMajorBitmap(j, n);
                    if (chunck) {
                        closest_horizontal_dim_y = j;
                        collision_detected = true;
                        goto end;
                    }
                }

                if (end_mod != 0) {
                    bit_mask = max_value >> (CHUNCK_BIT_SIZE - end_mod);
                    const unsigned int last_chunck = SolidsRowMajorBitmap(j, end_n + 1);
                    if (last_chunck & bit_mask) {
                        closest_horizontal_dim_y = j;
                        collision_detected = true;
                        goto end;
                    }
                }

            }
        }
    
    end:
        if (!collision_detected) {
            position = candidate_position;
            return false;
        }

        const double hitbox_x_dim = (position.first < closest_vertical_dim_x) ? position.first + half_width : position.first - half_width;
        const double hitbox_y_dim = (position.second < closest_horizontal_dim_y) ? position.second + half_height : position.second - half_height;
        const double vertical_scalar = ((double)closest_vertical_dim_x - hitbox_x_dim) * inverse_movement_vector.first;
        const double horizontal_scalar = ((double)closest_horizontal_dim_y - hitbox_y_dim) * inverse_movement_vector.second;
        const double smallest_scalar = (vertical_scalar > horizontal_scalar) ? vertical_scalar : horizontal_scalar;
        std::pair<double, double> new_position;
        new_position.first = position.first + smallest_scalar * movement_vector.first;
        new_position.second = position.second + smallest_scalar * movement_vector.second;
        position = new_position;

    return true;
}

/*
bool PhysicsEngine::isSolidBlock(unsigned short int block_id) {
    return block_id > LAST_NON_COLLISION_BLOCK_ID;
}

void PhysicsEngine::rigidCollisionDetection( bool & collision,
                                        std::pair<double, double> & position,
                                        std::pair<double, double> & velocity,
                                        std::pair<double, double> & acceleration,
                                        const std::pair<double, double> hitbox,
                                        const BlockMatrix & block_matrix
                                        ) {

    const std::pair<double, double> new_velocity = {velocity.first + acceleration.first * deltaTime_, velocity.second + acceleration.second * deltaTime_};
    const std::pair<double, double> movement_vector = {new_velocity.first * deltaTime_, new_velocity.second * deltaTime_};

    if (movement_vector.first == 0.0 && movement_vector.second == 0.0) {
        return;
    }

    const std::pair<double, double> candidate_position = {position.first + movement_vector.first, position.second + movement_vector.second};

    const std::pair<double, double> inverse_movement_vector = {1 / movement_vector.first, 1 / movement_vector.second};

    const double half_width = hitbox.first / 2;
    const double half_height = hitbox.second / 2;

    const std::pair<double, double> corner_1_direction_vector = {half_width, half_height};
    const std::pair<double, double> corner_4_direction_vector = {half_width, - half_height};

    const double c1_mv_dot_product = corner_1_direction_vector.first * movement_vector.first + corner_1_direction_vector.second * movement_vector.second;
    const double c4_mv_dot_product = corner_4_direction_vector.first * movement_vector.first + corner_4_direction_vector.second * movement_vector.second;

    std::pair<double, double> tmp_covering_vector;
    std::pair<double, double> tmp_divisor_vector;
    if (abs(c1_mv_dot_product) < abs(c4_mv_dot_product)) {
        tmp_covering_vector = corner_1_direction_vector;
        tmp_divisor_vector = corner_4_direction_vector;
    } else {
        tmp_covering_vector = corner_4_direction_vector;
        tmp_divisor_vector = corner_1_direction_vector;
    }

    const std::pair<double, double> covering_vector = tmp_covering_vector;
    const std::pair<double, double> opposite_covering_vector = {- tmp_covering_vector.first, - tmp_covering_vector.second};

    const std::pair<double, double> divisor_vector = ((divisor_vector.first * movement_vector.first + divisor_vector.second * movement_vector.second) > 0.0) ?
                                                        tmp_divisor_vector :
                                                        {- tmp_divisor_vector.first, - tmp_divisor_vector.second};

    const std::pair<double, double> point_1 = {position.first + covering_vector.first, position.second + covering_vector.second};
    const std::pair<double, double> point_2 = {position.first + opposite_covering_vector.first, position.second + opposite_covering_vector.second};
    const std::pair<double, double> end_point_1 = {candidate_position.first + covering_vector.first, candidate_position.second + covering_vector.second};
    const std::pair<double, double> end_point_2 = {candidate_position.first + opposite_covering_vector.first, candidate_position.second + opposite_covering_vector.second};
    const std::pair<double, double> divisor = {position.first + divisor_vector.first, position.second + divisor_vector.second};
    const std::pair<double, double> end_divisor = {candidate_position.first + divisor_vector.first, candidate_position.second + divisor_vector.second};

    int closest_vertical_dim_x;
    int closest_horizontal_dim_y;
    bool collision_detected = false;
    
    {
        int begin_i = (int)point_1.first;
        int end_i = (int)end_point_1.first;
        int increment_i = 1;
        if (movement_vector.first < 0) {
            int tmp = begin_i;
            begin_i = end_i;
            end_i = tmp;
            increment_i = -1;
        }
        for (int i = begin_i; i != end_i + increment_i; i+=increment_i) {
            int begin_j = (int)(point_1.second + (double)(i - (int)point_1.first) * inverse_movement_vector.first * movement_vector.second);
            int end_j = (int)(divisor.second + (double)(i - (int)divisor.first) * inverse_movement_vector.first * movement_vector.second);
            int increment_j = 1;
            if (movement_vector.second < 0) {
                int tmp = begin_j;
                begin_j = end_j;
                end_j = tmp;
                increment_j = -1;
            }
            for (int j = begin_j; j != end_j + increment_j; j+=increment_j) {
                unsigned short int block_id = block_matrix(i, j).id;
                if (isSolidBlock(block_id)) {
                    closest_vertical_dim_x = i;
                    collision_detected = true;
                    goto horizontal;
                }
            }
        }
    }

    horizontal:
        {
            int begin_j = (int)point_2.second;
            int end_j = (int)end_point_2.second;
            int increment_j = 1;
            if (movement_vector.second < 0) {
                int tmp = begin_j;
                begin_j = end_j;
                end_j = tmp;
                increment_j = -1;
            }
            for (int j = begin_j; j != end_j + increment_j; j+=increment_j) {
                int begin_i = (int)(point_2.first + (double)(j - (int)point_2.second) * inverse_movement_vector.second * movement_vector.first);
                int end_i = (int)(divisor.first + (double)(j - (int)divisor.second) * inverse_movement_vector.second * movement_vector.first);
                int increment_i = 1;
                if (movement_vector.first < 0) {
                    int tmp = begin_i;
                    begin_i = end_i;
                    end_i = tmp;
                    increment_i = -1;
                }
                for (int i = begin_i; i != end_i + increment_i; i+=increment_i) {
                    // unsigned short int block_id = block_matrix(j, i).id; ROW MAJOR
                    if (isSolidBlock(block_id)) {
                        closest_horizontal_dim_y = j;
                        collision_detected = true;
                        goto end;
                    }
                }
            }
        }
    
    end:
        if (!collision_detected) {
            position = candidate_position;
            return;
        }

        const double hitbox_x_dim = (position.first < closest_vertical_dim_x) ? position.first + half_width : position.first - half_width;
        const double hitbox_y_dim = (position.second < closest_horizontal_dim_y) ? position.second + half_height : position.second - half_height;
        const double vertical_scalar = ((double)closest_vertical_dim_x - hitbox_x_dim) * inverse_movement_vector.first;
        const double horizontal_scalar = ((double)closest_horizontal_dim_y - hitbox_y_dim) * inverse_movement_vector.second;
        const double smallest_scalar = (vertical_scalar > horizontal_scalar) ? vertical_scalar : horizontal_scalar;
        std::pair<double, double> new_position;
        new_position.first = position.first + smallest_scalar * movement_vector.first;
        new_position.second = position.second + smallest_scalar * movement_vector.second;
        position = new_position;

}
*/

/*
struct Line {   // Ax + By + C = 0:
    double A;
    double B;
    double C;
};

void PhysicsEngine::angeledCollisionDetection( bool & collision,
                                        std::pair<double, double> & position,
                                        std::pair<double, double> & velocity,
                                        std::pair<double, double> & acceleration,
                                        const std::pair<double, double> direction_unit_vector,
                                        const std::pair<double, double> hitbox,
                                        const BlockMatrix & block_matrix
                                        ) {

    const std::pair<double, double> new_velocity = {velocity.first + acceleration.first * deltaTime_, velocity.second + acceleration.second * deltaTime_};
    const std::pair<double, double> movement_vector = {new_velocity.first * deltaTime_, new_velocity.second * deltaTime_};

    if (movement_vector.first == 0.0 && movement_vector.second == 0.0) {
        goto end;
    }

    const std::pair<double, double> candidate_position = {position.first + movement_vector.first, position.second + movement_vector.second};

    //const std::pair<double, double> inverse_movement_vector = {1 / movement_vector.first, 1 / movement_vector.second};

    const double half_width = hitbox.first / 2;
    const double half_height = hitbox.second / 2;

    const std::pair<double, double> positive_orthogonal_rotation_dv = {-direction_unit_vector.second, direction_unit_vector.first};
    const std::pair<double, double> negative_orthogonal_rotation_dv = {direction_unit_vector.second, -direction_unit_vector.first};

    const std::pair<double, double> corner_1_direction_vector = { half_width * direction_unit_vector.first + half_height * positive_orthogonal_rotation_dv.first,
                                                                    half_width * direction_unit_vector.second + half_height * positive_orthogonal_rotation_dv.second};

    const std::pair<double, double> corner_4_direction_vector = { half_width * direction_unit_vector.first + half_height * negative_orthogonal_rotation_dv.first,
                                                                    half_width * direction_unit_vector.second + half_height * negative_orthogonal_rotation_dv.second};

    const double c1_mv_dot_product = corner_1_direction_vector.first * movement_vector.first + corner_1_direction_vector.second * movement_vector.second;
    const double c4_mv_dot_product = corner_4_direction_vector.first * movement_vector.first + corner_4_direction_vector.second * movement_vector.second;

    std::pair<double, double> tmp_covering_vector;
    std::pair<double, double> tmp_divisor_vector;
    if (abs(c1_mv_dot_product) < abs(c4_mv_dot_product)) {
        tmp_covering_vector = corner_1_direction_vector;
        tmp_divisor_vector = corner_4_direction_vector;
    } else {
        tmp_covering_vector = corner_4_direction_vector;
        tmp_divisor_vector = corner_1_direction_vector;
    }

    const std::pair<double, double> covering_vector = tmp_covering_vector;
    const std::pair<double, double> opposite_covering_vector = {- tmp_covering_vector.first, - tmp_covering_vector.second};

    const std::pair<double, double> divisor_vector = ((divisor_vector.first * movement_vector.first + divisor_vector.second * movement_vector.second) > 0.0) ?
                                                        tmp_divisor_vector :
                                                        {- tmp_divisor_vector.first, - tmp_divisor_vector.second};

    const std::pair<double, double> point_1 = {position.first + covering_vector.first, position.second + covering_vector.second};
    const std::pair<double, double> point_2 = {position.first + opposite_covering_vector.first, position.second + opposite_covering_vector.second};
    const std::pair<double, double> end_point_1 = {candidate_position.first + covering_vector.first, candidate_position.second + covering_vector.second};
    const std::pair<double, double> end_point_2 = {candidate_position.first + opposite_covering_vector.first, candidate_position.second + opposite_covering_vector.second};
    const std::pair<double, double> divisor = {position.first + divisor_vector.first, position.second + divisor_vector.second};
    const std::pair<double, double> end_divisor = {candidate_position.first + divisor_vector.first, candidate_position.second + divisor_vector.second};

    // Part 1:
    {
        Line p1_d = {divisor.second - point_1.second,
                        - (divisor.first - point_1.first),
                        divisor.first * point_1.second - point_1.first * divisor.second};
        Line ep1_ed = {end_divisor.second - end_point_1.second,
                        - (end_divisor.first - end_point_1.first),
                        end_divisor.first * end_point_1.second - end_point_1.first * end_divisor.second};
        Line d_ed = {end_divisor.second - divisor.second,
                        - (end_divisor.first - divisor.first),
                        end_divisor.first * divisor.second - divisor.first * end_divisor.second};
        Line p1_ep1 = {end_point_1.second - point_1.second,
                        - (end_point_1.first - point_1.first),
                        end_point_1.first * point_1.second - point_1.first * end_point_1.second};
        
        std::pair<double, double> p1_d_direction_vector = {- p1_d.B, p1_d.A};
        
        int begin_i = std::min_element({point_1.first, end_point_1.first, divisor.first, end_divisor.first});
        int end_i = std::max_element({point_1.first, end_point_1.first, divisor.first, end_divisor.first});
        int begin_j = std::min_element({point_1.second, end_point_1.second, divisor.second, end_divisor.second});
        int end_j = std::max_element({point_1.second, end_point_1.second, divisor.second, end_divisor.second});
        int increment_i = 1;
        int increment_j = 1;
        if (movement_vector.first < 0) {
            int tmp = begin_i;
            begin_i = end_i;
            end_i = tmp;
            increment_i = -1;
        }
        if (movement_vector.second < 0) {
            int tmp = begin_j;
            begin_j = end_j;
            end_j = tmp;
            increment_j = -1;
        }
        if (abs(p1_d_direction_vector.first) <= abs(p1_d_direction_vector.second)) {     // Column-major
            for (int i = begin_i; i != end_i + increment_i; i+=increment_i) {
                for (int j = begin_j; j != end_j + increment_j; j+=increment_j) {
                    
                }
            }
        } else {        // Row-major
            for (int j = begin_j; j != end_j + increment_j; j+=increment_j) {
                for (int i = begin_i; i != end_i + increment_i; i+=increment_i) {
                    const double double_i = (double)i;
                    const double double_j = (double)j;
                    const double f1 = p1_d.A * double_i + p1_d.B * double_j + p1_d.C;
                    const double f2 = ep1_ed.A * double_i + ep1_ed.B * double_j + ep1_ed.C;
                    const double f3 = p1_ep1.A * double_i + p1_ep1.B * double_j + p1_ep1.C;
                    const double f4 = d_ed.A * double_i + d_ed.B * double_j + d_ed.C;
                    if (f1 * f2 <= 0.0 && f3 * f4 <= 0.0) {
                        unsigned short int block_id = block_matrix(i, j).id;
                        if (isSolidBlock(block_id)) {

                        }
                    }
                }
            }
        }
    }



}
*/

/*
void PhysicsEngine::collisionDetection( bool & collision,
                                        std::pair<double, double> & position,
                                        std::pair<double, double> & velocity,
                                        std::pair<double, double> & acceleration,
                                        const std::pair<double, double> hitbox,
                                        const BlockMatrix & block_matrix
                                        ) {

    const std::pair<double, double> new_velocity = {velocity.first + acceleration.first * deltaTime_, velocity.second + acceleration.second * deltaTime_};

    const std::pair<double, double> movement_vector = {new_velocity.first * deltaTime_, new_velocity.second * deltaTime_};

    if (movement_vector.first == 0.0 && movement_vector.second == 0.0) {
        goto end;
    }

    const std::pair<double, double> candidate_position = {position.first + movement_vector.first, position.second + movement_vector.second};

    const std::pair<double, double> inverse_movement_vector = {1 / movement_vector.first, 1 / movement_vector.second};

    const double half_width = hitbox.first / 2;
    const double half_height = hitbox.second / 2;
    const std::pair<double, double> left_bottom = {position.first - half_width, position.second - half_height};
    const std::pair<double, double> right_bottom = {position.first + half_width, position.second - half_height};
    const std::pair<double, double> left_top = {position.first - half_width, position.second + half_height};
    const std::pair<double, double> right_top = {position.first + half_width, position.second + half_height};
    const std::pair<double, double> candidate_left_bottom = {candidate_position.first - half_width, candidate_position.second - half_height};
    const std::pair<double, double> candidate_right_bottom = {candidate_position.first + half_width, candidate_position.second - half_height};
    const std::pair<double, double> candidate_left_top = {candidate_position.first - half_width, candidate_position.second + half_height};
    const std::pair<double, double> candidate_right_top = {candidate_position.first + half_width, candidate_position.second + half_height};

    int closest_horizontal_dim_y = INT_MAX;
    int closest_vertical_dim_x = INT_MAX;
    bool collision_detected = false;
    if (movement_vector.first > 0.0 && movement_vector.second > 0.0) {

        int begin_i = (int)left_top.first;
        int end_i = (int)candidate_right_top.first;
        for (int i = begin_i; i <= end_i; i++) {
            int begin_j = (i <= (int)right_bottom.first) ?
                                (int)left_top.second + 1 :
                                (int)(right_bottom.second + (double)(i - (int)right_bottom.first) * inverse_movement_vector.first * movement_vector.second);
            int end_j = (i < (int)candidate_top_left.first) ?
                                (int)(left_top.second + (double)(i - (int)candidate_top_left.first) * inverse_movement_vector.first * movement_vector.second) :
                                (int)candidate_top_left.second;
            for (int j = begin_j; j <= end_j; j++) {
                unsigned short int block_id = block_matrix(i, j).id;
                if (isSolidBlock(block_id)) {
                    collision_detected = true;
                    double x_divisor = top_right.first + (double)(i - (int)top_right.first) * inverse_movement_vector.first * movement_vector.first;
                    if (x_divisor <= i) {
                        closest_vertical_dim_x = i;
                        goto end;
                    } else {
                        closest_horizontal_dim_y = j;
                        begin_i = i + 1;
                        goto diagonal_pos_pos_intermediate;
                    }
                }
            }
        }

        goto end;

        diagonal_pos_pos_intermediate:
            int end_j = closest_horizontal_dim_y;
            for (int i = begin_i; i <= end_i; i++) {
                int begin_j = (i <= (int)right_bottom.first) ?
                                (int)left_top.second + 1 :
                                (int)(right_bottom.second + (double)(i - (int)right_bottom.first) * inverse_movement_vector.first * movement_vector.second);
                for (int j = begin_j; j <= end_j; j++) {
                    unsigned short int block_id = block_matrix(i, j).id;
                    if (isSolidBlock(block_id)) {
                        collision_detected = true;
                        double x_divisor = top_right.first + (double)(i - (int)top_right.first) * inverse_movement_vector.first * movement_vector.first;
                        if (x_divisor <= i) {
                            closest_vertical_dim_x = i;
                            goto end;
                        } else {
                            closest_horizontal_dim_y = j;
                            end_j = closest_horizontal_dim_y;
                            break;
                        }
                    }
                }
            }
        
        goto end;

    } 
    
    if (movement_vector.first > 0.0 && movement_vector.second < 0.0) {

        int begin_i = (int)left_top.first;
        int end_i = (int)candidate_right_top.first;
        for (int i = begin_i; i <= end_i; i++) {
            int begin_j = (i <= (int)right_bottom.first) ?
                                (int)left_top.second + 1 :
                                (int)(right_bottom.second + (double)(i - (int)right_bottom.first) * inverse_movement_vector.first * movement_vector.second);
            int end_j = (i < (int)candidate_top_left.first) ?
                                (int)(left_top.second + (double)(i - (int)candidate_top_left.first) * inverse_movement_vector.first * movement_vector.second) :
                                (int)candidate_top_left.second;
            for (int j = begin_j; j <= end_j; j++) {
                unsigned short int block_id = block_matrix(i, j).id;
                if (isSolidBlock(block_id)) {
                    collision_detected = true;
                    double x_divisor = top_right.first + (double)(i - (int)top_right.first) * inverse_movement_vector.first * movement_vector.first;
                    if (x_divisor <= i) {
                        closest_vertical_dim_x = i;
                        goto end;
                    } else {
                        closest_horizontal_dim_y = j;
                        begin_i = i + 1;
                        goto diagonal_pos_pos_intermediate;
                    }
                }
            }
        }

        goto end;

        diagonal_pos_pos_intermediate:
            int end_j = closest_horizontal_dim_y;
            for (int i = begin_i; i <= end_i; i++) {
                int begin_j = (i <= (int)right_bottom.first) ?
                                (int)left_top.second + 1 :
                                (int)(right_bottom.second + (double)(i - (int)right_bottom.first) * inverse_movement_vector.first * movement_vector.second);
                for (int j = begin_j; j <= end_j; j++) {
                    unsigned short int block_id = block_matrix(i, j).id;
                    if (isSolidBlock(block_id)) {
                        collision_detected = true;
                        double x_divisor = top_right.first + (double)(i - (int)top_right.first) * inverse_movement_vector.first * movement_vector.first;
                        if (x_divisor <= i) {
                            closest_vertical_dim_x = i;
                            goto end;
                        } else {
                            closest_horizontal_dim_y = j;
                            end_j = closest_horizontal_dim_y;
                            break;
                        }
                    }
                }
            }
        
        goto end;

    }

    end:
        if (!collision_detected) {
            position = candidate_position;
            return;
        }

        const double hitbox_x_dim = (position.first < closest_vertical_dim_x) ? position.first + half_width : position.first - half_width;
        const double hitbox_y_dim = (position.second < closest_horizontal_dim_y) ? position.second + half_height : position.second - half_height;
        const double vertical_scalar = ((double)closest_vertical_dim_x - hitbox_x_dim) * inverse_movement_vector.first;
        const double horizontal_scalar = ((double)closest_horizontal_dim_y - hitbox_y_dim) * inverse_movement_vector.second;
        const double smallest_scalar = (vertical_scalar > horizontal_scalar) ? vertical_scalar : horizontal_scalar;
        std::pair<double, double> new_position;
        new_position.first = position.first + smallest_scalar * movement_vector.first;
        new_position.second = position.second + smallest_scalar * movement_vector.second;
        position = new_position;

}
*/


/*
std::pair<int, int> newPosition1() {
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
    const double half_height = hitbox.second / 2;
    const std::pair<double, double> left_bottom = {position.first - half_width, position.second - half_height};
    const std::pair<double, double> right_bottom = {position.first + half_width, position.second - half_height};
    const std::pair<double, double> left_top = {position.first - half_width, position.second + half_height};
    const std::pair<double, double> right_top = {position.first + half_width, position.second + half_height};
    const std::pair<double, double> candidate_left_bottom = {candidate_position.first - half_width, candidate_position.second - half_height};
    const std::pair<double, double> candidate_right_bottom = {candidate_position.first + half_width, candidate_position.second - half_height};
    const std::pair<double, double> candidate_left_top = {candidate_position.first - half_width, candidate_position.second + half_height};
    const std::pair<double, double> candidate_right_top = {candidate_position.first + half_width, candidate_position.second + half_height};

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
*/

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
        const double half_height = hitbox.second / 2;
        const std::pair<double, double> left_bottom = {position.first - half_width, position.second - half_height};
        const std::pair<double, double> right_bottom = {position.first + half_width, position.second - half_height};
        const std::pair<double, double> left_top = {position.first - half_width, position.second + half_height};
        const std::pair<double, double> right_top = {position.first + half_width, position.second + half_height};
        const std::pair<double, double> candidate_left_bottom = {candidate_position.first - half_width, candidate_position.second - half_height};
        const std::pair<double, double> candidate_right_bottom = {candidate_position.first + half_width, candidate_position.second - half_height};
        const std::pair<double, double> candidate_left_top = {candidate_position.first - half_width, candidate_position.second + half_height};
        const std::pair<double, double> candidate_right_top = {candidate_position.first + half_width, candidate_position.second + half_height};

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