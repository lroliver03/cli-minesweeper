// #include <stdio.h>
#include <stdio.h>
#include "game.h"

#define KEY_FLAG 'f'
#define KEY_FLAG_UPPERCASE 'F'
#define KEY_CLICK ' '
#define KEY_QUIT 'q'
#define KEY_QUIT_UPPERCASE 'Q'

typedef enum control_t {
  MOVE_UP,
  MOVE_DOWN,
  MOVE_LEFT,
  MOVE_RIGHT,
  ACTION_FLAG,
  ACTION_CLICK,
  ACTION_QUIT,
  ACTION_INVALID
} control_t;

control_t getInput();
void handleInput(game_t *game, control_t input);
void handleCellClick(game_t *game, cell_state_t state, uint8_t is_bomb);
void __recursiveZeroCellClick(game_t *game, uint8_t x, uint8_t y);
