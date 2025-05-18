#pragma once

struct R_Player {
    int player_id = 0;
    int skin_id = 0;

    PlayerRender & pr;

    int action_sprite_counter = 0;

    void init(Renderer & renderer) {
        pr = renderer.createPlayerRender(player_id, skin_id);
    }
};