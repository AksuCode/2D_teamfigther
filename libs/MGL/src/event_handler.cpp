#include "../include/event_handler.hpp"

EventHandler::EventHandler() {
    keyboard_state_ = SDL_GetKeyboardState(NULL); // DO NOT FREE !!!
}

void EventHandler::pollEvent() {
    while (SDL_PollEvent(&event_)) {
        switch (event_.type)
            case (SDL_QUIT):
                // Not implemented
            
            case (SDL_TEXTINPUT):
                text_input_ += event_.text.text;
    }
    
    mouse_key_state_ = SDL_GetMouseState(&mouse_position_.first, &mouse_position_.second);
}

void EventHandler::receiveTextInput() {
    SDL_StartTextInput();
}

std::string EventHandler::getTextInput() {
    std::string response = text_input_;
    text_input_.clear();
    return response;
}

void EventHandler::stopReceiveTextInput() {
    SDL_StopTextInput();
}

Uint8 *EventHandler::getKeyboardState() {
  return keyboard_state_;
}

std::pair<int, int> & EventHandler::getMousePosition() {
  return mouse_position_;
}

Uint32 & EventHandler::getMouseKeyState() {
  return mouse_key_state_;
}