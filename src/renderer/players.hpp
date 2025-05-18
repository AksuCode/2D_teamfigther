#ifndef PLAYERS_HPP
#define PLAYERS_HPP

#include <cstdint>
#include <string>
#include <vector>
#include <utility>

extern const std::string base_path;

// Character length has to be less than the number in the right most brackert [][?].
// While the first bracket is the number of stored strings.
extern const std::string player_id_to_spritesheet_directory_mapping[2];

// Spritesheet dimensions should be a power of 2 and they MUST BE SQUARE.
extern const uint16_t player_id_to_spritesheet_dimension_mapping[2];

extern const std::pair<uint16_t, uint16_t> player_id_to_sprite_dimension_mapping[2];

extern const std::vector<std::vector<std::pair<uint16_t, uint16_t>>> player_id_to_player_action_sprite_indexing_mapping;

namespace Players {

    const std::string getPlayerSpriteSheetPath(uint32_t player_id, uint32_t skin_id);

    uint16_t getPlayerSpriteSheetDimension(uint32_t player_id);

    std::pair<uint16_t, uint16_t> getPlayerSpriteDimensions(uint32_t player_id);

    const std::vector<std::pair<uint16_t, uint16_t>> & getPlayerActionSpriteIndexingMapping(uint32_t player_id);

}

#endif