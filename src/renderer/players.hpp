#ifndef PLAYERS_HPP
#define PLAYERS_HPP

#include <cstdint>
#include <string>
#include <vector>
#include <utility>

static const std::string base_path = "./assets/sprites";

// Character length has to be less than the number in the right most brackert [][?].
// While the first bracket is the number of stored strings.
static const char player_id_to_spritesheet_directory_mapping[2][20] = {
    "/wizard",
    "/warlock"
};

// Spritesheet dimensions should be a power of 2 and they MUST BE SQUARE.
static const uint16_t player_id_to_spritesheet_dimension_mapping[2] = {
    512,
    512
};

static const std::pair<uint16_t, uint16_t> player_id_to_sprite_dimension_mapping[2] = {
    {100, 100},
    {100, 100}
};

static const std::vector<std::vector<std::pair<uint16_t, uint16_t>>> player_id_to_player_action_sprite_indexing_mapping = {
    {{0, 5}, {5, 10}},
    {{0, 5}, {5, 10}}
};

std::string getPlayerSpriteSheetPath(uint32_t player_id, uint32_t skin_id = 0) {

    std::string path = base_path;

    path += player_id_to_spritesheet_directory_mapping[player_id];

    path += "/skin_";
    path += skin_id;
    path += ".bmp";

    return path;
}

uint16_t getPlayerSpriteSheetDimension(uint32_t player_id) {
    return player_id_to_spritesheet_dimension_mapping[player_id];
}

std::pair<uint16_t, uint16_t> getPlayerSpriteDimensions(uint32_t player_id) {
    return player_id_to_sprite_dimension_mapping[player_id];
}

std::vector<std::pair<uint16_t, uint16_t>> & getPlayerActionSpriteIndexingMapping(uint32_t player_id) {
    return player_id_to_player_action_sprite_indexing_mapping[player_id];
}

#endif