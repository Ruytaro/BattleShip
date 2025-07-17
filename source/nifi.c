#include "nifi.h"

const u32 GAME_ID = 0xBA771E01;


void nifi_deinit(game_t*game){
    if (game->nifi != NULL && game->nifi->ready){
        Wifi_ScanMode();
        game->nifi->ready=false;
    }
}

//inits nifi
void nifi_init(game_t* game,bool host) {
    nifi_t *nifi = (nifi_t*)calloc(sizeof(nifi_t),1);
    game->nifi = nifi;
    Wifi_InitDefault(INIT_ONLY);
    Wifi_SetChannel(13);
    if (host){
        Wifi_MultiplayerHostMode(1,sizeof(nifi_frame_t),sizeof(nifi_frame_t));
        while (!Wifi_LibraryModeReady()) swiWaitForVBlank();
        nifi->ready = true;
        nifi->host=1;
        Wifi_MultiplayerAllowNewClients(true);
        Wifi_BeaconStart(game->player_name, GAME_ID);
        Wifi_MultiplayerFromClientSetPacketHandler(nifi_rx_handler_host);
    } else {
        Wifi_ScanModeFilter(WSCAN_LIST_NDS_HOSTS);
        Wifi_MultiplayerClientMode(sizeof(nifi_frame_t));
        while (!Wifi_LibraryModeReady()) swiWaitForVBlank();
        nifi->ready = true;
        Wifi_ScanMode();
        Wifi_MultiplayerFromHostSetPacketHandler(nifi_rx_handler_client);
    }
}

void nifi_rx_handler_host(Wifi_MPPacketType type, int aid, int base, int len) {
    printf("Client %d: ", aid);
    if (len <= 0) {
        printf("No data received.\n");
        return;
    }
    u8 *data = (u8*)calloc(len,1);
    Wifi_RxRawReadPacket(base, len, data);
    switch (type) {
    case WIFI_MPTYPE_REPLY:
        break;
    case WIFI_MPTYPE_DATA:
        break;
    case WIFI_MPTYPE_CMD:
        break;
    default:
        break;
    }
    free(data);
}
void nifi_rx_handler_client(Wifi_MPPacketType type, int base, int len) {
    if (len <= 0) {
        printf("No data received.\n");
        return;
    }
    u8 *data = (u8*)calloc(len,1);
    Wifi_RxRawReadPacket(base, len, data);
    switch (type) {
    case WIFI_MPTYPE_REPLY:
        break;
    case WIFI_MPTYPE_DATA:
        break;
    case WIFI_MPTYPE_CMD:
        break;
    default:
        break;
    }
    free(data);
}

void nifi_scanAPs(game_t* game) {
    if (game->nifi == NULL)
        return;
    nifi_t* nifi = game->nifi;
    if (!nifi->ready)
        return;
    for (u8 i = 0; i< nifi->count; i++)
        menu_remove_option(&game->menu, 0);
    int count = Wifi_GetNumAP();
    int valid = 0;
    Wifi_AccessPoint* tmpAps = (Wifi_AccessPoint*)calloc(count, sizeof(Wifi_AccessPoint));
    for (int i = 0; i < count; i++) {
        Wifi_AccessPoint ap;
        Wifi_GetAPData(i, &ap);
        if (ap.nintendo.game_id != GAME_ID)
            continue;
        if (!ap.nintendo.allows_connections)
            continue;
        tmpAps[valid] = ap;
        valid++;
    }
    nifi->count=valid;
    nifi->APs = (Wifi_AccessPoint*)realloc(tmpAps, valid * sizeof(Wifi_AccessPoint));
    
}

void nifi_updateAPs(game_t* game){
    for (u8 v = 0; v < game->nifi->count; v++){
        menu_insert_option(&game->menu, v, game->nifi->APs[v].ssid, game_connect);
    }
}

void nifi_connect(game_t* game) {
    if (game->nifi == NULL)
        return;
    nifi_t* nifi = game->nifi;
    if (!nifi->ready)
        return;
    u8 index = game->menu.selected_option;
    Wifi_AccessPoint ap = nifi->APs[index];
    Wifi_ConnectOpenAP(&ap);
    bool trying = true;
    while (trying) {
        swiWaitForVBlank();
        switch (Wifi_AssocStatus()) {
            case ASSOCSTATUS_ASSOCIATED:
                trying = false;
                nifi->connected = true;
                break;
            case ASSOCSTATUS_CANNOTCONNECT:
                trying = false;
            default:
                break;
        }
    }
}