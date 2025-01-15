#include <YSI_Coding\y_hooks>
#include <YSI_Coding\y_timers>

stock bool:SavePlayerData(playerid){
    GetPlayerHealth(playerid, gPlayerData[playerid][pHealth]);
    GetPlayerArmour(playerid, gPlayerData[playerid][pArmor]);

    GetPlayerPos(playerid, gPlayerData[playerid][pPos][0], gPlayerData[playerid][pPos][1], gPlayerData[playerid][pPos][2]);
    GetPlayerFacingAngle(playerid, gPlayerData[playerid][pPos][3]);

    mysql_format(db, DB_query, sizeof(DB_query), 
        "UPDATE `PlayerData` SET `Health` = '%f', `Armor` = '%f', `Thirst` = '%d', `Hunger` = '%d', `PosX` = '%f', `PosY` = '%f', `PosZ` = '%f', `PosA` = '%f' WHERE `PlayerID` = '%d'",
        gPlayerData[playerid][pHealth], gPlayerData[playerid][pArmor], gPlayerData[playerid][pThirst], gPlayerData[playerid][pHunger], gPlayerData[playerid][pPos][0], gPlayerData[playerid][pPos][1], gPlayerData[playerid][pPos][2], gPlayerData[playerid][pPos][3], gPlayerData[playerid][pID]);
    mysql_tquery(db, DB_query);
    
    return true;
}

ptask SavePlayerDataTask[300000](playerid){
    if(gPlayerData[playerid][pLogged] && gPlayerData[playerid][pID] != 0){
        SavePlayerData(playerid);
    }
    SSM(playerid, "Your data has been saved.");
    return true;
}

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

hook OnPlayerDisconnect(playerid, reason) {
    if(gPlayerData[playerid][pLogged] && gPlayerData[playerid][pID] != 0){
        SavePlayerData(playerid);
    }
    SetPlayerName(playerid, gMasterData[playerid][msUsername]);
    return true;
}

hook OnGameModeExit() {
    new i;
    for(i = 0; i < MAX_PLAYERS; i++){
        if(gPlayerData[i][pID] != 0){
            SavePlayerData(i);
        }
        SetPlayerName(i, gMasterData[i][msUsername]);
    }
    return true;
}