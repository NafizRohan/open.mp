/*

  __  __      _                ____       _       _         _____       _      _____  _             
 |  \/  |    | |              / __ \     (_)     (_)       |  __ \     | |    |  __ \| |            
 | \  / | ___| |_ _ __ ___   | |  | |_ __ _  __ _ _ _ __   | |__) |___ | | ___| |__) | | __ _ _   _ 
 | |\/| |/ _ \ __| '__/ _ \  | |  | | '__| |/ _` | | '_ \  |  _  // _ \| |/ _ \  ___/| |/ _` | | | |
 | |  | |  __/ |_| | | (_) | | |__| | |  | | (_| | | | | | | | \ \ (_) | |  __/ |    | | (_| | |_| |
 |_|  |_|\___|\__|_|  \___/   \____/|_|  |_|\__, |_|_| |_| |_|  \_\___/|_|\___|_|    |_|\__,_|\__, |
                                                                                               __/ |                                             __/ |
                                                                                              |___/                                             |___/ 
        */

// Include core libraries and plugins
#include <open.mp>
#include <easyDialog>
#include <a_mysql>
#include <bcrypt>
#include <mapandreas>
#include <Pawn.CMD>
#include <sscanf2>
#include <streamer>
#include <dini2>
#include <YSI_Data\y_foreach>

/*
                 ___      _
                / __| ___| |_ _  _ _ __
                \__ \/ -_)  _| || | '_ \
                |___/\___|\__|\_,_| .__/
                                  |_|
*/

// Core includes for server functionality
#include <Core/Defines>
#include <Core/Enums>
#include <Core/ServerData>
#include <Core/Strings>
#include <functions>
#include <callbacks>

// Player-related includes
#include <Player/Login>
#include <Player/SavePlayerData>
// Admin-related includes
#include <Player/Admin/AdminInit>
#include <Player/Admin/Dialog>

// Main entry point (required by SA-MP)
main() {}

// Called when the gamemode starts
public OnGameModeInit()
{
    // Initialize MapAndreas for map data
    if (!MapAndreas_Init(MAP_ANDREAS_MODE_FULL, "scriptfiles/SAfull.hmap")) {
            printf("MapAndreas initialization failed!");
            return 0;
    }
    return 1;
}

// Called when the gamemode ends
public OnGameModeExit()
{
    // Perform any necessary cleanup here
    return 1;
}

// Called when a player requests to select a class
public OnPlayerRequestClass(playerid, classid)
{
    // Handle player class selection here
    return 1;
}

// Called when a player connects to the server
public OnPlayerConnect(playerid)
{
    new name[MAX_PLAYER_NAME];
    GetPlayerName(playerid, name, sizeof(name));
    printf("Player %s(%d) has connected to the server.", name, playerid);
    // Initialize player data here
    return 1;
}

// Called when a player disconnects from the server
public OnPlayerDisconnect(playerid, reason)
{
    new name[MAX_PLAYER_NAME];
    GetPlayerName(playerid, name, sizeof(name));
    printf("Player %s(%d) has disconnected from the server. Reason: %d", name, playerid, reason);
    // Save player data and perform cleanup here
    return 1;
}