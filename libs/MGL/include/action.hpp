#ifndef MGL_ACTION_HPP
#define MGL_ACTION_HPP

#include <vector>
#include <array>
#include <utility>

#include <SDL2/SDL.h>

enum ActionCode : int {
    LEFT,
    RIGHT,
    UP,
    DOWN,
    USE,
    ACTION_CODE_COUNT // THIS IS ALWAYS LAST!!! It tells the length of ActionCode (number of actions). 
};

class Action {
    public:
        const std::array<bool, ActionCode::ACTION_CODE_COUNT> & getActions(const Uint8 * keyboard_state, Uint32 mouse_state);

    private:
        std::array<bool, ActionCode::ACTION_CODE_COUNT> actions_;
        std::vector<std::pair<int, int>> action_code_to_keyboard_lookup_ = {
                                                                                {ActionCode::LEFT, 4},
                                                                                {ActionCode::RIGHT, 7},
                                                                                {ActionCode::UP, 26},
                                                                                {ActionCode::DOWN, 22}
                                                                            };
        std::vector<std::pair<int, int>> action_code_to_mouse_lookup_ = {
                                                                            {ActionCode::USE, 1}
                                                                        };
};

#endif