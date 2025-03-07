#include "./world_render.hpp"

WorldRender::WorldRender(GameWindow * game_window) : game_window_(game_window) {
    wr_ = new WizardRender(game_window_);
}

WorldRender::~WorldRender() {
    delete wr_;
}

void WorldRender::renderW(WizardRender * w_render, std::pair<int, int> destination_position, float scaling) {
    w_render->renderActor(0, wr_action_counter, destination_position, scaling);
}

void WorldRender::renderWorld() {
    renderW(wr_, {500, 500}, 1.0f);
}

void WorldRender::loadWorld() {
    wr_->loadSpriteSheet();
    if (!wr_->spriteSheetLoaded()) {exit(-1);}
    wr_->loadSpriteRender();
    if (!wr_->spriteRenderLoaded()) {exit(-1);}
}