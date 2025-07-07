#include "game.h"


void game_init(game_t *game)
{
    game->state = GAME_STATE_MENU;
    game->is_networked = true;
    setup_main_menu(game);
    menu_disable(&game->menu,false);
}

void game_start_host(game_t* game)
{
    nifi_init(game,true);
    menu_init(&game->menu, setup_play_menu);
    menu_add_option(&game->menu, "Back", setup_play_menu);
    game->state = GAME_STATE_WAIT_CLIENT;
}

void game_search_host(game_t* game)
{
    nifi_init(game,false);
    menu_init(&game->menu, setup_play_menu);
    menu_add_option(&game->menu, "Back", setup_play_menu);
    game->state = GAME_STATE_SEARCH_HOST;
}

void game_init_boards(game_t* game)
{
    game->board = board_init();
    game->fleet = fleet_init();
    game->enemy_board = board_init();
    game->enemy_fleet = fleet_init();
    game->state = GAME_STATE_SETUP;
}

void setup_play_menu(game_t* game) {
    menu_init(&game->menu, setup_main_menu);
    menu_add_option(&game->menu, "Host Game", game_start_host);
    menu_add_option(&game->menu, "Join Game", game_search_host);
    menu_add_option(&game->menu, "Back to Main Menu", setup_main_menu);
}

void setup_main_menu(game_t* game) {
    menu_init(&game->menu,NULL);  
    menu_add_option(&game->menu, "Play game",setup_play_menu); 
    menu_add_option(&game->menu, "Settings",setup_settings_menu);
    menu_add_option(&game->menu, "Exit",NULL);
    menu_set_game(&game->menu, game);
}

void setup_settings_menu(game_t* game) {
    menu_init(&game->menu, setup_main_menu);
    menu_add_option(&game->menu, game->is_sound_on ? "Sound: [ON]/OFF" : "Sound: ON/[OFF]",game_sound_toggle);
    menu_add_option(&game->menu, "Back to Main Menu",setup_main_menu);
}

void game_sound_toggle(game_t* game) {
    game->is_sound_on = !game->is_sound_on;
    menu_update_option(&game->menu, 0, game->is_sound_on ? "Sound: [ON]/OFF" : "Sound: ON/[OFF]",game_sound_toggle);
}

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
    game->is_networked = true;
}

void game_update(game_t *game,input_t *input) {
    if (!game->menu.disabled)
        menu_handle_input(&game->menu, input->keys);
}

void game_draw(game_t *game) {
    if (!game->menu.disabled)
        menu_draw(&game->menu);
}