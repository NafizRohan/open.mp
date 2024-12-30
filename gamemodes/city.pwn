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
#undef MAX_PLAYERS
#define MAX_PLAYERS     100
#include <a_mysql>
#include <bcrypt>
#include <mapandreas>
#include <Pawn.CMD>
#include <sscanf2>
#include <dini2>
#include <easyDialog>
#include <YSI_Data\y_foreach>

/*
     ___      _
    / __| ___| |_ _  _ _ __
    \__ \/ -_)  _| || | '_ \
    |___/\___|\__|\_,_| .__/
                      |_|
*/

// Core
#include <Core\defines>
#include <Core\serverdata>
#include <functions>
#include <callbacks>

#include <Core\strings>
#include <Core\login>
////////////////////////////

// Plyer
#include <Player\saveplayerdata>
//Admin
#include <Admin\admin>
#include <Admin\admindialogs>

// Vehicle
#include <Vehicle\vehfunc>
main(){
    MapAndreas_Init(MAP_ANDREAS_MODE_FULL, "scriptfiles/SAfull.hmap");
}
public OnGameModeInit()
{
    
    printf(" ");
    printf("  -------------------------------");
	printf("  |  Loaded all Gamemode files  |");
	printf("  -------------------------------");
	printf(" ");
    return 1;
}

public OnGameModeExit(){
    return 1;
}

public OnPlayerRequestClass(playerid, classid){
    return 1;
}