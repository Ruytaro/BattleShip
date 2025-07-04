#include <stdlib.h>
#include <stdbool.h>
#include "square.h"
#include "ship.h"

extern square_t* enemy_board;
extern square_t* my_board;
extern ship_t* fleet;


void board_init();
void fleet_init();
void board_free();
void fleet_free();
void board_reset();
void fleet_reset();

int place_ship(square_t* board,uint8_t index,ship_t* ship);