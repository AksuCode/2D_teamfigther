#include "./actor_render.hpp"

ActorRender::ActorRender(GameWindow * gw, const char bmp_path[], std::pair<int, int> sprite_dimensions, std::vector<std::vector<std::pair<int, int>>> sprites_per_action) : gw_(gw), sprite_dimensions_(sprite_dimensions), sprites_per_action_(sprites_per_action) {
    bmp_path_ = new char[strlen(original) + 1];
    strcpy(bmp_path_, bmp_path);

    assert((bmp_path_ != nullptr) && "bmp_path should be a valid c-string.");

    ss_ = new SpriteSheet(bmp_path_);
    sr_ = new SpriteRender(gw_, sprite_dimensions_);
    if (ss_ == nullptr || sr_ == nullptr) {exit(-1);}
}

ActorRender::~ActorRender() {
    delete bmp_path_;
    delete sr_;
    delete ss_;
}

void ActorRender::loadSpriteSheet() {
    assert((ss_ != nullptr) && "ss_ should be a valid pointer by subclass constructor.");
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
    assert((ss_ != nullptr) && "ss_ should be a valid pointer by subclass constructor.");
    ss_->unload();
    ss_loaded_ = false;
}

void ActorRender::loadSpriteRender() {
    assert((sr_ != nullptr) && "sr_ should be a valid pointer by subclass constructor.");
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
    assert((sr_ != nullptr) && "sr_ should be a valid pointer by subclass constructor.");
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

int ActorRender::renderActor(const int action, int & action_sprite_counter, const std::pair<int, int> destination_position, const float scaling = 1.0f) {

    assert((sr_ != nullptr) && "sr_ should be a valid pointer by subclass constructor.");

    if (action_sprite_counter >= sprites_per_action_[action].size()) {
        action_sprite_counter = 0;
    }

    const std::pair<int, int> sprite_index = sprites_per_action_[action][action_sprite_counter];
    action_sprite_counter += 1;
    return sr_->renderSpriteScaled(sprite_index, destination_position, scaling);
}