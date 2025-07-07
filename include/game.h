#include <stdlib.h>
#include <stdbool.h>
#include "board.h"
#include "fleet.h"
#include "input.h"

#ifndef GAME_H
#define GAME_H

#include "menu.h"

typedef enum{
    GAME_STATE_MAIN_MENU,
    GAME_STATE_SETTINGS,
    GAME_STATE_INIT,
    GAME_STATE_SETUP,
    GAME_STATE_PLAYING,
    GAME_STATE_PAUSED,
    GAME_STATE_WIN,
    GME_STATE_LOSE,
} GameState;

typedef struct game{
    uint8_t state;          // Current game state
    square_t* board;        // Player's board
    square_t* enemy_board;  // Enemy's board
    ship_t* fleet;          // Player's fleet
    ship_t* enemy_fleet;    // Enemy's fleet
    bool is_multiplayer;    // Multiplayer mode flag
    bool is_networked;      // Networked game flag
    menu_t menu;            // Game menu
    bool is_sound_on;      // Sound on/off flag
} game_t;

void game_init(game_t*);
void game_free(game_t*);
void game_reset(game_t*);
void game_update(game_t*,input_t*);
void game_draw(game_t*);
void setupMain_menu(game_t* game);
void setupSettings_menu(game_t* game);
void game_init_boards(game_t* game);
void game_sound_toggle(game_t* game);

#endif