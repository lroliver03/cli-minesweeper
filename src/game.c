#include "game.h"

game_t* createGame(uint8_t rows, uint8_t cols, float mine_probability) {
    game_t *game = malloc(sizeof(game_t));
    game->state = ONGOING;
    game->cursor.x = cols/2;
    game->cursor.y = rows/2;
    game->mine_probability = mine_probability;
    game->board = createBoard(rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            setCellState(game->board, i, j, HIDDEN);
            setCellIsBomb(game->board, i, j, (rand()/(float)RAND_MAX < mine_probability));
        }
    }

    setBoardState(game->board, NONE);
}

void deleteGame(game_t *game) {
    deleteBoard(game->board);
    free(game);
}

game_state_t getGameState(game_t *game) {
    return game->state;
}

void setGameState(game_t *game, game_state_t state) {
    game->state = state;
}

void moveCursor(game_t *game, int16_t dx, int16_t dy) {
    moveCursorTo(game, game->cursor.x + dx, game->cursor.y + dy);
}

void moveCursorTo(game_t *game, uint8_t x, uint8_t y) {
    game->cursor.x = x;
    game->cursor.y = y;
    if (game->cursor.x < 0) game->cursor.x = 0;
    else if (game->cursor.x >= game->board->cols) game->cursor.x = game->board->cols - 1;
    if (game->cursor.y < 0) game->cursor.y = 0;
    else if (game->cursor.y >= game->board->rows) game->cursor.y = game->board->rows - 1;
}
