#pragma once

#include <stdio.h>
#include "dialog.h"
#include "input.h"
#include "game.h"

void handleInput(game_t *game, control_t input);
void handleCellClick(game_t *game, cell_state_t state, uint8_t is_bomb);
void __recursiveZeroCellClick(game_t *game, uint8_t x, uint8_t y);
