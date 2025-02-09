#include "../include/renderer.hpp"

Renderer::Renderer(SDL_Window * window_ptr) {
    renderer_ = SDL_CreateRenderer(window_ptr, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (renderer_ == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create a renderer: %s\n", SDL_GetError());
        exit(-1);
    }
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(renderer_);
}

int Renderer::clearRenderer(Uint8 r, Uint8 g, Uint8 b, Uint8 t) {
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

int Renderer::drawRectangle(Uint8 r, Uint8 g, Uint8 b, Uint8 t, int x, int y, int w, int h) {
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

void Renderer::updateWindow() {
  SDL_RenderPresent(renderer_);
}