#include "./actor_render.hpp"

ActorRender::ActorRender(GameWindow * gw, uint32_t player_id, uint32_t skin_id = 0) {

    std::string bmp_path = Players.getPlayerSpriteSheetPath(player_id, skin_id);

    sprite_sheet_dimensions_ = getPlayerSpriteSheetDimension(player_id);

    sprite_dimensions_ = Players.getPlayerSpriteDimensions(player_id);

    action_sprite_indexing_ = getPlayerActionSpriteIndexingMapping(player_id);

    assert((bmp_path != nullptr) && "bmp_path should be a valid c-string.");

    ss_ = new SpriteSheet(bmp_path);
    sr_ = new SpriteRender(gw, sprite_dimensions_);
    if (ss_ == nullptr || sr_ == nullptr) {exit(-1);}
}

ActorRender::~ActorRender() {
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