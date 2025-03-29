#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <utility>

class Actor {
    public:
        Actor(std::pair<int, int> starting_position);
        const std::pair<double, double> & getPosition();
        const std::pair<double, double> & getVelocity();
        const std::pair<double, double> & getAcceleration();
        const std::pair<double, double> & getHitbox();
        void setPosition(const std::pair<double, double> & position);
        void setVelocity(const std::pair<double, double> & velocity);
    private:
        unsigned short int actor_id_;
        unsigned short int actor_model_;

        /****************************************************************/
        //                       PHYSICS VARIABLES                      //
        /****************************************************************/
        // (x, y)
        std::pair<double, double> position_;
        std::pair<double, double> velocity_;
        std::pair<double, double> acceleration_;
        unsigned int weigth_;
        /****************************************************************/
        /****************************************************************/

        /****************************************************************/
        //                       PHYSICS CONSTANTS                      //
        /****************************************************************/
        std::pair<double, double> hit_box_;  // (width, heigth)
        double movement_acceleration_increment_;
        double horizontal_velocity_limit_;
        double rise_velocity_limit_;
        double fall_velocity_limit_;
        /****************************************************************/
        /****************************************************************/
        
        /****************************************************************/
        //                       GAME LOGIC VARIABLES                   //
        /****************************************************************/
        unsigned int health_points_;
        /****************************************************************/
        /****************************************************************/
};

#endif