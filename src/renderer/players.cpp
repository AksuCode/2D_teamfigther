#include "./players.hpp"

const std::string base_path = "./assets/sprites";

const std::string player_id_to_spritesheet_directory_mapping[2] = {
    "/wizard",
    "/warlock"
};

const uint16_t player_id_to_spritesheet_dimension_mapping[2] = {
    512,
    512
};

const std::pair<uint16_t, uint16_t> player_id_to_sprite_dimension_mapping[2] = {
    {100, 100},
    {100, 100}
};

const std::vector<std::vector<std::pair<uint16_t, uint16_t>>> player_id_to_player_action_sprite_indexing_mapping = {
    {{0, 5}, {5, 10}},
    {{0, 5}, {5, 10}}
};

namespace Players {

    const std::string getPlayerSpriteSheetPath(uint32_t player_id, uint32_t skin_id = 0) {

        std::string path = base_path;

        path += player_id_to_spritesheet_directory_mapping[player_id];

        path += "/skin_";
        path += std::to_string(skin_id);
        path += ".bmp";

        return path;
    }

    uint16_t getPlayerSpriteSheetDimension(uint32_t player_id) {
        return player_id_to_spritesheet_dimension_mapping[player_id];
    }

    std::pair<uint16_t, uint16_t> getPlayerSpriteDimensions(uint32_t player_id) {
        return player_id_to_sprite_dimension_mapping[player_id];
    }

    const std::vector<std::pair<uint16_t, uint16_t>> & getPlayerActionSpriteIndexingMapping(uint32_t player_id) {
        return player_id_to_player_action_sprite_indexing_mapping[player_id];
    }

}