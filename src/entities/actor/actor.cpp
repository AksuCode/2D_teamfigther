#include "./actor.hpp"

Actor::Actor(std::pair<int, int> starting_position) {
    position_.first = (double)starting_position.first;
    position_.second = (double)starting_position.second;
}

const std::pair<double, double> & Actor::getPosition() {
    return position_;
}

const std::pair<double, double> & Actor::getVelocity() {
    return velocity_;
}

const std::pair<double, double> & Actor::getAcceleration() {
    return acceleration_;
}

const std::pair<double, double> & Actor::getHitbox() {
    return hit_box_;
}

void Actor::setPosition(const std::pair<double, double> & position) {
    position_.first = position.first;
    position_.second = position.second;
}

void Actor::setVelocity(const std::pair<double, double> & velocity) {
    velocity_.first = velocity.first;
    velocity_.second = velocity.second;
}