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

  // Hide key inputs.
  static struct termios oldt, newt;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);

  srand(time(NULL));

  game_t *game = createGame(ROWS, COLS, MINES);

  printf("\033[2J");
  game_state_t game_state;
  drawBoard(game);
  while ((game_state = getGameState(game)) == GSTATE_ONGOING || game_state == GSTATE_MENU) {
    control_t input = getInput();

    if (game_state == GSTATE_MENU) {
      handleMenuInput(game, input);
      drawMenu(game);
    } else if (game_state == GSTATE_ONGOING) {
      handleGameInput(game, input);
      drawBoard(game);
    }
    
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
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  
  return 0;
}