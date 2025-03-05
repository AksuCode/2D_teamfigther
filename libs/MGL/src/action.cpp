#include "../include/action.hpp"

const std::array<bool, (int)ActionCode::ACTION_CODE_COUNT> & Action::getActions(const Uint8 * keyboard_state, Uint32 mouse_state) {

    for(int i = 0; i < (int)ActionCode::ACTION_CODE_COUNT; i++) {
        actions_[i] = false;
    }

    for (auto it = action_code_to_keyboard_lookup_.begin(); it != action_code_to_keyboard_lookup_.end(); it++) {
        if (keyboard_state[(*it).second]) {
            actions_[(*it).first] = true;
        }
    }

    for (auto it = action_code_to_mouse_lookup_.begin(); it != action_code_to_mouse_lookup_.end(); it++) {
        if (mouse_state & SDL_BUTTON((*it).second)) {
            actions_[(*it).first] = true;
        }
    }

    return actions_;
}