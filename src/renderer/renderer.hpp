#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <utility>
#include <unordered_map>

#include "MGL/include/game_window.hpp"
#include "MGL/include/sprite_render.hpp"

struct Renderer {
    GameWindow * gw;

    static void initializeRenderer(GameWindow * game_window) {
        gw = new GameWindow();
    }

    static void closeRenderer() {
        delete gw;
    }

    std::unordered_map<int, CharacterRenderer *> character_renderers;

    static void addCharacterRender(int character_id, int skin_id) {
        CharacterRenderer * cr = new CharacterRenderer();
        int id = 1000 * character_id + skin_id;
        character_renderers.insert({id, cr});
    }

}

class Renderer {
    public:
        WorldRender(GameWindow * game_window);
        ~WorldRender();
        void renderWorld();
        void loadWorld();

    private:
        GameWindow * game_window_;

        WizardRender * wr_;
        int wr_action_counter = 0;

        void renderW(WizardRender * w_render, std::pair<int, int> destination_position, float scaling);
};

#endif