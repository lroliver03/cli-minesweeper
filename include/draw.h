#include <stdio.h>
#include "ANSI_ESC/colors.h"
#include "ANSI_ESC/format.h"
#include "board.h"

#define CHAR_HIDDEN '#'
#define CHAR_FLAG 'F'
#define CHAR_BOMB '*'

void drawBoard(board_t *board);
