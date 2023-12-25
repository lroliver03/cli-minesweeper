#include "board.h"

board_t *createBoard(uint8_t rows, uint8_t cols) {
  board_t *b = malloc(sizeof(board_t));
  b->rows = rows;
  b->cols = cols;
  b->state = NONE;
  b->cells = calloc(sizeof(cell_t), rows * cols);
  for (int i = 0; i < b->rows; i++) {
    for (int j = 0; j < b->cols; j++) {
      b->cells[b->rows * i + j].state = HIDDEN;
      b->cells[b->rows * i + j].is_bomb = 0;
      b->cells[b->rows * i + j].neighbors = 0;
    }
  }
  return b;
}

void deleteBoard(board_t *board) {
  free(board->cells);
  free(board);
}

void resetBoard(board_t *board, uint8_t rows, uint8_t cols) {
  board->rows = rows;
  board->cols = cols;
  board->state = NONE;
  free(board->cells);
  board->cells = calloc(sizeof(cell_t), rows * cols);
  for (int i = 0; i < board->rows; i++) {
    for (int j = 0; j < board->cols; j++) {
      board->cells[board->rows * i + j].state = HIDDEN;
      board->cells[board->rows * i + j].is_bomb = 0;
      board->cells[board->rows * i + j].neighbors = 0;
    }
  }
}

board_state_t getBoardState(board_t *board) {
  return board->state;
}

void setBoardState(board_t *board, board_state_t state) {
  board->state = state;
}

cell_state_t getCellState(board_t *board, uint8_t x, uint8_t y) {
  return board->cells[board->rows * y + x].state;
}

uint8_t getCellIsBomb(board_t *board, uint8_t x, uint8_t y) {
  return board->cells[board->rows * y + x].is_bomb;
}

uint8_t getCellNeighbors(board_t *board, uint8_t x, uint8_t y) {
  return board->cells[board->rows * y + x].neighbors;
}

void setCellState(board_t *board, uint8_t x, uint8_t y, cell_state_t state) {
  board->cells[board->rows * y + x].state = state;
}

void setCellIsBomb(board_t *board, uint8_t x, uint8_t y, uint8_t is_bomb) {
  // set bomb, update neighbors.
  if (board->cells[board->rows * y + x].is_bomb == is_bomb)
    return;
  board->cells[board->rows * y + x].is_bomb = is_bomb;

  uint8_t x_lower = (x > 0)?(x - 1):(0);
  uint8_t x_upper = (x < board->cols - 1)?(x + 2):(board->cols);
  uint8_t y_lower = (y > 0)?(y - 1):(0);
  uint8_t y_upper = (y < board->rows - 1)?(y + 2):(board->rows);

  for (int i = y_lower; i < y_upper; ++i) {
    for (int j = x_lower; j < x_upper; ++j) {
      if (i == y && j == x) continue;
      if (is_bomb)
        ++board->cells[board->rows * i + j].neighbors;
      else
        --board->cells[board->rows * i + j].neighbors;
    }
  }
}

// void setCellNeighbors(board_t *board, uint8_t x, uint8_t y, uint8_t neighbors) {
//   board->cells[board->rows * y + x].neighbors = neighbors;
// }

// void updateNeighbors(board_t *board) {
//   uint8_t x_lower, x_upper, y_lower, y_upper; // 3x3 bounds
  
//   for (int i = 0; i < board->rows; ++i) {
//     for (int j = 0; j < board->cols; ++j) {

//       y_lower = (i > 0)?(i - 1):(0);
//       y_upper = (i < board->rows - 1)?(board->rows):(i + 1);
//       x_lower = (j > 0)?(j - 1):(0);
//       x_upper = (j < board->cols - 1)?(board->cols):(j + 1);

//       for (int y = y_lower; y <= y_upper; ++y) {
//         for (int x = x_lower; x <= x_upper; ++x) {
//           if (x == j && y == i) continue;
//           if (getCellIsBomb(board, x, y))
//             setCellNeighbors(board, j, i, getCellNeighbors(board, j, i) + 1);
//         }
//       }

//     }
//   }
// }
