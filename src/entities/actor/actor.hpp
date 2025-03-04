#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <utility>

class Actor {
    public:
        
    private:
        /****************************************************************/
        //                         WORLD VARIABLES                      //
        /****************************************************************/
        std::pair<float, float> position_;
        std::pair<float, float> velocity_;
        std::pair<float, float> acceleration_;
        /****************************************************************/
        /****************************************************************/

        /****************************************************************/
        //                 PHYSICAL INITIAL CONSTANT STATS              //
        /****************************************************************/
        /*
        const unsigned int weigth_;
        const unsigned int strength_;
        const std::pair<float, float> max_velocity_;
        const std::pair<float, float> max_acceleration_;
        */
        /****************************************************************/
        /****************************************************************/

        /****************************************************************/
        //                 INNATE INITIAL CONSTANT STATS                //
        /****************************************************************/
        /*
        const unsigned int health_points_;
        const unsigned short int durability_;
        */
        /****************************************************************/
        /****************************************************************/
};

#endif