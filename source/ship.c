#include "ship.h"

ship_t* ship_init(uint8_t ship_id, uint8_t length) {
    ship_t* ship = (ship_t*)calloc(1, sizeof(ship_t));
    if (ship == NULL) {
        exit(EXIT_FAILURE);
    }
    ship->ship_id = ship_id;
    ship->length = length + 2; // Adjust length to include additional bits
    ship->status = STORED;
    ship->cells = (square_t**)calloc(ship->length, sizeof(square_t));
    if (ship->cells == NULL) {
        free(ship);
        exit(EXIT_FAILURE);
    }
    return ship;
}

void ship_free(ship_t* ship) {
    if (ship == NULL) {
        return;
    }
    if (ship->cells != NULL) {
        free(ship->cells);
        ship->cells = NULL;
    }
    free(ship);
}

void ship_reset(ship_t* ship) {
    if (ship == NULL) {
        return;
    }
    ship->status = STORED;
    for (uint8_t i = 0; i < ship->length; i++) {
        ship->cells[i]->revealed = 0;
        ship->cells[i]->state = FOGOFWAR;
        ship->cells[i]->ship = 0;
        ship->cells[i]=NULL; // Reset the cell pointer
    }
}