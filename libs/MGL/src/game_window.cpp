#include "../include/game_window.hpp"

GameWindow::GameWindow(): window_(nullptr), window_width_(0), window_heigth_(0), renderer_(nullptr) {}

GameWindow::~GameWindow() {
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);
}

int GameWindow::getWindowWidth() { return window_width_; }

int GameWindow::getWindowHeigth() { return window_heigth_; }

int GameWindow::createOrUpdateWindow(bool full_screen, int window_width, int window_heigth) {
  if (renderer_ != nullptr) {
    SDL_DestroyRenderer(renderer_);
  }

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

  GameWindow::createRenderer(window_);

  return 0;
}

void GameWindow::createWindow(int width, int heigth, uint32_t flags) {
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

void GameWindow::createRenderer(SDL_Window * window_ptr) {
  renderer_ = SDL_CreateRenderer(window_ptr, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
  if (renderer_ == NULL) {
      SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create a renderer: %s\n", SDL_GetError());
  } else {
    renderer_ = SDL_CreateRenderer(window_ptr, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_SOFTWARE);
    if (renderer_ == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create a renderer: %s\n", SDL_GetError());
        exit(-1);
    }
  }
}

int GameWindow::clearRenderer(Uint8 r, Uint8 g, Uint8 b, Uint8 t) {
  if (SDL_SetRenderDrawColor(renderer_, r, g, b, t) < 0) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Renderer color setting error: %s\n", SDL_GetError());
    return -1;
  }
  if (SDL_RenderClear(renderer_) < 0) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Renderer clear error: %s\n", SDL_GetError());
    return -1;
  }

  return 0;
}

int GameWindow::drawRectangle(Uint8 r, Uint8 g, Uint8 b, Uint8 t, int x, int y, int w, int h) {
  SDL_Rect new_rectangle = {x, y, w, h};
  if (SDL_SetRenderDrawColor(renderer_, r, g, b, t) < 0) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Renderer color setting error: %s\n", SDL_GetError());
    return -1;
  }
  if (SDL_RenderFillRect(renderer_, &new_rectangle) < 0) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Renderer fill error: %s\n", SDL_GetError());
    return -1;
  }

  return 0;
}

int GameWindow::renderTexture(SDL_Texture * texture,
                  const SDL_Rect * src_rect,
                  const SDL_Rect * dst_rect) {
  return SDL_RenderCopy(renderer_, texture, src_rect, dst_rect);
}

int GameWindow::renderTextureEx(SDL_Texture * texture,
                  const SDL_Rect * src_rect,
                  const SDL_Rect * dst_rect,
                  const double angle,
                  const SDL_Point *center,
                  const SDL_RendererFlip flip) {
  return SDL_RenderCopyEx(renderer_, texture, src_rect, dst_rect, angle, center, flip);
}

int GameWindow::renderTextureF(SDL_Texture * texture,
                  const SDL_Rect * src_rect,
                  const SDL_FRect * dst_rect) {
  return SDL_RenderCopyF(renderer_, texture, src_rect, dst_rect);
}

int GameWindow::renderTextureExF(SDL_Texture * texture,
                  const SDL_Rect * src_rect,
                  const SDL_FRect * dst_rect,
                  const double angle,
                  const SDL_FPoint *center,
                  const SDL_RendererFlip flip) {
  return SDL_RenderCopyExF(renderer_, texture, src_rect, dst_rect, angle, center, flip);
}

void GameWindow::updateWindow() {
  SDL_RenderPresent(renderer_);
}

const GameWindow::GW_Renderer GameWindow::getRenderer() {
  return renderer_;
}