#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <utility>
#include <unordered_map>

#include "MGL/include/game_window.hpp"
#include "MGL/include/sprite_render.hpp"

#include "./player_render.hpp"

#include "./tile_world.hpp"

class Renderer {
    public:
        Renderer(GameWindow * gw);
        
        int createPlayerRender(const int player_id, const int skin_id);
        int loadPlayer(const int player_id, const int skin_id);
        int renderPlayer(const int player_id,
                        const int skin_id, 
                        const int action,
                        int & action_sprite_counter,
                        const std::pair<int, int> destination_position,
                        const float scaling);

        void renderWorld();
        void loadWorld();

    private:
        GameWindow * gw_;

        std::unordered_map<int, PlayerRender *> players_;
};

#endif