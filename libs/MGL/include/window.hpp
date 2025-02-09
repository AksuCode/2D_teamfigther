#ifndef MGL_WINDOW_HPP
#define MGL_WINDOW_HPP

#include <vector>
#include <iostream>

#include <SDL2/SDL.h>

#include "renderer.hpp"

class Window {
  public:
    Window();

    ~Window();

    int getWindowWidth();

    int getWindowHeigth();

    /*
    * Creates a custom size window.
    * Parameters:
    * full_screen - set window to full screen mode
    * window_width - width of the window in screen coordinates
    * window_heigth - heigth of the window in screen coordinates
    * Returns 0 on succesful update and -1 on failure. Terminates program when window creation fails.
    */
    int createOrUpdateWindow(bool full_screen, int window_width, int window_heigth);

  private:
    SDL_Window *window_;
    int window_width_;
    int window_heigth_;
    Renderer *window_renderer_;

    /*
    * Creates a window. Terminates program on failure.
    */
    void createWindow(int width, int heigth, uint32_t flags);
};

#endif