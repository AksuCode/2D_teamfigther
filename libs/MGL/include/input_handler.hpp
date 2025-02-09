#ifndef MGL_INPUT_HANDLER_HPP
#define MGL_INPUT_HANDLER_HPP

#include <vector>

#include <SDL2/SDL.h>

class InputHandler {
  public:
    InputHandler();

    Uint8 getKeyboardState();

    std::pair<int, int> getMousePosition();

    Uint32 getMouseKeyState();

  private:
    const Uint8 * keyboard_state_; 
    int mouse_pos_x_;
    int mouse_pos_y_;
    Uint32 mouse_key_state_;
    SDL_Event event_;

    void updateInputState();
};

#endif