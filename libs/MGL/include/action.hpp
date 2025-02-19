#ifndef MGL_ACTION_HPP
#define MGL_ACTION_HPP

#include <vector>

class Action {
    public:
        const enum class ActionCode {
            LEFT,
            RIGT,
            UP,
            DOWN,
            USE,
        };

        Action();

        std::vector<int> getActions(Uint8 * keyboard_state, Uint32 & mouse_state);

    private:
        constexpr std::array<std::pair<int, int>> action_code_to_keyboard_lookup_;
        constexpr std::array<std::pair<int, int>> action_code_to_mouse_lookup_;
};

#endif