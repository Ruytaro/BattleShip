#include "menu.h"

void menu_init(menu_t* menu, void (*exit_callback)(game_t*)) {
    menu->selected_option = 0; // No option selected
    menu->num_options = 0; // No options added yet
    menu->exit_callback = exit_callback; // Set exit callback
}

void menu_free(menu_t* menu) {
    for (uint8_t i = 0; i < menu->num_options; i++) {
        free(menu->options[i]); // Free each option string
    }
}

void menu_disable(menu_t* menu,bool disable) {
    menu->disabled = disable;
}

void menu_reset(menu_t* menu) {
    menu->selected_option = 0; // Reset selected option
    menu->num_options = 0; // Reset number of options
    for (uint8_t i = 0; i < 10; i++) {
        if (menu->options[i] != NULL) {
            free(menu->options[i]); // Free each option string
        }
    }
}
void menu_add_option(menu_t* menu, const char* option, void (*callback)(game_t*)) {
    if (menu->num_options < 10) {
        menu->options[menu->num_options] = malloc(strlen(option) + 1);
        if (menu->options[menu->num_options] != NULL) {
            strcpy(menu->options[menu->num_options], option);
            menu->num_options++;
        }
        if (callback != NULL) {
            menu->callbacks[menu->num_options - 1] = callback; // Store the callback
        } else {
            menu->callbacks[menu->num_options - 1] = NULL; // No callback
        }
    }
}
void menu_remove_option(menu_t* menu, uint8_t index) {
    if (index < menu->num_options) {
        free(menu->options[index]); // Free the option string
        for (uint8_t i = index; i < menu->num_options - 1; i++) {
            menu->options[i] = menu->options[i + 1]; // Shift options left
        }
        menu->options[menu->num_options - 1] = NULL; // Clear last option
        menu->callbacks[index] = NULL; // Clear callback for removed option
        menu->num_options--;
    }
}

void menu_update_option(menu_t* menu, uint8_t index, const char* new_option, void (*callback)(game_t*)) {
    if (index < menu->num_options) {
        free(menu->options[index]); // Free old option string
        menu->options[index] = malloc(strlen(new_option) + 1);
        if (menu->options[index] != NULL) {
            strcpy(menu->options[index], new_option); // Set new option string
        }
        menu->callbacks[index] = callback; // Update callback
    }
}

void menu_select_option(menu_t* menu, uint8_t index) {
    if (index < menu->num_options) {
        menu->selected_option = index; // Set selected option
    }
}
void menu_draw(const menu_t* menu) {
    consoleClear(); // Clear the console for drawing
    for (uint8_t i = 0; i < menu->num_options; i++) {
        if (i == menu->selected_option) {
            printf("-> %s\n", menu->options[i]); // Highlight selected option
        } else {
            printf("   %s\n", menu->options[i]); // Regular option
        }
    }
}
void menu_handle_input(menu_t* menu, uint16_t input) {
    if (input & KEY_UP) {
        if (menu->selected_option > 0) {
            menu->selected_option--; // Move up in the menu
        }
    } else if (input & KEY_DOWN) {
        if (menu->selected_option < menu->num_options - 1) {
            menu->selected_option++; // Move down in the menu
        }
    } else if (input & KEY_A) {
        if (menu->callbacks[menu->selected_option] != NULL) {
            menu->callbacks[menu->selected_option](menu->game); // Call the callback function
        }
    } else if (input & KEY_B) {
        if (menu->exit_callback != NULL) {
            menu->exit_callback(menu->game); // Call the exit callback if set
        }
    }
}

void menu_set_game(menu_t* menu, game_t* game) {
    menu->game = game; // Set the game context for the menu
}