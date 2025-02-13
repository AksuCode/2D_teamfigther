#ifndef MGL_EVENT_HANDLER_HPP
#define MGL_EVENT_HANDLER_HPP

#include <SDL2/SDL.h>

#include <string>
#include <vector>

class EventHandler {
    public:
    
        EventHandler();

        void pollEvent();
        void receiveTextInput();
        std::string getTextInput();
        void stopReceiveTextInput();
        
        Uint8 getKeyboardState();

        std::pair<int, int> getMousePosition();

        Uint32 getMouseKeyState();

    private:
        SDL_Event event_;
        std::string text_input_;

        const Uint8 * keyboard_state_; 
        int mouse_pos_x_;
        int mouse_pos_y_;
        Uint32 mouse_key_state_;
};

#endif