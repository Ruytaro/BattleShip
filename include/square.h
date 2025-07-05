#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef SQUARE_H
#define SQUARE_H
typedef enum {
    FOGOFWAR,
    WATER,
    SHIP_INTACT,
    SHIP_DAMAGED,
    SECTION_DAMAGED,
    SHIP_SHUNKED,
} SquareStatus;

typedef struct {
    uint8_t revealed:1; // 0 for unrevealed, 1 for revealed
    uint8_t state:3; // SquareStatus enum values
    uint8_t ship:4; // 1-15 for ship ID, 0 for no ship
} square_t;

#endif