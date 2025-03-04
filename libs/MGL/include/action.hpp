#ifndef MGL_ACTION_HPP
#define MGL_ACTION_HPP

#include <vector>
#include <array>
#include <utility>

#include <SDL2/SDL.h>

class Action {
    public:
        enum class ActionCode {
            LEFT,
            RIGHT,
            UP,
            DOWN,
            USE,
        };

        Action();

        std::vector<int> getActions(Uint8 * keyboard_state, Uint32 & mouse_state);

    private:
        std::array<std::pair<int, int>, 4> action_code_to_keyboard_lookup_ = {
                                                                                {ActionCode::LEFT, 4},
                                                                                {ActionCode::RIGHT, 7},
                                                                                {ActionCode::UP, 26},
                                                                                {ActionCode::DOWN, 22}
                                                                            };
        std::array<std::pair<int, int>, 1> action_code_to_mouse_lookup_ = {{ActionCode::USE, 1}};
};

#endif