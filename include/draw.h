#pragma once

#include <stdio.h>
#include "ANSI_ESC/ansi.h"
#include "charset/border.h"
#include "charset/cells.h"
#include "dialog.h"
#include "game.h"

extern char *MENU_TITLE;

#define CELL_X_SPACING 3
#define CELL_Y_SPACING 1

#define PADDING_Y 0
#define PADDING_X 1
#define OFFSET_Y 1
#define OFFSET_X 1

#define COLOR_HIDDEN ESC_BRIGHT_BLACK
#define COLOR_FLAGGED ESC_BRIGHT_REDBG

#define MAX_MAINMENU_OPTIONS 3

void drawMenu(game_t *game);
void drawSettings(game_t *game);
void drawBoard(game_t *game);

extern const char *NEIGHBOR_COLORS[];
extern const char NEIGHBOR_CHARS[];
