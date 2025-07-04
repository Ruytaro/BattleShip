// SPDX-License-Identifier: CC0-1.0
//
// SPDX-FileContributor: Antonio Niño Díaz, 2023

#include <stdio.h>
#include <time.h>

#include <nds.h>
#include <gl2d.h>
#include <maxmod9.h>
#include "board.h"

typedef enum{
    GAME_STATE_INIT = 0,
    GAME_STATE_MENU,
    GAME_STATE_SETTINGS,
    GAME_STATE_SETUP,
    GAME_STATE_PLAYING,
    GAME_STATE_PAUSED,
    GAME_STATE_GAME_OVER,
} GameState;

uint8_t game_state = 0;

void handle_input();

int main(int argc, char **argv)
{
    videoSetMode(MODE_0_3D);

    game_state = GAME_STATE_INIT;
    board_init();
    fleet_init();

    
    // Initialize GL2D
    glScreen2D();

    while (1)
    {
        // Handle input
        handle_input();

        glBegin2D();

        // End 2D scene
        glEnd2D();

        glFlush(0);
        swiWaitForVBlank();

    }

    return 0;
}


void handle_input()
{
    scanKeys();
    u16 keys = keysDown();
    if (keys & KEY_TOUCH) {
        touchPosition touch;
        touchRead(&touch);
        // Handle touch input
    }
    if (keys & KEY_A) {
        // Handle A button press
    }
    if (keys & KEY_B) {
        // Handle B button press
    }
    if (keys & KEY_UP) {
        // Handle B button press
    }
    if (keys & KEY_DOWN) {
        // Handle A button press
    }
    if (keys & KEY_LEFT) {
        // Handle Start button press
    }
    if (keys & KEY_RIGHT) {
        // Handle Select button press
    }
}