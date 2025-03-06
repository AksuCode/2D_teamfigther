#include "./game.hpp"

void log_to_file(void *userdata, int category, SDL_LogPriority priority, const char *message) {
  FILE *logFile = fopen("./log/SDL_log.log", "a");
  if (logFile) {
    fprintf(logFile, "[%d] %s\n", priority, message);
    fflush(logFile);  // Ensure data is written
    fclose(logFile);
  } else {
    std::cerr << "SDL_log.log file failed to open for write." << std::endl;
    std::cerr << "Perhaps ./log directory missing." << std::endl;
  }
}

int main(int argc, char *argv[]) {
  Game * game = new Game(log_to_file);
  game->gameLoop();
  return 0;
}