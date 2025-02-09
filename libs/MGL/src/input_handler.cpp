#include "../include/input_handler.hpp"

InputHandler::InputHandler() {
  keyboard_state_ = SDL_GetKeyboardState(NULL);
}

Uint8 InputHandler::getKeyboardState() {
  return keyboard_state_;
}

std::pair<int, int> InputHandler::getMousePosition() {
  return std::pair(mouse_pos_x_, mouse_pos_y_);
}

Uint32 InputHandler::getMouseKeyState() {
  return mouse_key_state_;
}

void InputHandler::updateInputState() {
  SDL_PumpEvents();
  mouse_key_state_ = SDL_GetMouseState(&mouse_pos_x_, &mouse_pos_y_);
}