#include "controls.h"

control_t getInput() {
  switch (getc(stdin)) {
    case KEY_FLAG:
    case KEY_FLAG_UPPERCASE:
      return ACTION_FLAG;
    case KEY_CLICK:
      return ACTION_CLICK;
    case KEY_QUIT:
      return ACTION_QUIT;
    case '\033':
      getc(stdin);
      switch (getc(stdin)) {
        case 'A':
          return MOVE_UP;
        case 'B':
          return MOVE_DOWN;
        case 'C':
          return MOVE_RIGHT;
        case 'D':
          return MOVE_LEFT;
      }
  }
  return ACTION_INVALID;
}

void handleInput(game_t *game, control_t input) {
  cell_state_t state = getCellState(game->board, game->cursor.x, game->cursor.y);
  uint8_t is_bomb = getCellIsBomb(game->board, game->cursor.x, game->cursor.y);
  switch (input) {
    case MOVE_UP:
      if (game->cursor.y > 0) --game->cursor.y;
      break;
    case MOVE_DOWN:
      if (game->cursor.y < game->board->rows - 1) ++game->cursor.y;
      break;
    case MOVE_LEFT:
      if (game->cursor.x > 0) --game->cursor.x;
      break;
    case MOVE_RIGHT:
      if (game->cursor.x < game->board->cols - 1) ++game->cursor.x;
      break;
    case ACTION_FLAG:
      if (state == HIDDEN)
        setCellState(game->board, game->cursor.x, game->cursor.y, FLAGGED);
      else if (state == FLAGGED)
        setCellState(game->board, game->cursor.x, game->cursor.y, HIDDEN);
      break;
    case ACTION_CLICK:
      if (state == HIDDEN) {
        setCellState(game->board, game->cursor.x, game->cursor.y, SHOWN);
        if (is_bomb)
          setBoardState(game->board, LOSE);
      }
      break;
    case ACTION_QUIT:
      setGameState(game, QUIT);
      break;
  }
}