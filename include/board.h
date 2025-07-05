#include <stdlib.h>
#include <stdbool.h>
#include "ship.h"

square_t* board_init();
void board_free(square_t*);
void board_reset(square_t*);

int place_ship(square_t* board,uint8_t index,ship_t* ship);