#ifndef MGL_RENDERER_HPP
#define MGL_RENDERER_HPP

#include <SDL2/SDL.h>

class Renderer {
    public:
        Renderer(SDL_Window * window_ptr);
        
        ~Renderer();

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

        /*
        * Update the window with the present renderer.
        */
        void updateWindow();

    private:
        SDL_Renderer *renderer_;
};

#endif