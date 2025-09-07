#include <stdint.h>
#include "square.h"

#ifndef SHIP_H
#define SHIP_H
typedef struct {
    uint8_t ship_id:4, // 4 bits for ship ID (1-15)
            length:2,  // 2 bits for ship length (0-3) + 2
            status:2;  // ship status (0-3)
    square_t** cells;
} ship_t;

typedef enum{
    STORED = 0, // Ship is stored and not placed on the board
    PLACED = 1, // Ship is placed on the board
    DAMAGED = 2, // Ship is damaged
    SUNK = 3, // Ship is sunk
} ShipStatus;

ship_t* ship_init(uint8_t ship_id, uint8_t length);
void ship_free(ship_t* ship);
void ship_reset(ship_t* ship);

#endif