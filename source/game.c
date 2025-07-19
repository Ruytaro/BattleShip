#include "game.h"

// set game name for online
void game_set_name(game_t *game) {
    u8 chars = PersonalData->nameLen;
    u8 bytes_in = chars * 2;
    u8 utf8_len = bytes_in + 1;
    if (chars <= 0) {
        game->player_name = "Player";
        return;
    }
    char *utf8 = calloc(utf8_len,1);
    if (utf16_to_utf8(utf8,utf8_len,(char16_t *)PersonalData->name,bytes_in)>0){
        game->player_name = utf8;
        return;
    }
    game->player_name = "Player";
}

// init game
void game_init(game_t *game) {
    game->state = GAME_STATE_MENU;
    game_set_name(game);
    setup_main_menu(game);
    menu_disable(&game->menu,false);
}

// setup main menu
void setup_main_menu(game_t* game) {
    menu_init(game, NULL);  
    menu_add_option(&game->menu, "Play game",setup_play_menu); 
    menu_add_option(&game->menu, "Settings",setup_settings_menu);
    menu_add_option(&game->menu, "Exit",NULL);
}

// setup play menu
void setup_play_menu(game_t* game) {
    nifi_deinit(game);
    game->state = GAME_STATE_MENU;
    menu_init(game, setup_main_menu);
    menu_add_option(&game->menu, "Host Game", game_start_host);
    menu_add_option(&game->menu, "Join Game", game_search_host);
    menu_add_option(&game->menu, "Back to Main Menu", setup_main_menu);
}

// setup game as host
void game_start_host(game_t* game) {
    nifi_init(game,true);
    menu_init(game, setup_play_menu);
    menu_add_option(&game->menu, "Back", setup_play_menu);
    game->state = GAME_STATE_WAIT_CLIENT;
}

// setup game as client
void game_search_host(game_t* game) {
    nifi_init(game,false);
    menu_init(game, setup_play_menu);
    menu_add_option(&game->menu, "Back", setup_play_menu);
    game->state = GAME_STATE_SEARCH_HOST;
}

// setup config menu
void setup_settings_menu(game_t* game) {
    menu_init(game, setup_main_menu);
    menu_add_option(&game->menu, game->is_sound_on ? "Sound: [ON]/OFF" : "Sound: ON/[OFF]",game_sound_toggle);
    menu_add_option(&game->menu, "Back to Main Menu",setup_main_menu);
}

// sound toggle
void game_sound_toggle(game_t* game) {
    game->is_sound_on = !game->is_sound_on;
    menu_update_option(&game->menu, 0, game->is_sound_on ? "Sound: [ON]/OFF" : "Sound: ON/[OFF]",game_sound_toggle);
}

/// @brief 
/// @param game 
void game_connect(game_t* game) {
    nifi_connect(game);
}

// update logic
void game_update(game_t *game,input_t *input) {
    if (!game->menu.disabled)
        menu_handle_input(game, input->keys);
    switch (game->state) {
    case GAME_STATE_SEARCH_HOST:
        nifi_scanAPs(game);
        nifi_updateAPs(game);
        break;
    case GAME_STATE_WAIT_CLIENT:
        nifi_check_clients(game);
        break;
    case GAME_STATE_INITIALIZING:
        game_init_boards(game);
        break;
    case GAME_STATE_SETUP:
        menu_disable(&game->menu,true);
        nifi_check_conexion(game);
    default:
        break;
    }
}

// draw login
void game_draw(game_t *game) {
    consoleClear(); // Clear the console for drawing
    if (!game->menu.disabled)
        menu_draw(&game->menu);
    switch (game->state) {
    case GAME_STATE_WAIT_CLIENT:
        printf("Game name: %s\n",game->player_name);
        printf("Waiting for clients...\n");
        break;
    case GAME_STATE_SETUP:
        printf("Wohooooooo!");
        break;
    default:
        break;    
    }
}

// inits game boards
void game_init_boards(game_t* game) {
    game->board = board_init();
    game->fleet = fleet_init();
    game->enemy_board = board_init();
    game->enemy_fleet = fleet_init();
    game->state = GAME_STATE_SETUP;
    game->cursor.active=1;
}

// frees game
void game_free(game_t *game) {
    if (game == NULL)
      return;
    if (game->board)
        free(game->board);
    if (game->enemy_board)
        free(game->enemy_board);
    if (game->fleet)
        free(game->fleet);
}

// resets game
void game_reset(game_t *game) {
    if (game == NULL)
      return;
    if (game->board)
        board_reset(game->board);
    if (game->enemy_board)
        board_reset(game->enemy_board);
    if (game->fleet)
        fleet_reset(game->fleet); 
    if (game->enemy_fleet)
        fleet_reset(game->enemy_fleet);
    game->state = GAME_STATE_MENU;
}