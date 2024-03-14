#pragma once

#include <assert.h>
#include <stdint.h>
#include <time.h>

typedef enum game_state_t {
  GSTATE_MENU,
  GSTATE_ONGOING,
  GSTATE_END,
  GSTATE_QUIT
} game_state_t;

typedef struct state_t {
  uint8_t started;
  game_state_t game_state;
  time_t start_time;
  int16_t mines_left;
  uint8_t flags_left;
  uint16_t hidden_cells;
} state_t;
