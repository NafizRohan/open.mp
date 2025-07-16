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

// Core
#include <Core/Defines>
#include <Core/Enums>
#include <Core/ServerData>
#include <Core/Strings>
#include <functions>
#include <callbacks>

// Player
#include <Player/Login>
#include <Player/SavePlayerData>
// Admin
#include <Player/Admin/AdminInit>
#include <Player/Admin/Dialog>
// Job
// #include <Job/LoadJob>
// #include <Job/CreateJob>

main() {}

public OnGameModeInit()
{
    printf(" ");
    printf("  -------------------------------");
    printf("  |  Loaded all Gamemode files  |");
    printf("  -------------------------------");
    printf(" ");
    
    if (!MapAndreas_Init(MAP_ANDREAS_MODE_FULL, "scriptfiles/SAfull.hmap"))
    {
        printf("MapAndreas initialization failed!");
        return 0;
    }
    return 1;
}

public OnGameModeExit()
{
    // Perform any necessary cleanup here
    return 1;
}

public OnPlayerRequestClass(playerid, classid)
{
    // Handle player class selection here
    return 1;
}

public OnPlayerConnect(playerid)
{
    new name[MAX_PLAYER_NAME];
    GetPlayerName(playerid, name, sizeof(name));
    printf("Player %s(%d) has connected to the server.", name, playerid);
    // Initialize player data here
    return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
    new name[MAX_PLAYER_NAME];
    GetPlayerName(playerid, name, sizeof(name));
    printf("Player %s(%d) has disconnected from the server. Reason: %d", name, playerid, reason);
    // Save player data and perform cleanup here
    return 1;
}