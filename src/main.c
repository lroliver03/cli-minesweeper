#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>
#include "game.h"
#include "draw.h"
#include "controls.h"

#define ROWS 10
#define COLS 10
#define MINES 10

int main() {
  srand(time(NULL));

  // Hide key inputs.
  static struct termios oldt, newt;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);

  game_t *game = createGame();
  startGame(game, ROWS, COLS, MINES);
  setGameState(game, GSTATE_MENU);
  moveCursorTo(game, 0, 0);

  // printf("\033[2J");
  ESC_ERASEALL();
  game_state_t game_state;
  drawBoard(game);
  while ((game_state = getGameState(game)) == GSTATE_ONGOING || game_state == GSTATE_MENU) {
    // control_t input = getInput();

    if (game_state == GSTATE_MENU) {
      drawMenu(game);
      handleMenuInput(game, getInput());
    } else if (game_state == GSTATE_ONGOING) {
      drawBoard(game);
      handleGameInput(game, getInput());
    }

    // LAST TIME YOU WORKED ON THIS, YOU WERE UNDER THE EFFECT OF 3 BEERS, HAD SEEN THEM TOGETHER AND COULDN'T REALLY KEEP IT TOGETHER
    // IT'S NOT REALLY YOUR FAULT AT THIS POINT
    // JUST GET BACK TO WORK WHEN YOU READ THIS SOBER
    
    if (getBoardState(game->board) == BSTATE_LOSE) {
      printf("\nYou triggered a bomb! Game over!");
      setGameState(game, GSTATE_QUIT);
    } else if (game->state.hidden_cells == 0) {
      printf("\nYou safely discovered all bombs! You win!");
      setGameState(game, GSTATE_END);
    }
  }

  deleteGame(game);

  printf("\n\n%s", ESC_RESET);
  ESC_ERASEALL();
  ESC_GOTO(0, 0);
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  
  return 0;
}