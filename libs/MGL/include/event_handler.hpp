#ifndef MGL_EVENT_HANDLER_HPP
#define MGL_EVENT_HANDLER_HPP

#include <SDL2/SDL.h>

#include <string>

class EventHandler {
    public:
    
        void pollEvent();
        void receiveTextInput();
        std::string getTextInput();
        void stopReceiveTextInput();

    private:
        SDL_Event event_;
        std::string text_input_;
};

#endif