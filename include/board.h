#include "ship.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

square_t *board_init();
void board_free(square_t *);
void board_reset(square_t *);
void board_draw(square_t *, bool);

uint8_t place_ship(square_t *board, uint8_t index, ship_t *ship);