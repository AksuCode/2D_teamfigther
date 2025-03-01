#include "./wizard_render.hpp"

WizardRender::WizardRender(const GameWindow * gw, const char * bmp_path = "./assets/sprites/wizard/default.bmp") {
    ss_ = new SpriteSheet(bmp_path);
    sr_ = new SpriteRender(gw, {100, 100});             // {100, 100} is the (w,h) dimension of sprites in the spritesheet from bmp_path.
    if (ss_ == nullptr || sr_ == nullptr) {exit(-1);}
}

WizardRender::~WizardRender() {
    delete sr_;
    delete ss_;
}

void WizardRender::renderActor() {
    if (action_sprite_counter_ >= sprite_amount_per_action_mapping_[action_]) {
        action_sprite_counter_ = 0;
    }

    const std::pair<int, int> sprite_index = {action_, action_sprite_counter_};
    sr_->renderSpriteScaled(sprite_index, destination_position_, scaling_)

    action_sprite_counter_ += 1;
}