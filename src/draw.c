#include "draw.h"

void drawBoard(board_t *board) {
    uint8_t rows = board->rows;
    uint8_t cols = board->cols;
    printf("\n");
    for (int i = 0; i < board->rows; i++) {
        printf(" ");
        for (int j = 0; j < board->cols; j++) {
            switch (board->cells[board->rows*i + j].state) {
                case HIDDEN: printf("%c", CHAR_HIDDEN); break;
                case SHOWN: printf("%1d", board->cells[board->rows*i + j].neighbors); break;
                case FLAGGED: printf("%c", CHAR_FLAG); break;
            }
            printf(" ");
        }
        printf("\n\n");
    }
}
