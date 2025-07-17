#if defined _MORP_PLAYER_SAVEPLAYERDATA_INCLUDED
    #endinput
#endif
#define _MORP_PLAYER_SAVEPLAYERDATA_INCLUDED
#include <YSI_Coding\y_hooks>
#include <YSI_Coding\y_timers>

// Saves the current player's data (health, armor, position, etc.) to the database.
stock bool:SavePlayerData(playerid){
    GetPlayerHealth(playerid, gPlayerData[playerid][pHealth]);
    GetPlayerArmour(playerid, gPlayerData[playerid][pArmor]);

    GetPlayerPos(playerid, gPlayerData[playerid][pPos][0], gPlayerData[playerid][pPos][1], gPlayerData[playerid][pPos][2]);
    GetPlayerFacingAngle(playerid, gPlayerData[playerid][pPos][3]);

    mysql_format(db, DB_query, sizeof(DB_query), 
        "UPDATE `PlayerData` SET `Health` = '%f', `Armor` = '%f', `Thirst` = '%d', `Skin` = '%d' `Hunger` = '%d', `PosX` = '%f', `PosY` = '%f', `PosZ` = '%f', `PosA` = '%f' WHERE `PlayerID` = '%d'",
        gPlayerData[playerid][pHealth], gPlayerData[playerid][pArmor], gPlayerData[playerid][pThirst], gPlayerData[playerid][pSkin],gPlayerData[playerid][pHunger], gPlayerData[playerid][pPos][0], gPlayerData[playerid][pPos][1], gPlayerData[playerid][pPos][2], gPlayerData[playerid][pPos][3], gPlayerData[playerid][pID]);
    mysql_tquery(db, DB_query);
    
    return true;
}

// Periodic task to save player data every 5 minutes (300000 ms).
ptask SavePlayerDataTask[300000](playerid){
    if(gPlayerData[playerid][pLogged] && gPlayerData[playerid][pID] != 0){
        SavePlayerData(playerid);
    }
    return true;
}

// Callback: Called when a player connects. Resets all player and master data for the joining player.
hook OnPlayerConnect(playerid) {
    // Master Data Reset
    gMasterData[playerid][msID] = 0;
    gMasterData[playerid][msSelected] = 0;
    gMasterData[playerid][msAlias_1] = EOS;
    gMasterData[playerid][msAlias_2] = EOS;
    gMasterData[playerid][msAlias_3] = EOS;
    gMasterData[playerid][msPasswordHash] = EOS;

    // Player Data Reset
    gPlayerData[playerid][pID] = 0;
    gPlayerData[playerid][pMasterID] = 0;
    gPlayerData[playerid][pCode] = 0;
    gPlayerData[playerid][pSkin] = 0;
    gPlayerData[playerid][pHealth] = 0.0;
    gPlayerData[playerid][pArmor] = 0.0;
    gPlayerData[playerid][pHunger] = 0;
    gPlayerData[playerid][pThirst] = 0;
    gPlayerData[playerid][pLogged] = false;
    gPlayerData[playerid][pAdmin] = 1;
    gPlayerData[playerid][pPos][0] = 0.0;
    gPlayerData[playerid][pPos][1] = 0.0;
    gPlayerData[playerid][pPos][2] = 0.0;
    gPlayerData[playerid][pPos][3] = 0.0;

    SetPlayerColor(playerid, 0xFFFFFF00);    
    return true;
}

// Callback: Called when a player disconnects. Saves player data and resets player name.
hook OnPlayerDisconnect(playerid, reason) {
    if(gPlayerData[playerid][pLogged] && gPlayerData[playerid][pID] != 0){
        SavePlayerData(playerid);
    }
    SetPlayerName(playerid, gMasterData[playerid][msUsername]);
    return true;
}

// Callback: Called when the gamemode is exiting. Saves all connected players' data and resets their names.
hook OnGameModeExit() {
    // Save all players' data
    for(new i = 0; i < MAX_PLAYERS; i++){
        if(gPlayerData[i][pID] != 0){
            SavePlayerData(i);
        }
        SetPlayerName(i, gMasterData[i][msUsername]);
    }
    return true;
}