#include "draw.h"

void draw(game_t *game) {
  uint8_t rows = game->board->rows;
  uint8_t cols = game->board->cols;
  printf("\033[2J");
  // printf("\033[0;0H");
  ESC_GOTO(0, 0);

  // Draw game stats.
  printf("Mines remaining: %d", game->state.mines_left);
  printf("\nDEBUG: game->state.hidden_cells == %d", game->state.hidden_cells);

  // Draw board.
  for (int i = 0; i < game->board->rows; i++) {
    for (int j = 0; j < game->board->cols; j++) {
      uint8_t is_cursor = (i == getCursorY(game) && j == getCursorX(game));

      if (is_cursor) {
        ESC_GOTO(CELL_X_SPACING*j, CELL_Y_SPACING*i + 4);
        printf("< >");
      }

      // printf("\033[%d;%dH", CELL_Y_SPACING * i + 3, CELL_X_SPACING * j + 1);
      ESC_GOTO(CELL_X_SPACING*j + 1, CELL_Y_SPACING*i + 4);

      switch (getCellState(game->board, j, i)) {
        case HIDDEN:
          printf("%s%c%s", COLOR_HIDDEN, CHAR_HIDDEN, ESC_RESET);
          break;
        case SHOWN:
          if (getCellIsBomb(game->board, j, i))
            printf("%s%c%s", ESC_REDBG, CHAR_BOMB, ESC_RESET);
          else {
            uint8_t neighbors = getCellNeighbors(game->board, j, i);
            printf("%s%c%s", NEIGHBOR_COLORS[neighbors], NEIGHBOR_CHARS[neighbors], ESC_RESET);
          }
          break;
        case FLAGGED:
          printf("%s%s%c%s", COLOR_FLAGGED, ESC_BOLD, CHAR_FLAG, ESC_RESET);
          break;
      }
    }
  }
  printf("\n\n");
}

const char *NEIGHBOR_COLORS[] = {
  ESC_BRIGHT_BLACK,
  ESC_BRIGHT_BLUE,
  ESC_BRIGHT_GREEN,
  ESC_BRIGHT_RED,
  ESC_BLUE,
  ESC_RED,
  ESC_CYAN,
  ESC_WHITE,
  ESC_BRIGHT_BLACK
};

const char NEIGHBOR_CHARS[] = {
  '.',
  '1',
  '2',
  '3',
  '4',
  '5',
  '6',
  '7',
  '8'
};
