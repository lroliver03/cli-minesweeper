#pragma once

#include <stdlib.h>
#include <stdint.h>
#include "mine.h"

typedef enum board_state_t {
  BSTATE_UNINIT,
  BSTATE_ACTIVE,
  BSTATE_WIN,
  BSTATE_LOSE
} board_state_t;

typedef struct board_t {
  uint8_t rows, cols; // Board won't be bigger than 255x255 cells.
  cell_t *cells;
  board_state_t state;
} board_t;

board_t *createBoard(uint8_t rows, uint8_t cols);
void deleteBoard(board_t *board);
void resetBoard(board_t *board, uint8_t rows, uint8_t cols);
board_state_t getBoardState(board_t *board);
void setBoardState(board_t *board, board_state_t state);
cell_state_t getCellState(board_t *board, uint8_t x, uint8_t y);
uint8_t getCellIsBomb(board_t *board, uint8_t x, uint8_t y);
uint8_t getCellNeighbors(board_t *board, uint8_t x, uint8_t y);
void setCellState(board_t *board, uint8_t x, uint8_t y, cell_state_t state);
void setCellIsBomb(board_t *board, uint8_t x, uint8_t y, uint8_t is_bomb);