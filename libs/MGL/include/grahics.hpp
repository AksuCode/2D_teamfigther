#ifndef MGL_GRAPHICS_HPP
#define MGL_GRAPHICS_HPP

#include "graphics/window.hpp"

class Graphics {
    public:
        Graphics();
        ~Graphics();
        initializeOrUpdateGraphics();
    private:
        Window* mgl_window_;
        Renderer* mgl_renderer_;
};

#endif