#include "./renderer.hpp"

Renderer::Renderer(GameWindow * gw) : gw_(gw) {}

int Renderer::createPlayerRender(const int player_id, const int skin_id) {
    const int id = skin_id + player_id * 10000;
    if (players_.contains(id)) {
        PlayerRender * player_render = players_.at(id);
        player_render->incrementRefcount();
    } else {
        players_.emplace(id, new PlayerRender(gw_, player_id, skin_id));
    }
    return 0;
}

int Renderer::loadPlayer(const int player_id, const int skin_id) {

    const int id = skin_id + player_id * 10000;
    PlayerRender * player_render = players_.at(id);
    player_render->loadSpriteSheet();
    player_render->loadSpriteRender();
    return 0;
}

int Renderer::renderPlayer(const int player_id,
                const int skin_id, 
                const int action,
                int & action_sprite_counter,
                const std::pair<int, int> destination_position,
                const float scaling) {
    const int id = skin_id + player_id * 10000;
    PlayerRender * player_render = players_.at(id);
    player_render->renderPlayer(action, action_sprite_counter, destination_position, scaling);
    return 0;
}

int Renderer::createWorldRender(solid_world * sw) {
    wr_ = new WorldRender(gw_, sw);
    wr_->initWorldRender();
    return 0;
}

int Renderer::updateWorldRender() {
    wr_->updateWorldRender();
    return 0;
}

int Renderer::renderWorld() {
    wr_->renderWorld();
    return 0;
}