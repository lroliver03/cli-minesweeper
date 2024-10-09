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

  // Game loop.
  ESC_ERASEALL();
  game_state_t game_state;
  drawBoard(game);
  while ((game_state = getGameState(game)) == GSTATE_ONGOING || game_state == GSTATE_MENU) {
    // control_t input = getInput();

    if (game_state == GSTATE_MENU) {
      drawMenu(game);
      handleMenuInput(game, getInput());
    } else if (game_state == GSTATE_SETTINGS) {
      drawSettings(game);
      handleSettingsInput(game, getInput());
    } else if (game_state == GSTATE_ONGOING) {
      drawBoard(game);
      handleGameInput(game, getInput());
    }
    
    if (getBoardState(game->board) == BSTATE_LOSE) {
      printf("\nYou triggered a bomb! Game over!\nPress any key to continue...");
      getchar();
      setGameState(game, GSTATE_QUIT);
    } else if (game->state.hidden_cells == 0) {
      drawBoard(game);
      printf("\nYou safely discovered all bombs! You win!\nPress any key to continue...");
      getchar();
      dialog_result_t response = doDialog(2, 2, 36, 6, "", "Do you wish to go to the main menu?", DIALOG_FORM_YES_NO);
      if (response == DIALOG_YES) {
        setGameState(game, GSTATE_MENU);
        resetGame(game, game->board->rows, game->board->cols, game->mines);
      } else if (response == DIALOG_NO)
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