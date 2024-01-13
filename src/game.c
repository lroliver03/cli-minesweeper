#include "game.h"

game_t *createGame(uint8_t rows, uint8_t cols, uint8_t mines) {
  game_t *game = malloc(sizeof(game_t));
  game->cursor.x = cols / 2;
  game->cursor.y = rows / 2;
  game->mines = mines;
  game->state.game_state = GSTATE_ONGOING;
  game->state.mines_left = mines;
  game->state.flags_left = mines;
  game->state.hidden_cells = rows * cols - mines;
  time(&(game->state.start_time));
  game->board = createBoard(rows, cols);

  assert((mines > 0) && "The board must have at least one mine!");
  assert((mines < rows * cols) && "There must be less mines than cells in a board!");

  uint8_t mine_counter = mines;
  while (mine_counter > 0) {
    uint8_t mine_x = rand() % cols, mine_y = rand() % rows;
    if (!getCellIsBomb(game->board, mine_x, mine_y)) {
      setCellIsBomb(game->board, mine_x, mine_y, 1);
      --mine_counter;
    }
  }

  setBoardState(game->board, BSTATE_NONE);
  return game;
}

void deleteGame(game_t *game) {
  deleteBoard(game->board);
  free(game);
}

game_state_t getGameState(game_t *game) {
  return game->state.game_state;
}

uint8_t getTotalMines(game_t *game) {
  return game->mines;
}

int16_t getRemainingMines(game_t *game) {
  return game->state.mines_left;
}

time_t getTimeSinceStart(game_t *game) {
  return time(NULL) - game->state.start_time;
}

void setGameState(game_t *game, game_state_t state) {
  game->state.game_state = state;
}

void moveCursor(game_t *game, int16_t dx, int16_t dy) {
  moveCursorTo(game, game->cursor.x + dx, game->cursor.y + dy);
}

void moveCursorTo(game_t *game, uint8_t x, uint8_t y) {
  game->cursor.x = x;
  game->cursor.y = y;

  if (game->cursor.x < 0)
    game->cursor.x = 0;
  else if (game->cursor.x >= game->board->cols)
    game->cursor.x = game->board->cols - 1;
  
  if (game->cursor.y < 0)
    game->cursor.y = 0;
  else if (game->cursor.y >= game->board->rows)
    game->cursor.y = game->board->rows - 1;
}

uint8_t getCursorX(game_t *game) {
  return game->cursor.x;
}

uint8_t getCursorY(game_t *game) {
  return game->cursor.y;
}
