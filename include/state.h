#pragma once

#include <assert.h>
#include <stdint.h>
#include <time.h>

typedef enum game_state_t {
  MENU,
  ONGOING,
  END,
  QUIT
} game_state_t;

typedef struct state_t {
  game_state_t game_state;
  time_t start_time;
  int16_t mines_left;
} state_t;
