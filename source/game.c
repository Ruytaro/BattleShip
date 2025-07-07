#include "game.h"


void game_init(game_t *game)
{
    // Initialize game state
    game->state = GAME_STATE_MAIN_MENU;
    setupMain_menu(game);
    // Initialize boards and fleet
    game->board = board_init();
    game->enemy_board = board_init();
    game->fleet = fleet_init();
}

void setupMain_menu(game_t* game)
{
    // Initialize the main menu
    menu_init(&game->menu,NULL);  
    // Add options to the main menu
    menu_add_option(&game->menu, "Start Game",NULL); 
    menu_add_option(&game->menu, "Settings",setupSettings_menu);
    menu_add_option(&game->menu, "Exit",NULL);
    menu_set_game(&game->menu, game);
    
    // Set the initial state of the game
    game->state = GAME_STATE_MAIN_MENU;
}

void setupSettings_menu(game_t* game)
{
    // Initialize the settings menu
    menu_init(&game->menu, setupMain_menu); // Set the exit callback to return to the main menu
    
    // Add options to the settings menu
    menu_add_option(&game->menu, "Sound: ON/[OFF]",game_sound_toggle);
    menu_add_option(&game->menu, "Multiplayer: ON/OFF",NULL);
    menu_add_option(&game->menu, "Networked Game: ON/OFF",NULL);
    menu_add_option(&game->menu, "Back to Main Menu",setupMain_menu);
    menu_set_game(&game->menu, game);

    // Set the initial state of the game
    game->state = GAME_STATE_SETTINGS;
}

void game_sound_toggle(game_t* game)
{
    game->is_sound_on = !game->is_sound_on;
    game->menu.options[0] = game->is_sound_on ? "Sound: [ON]/OFF" : "Sound: ON/[OFF]";
}

void game_free(game_t *game)
{
    // Free boards and fleet
    if (game->board)
    {
        free(game->board);
    }
    if (game->enemy_board)
    {
        free(game->enemy_board);
    }
    if (game->fleet)
    {
        free(game->fleet);
    }
}

void game_reset(game_t *game)
{
    if (game == NULL)
      return;
    // Free existing resources
    if (game->board)
        board_reset(game->board);
    if (game->enemy_board)
        board_reset(game->enemy_board);
    if (game->fleet)
        fleet_reset(game->fleet); 
    if (game->enemy_fleet)
        fleet_reset(game->enemy_fleet);
    // Reset game state
    game->state = GAME_STATE_MAIN_MENU;
    game->is_multiplayer = false;
    game->is_networked = false;
}

void game_update(game_t *game,input_t *input)
{
    // Update game logic based on the current state
    switch (game->state)
    {
        case GAME_STATE_MAIN_MENU:
            menu_handle_input(&game->menu, input->keys);
            break;
        case GAME_STATE_SETTINGS:
            menu_handle_input(&game->menu, input->keys);
            // Handle settings logic
            break;
        case GAME_STATE_INIT:
            // Initialize game resources
            break;
        case GAME_STATE_SETUP:
            // Handle setup logic
            break;
        case GAME_STATE_PLAYING:
            // Handle playing logic
            break;
        case GAME_STATE_PAUSED:
            // Handle paused logic
            break;
        case GAME_STATE_WIN:
            // Handle win logic
            break;
        case GME_STATE_LOSE:
            // Handle lose logic
            break;
    }
}

void game_draw(game_t *game)
{
    // Draw game elements based on the current state
    switch (game->state)
    {
        case GAME_STATE_MAIN_MENU:
            menu_draw(&game->menu);
            break;
        case GAME_STATE_SETTINGS:
            menu_draw(&game->menu);
            // Draw settings
            break;
        case GAME_STATE_INIT:
            // Draw initialization screen
            break;
        case GAME_STATE_SETUP:
            // Draw setup screen
            break;
        case GAME_STATE_PLAYING:
            // Draw playing screen
            break;
        case GAME_STATE_PAUSED:
            // Draw paused screen
            break;
        case GAME_STATE_WIN:
            // Draw win screen
            break;
        case GME_STATE_LOSE:
            // Draw lose screen
            break;
    }
}