// SPDX-License-Identifier: CC0-1.0
//
// SPDX-FileContributor: Antonio Niño Díaz, 2023

#include <stdio.h>
#include <time.h>

#include <nds.h>
#include <gl2d.h>
#include <system.h>
#include <filesystem.h>
#include <nf_lib.h>

#include "game.h"

game_t game;
input_t input;

int main(int argc, char **argv) {
    NF_Set2D(0, 0);
    NF_Set2D(1, 0);
    consoleDemoInit();
    game_init(&game);
    swiWaitForVBlank();
    while (1) {
        input_handle(&input);
        game_update(&game,&input);
        game_draw(&game);
        swiWaitForVBlank();
    }
    return 0;
}