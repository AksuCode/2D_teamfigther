#include "./player_render.hpp"

PlayerRender::PlayerRender(GameWindow * gw, uint32_t player_id, uint32_t skin_id = 0) : ss_(nullptr), sr_(nullptr), reference_count_(1) {

    const std::string bmp_path = Players::getPlayerSpriteSheetPath(player_id, skin_id);

    uint16_t sprite_sheet_dimensions = Players::getPlayerSpriteSheetDimension(player_id);
    int sprite_sheet_dimensions_int = (int)sprite_sheet_dimensions;

    std::pair<uint16_t, uint16_t> sprite_dimensions = Players::getPlayerSpriteDimensions(player_id);
    std::pair<int, int> sprite_dimensions_int = (std::pair<int, int>)sprite_dimensions;

    action_sprite_indexing_ = Players::getPlayerActionSpriteIndexingMapping(player_id);

    ss_ = new SpriteSheet(bmp_path, sprite_sheet_dimensions_int, sprite_dimensions_int);
    sr_ = new SpriteRender(gw, ss_);
    if (ss_ == nullptr || sr_ == nullptr) {exit(-1);}
}

PlayerRender::~PlayerRender() {
    delete sr_;
    delete ss_;
}

int PlayerRender::getReferenceCount() {
    return reference_count_;
}

void PlayerRender::incrementRefcount() {
    reference_count_++;
}

void PlayerRender::decrementRefcount() {
    reference_count_--;
}

void PlayerRender::loadSpriteSheet() {
    ss_->load();
}

void PlayerRender::unloadSpriteSheet() {
    ss_->unload();
}

void PlayerRender::loadSpriteRender() {
    sr_->load();
}

void PlayerRender::unloadSpriteRender() {
    sr_->unload();
}

bool PlayerRender::spriteSheetLoaded() {
    return ss_->isLoaded();
}

bool PlayerRender::spriteRenderLoaded() {
    return sr_->isLoaded();
}

int PlayerRender::renderPlayer(const int action, int & action_sprite_counter, const std::pair<int, int> destination_position, const float scaling = 1.0f) {

    const std::pair<uint16_t, uint16_t> action_indices = action_sprite_indexing_[action];

    if (action_sprite_counter >= (action_indices.second - action_indices.first)) {
        action_sprite_counter = 0;
    }

    const int sprite_index = static_cast<int>(action_indices.first) + action_sprite_counter;
    action_sprite_counter += 1;
    return sr_->renderSpriteScaled(sprite_index, destination_position, scaling);
}