#include "./wizard_render.hpp"

WizardRender::WizardRender(GameWindow * gw, const char bmp_path[]) {

    /***************************************************************/
    // HARDCODE SPRITESHEET SPECIFICATIONS. SPECIFIC TO THIS ACTOR //
    /***************************************************************/

    // Map the amount of sprites per action from the sprite sheet.
    sprite_amount_per_action_mapping_ = new int[4]{
        1,
        1,
        1,
        1
    };

    // {w, h} pixel dimension of a sprite in the spritesheet.
    sprite_dimensions_ = {100, 100};

    /***************************************************************/
    /***************************************************************/

    assert((bmp_path != nullptr) && "bmp_path should be a valid c-string.");

    ss_ = new SpriteSheet(bmp_path);
    sr_ = new SpriteRender(gw, sprite_dimensions_);
    if (ss_ == nullptr || sr_ == nullptr) {exit(-1);}
}

WizardRender::~WizardRender() {
    delete sr_;
    delete ss_;
}