#pragma once

#include <stdio.h>
#include "ANSI_ESC/ansi.h"
#include "game.h"

#define CHAR_HIDDEN '#'
#define CHAR_FLAG 'F'
#define CHAR_BOMB '*'

#define CELL_X_SPACING 3
#define CELL_Y_SPACING 1

#define PADDING_Y 2
#define PADDING_X 2

#define COLOR_HIDDEN ESC_BRIGHT_BLACK
#define COLOR_FLAGGED ESC_BRIGHT_REDBG

void draw(game_t *game);

extern const char *NEIGHBOR_COLORS[];
extern const char NEIGHBOR_CHARS[];
