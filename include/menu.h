#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <nds.h>


#ifndef MENU_H
#define MENU_H

typedef struct game game_t; // Forward declaration of game_t

typedef struct 
{
    uint8_t state;           // Current menu state
    uint8_t selected_option; // Index of the currently selected menu option
    char* options[10];       // Array of menu options (up to 10 options, each up to 20 characters)
    uint8_t num_options;     // Number of options in the menu
    void (*callbacks[10])(game_t*); // Array of function pointers for option callbacks
    void (*exit_callback)(game_t*); // Callback for exiting the menu
    game_t* game;           // Pointer to the game structure for context
} menu_t;

void menu_init(menu_t*, void (*exit_callback)(game_t*));
void menu_free(menu_t*);
void menu_reset(menu_t*);
void menu_add_option(menu_t*, const char* option,void (*callback)(game_t*));
void menu_update_option(menu_t*, uint8_t index, const char* new_option, void (*callback)(game_t*));
void menu_remove_option(menu_t*, uint8_t index);
void menu_select_option(menu_t*, uint8_t index);
void menu_draw(const menu_t* menu);
void menu_handle_input(menu_t* menu, uint16_t input);
void menu_set_game(menu_t* menu, game_t* game);


#include "game.h"
#endif