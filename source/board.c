#include "board.h"

square_t *board_init() {
  square_t *board = (square_t *)calloc(100, sizeof(square_t));
  if (board == NULL) {
    exit(EXIT_FAILURE);
  }
  return board;
}

void board_free(square_t *board) {
  free(board);
  board = NULL;
}

void board_reset(square_t *board) {
  for (int i = 0; i < 100; i++) {
    board[i].revealed = 0;
    board[i].state = FOGOFWAR;
    board[i].ship = 0;
  }
}

uint8_t place_ship(square_t *board, uint8_t index, ship_t *ship) {
  if (index > 100) {
    return 1;
  }
  if (ship == NULL || ship->cells == NULL) {
    return 2;
  }
  int size = ship->length + 2;

  for (int i = 0; i < size; i++) {
  }
  return 0; // Success
}

void board_draw(square_t *board, bool reveal) {
  if (board == NULL) {
    return;
  }
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      square_t *square = &board[i * 10 + j];
      switch (square->state) {
      case SHIP_DAMAGED:
        printf("x");
        break;
      case SHIP_SHUNKED:
        printf("X");
        break;
      case WATER:
        printf("W");
        break;
      case SHIP_INTACT:
        printf("O");
        break;
      case FOGOFWAR:
        printf("?");
        break;
      }
    }
    printf("\n");
  }
}