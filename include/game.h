#pragma once

#include <stdlib.h>
#include <stdint.h>
#include "board.h"

typedef enum game_state_t {
    ONGOING, // Game running
    QUIT // Quitting game
} game_state_t;

typedef struct cursor_t {
    uint8_t x, y;
} cursor_t;

typedef struct game_t {
    game_state_t state;
    cursor_t cursor;
    float mine_probability; // Between 0.0 and 1.0
    board_t *board;
} game_t;

game_t* createGame(uint8_t rows, uint8_t cols, float mine_probability);
void deleteGame(game_t *game);
game_state_t getGameState(game_t *game);
void setGameState(game_t *game, game_state_t state);

void moveCursor(game_t *game, int16_t dx, int16_t dy);
void moveCursorTo(game_t *game, uint8_t x, uint8_t y);
