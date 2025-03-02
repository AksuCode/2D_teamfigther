#include "./actor_render.hpp"

ActorRender::ActorRender() : ss_(nullptr), ss_loaded_(false), sr_(nullptr), sr_loaded_(false), sprite_amount_per_action_mapping_(nullptr), sprite_dimensions_({0, 0}) {}

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

std::pair<int, int> ActorRender::getSpriteDimensions() {
    return sprite_dimensions_;
}

void ActorRender::renderActor(int action, int & action_sprite_counter, std::pair<int, int> destination_position, float scaling = 1.0f) {
    if (action_sprite_counter >= sprite_amount_per_action_mapping_[action]) {
        action_sprite_counter = 0;
    }

    const std::pair<int, int> sprite_index = {action, action_sprite_counter};
    sr_->renderSpriteScaled(sprite_index, destination_position, scaling);

    action_sprite_counter += 1;
}