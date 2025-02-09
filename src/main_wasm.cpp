#include "MGL/include/window.hpp"
#include "MGL/include/gamestatehandler.hpp"

// If compilation is done with emscripten
#ifdef __EMSCRIPTEN__
#include "emscripten.h"
#endif

void gameLoop() {}

int main(int argc, char *argv[]) {
  emscripten_set_main_loop(gameLoop, 0, 1);
  return 0;
}