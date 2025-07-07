// SPDX-License-Identifier: CC0-1.0
//
// SPDX-FileContributor: Antonio Niño Díaz, 2023

#include <stdio.h>
#include <time.h>

#include <nds.h>
#include <gl2d.h>
#include <filesystem.h>
#include <nf_lib.h>

#include "game.h"

void handle_input(game_t*);

game_t game;
input_t input;

int main(int argc, char **argv)
{
    NF_Set2D(0, 0);
    NF_Set2D(1, 0);
    consoleDemoInit();
    game_init(&game);
    swiWaitForVBlank();
    /*
    printf("\n NitroFS init. Please wait.\n\n");
    printf(" Iniciando NitroFS,\n por favor, espere.\n\n");
    swiWaitForVBlank();
    
    // Initialize NitroFS and set it as the root folder of the filesystem
    nitroFSInit(NULL);
    NF_SetRootFolder("NITROFS");
    consoleClear();

    // Initialize 3D engine in the bottom screen in mode 0
    NF_Set3D(1, 0);

    // Initialize tiled backgrounds system
    NF_InitTiledBgBuffers();    // Initialize storage buffers
    NF_InitTiledBgSys(0);       // Top screen

    // Initialize 3D sprite system
    NF_InitSpriteBuffers();     // Initialize storage buffers
    NF_Init3dSpriteSys();
    */
    while (1)
    {
        input_handle(&input);
        game_update(&game,&input);
        game_draw(&game);
        swiWaitForVBlank();
    }

    return 0;
}