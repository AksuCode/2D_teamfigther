#ifndef MGL_GAME_WINDOW_HPP
#define MGL_GAME_WINDOW_HPP

#include <vector>
#include <iostream>

#include <SDL2/SDL.h>

// THIS IS NOT THREAD SAFE ATM. DOING OPERATIONS ON RENDERER FROM MULTIPLE THREADS WILL CAUSE PROBLEMS.
class GameWindow {
  public:
    GameWindow();

    ~GameWindow();

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

    /*
    * Clear renderer with the specified color.
    * Parameters:
    * r - red value of pixels
    * g - green value of pixels
    * b - blue value of pixels
    * t - transparency of the covering color
    * Returns 0 on success and -1 on failure.
    */
    int clearRenderer(Uint8 r, Uint8 g, Uint8 b, Uint8 t);

    /*
    * Draw a rectangle on the window.
    * Parameters:
    * r - red value of rectangle pixels
    * g - green value of rectangle pixels
    * b - blue value of rectangle pixels
    * t - transparency of the rectangle
    * x - horizontal position of rectangle in window coordinates
    * y - vertical position of rectangle in window coordinates
    * w - width of rectangle in window coordinates
    * h - heigth of rectangle in window coordinates
    * Returns 0 on success and -1 on failure.
    */
    int drawRectangle(Uint8 r, Uint8 g, Uint8 b, Uint8 t, int x, int y, int w, int h);

    int GameWindow::renderTexture(SDL_Texture * texture_,
                  const SDL_Rect * src_rect,
                  const SDL_Rect * dst_rect);

    int renderTextureEx(SDL_Texture * texture_,
                      const SDL_Rect * src_rect,
                      const SDL_Rect * dst_rect,
                      const double angle,
                      const SDL_Point *center,
                      const SDL_RendererFlip flip);

    /*
    * Update the window with the present renderer.
    */
    void updateWindow();

  private:
    SDL_Window *window_;
    int window_width_;
    int window_heigth_;
    SDL_Renderer *renderer_;
    std::mutex renderer_mutex_;

    /*
    * Creates a window. Terminates program on failure.
    */
    void createWindow(int width, int heigth, uint32_t flags);

    void createRenderer(SDL_Window * window_ptr);
};

#endif