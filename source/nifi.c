#include "nifi.h"


void nifi_init(game_t* game,bool host) {
    
    Wifi_InitDefault(INIT_ONLY);
    Wifi_SetChannel(13);
    if (host){
        Wifi_MultiplayerHostMode(1,sizeof(nifi_frame_t),sizeof(nifi_frame_t));
        while (!Wifi_LibraryModeReady()) swiWaitForVBlank();
        Wifi_MultiplayerAllowNewClients(true);
        Wifi_BeaconStart("BattleShip", 0xBA771E);
        Wifi_MultiplayerFromClientSetPacketHandler(nifi_rx_handler_host);
    } else {
        Wifi_MultiplayerFromHostSetPacketHandler(nifi_rx_handler_client);
    }
}

void nifi_rx_handler_host(Wifi_MPPacketType type, int aid, int base, int len) {
    printf("Client %d: ", aid);
    if (type == WIFI_MPTYPE_REPLY)
    {
        for (int i = 0; i < len; i += 2)
        {
            u16 data = 0;
            Wifi_RxRawReadPacket(base + i, sizeof(data), (void *)&data);
            printf("%04X ", data);
        }
        printf("\n");
    }
    else if (type == WIFI_MPTYPE_DATA)
    {
        if (len < 50)
        {
            char string[50];
            Wifi_RxRawReadPacket(base, len, &string);
            string[len] = 0;
            printf("%s", string);
        }
        printf("\n");
    }
}
void nifi_rx_handler_client(Wifi_MPPacketType type, int base, int len) {
    if (type == WIFI_MPTYPE_REPLY)
    {
        for (int i = 0; i < len; i += 2)
        {
            u16 data = 0;
            Wifi_RxRawReadPacket(base + i, sizeof(data), (void *)&data);
            printf("%04X ", data);
        }
        printf("\n");
    }
    else if (type == WIFI_MPTYPE_DATA)
    {
        if (len < 50)
        {
            char string[50];
            Wifi_RxRawReadPacket(base, len, &string);
            string[len] = 0;
            printf("%s", string);
        }
        printf("\n");
    }
}