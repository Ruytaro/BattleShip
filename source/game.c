#include "game.h"

uint8_t game_state;

void game_init() {
    // Initialize game state
    game_state = GAME_STATE_INIT;

    // Initialize boards and fleet
    board_init();
    fleet_init();
}