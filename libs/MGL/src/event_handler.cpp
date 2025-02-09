#include "../include/event_handler.hpp"

void EventHandler::pollEvent() {
    while (SDL_PollEvent(&event_)) {
        switch (event_.type)
            case (SDL_QUIT):
                // Not implemented
            
            case (SDL_TEXTINPUT):
                text_input_ += event_.text.text;
    }
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
    SDL_StopTextInput()
}