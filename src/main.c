#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include "game.h"
#include "draw.h"
#include "controls.h"

int main() {

  // Hide key inputs.
  static struct termios oldt, newt;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);

  game_t *game = createGame(10, 10, 0.3);
  printf("\033[2J");
  while (getGameState(game) == ONGOING) {
    draw(game);
    handleInput(game, getInput());
  }

  printf("\n\n");
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  
  return 0;
}