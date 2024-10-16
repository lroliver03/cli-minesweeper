#include "draw.h"

static const char *MAINMENU_OPTIONS[] = {
  "PLAY",
  "SETTINGS",
  "QUIT"
};

uint8_t title_selected;
uint8_t CURRENT_TITLE;

void drawMenu(game_t *game) {
  ESC_ERASEALL();
  ESC_GOTO(0, 0);

  // Make title bold.
  printf("%s", ESC_BOLD);

  // Get random title.
  FILE *fptr = fopen("../config/title.txt", "r");

  if (fptr == NULL) {
    printf("Not able to open file.\n");
  }

  unsigned int TITLE_MAX;
  fscanf(fptr, "%d", &TITLE_MAX);
  // printf("TITLE_MAX = %d\n\n", TITLE_MAX); // Debug.

  // If we're supposed to change title, get random index.
  if (game->state.change_title) {
    CURRENT_TITLE = (rand() % TITLE_MAX);
    game->state.change_title = 0;
  }
  title_selected = CURRENT_TITLE;

  char buffer[200];
  while (title_selected >= 0 && fgets(buffer, 200, fptr)) {
    if (buffer[0] == '%') {
      title_selected--;
      continue;
    }
    if (title_selected == 0) printf("%s", buffer);
  }

  fclose(fptr);

  printf("%s\n\n", ESC_RESET);

  for (uint8_t i = 0; i < MAX_MAINMENU_OPTIONS; ++i) {
    if (getCursorY(game) == i)
      printf("%s > ", ESC_BOLD);
    else
      printf("  ");
    printf("%s%s\n", MAINMENU_OPTIONS[i], ESC_RESET);
  }

//   if (getCursorY(game) == 0)
//     printf("%s > ", ESC_BOLD);
//   else
//     printf("  ");
//   printf("PLAY%s\n", ESC_RESET);

//   if (getCursorY(game) == 1)
//     printf("%s > ", ESC_BOLD);
//   else
//     printf("  ");
//   printf("QUIT%s\n", ESC_RESET);
}

void drawSettings(game_t *game) {
  return;
}

void drawBoard(game_t *game) {
  uint8_t rows = game->board->rows;
  uint8_t cols = game->board->cols;
  ESC_ERASEALL();
  // printf("\033[0;0H");
  ESC_GOTO(0, 0);

  // Draw board contents.
  for (int i = 0; i < game->board->rows; i++) {
    for (int j = 0; j < game->board->cols; j++) {
      uint8_t is_cursor = (i == getCursorY(game) && j == getCursorX(game));

      uint16_t pos_x = CELL_X_SPACING*j + PADDING_X + OFFSET_X + 2;
      uint16_t pos_y = CELL_Y_SPACING*i + PADDING_Y + OFFSET_Y + 1;

      if (is_cursor) {
        ESC_GOTO(pos_x - 1, pos_y);
        printf("< >");
      }

      // printf("\033[%d;%dH", CELL_Y_SPACING * i + 3, CELL_X_SPACING * j + 1);
      ESC_GOTO(pos_x, pos_y);

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

  // Draw board frame.
    // Top side: 1x corner, (PADDING_X + game->board->cols*CELL_X_SPACING + PADDING_X)x horizontal, 1x corner
  ESC_GOTO(OFFSET_X, OFFSET_Y);
  putchar(CHAR_BORDER_CORNER);
  for (int i = 0; i < game->board->cols*CELL_X_SPACING + 2*PADDING_X; ++i) putchar(CHAR_BORDER_HORIZONTAL);
  putchar(CHAR_BORDER_CORNER);
  putchar('\n');
    // Left and right sides: (PADDING_Y + game->board->rows*CELL_Y_SPACING + PADDING_Y)x (1x vertical, (PADDING_X + game->board->cols*CELL_X_SPACING + PADDING_X)x blank, 1x vertical)
  for (int i = 0; i < game->board->rows*CELL_Y_SPACING + 2*PADDING_Y; ++i) {
    putchar(CHAR_BORDER_VERTICAL);
    // for (int j = 0; j < game->board->cols*CELL_X_SPACING + 2*PADDING_X; ++j) putchar(' ');
    ESC_GOTO(game->board->cols*CELL_X_SPACING + 2*PADDING_X + OFFSET_X + 1, i + OFFSET_Y + 1);
    putchar(CHAR_BORDER_VERTICAL);
    putchar('\n');
  }
    // Bottom side.
  ESC_GOTO(OFFSET_X, game->board->rows*CELL_Y_SPACING + OFFSET_Y + 2*PADDING_Y + 1);
  putchar(CHAR_BORDER_CORNER);
  for (int i = 0; i < game->board->cols*CELL_X_SPACING + 2*PADDING_X; ++i) putchar(CHAR_BORDER_HORIZONTAL);
  putchar(CHAR_BORDER_CORNER);
  putchar('\n');

  // Draw game stats.
  ESC_GOTO(game->board->cols*CELL_X_SPACING + 2*PADDING_X + OFFSET_X + 3, OFFSET_Y + 1);
  printf("Mines remaining: %d", game->state.mines_left);
  ESC_GOTO(game->board->cols*CELL_X_SPACING + 2*PADDING_X + OFFSET_X + 3, OFFSET_Y + 2);
  time_t game_time = time(NULL) - game->state.start_time;
  printf("Time: %ldmin%lds", game_time/60, game_time%60);
  // printf("\nDEBUG: game->state.hidden_cells == %d", game->state.hidden_cells);

  ESC_GOTO(OFFSET_X, game->board->rows*CELL_Y_SPACING + OFFSET_Y + 2*PADDING_Y + 2);
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
