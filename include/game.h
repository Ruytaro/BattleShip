#include <nds.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "board.h"
#include "cursor.h"
#include "fleet.h"
#include "input.h"
#include "menu.h"
#include "nifi.h"

typedef enum {
  GAME_STATE_MENU,
  GAME_STATE_SEARCH_HOST,
  GAME_STATE_WAIT_CLIENT,
  GAME_STATE_INITIALIZING,
  GAME_STATE_SETUP,
  GAME_STATE_PLAYING,
  GAME_STATE_PAUSED,
  GAME_STATE_WIN,
  GAME_STATE_LOSE,
} GameState;

typedef struct game {
  GameState state;       // Current game state
  square_t *board;       // Player's board
  square_t *enemy_board; // Enemy's board
  ship_t *fleet;         // Player's fleet
  ship_t *enemy_fleet;   // Enemy's fleet
  menu_t menu;           // Game menu
  bool is_sound_on;      // Sound on/off flag
  nifi_t *nifi;          // Store nifi status
  char *player_name;     // Player's name
  cursor_t cursor;
} game_t;

void game_init(game_t *);
void game_free(game_t *);
void game_reset(game_t *);
void game_update(game_t *, input_t *);
void game_draw(game_t *);
void setup_main_menu(game_t *);
void setup_settings_menu(game_t *);
void setup_play_menu(game_t *);
void game_start_host(game_t *);
void game_search_host(game_t *);
void game_init_boards(game_t *);
void game_sound_toggle(game_t *);
void game_connect(game_t *);
void game_debug_test(game_t *);
