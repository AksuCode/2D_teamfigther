#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <utility>
#include <unordered_map>

#include "MGL/include/game_window.hpp"
#include "MGL/include/sprite_render.hpp"

#include "./player_render.hpp"

#include "./world_render.hpp"
#include "../world.hpp"

class Renderer {
    public:
        Renderer(GameWindow * gw);

        void Init();
    
        void updateViewportFocalPointWorldPoint(std::pair<double, double> world_point_as_viewport_focal_point);

        int createPlayerRender(const int player_id, const int skin_id);
        int loadPlayer(const int player_id, const int skin_id);
        int renderPlayer(const int player_id,
                        const int skin_id, 
                        const int action,
                        int & action_sprite_counter,
                        const std::pair<double, double> world_point,
                        const float scaling);

        void createWorldRender(solid_world * sw);
        void updateWorldRender();
        void renderWorld();

    private:
        GameWindow * gw_;
        std::pair<int, int> viewport_middle_point_;

        std::unordered_map<int, PlayerRender *> players_;
        
        WorldRender * wr_;
        std::pair<double, double> world_point_as_viewport_focal_point_ = {0.0, 0.0};
};

#endif