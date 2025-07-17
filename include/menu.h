#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <nds.h>



#ifndef MENU_H
#define MENU_H
typedef struct game game_t;

typedef struct 
{
    uint8_t selected_option; // Index of the currently selected menu option
    char* labels[10];       // Array of menu options (up to 10 options)
    uint8_t num_options;     // Number of options in the menu
    void (*callbacks[10])(game_t*); // Array of function pointers for option callbacks
    void (*exit_callback)(game_t*); // Callback for exiting the menu
    bool disabled;         // Flag to disable the menu
} menu_t;

void menu_init(game_t*, void (*exit_callback)(game_t*));
void menu_free(menu_t*);
void menu_reset(menu_t*);
void menu_add_option(menu_t*, const char* option,void (*callback)(game_t*));
void menu_insert_option(menu_t*, u8, const char* option,void (*callback)(game_t*));
void menu_update_option(menu_t*, uint8_t index, const char* new_option, void (*callback)(game_t*));
void menu_remove_option(menu_t*, uint8_t index);
void menu_select_option(menu_t*, uint8_t index);
void menu_draw(const menu_t* menu);
void menu_handle_input(game_t* game, uint16_t input);
void menu_disable(menu_t* menu, bool);


#include "game.h"
#endif