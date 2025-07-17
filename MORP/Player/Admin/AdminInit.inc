#include <YSI_Coding\y_hooks>
#include <Player\ShowDialog>

// Arrays to store map coordinates for each player
new Float:MapX[MAX_PLAYERS], Float:MapY[MAX_PLAYERS], Float:MapZ[MAX_PLAYERS];

// Command to open the admin settings dialog
CMD:settings(playerid, const params[]){
    if(!IsPlayerServerAdmin(playerid)) return SEM(playerid, "You are not an admin."); // Check admin status
    ShowDialog(playerid, DIALOG_ADMIN_PANEL); // Show admin panel dialog
    return true;
}

// Hook called when a player connects to the server
hook OnPlayerConnect(playerid){
    MapX[playerid] = 0.0; // Initialize X coordinate
    MapY[playerid] = 0.0; // Initialize Y coordinate
    MapZ[playerid] = 0.0; // Initialize Z coordinate
    return true;
}

// Hook called when a player clicks on the map
hook OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ){
    if(IsPlayerServerAdmin(playerid)){
        MapX[playerid] = fX; // Store clicked X coordinate
        MapY[playerid] = fY; // Store clicked Y coordinate
        MapAndreas_FindZ_For2DCoord(fX, fY, MapZ[playerid]); // Find and store Z coordinate using MapAndreas
    }
    return true;
}