/* Optimized Login & Registration */
#include <YSI_Coding\y_hooks>
#include <Player\playerdata>
#include <Player\playerdialogs>


hook OnPlayerRequestClass(playerid, classid) {
    if (IsPlayerNPC(playerid)) return 1;
    TogglePlayerSpectating(playerid, true);
    CallRemoteFunction("CheckPlayerMasterAccount", "i", playerid);
    return 1;
}

CB:CheckPlayerMasterAccount(playerid) {
    new name[MAX_PLAYER_NAME];
    GetPlayerName(playerid, name);

    if (findsymbol(name)) {
        SEM(playerid,  "Your name contains invalid characters! Use letters (A-Z, a-z) and digits (0-9) only.");
        SetTimerEx("KickPlayer", 1500, false, "i", playerid);
        return 1;
    }

    mysql_format(db, DB_query, sizeof(DB_query), 
        "SELECT MasterID, Username, Password, Alias1, Alias2, Alias3 FROM `MasterData` WHERE `Username` = '%e'", name);
    mysql_tquery(db, DB_query, "CheckPlayerAccounts", "i", playerid);
    return 1;
}

CB:CheckPlayerAccounts(playerid) {
    new rows;
    cache_get_row_count(rows);

    if (rows) {
        SSM(playerid, "Fetching your data from the server, please hold on...");

        cache_get_value_name_int(0, "MasterID", gMasterData[playerid][msID]);
        cache_get_value_name(0, "Username", gMasterData[playerid][msUsername]);
        cache_get_value_name(0, "Password", gMasterData[playerid][msPasswordHash]);
        cache_get_value_name(0, "Alias1", gMasterData[playerid][msAlias_1]);
        cache_get_value_name(0, "Alias2", gMasterData[playerid][msAlias_2]);
        cache_get_value_name(0, "Alias3", gMasterData[playerid][msAlias_3]);

        ShowDialog(playerid, DIALOG_PASSWORD);
    } else {
        GetPlayerName(playerid, gMasterData[playerid][msUsername]);
        ShowDialog(playerid, DIALOG_REGISTER);
    }
    return 1;
}

CB:RefreshMasterData(playerid){
    gMasterData[playerid][msID] = cache_insert_id();

    mysql_format(db, DB_query, sizeof(DB_query), 
        "SELECT MasterID, Username, Password, Alias1, Alias2, Alias3 FROM `MasterData` WHERE `Username` = '%e'", gMasterData[playerid][msUsername]);
    mysql_tquery(db, DB_query, "CheckPlayerAccounts", "i", playerid);
}

CB:OnPasswordHashed(playerid, hashid) {
    new hash[BCRYPT_HASH_LENGTH];
    bcrypt_get_hash(hash);

    mysql_format(db, DB_query, sizeof(DB_query), 
        "INSERT INTO `MasterData` (`MasterID`, `Username`, `Password`, `Alias1`, `Alias2`, `Alias3`) VALUES (NULL, '%e', '%e', 'NULL', 'NULL', 'NULL')", 
        gMasterData[playerid][msUsername], hash);
    mysql_tquery(db, DB_query, "RefreshMasterData", "i", playerid);
}

CB:OnPasswordVerify(playerid, bool:success) {
    if (success) {
        SSM(playerid, "Login successful! Welcome to the server.");

        new string[128];
        format(string, sizeof(string),
            "Characters\n1. %s\n2. %s\n3. %s",
            strcmp(gMasterData[playerid][msAlias_1], "NULL", true) == 0 ? "Empty Slot" : ReturnString(gMasterData[playerid][msAlias_1]),
            strcmp(gMasterData[playerid][msAlias_2], "NULL", true) == 0 ? "Empty Slot" : ReturnString(gMasterData[playerid][msAlias_2]),
            strcmp(gMasterData[playerid][msAlias_3], "NULL", true) == 0 ? "Empty Slot" : ReturnString(gMasterData[playerid][msAlias_3]));

        ShowDialog(playerid, DIALOG_LOGIN, string);
    } else {
        SEM(playerid, "Incorrect password. Please try again.");
        ShowDialog(playerid, DIALOG_PASSWORD);
    }
    return 1;
}

CB:LoadPlayerData(playerid){
    new rows;
    cache_get_row_count(rows);
    if(rows){
        new health, armor;
        cache_get_value_name_int(0, "PlayerID", gPlayerData[playerid][pID]);
        cache_get_value_name(0, "Name", gPlayerData[playerid][pName], MAX_PLAYER_NAME);

        cache_get_value_int(0, "Skin", gPlayerData[playerid][pSkin]);
        cache_get_value_int(0, "Health", health);
        cache_get_value_int(0, "Armor", armor);
        cache_get_value_int(0, "Thirst", gPlayerData[playerid][pThirst]);
        cache_get_value_int(0, "Hunger", gPlayerData[playerid][pHunger]);
        cache_get_value_int(0, "Code", gPlayerData[playerid][pCode]);

        cache_get_value_float(0, "PosX", gPlayerData[playerid][pPos][0]);
        cache_get_value_float(0, "PosY", gPlayerData[playerid][pPos][1]);
        cache_get_value_float(0, "PosZ", gPlayerData[playerid][pPos][2]);
        cache_get_value_float(0, "PosA", gPlayerData[playerid][pPos][3]);

        gPlayerData[playerid][pHealth] = float(health);
        gPlayerData[playerid][pArmor] = float(armor);
        gPlayerData[playerid][pLogged] = true;
        SetSpawnInfo(playerid, 0, gPlayerData[playerid][pSkin], gPlayerData[playerid][pPos][0], gPlayerData[playerid][pPos][1], gPlayerData[playerid][pPos][2], gPlayerData[playerid][pPos][3], WEAPON_FIST);
        CallRemoteFunction("Spawn", "i", playerid);
    }
    return 1;
}

