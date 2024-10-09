#pragma once

#include <stdio.h>
#include "draw.h"
#include "dialog.h"
#include "input.h"
#include "game.h"

void handleMenuInput(game_t *game, control_t input);
void handleSettingsInput(game_t *game, control_t input);
void handleGameInput(game_t *game, control_t input);
void handleCellClick(game_t *game, cell_state_t state, uint8_t is_bomb);
