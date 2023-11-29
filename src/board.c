#include "board.h"

board_t* createBoard(uint8_t rows, uint8_t cols) {
    board_t *b = malloc(sizeof(board_t));
    b->rows = rows;
    b->cols = cols;
    b->state = INACTIVE;
    b->cells = calloc(sizeof(cell_t), rows*cols);
    for (int i = 0; i < b->rows; i++) {
        for (int j = 0; j < b->cols; j++) {
            b->cells[b->rows*i + j].state = HIDDEN;
            b->cells[b->rows*i + j].is_bomb = 0;
            b->cells[b->rows*i + j].neighbors = 0;
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
    board->state = INACTIVE;
    free(board->cells);
    board->cells = calloc(sizeof(cell_t), rows*cols);
    for (int i = 0; i < board->rows; i++) {
        for (int j = 0; j < board->cols; j++) {
            board->cells[board->rows*i + j].state = HIDDEN;
            board->cells[board->rows*i + j].is_bomb = 0;
            board->cells[board->rows*i + j].neighbors = 0;
        }
    }
}

board_state_t getBoardState(board_t *board) {
    return board->state;
}

cell_state_t getCellState(board_t *board, uint8_t x, uint8_t y) {
    return board->cells[board->rows*y + x].state;
}

uint8_t getCellIsBomb(board_t *board, uint8_t x, uint8_t y) {
    return board->cells[board->rows*y + x].is_bomb;
}

uint8_t getCellNeighbors(board_t *board, uint8_t x, uint8_t y) {
    return board->cells[board->rows*y + x].neighbors;
}

void setCellState(board_t *board, uint8_t x, uint8_t y, cell_state_t state) {
    board->cells[board->rows*y + x].state = state;
}

void setCellIsBomb(board_t *board, uint8_t x, uint8_t y, uint8_t is_bomb) {
    // set bomb, update neighbors.
    if (board->cells[board->rows*y + x].is_bomb == is_bomb) return;
    board->cells[board->rows*y + x].is_bomb = 1;
}