CB:Spawn(playerid) {
    TogglePlayerSpectating(playerid, false);
    SetPlayerName(playerid, gPlayerData[playerid][pName]);
    SetPlayerHealthEx(playerid, gPlayerData[playerid][pHealth]);
    SetPlayerArmorEx(playerid, gPlayerData[playerid][pArmor]);
    SetPlayerColor(playerid, 0xFFFFFF00);

    SpawnPlayer(playerid);
}

Dialog:ShowRegisterDialog(playerid, response, listitem, inputtext[]) {
    if (response) {
        if (isnull(inputtext)) {
            Dialog_Show(playerid, ShowRegisterDialog, DIALOG_STYLE_PASSWORD, 
                COLOR_YELLOW "Set Password", 
                "Password cannot be empty. Please set a strong password:", 
                "Continue", "Cancel");
        } else {
            bcrypt_hash(playerid, "OnPasswordHashed", inputtext, 12);
        }
    } else {
        CallRemoteFunction("KickPlayer", "i", playerid);
    }
    return 1;
}

Dialog:ShowPasswordBox(playerid, response, listitem, inputtext[]) {
    if (response) {
        if (isnull(inputtext)) {
            Dialog_Show(playerid, ShowPasswordBox, DIALOG_STYLE_PASSWORD, 
                COLOR_YELLOW "Login", 
                "Password cannot be empty. Please enter your password:", 
                "Submit", "Cancel");
        } else {
            bcrypt_verify(playerid, "OnPasswordVerify", inputtext, gMasterData[playerid][msPasswordHash]);
        }
    } else {
        CallRemoteFunction("KickPlayer", "i", playerid);
    }
    return 1;
}

Dialog:ShowCharacterBox(playerid, response, listitem, inputtext[]){
    if (!response) return 1; // Exit early if no response

    new alias[MAX_PLAYER_NAME];

    if (listitem >= 0 && listitem < 3) {
        gMasterData[playerid][msSelected] = listitem+1;
        switch (listitem) {
            case 0: strmid(alias, gMasterData[playerid][msAlias_1], 0, sizeof(alias), sizeof(alias)); 
            case 1: strmid(alias, gMasterData[playerid][msAlias_2], 0, sizeof(alias), sizeof(alias)); 
            case 2: strmid(alias, gMasterData[playerid][msAlias_3], 0, sizeof(alias), sizeof(alias));
        }

        if (strcmp(alias, "NULL", true) == 0) {
            ShowDialog(playerid, DIALOG_CREATE_CHARACTER);
        } else {
            mysql_format(db, DB_query, sizeof(DB_query), "SELECT * FROM `PlayerData` WHERE `Name` = '%e'",
            alias);
            mysql_tquery(db, DB_query, "LoadPlayerData", "i", playerid);
        }
    }
    return 1;
}

Dialog:ShowDialogCreate(playerid, response, listitem, inputtext[]){
    if(!response) return CallRemoteFunction("KickPlayer", "i", playerid);
    if(isnull(inputtext)){
        ShowDialog(playerid, DIALOG_CREATE_CHARACTER);
        return 1;
    }
    if(isValidUnderscoreString(inputtext)){
        strcpy(gPlayerData[playerid][pName], inputtext, MAX_PLAYER_NAME);
        gPlayerData[playerid][pSkin] = 1;

        mysql_format(db, DB_query, sizeof(DB_query), "INSERT INTO `PlayerData` (`Name`, `MasterID`, `Skin`) VALUES ('%e', '%i', '%i')",
        gPlayerData[playerid][pName], gMasterData[playerid][msID], gPlayerData[playerid][pSkin]);
        mysql_tquery(db, DB_query);
        
        SetPlayerName(playerid, gPlayerData[playerid][pName]);
        SetPlayerSkin(playerid, gPlayerData[playerid][pSkin]);

        mysql_format(db, DB_query, sizeof(DB_query), "UPDATE `MasterData` SET `Alias%i` = '%e' WHERE `MasterID` = '%i'",
        gMasterData[playerid][msSelected], gPlayerData[playerid][pName], gMasterData[playerid][msID]);
        mysql_tquery(db, DB_query, "Spawn", "i", playerid);
        return 1;
    }
    SEM(playerid, "The name you entered does not meet our required format. Please use the format: John_Doe (only letters and a single underscore are allowed).");
    ShowDialog(playerid, DIALOG_CREATE_CHARACTER);
    return 1;
}

