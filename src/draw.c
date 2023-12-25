#include "draw.h"

void draw(game_t *game) {
  uint8_t rows = game->board->rows;
  uint8_t cols = game->board->cols;
  printf("\033[2J");
  printf("\033[0;0H");
  printf("\n");

  for (int i = 0; i < game->board->rows; i++) {
    for (int j = 0; j < game->board->cols; j++) {
      uint8_t is_cursor = (i == getCursorY(game) && j == getCursorX(game));
      printf("\033[%d;%dH", CELL_SPACING * i + 1, CELL_SPACING * j + 1);

      if (is_cursor) 
        printf(ESC_REVERSE);

      switch (getCellState(game->board, j, i)) {
        case HIDDEN:
          printf("%s%c%s", ESC_DIM, CHAR_HIDDEN, ESC_UNDIM);
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
          printf("%s%c%s", ESC_REDBG, CHAR_FLAG, ESC_RESET);
          break;
      }

      if (is_cursor) 
        printf(ESC_UNREVERSE);
    }
  }
}

const char *NEIGHBOR_COLORS[] = {
  ESC_WHITE,
  ESC_BLUE,
  ESC_GREEN,
  ESC_RED,
  ESC_CYAN,
  ESC_MAGENTA,
  ESC_YELLOW,
  ESC_WHITE,
  ESC_WHITE
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
