#include "menu.h"
#include "game.h"

void menu_init(game_t* game, void (*exit_callback)(game_t*)) {
    menu_t* menu = &game->menu;
    menu->selected_option = 0; // No option selected
    menu->num_options = 0; // No options added yet
    menu->exit_callback = exit_callback; // Set exit callback
}

void menu_free(menu_t* menu) {
    for (uint8_t i = 0; i < menu->num_options; i++) {
        free(menu->labels[i]); // Free each option string
    }
}

void menu_disable(menu_t* menu,bool disable) {
    menu->disabled = disable;
}

void menu_reset(menu_t* menu) {
    menu->selected_option = 0; // Reset selected option
    menu->num_options = 0; // Reset number of options
    for (uint8_t i = 0; i < 10; i++) {
        if (menu->labels[i] != NULL) {
            free(menu->labels[i]); // Free each option string
        }
    }
}
void menu_add_option(menu_t* menu, const char* option, void (*callback)(game_t*)) {
    if (menu->num_options == 10)
        return;
    menu->labels[menu->num_options] = malloc(strlen(option) + 1);
    if (menu->labels[menu->num_options] != NULL) {
        strcpy(menu->labels[menu->num_options], option);
        menu->num_options++;
    }
    if (callback != NULL) {
        menu->callbacks[menu->num_options - 1] = callback; // Store the callback
    } else {
        menu->callbacks[menu->num_options - 1] = NULL; // No callback
    }   
}

void menu_insert_option(menu_t* menu, u8 index, const char* label, void (*callback)(game_t*)) {
    if (menu->num_options == 10)
        return;
    for (uint8_t i = menu->num_options; i > index; i--) { //move entries arround
        menu->callbacks[i]=menu->callbacks[i-1];
        menu->labels[i]=menu->labels[i-1];
    }
    menu->labels[index] = malloc(strlen(label) + 1);
    if (menu->labels[index] != NULL) {
        strcpy(menu->labels[index], label);
        menu->num_options++;
    }
    if (callback != NULL) {
        menu->callbacks[index] = callback; // Store the callback
    } else {
        menu->callbacks[index] = NULL; // No callback
    }
}

void menu_remove_option(menu_t* menu, uint8_t index) {
    if (index < menu->num_options) {
        free(menu->labels[index]); // Free the option string
        for (uint8_t i = index; i < menu->num_options - 1; i++) { //move entries arround
            menu->labels[i] = menu->labels[i + 1];
            menu->callbacks[i] = menu->callbacks[i + 1];
        }
        menu->labels[menu->num_options - 1] = NULL; // Clear last option
        menu->callbacks[menu->num_options - 1] = NULL; // Clear callback for removed option
        menu->num_options--;
    }
}

void menu_update_option(menu_t* menu, uint8_t index, const char* new_option, void (*callback)(game_t*)) {
    if (index < menu->num_options) {
        free(menu->labels[index]); // Free old option string
        menu->labels[index] = malloc(strlen(new_option) + 1);
        if (menu->labels[index] != NULL) {
            strcpy(menu->labels[index], new_option); // Set new option string
        }
        menu->callbacks[index] = callback; // Update callback
    }
}

void menu_draw(const menu_t* menu) {
    for (uint8_t i = 0; i < menu->num_options; i++) {
        if (i == menu->selected_option) {
            printf("-> %s\n", menu->labels[i]); // Highlight selected option
        } else {
            printf("   %s\n", menu->labels[i]); // Regular option
        }
    }
}

void menu_handle_input(game_t* game, uint16_t input) {
    menu_t* menu = &game->menu;
    if (input & KEY_UP) {
        if (menu->selected_option > 0)
            menu->selected_option--;
    } else if (input & KEY_DOWN) {
        if (menu->selected_option < menu->num_options - 1)
            menu->selected_option++;
    } else if (input & KEY_A) {
        if (menu->callbacks[menu->selected_option] != NULL)
            menu->callbacks[menu->selected_option](game);
    } else if (input & KEY_B) {
        if (menu->exit_callback != NULL)
            menu->exit_callback(game);
    }
}