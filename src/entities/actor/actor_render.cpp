#include "./actor_render.hpp"

ActorRender::ActorRender() : ss_(nullptr), ss_loaded_(false), sr_(nullptr), sr_loaded_(false), action_(0), action_frame_counter_(0), scaling_(1.0f), destination_position_({0,0}) {}

void ActorRender::loadSpriteSheet() {
    if (ss_ == nullptr) {
        ss_loaded_ = false;
        return;
    }
    if (ss_->load() < 0) {
        ss_loaded_ = false;
        return;
    }
    ss_loaded_ = true;
}

void ActorRender::unloadSpriteSheet() {
    ss_->unload();
    ss_loaded_ = false;
}

void ActorRender::loadSpriteRender() {
    if (sr_ == nullptr) {
        sr_loaded_ = false;
        return;
    }
    if (sr_->load(ss_->getSpriteSheet()) < 0) {
        sr_loaded_ = false;
        return;
    }
    sr_loaded_ = true;
}

void ActorRender::unloadSpriteRender() {
    sr_->unload();
    sr_loaded_ = false;
}

bool ActorRender::spriteSheetLoaded() {
    return ss_loaded_;
}

bool ActorRender::spriteRenderLoaded() {
    return sr_loaded_;
}

void ActorRender::setAction(int action) {
    if (action_ == action) {return;}
    action_ = action;
    action_frame_counter_ = 0;
}

void ActorRender::setDestination(const std::pair<int, int> & destination_position) {
    destination_position_ = destination_position;
}