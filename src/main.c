#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>
#include "game.h"
#include "draw.h"
#include "controls.h"

#define ROWS 20
#define COLS 20
#define MINES 40

int main() {

  // Hide key inputs.
  static struct termios oldt, newt;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);

  srand(time(NULL));

  game_t *game = createGame(ROWS, COLS, MINES);

  printf("\033[2J");
  draw(game);
  while (getGameState(game) == ONGOING) {
    handleInput(game, getInput());
    draw(game);
    if (getBoardState(game->board) == LOSE) {
      printf("\n\nYou triggered a bomb! Game over!");
      setGameState(game, QUIT);
    }
  }

  deleteGame(game);

  printf("\n\n%s", ESC_RESET);
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  
  return 0;
}