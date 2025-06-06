#ifndef WORLD_RENDER_HPP
#define WORLD_RENDER_HPP

#include <cstdint>
#include <utility>
#include <chrono>

#include <SDL2/SDL.h>

#include "MGL/include/game_window.hpp"

#include "../config.hpp"
#include "../world.hpp"

class WorldRender {
    public:
        WorldRender(GameWindow * gw, solid_world * sw, std::pair<double, double> * world_point_at_viewport_focal_point);
        ~WorldRender();

        void InitAndReconfig();

        void InitialDraw();

        void renderWorld();

    private:
        GameWindow * gw_;
        solid_world * sw_;
        SDL_Texture * texture_;

        std::pair<double, double> * world_point_at_viewport_focal_point_;
        std::pair<double, double> previous_world_point_at_viewport_focal_point_; 

        int viewport_width_;
        int viewport_height_;

        int texture_width_;
        int texture_height_;

        SDL_Texture * createChunkTexture();
};

#endif