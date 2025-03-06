#include "./world_render.hpp"

WorldRender::WorldRender(GameWindow * game_window) : game_window_(game_window) {
    wr_ = new WizardRender(game_window_, NULL);
}

WorldRender::~WorldRender() {
    delete wr_;
}

void WorldRender::renderW(WizardRender * w_render, std::pair<int, int> destination_position, float scaling) {
    int tmp = 1;
    w_render->renderActor(0, tmp, destination_position, scaling);
}

void WorldRender::renderWorld() {
    renderW(wr_, {0,0}, 1.0f);
}