#include "MGL/include/window.hpp"
#include "MGL/include/gamestatehandler.hpp"

#include "./game.hpp"

void gameLoop() {
  while(true) {

  }
}

int main(int argc, char *argv[]) {
  game = new Game();
  game->gameLoop();
  return 0;
}