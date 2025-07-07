#include <stdio.h>
#include <nds.h>
#include <dswifi9.h>

#ifndef NIFI_H
#define NIFI_H

#define NIFI_VERSION 0x01

typedef struct game game_t;

typedef struct nifi
{
    game_t* game;
} nifi_t;




// Function to initialize the NIFI system
void nifi_init(game_t*,bool);
void nifi_rx_handler_host(Wifi_MPPacketType, int, int, int);
void nifi_rx_handler_client(Wifi_MPPacketType, int, int);



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