#include "board.h"


square_t* board_init() {
    square_t* board = (square_t*)calloc(100,sizeof(square_t));
    if (board == NULL) {
        exit(EXIT_FAILURE);
    }
    return board;
}


void board_free(square_t* board) {
    free(board);
    board = NULL;
}


void board_reset(square_t* board) {
    for (int i = 0; i < 100; i++) {
        board[i].revealed = 0;
        board[i].state = FOGOFWAR;
        board[i].ship = 0;
    }
}

int place_ship(square_t* board, uint8_t index, ship_t* ship) {
    if (index < 0 || index >= 100) {
        return 1; // Invalid index
    }
    if (ship == NULL || ship->cells == NULL) {
        return 2; // Invalid ship or ship cells
    }


    return 0; // Success
}