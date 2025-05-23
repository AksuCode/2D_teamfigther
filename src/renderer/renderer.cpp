#include "./renderer.hpp"

Renderer::Renderer(GameWindow * gw) : gw_(gw) {}

void Renderer::Init() {
    viewport_middle_point_ = {gw_->getWindowWidth() / 2, gw_->getWindowHeigth() / 2};
}

void Renderer::updateViewportFocalPointWorldPoint(std::pair<double, double> world_point_as_viewport_focal_point) {
    world_point_as_viewport_focal_point_ = world_point_as_viewport_focal_point;

}

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
                const std::pair<double, double> world_point,
                const float scaling) {
    const int id = skin_id + player_id * 10000;
    PlayerRender * player_render = players_.at(id);
    const std::pair<int, int> point = {world_point.first - world_point_as_viewport_focal_point_.first + viewport_middle_point_.first - 50, world_point.second - world_point_as_viewport_focal_point_.second + viewport_middle_point_.second - 50};
    player_render->renderPlayer(action, action_sprite_counter, point, scaling);
    return 0;
}

void Renderer::createWorldRender(solid_world * sw) {
    wr_ = new WorldRender(gw_, sw, &world_point_as_viewport_focal_point_);
    wr_->InitAndReconfig();
}

void Renderer::updateWorldRender() {
    wr_->InitialDraw();
}

void Renderer::renderWorld() {
    wr_->renderWorld();
}