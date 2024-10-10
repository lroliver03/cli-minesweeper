#include "controls.h"

static void __recursiveZeroCellClick(game_t *game, uint8_t x, uint8_t y) {
  // If cell is bomb or is already shown, return.
  if (getCellIsBomb(game->board, x, y) || (getCellState(game->board, x, y) == SHOWN)) return; // This getCellState inside the IF statement avoids infinite recursive loops. DON'T REMOVE IT.

  setCellState(game->board, x, y, SHOWN);
  --game->state.hidden_cells;

  if (getCellNeighbors(game->board, x, y) > 0) return;
  
  uint8_t x_lower = (x > 0)?(x - 1):(0);
  uint8_t x_upper = (x < game->board->cols - 1)?(x + 2):(game->board->cols);
  uint8_t y_lower = (y > 0)?(y - 1):(0);
  uint8_t y_upper = (y < game->board->rows - 1)?(y + 2):(game->board->rows);

  for (int i = y_lower; i < y_upper; ++i) {
    for (int j = x_lower; j < x_upper; ++j) {
      if (i == y && j == x) continue;
      __recursiveZeroCellClick(game, j, i);
    }
  }
}

void handleMenuInput(game_t *game, control_t input) {
  switch (input) {
    case MOVE_UP:
      if (game->cursor.y > 0) --game->cursor.y;
      break;
    case MOVE_DOWN:
      if (game->cursor.y < MAX_MAINMENU_OPTIONS - 1) ++game->cursor.y;
      break;
    case ACTION_CLICK:
      switch (game->cursor.y) {
        case 0: setGameState(game, GSTATE_ONGOING); break;
        case 1:
          setGameState(game, GSTATE_SETTINGS); break;
        case 2:
          if (doDialog(2, 5, 30, 6, "Quit game?", NULL, DIALOG_FORM_YES_NO) == DIALOG_YES)
            setGameState(game, GSTATE_QUIT);
          break;
      }
      if (game->cursor.y == 0)
        setGameState(game, GSTATE_ONGOING);
      else if (game->cursor.y == 1)
        if (doDialog(2, 5, 30, 6, "Quit game?", NULL, DIALOG_FORM_YES_NO) == DIALOG_YES)
          setGameState(game, GSTATE_QUIT);
      break;
    case ACTION_QUIT:
      if (doDialog(2, 5, 30, 6, "Quit game?", NULL, DIALOG_FORM_YES_NO) == DIALOG_YES)
        setGameState(game, GSTATE_QUIT);
      break;
  }
}

void handleSettingsInput(game_t *game, control_t input) {
  return;
}

void handleGameInput(game_t *game, control_t input) {
  cell_state_t cell_state = getCellState(game->board, game->cursor.x, game->cursor.y);
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
      if (cell_state == HIDDEN) {
        setCellState(game->board, game->cursor.x, game->cursor.y, FLAGGED);
        --game->state.mines_left;
        if (getCellIsBomb(game->board, getCursorX(game), getCursorY(game)))
          --game->state.flags_left;
      } else if (cell_state == FLAGGED) {
        setCellState(game->board, game->cursor.x, game->cursor.y, HIDDEN);
        ++game->state.mines_left;
        if (getCellIsBomb(game->board, getCursorX(game), getCursorY(game)))
          ++game->state.flags_left;
      }
      break;
    case ACTION_CLICK:
      handleCellClick(game, cell_state, is_bomb); // Complex logic, warrants separate function.
      break;
    case ACTION_QUIT:
      if (doDialog(2, 5, 30, 8, "Are you sure?", "If you quit, your progress will not be saved.", DIALOG_FORM_YES_NO) == DIALOG_YES) {
        setGameState(game, GSTATE_MENU);
        moveCursorTo(game, 0, 0);
      }
      break;
  }
}

void handleCellClick(game_t *game, cell_state_t state, uint8_t is_bomb) {
  uint8_t x = getCursorX(game), y = getCursorY(game);
  if (state == HIDDEN) {
    // If cell is bomb, lose game.
    if (is_bomb)
      setBoardState(game->board, BSTATE_LOSE);

    // If cell has no bomb neighbors, show adjacent cells with no bomb neighbors.
    if (getCellNeighbors(game->board, x, y) == 0)
      __recursiveZeroCellClick(game, x, y);
    else { // Else, just show cell.
      setCellState(game->board, x, y, SHOWN);
      --game->state.hidden_cells;
    }

  } else if (state == SHOWN) {
    uint8_t correctly_flagged_count = 0;

    uint8_t x_lower = (x > 0)?(x - 1):(0);
    uint8_t x_upper = (x < game->board->cols - 1)?(x + 2):(game->board->cols);
    uint8_t y_lower = (y > 0)?(y - 1):(0);
    uint8_t y_upper = (y < game->board->rows - 1)?(y + 2):(game->board->rows);

    for (int i = y_lower; i < y_upper; ++i) {
      for (int j = x_lower; j < x_upper; ++j) {
        if (i == y && j == x) continue;
        if (getCellIsBomb(game->board, j, i) && (getCellState(game->board, j, i) == FLAGGED)) ++correctly_flagged_count;
      }
    }

    if (correctly_flagged_count == getCellNeighbors(game->board, x, y)) {
      for (int i = y_lower; i < y_upper; ++i) {
        for (int j = x_lower; j < x_upper; ++j) {
          if (i == y && j == x) continue;
          __recursiveZeroCellClick(game, j, i);
        }
      }
    }
  }
}
