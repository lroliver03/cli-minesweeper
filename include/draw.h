#pragma once

#include <stdio.h>
#include "ANSI_ESC/colors.h"
#include "ANSI_ESC/format.h"
#include "game.h"

#define CHAR_HIDDEN '#'
#define CHAR_FLAG 'F'
#define CHAR_BOMB '*'
#define CELL_SPACING 2

void draw(game_t *game);

extern const char *NEIGHBOR_COLORS[];
extern const char NEIGHBOR_CHARS[];
