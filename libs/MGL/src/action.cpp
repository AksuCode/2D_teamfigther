#include "../include/action.hpp"

Action::Action() {}

std::vector<int> Action::getActions(Uint8 * keyboard_state, Uint32 & mouse_state) {
    std::vector<int> response;

    for (auto it = action_code_to_keyboard_lookup_.begin(); it != action_code_to_keyboard_lookup_.end(); it++) {
        if (keyboard_state[it.second]) {
            response.push_back(it.first);
        }
    }

    for (auto it = action_code_to_mouse_lookup_.begin(); it != action_code_to_mouse_lookup_.end(); it++) {
        if (SDL_BUTTON(it.second)) {
            response.push_back(it.first);
        }
    }

    return response;
}