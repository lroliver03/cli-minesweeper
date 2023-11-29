#pragma once

#include <stdint.h>

/** Mine state enum
 * `HIDDEN`: cell has not been clicked
 * `SHOWN`: cell has been clicked
 * `FLAGGED`: cell has been flagged
*/
typedef enum cell_state_t {
    HIDDEN,
    SHOWN,
    FLAGGED
} cell_state_t;

typedef struct cell_t {
    cell_state_t state;
    uint8_t is_bomb;
    uint8_t neighbors;
} cell_t;