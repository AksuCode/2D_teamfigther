#include "../../include/graphics/window.hpp"

Window::Window(): window_(nullptr), window_width_(0), window_heigth_(0), window_renderer_(nullptr) {}

Window::~Window() {
  delete window_renderer_;
  SDL_DestroyWindow(window_);
}

int Window::getWindowWidth() { return window_width_; }

int Window::getWindowHeigth() { return window_heigth_; }

Renderer * getRenderer() { return window_renderer_; }

int Window::createOrUpdateWindow(bool full_screen, int window_width, int window_heigth) {
  if (window_ == nullptr) {
    if (full_screen) {
      createWindow(window_width, window_heigth, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
    } else {
      createWindow(window_width, window_heigth, SDL_WINDOW_OPENGL);
    }
  } else {
    if (full_screen) {
      if (SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Window modification error: %s\n", SDL_GetError());
        return -1;
      }
    } else {
      SDL_SetWindowSize(window_, window_width, window_heigth);
    }
  }
  SDL_GetWindowSize(window_, &window_width_, &window_heigth_);

  // Create renderer
  window_renderer_ = new Renderer(window_);

  return 0;
}

void Window::createWindow(int width, int heigth, uint32_t flags) {
  window_ = SDL_CreateWindow("",                      // window title. No title.
                            SDL_WINDOWPOS_UNDEFINED,  // Window position x
                            SDL_WINDOWPOS_UNDEFINED,  // Window position y
                            width,                    // width, in pixels
                            heigth,                   // height, in pixels
                            flags                     // flags - see below
  );
  if (window_ == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
    exit(-1);
  }
}