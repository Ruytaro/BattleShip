#include <stdint.h>
#include "square.h"
typedef struct
{
    uint8_t ship_id:4; // 4 bits for ship ID (1-15)
    uint8_t lenght:2; // 2 bits for ship length (0-3) + 2
    uint8_t status:2;
    square_t* cells; // Pointer to an array of cells occupied by the ship
}ship_t;

typedef enum{
    STORED = 0, // Ship is stored and not placed on the board
    PLACED = 1, // Ship is placed on the board
    DAMAGED = 2, // Ship is damaged
    SUNK = 3, // Ship is sunk
} ShipStatus;
