#include <stdio.h>
#include <nds.h>
#include <dswifi9.h>
#include <iconv.h>
#include <system.h>

#ifndef GAME_H
    #include "game.h"
#endif

#ifndef NIFI_H
#define NIFI_H

typedef struct nifi
{
    u8 ready:1;
    u8 host:1;
    u8 connected:1;
    u8 count:4;
    Wifi_AccessPoint* APs;
} nifi_t;


// Function to initialize the NIFI system
void nifi_init(game_t*,bool);
void nifi_rx_handler_host(Wifi_MPPacketType, int, int, int);
void nifi_rx_handler_client(Wifi_MPPacketType, int, int);
void nifi_scanAPs(game_t*);
void nifi_connect(game_t*);
void nifi_deinit(game_t*);
void nifi_updateAPs(game_t*);

typedef struct nifi_frame{
    u8 version;      // Version of protocol
    u8 flags;        // Flags for the frame
    u8 source;       // Source address of the frame
    u8 destination;  // Destination address of the frame
    u8 sequence;     // Sequence number for the frame
    u8 ack;          // Acknowledgment number for the frame
    u8 type;          // Type of the frame
    u8 length;        // Length of the frame
    u8 data[55];     // Data payload, max 256 bytes
    u8 checksum;     // Checksum for error detection
} nifi_frame_t;

#endif