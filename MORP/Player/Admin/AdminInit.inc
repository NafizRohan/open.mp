#include <YSI_Coding\y_hooks>
#include <Player\ShowDialog>
new Float:MapX[MAX_PLAYERS], Float:MapY[MAX_PLAYERS], Float:MapZ[MAX_PLAYERS];

CMD:settings(playerid, const params[]){
    if(!IsPlayerServerAdmin(playerid)) return SEM(playerid, "You are not an admin.");
    ShowDialog(playerid, DIALOG_ADMIN_PANEL);
    return true;
}

hook OnPlayerConnect(playerid){
    MapX[playerid] = 0.0;
    MapY[playerid] = 0.0;
    MapZ[playerid] = 0.0;
    return true;
}

hook OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ){
    if(IsPlayerServerAdmin(playerid)){
        MapX[playerid] = fX;
        MapY[playerid] = fY;
        MapAndreas_FindZ_For2DCoord(fX, fY, MapZ[playerid]);
    }
    return true;
}