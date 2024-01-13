#pragma once

#include <stdio.h>
#include "ANSI_ESC/ansi.h"
#include "charset/border.h"
#include "charset/cells.h"
#include "dialog.h"
#include "game.h"

#define MENU_TITLE \
" _____       _     _____                           \n" \
"|   __|_ _ _| |___|   __|_ _ _ ___ ___ ___ ___ ___ \n" \
"|__   | | | . | . |__   | | | | -_| -_| . | -_|  _|\n" \
"|_____|___|___|___|_____|_____|___|___|  _|___|_|  \n" \
"                                      |_|          \n"

#define CELL_X_SPACING 3
#define CELL_Y_SPACING 1

#define PADDING_Y 0
#define PADDING_X 1
#define OFFSET_Y 1
#define OFFSET_X 1

#define COLOR_HIDDEN ESC_BRIGHT_BLACK
#define COLOR_FLAGGED ESC_BRIGHT_REDBG

void drawMenu(game_t *game);
void drawBoard(game_t *game);

extern const char *NEIGHBOR_COLORS[];
extern const char NEIGHBOR_CHARS[];
