#include <stdlib.h>
#include <stdbool.h>
#include "board.h"
#include "fleet.h"

typedef enum{
    GAME_STATE_MENU,
    GAME_STATE_SETTINGS,
    GAME_STATE_INIT,
    GAME_STATE_SETUP,
    GAME_STATE_PLAYING,
    GAME_STATE_PAUSED,
    GAME_STATE_WIN,
    GME_STATE_LOSE,
} GameState;

void game_init();
void game_free();
void game_reset();
