#include "board.h"


square_t* my_board = NULL;
square_t* enemy_board = NULL;
ship_t* fleet = NULL;

uint8_t fleet_sizes[] = {0,0,0,0,1,1,1,1,1,2,2,3};

square_t* cursor = NULL;


void board_init() {
    my_board = (square_t*)calloc(100,sizeof(square_t));
    enemy_board =  (square_t*)calloc(100,sizeof(square_t));

    if (my_board == NULL || enemy_board == NULL) {
        exit(EXIT_FAILURE);
    }
    cursor = my_board;
}

void fleet_init() {
    uint8_t fleet_size = sizeof(fleet_sizes);
    fleet = (ship_t*)calloc(fleet_size, sizeof(ship_t));
    if (fleet == NULL) {
        exit(EXIT_FAILURE);
    }
    for (uint8_t i = 0; i < fleet_size; i++)
    {
        fleet[i].ship_id = i + 1;
        fleet[i].lenght= fleet_sizes[i] + 2;
        fleet[i].status = STORED;
        fleet[i].cells = (square_t*)calloc(fleet[i].lenght, sizeof(square_t));
        if (fleet[i].cells == NULL) {
            exit(EXIT_FAILURE);
        }
    }   
}

void board_free() {
    free(my_board);
    free(enemy_board);
    my_board = NULL;
    enemy_board = NULL;
}

void fleet_free() {
    for (int i = 0; i < 10; i++) {
        if (fleet[i].cells != NULL) {
            free(fleet[i].cells);
            fleet[i].cells = NULL;
        }
    }
    free(fleet);
    fleet = NULL;
}

void board_reset() {
    for (int i = 0; i < 100; i++) {
        my_board[i].revealed = 0;
        my_board[i].state = FOGOFWAR;
        my_board[i].ship = 0;

        enemy_board[i].revealed = 0;
        enemy_board[i].state = FOGOFWAR;
        enemy_board[i].ship = 0;
    }
}

void fleet_reset() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < fleet[i].lenght; j++) {
            if (fleet[i].cells != NULL) {
                free(fleet[i].cells);
                fleet[i].cells = NULL;
            }
        }
        fleet[i].ship_id = 0;
        fleet[i].lenght = 0;
        fleet[i].status = STORED;
    }
}

void board_cursor_reset() {
    cursor = my_board;
}

void move_cursor(uint8_t index) {
    if (index < 0 || index >= 100) {
        return; // Invalid index
    }
    cursor = &my_board[index];
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