#if defined _MORP_PLAYER_LOGIN_INCLUDED
    #endinput
#endif
#define _MORP_PLAYER_LOGIN_INCLUDED

#include <YSI_Coding\y_hooks>
#include <Player\ShowDialog>

// Hook for player class request
// Called when a player requests a class (on connect)
hook OnPlayerRequestClass(playerid, classid)
{
    if (IsPlayerNPC(playerid)) return 1; // Ignore NPCs
    TogglePlayerSpectating(playerid, true); // Put player in spectate mode
    CallRemoteFunction("CheckPlayerMasterAccount", "i", playerid); // Start login/register process
    return 1;
}

// Function to check if password is strong
// Returns true if password contains upper, lower, digit, and special char
bool:isStrongPassword(const password[])
{
    new hasUpper, hasLower, hasDigit, hasSpecial;
    for (new i = 0, len = strlen(password); i < len; i++)
    {
        if (password[i] >= 'A' && password[i] <= 'Z') hasUpper = true;
        else if (password[i] >= 'a' && password[i] <= 'z') hasLower = true;
        else if (password[i] >= '0' && password[i] <= '9') hasDigit = true;
        else hasSpecial = true;
    }
    return hasUpper && hasLower && hasDigit && hasSpecial;
}

// Callback to check player's master account
// Checks if player has a master account or needs to register
CB:CheckPlayerMasterAccount(playerid)
{
    new name[MAX_PLAYER_NAME];
    GetPlayerName(playerid, name);

    if (findsymbol(name))
    {
        SEM(playerid, "Your name contains invalid characters! Use letters (A-Z, a-z) and digits (0-9) only.");
        SetTimerEx("KickPlayer", 1500, false, "i", playerid); // Kick after warning
        return 1;
    }

    // Query master account data
    mysql_format(db, DB_query, sizeof(DB_query),
        "SELECT MasterID, Username, Password, Alias1, Alias2, Alias3 FROM `MasterData` WHERE `Username` = '%e'", name);
    mysql_tquery(db, DB_query, "CheckPlayerAccounts", "i", playerid);
    return 1;
}

// Callback to check player's accounts
// Loads master account data or shows register dialog
CB:CheckPlayerAccounts(playerid)
{
    new rows;
    cache_get_row_count(rows);

    if (rows)
    {
        SSM(playerid, "Fetching your data from the server, please hold on...");

        // Load master data from database
        cache_get_value_name_int(0, "MasterID", gMasterData[playerid][msID]);
        cache_get_value_name(0, "Username", gMasterData[playerid][msUsername]);
        cache_get_value_name(0, "Password", gMasterData[playerid][msPasswordHash]);
        cache_get_value_name(0, "Alias1", gMasterData[playerid][msAlias_1]);
        cache_get_value_name(0, "Alias2", gMasterData[playerid][msAlias_2]);
        cache_get_value_name(0, "Alias3", gMasterData[playerid][msAlias_3]);

        ShowDialog(playerid, DIALOG_PASSWORD); // Ask for password
    }
    else
    {
        // No account found, show register dialog
        GetPlayerName(playerid, gMasterData[playerid][msUsername]);
        ShowDialog(playerid, DIALOG_REGISTER);
    }
    return 1;
}

// Callback to refresh master data
// Reloads master data after registration
CB:RefreshMasterData(playerid)
{
    gMasterData[playerid][msID] = cache_insert_id();

    mysql_format(db, DB_query, sizeof(DB_query),
        "SELECT MasterID, Username, Password, Alias1, Alias2, Alias3 FROM `MasterData` WHERE `Username` = '%e'", 
        gMasterData[playerid][msUsername]);
    mysql_tquery(db, DB_query, "CheckPlayerAccounts", "i", playerid);
    return 1;
}

// Callback for password hashing
// Called after password is hashed during registration
CB:OnPasswordHashed(playerid, hashid)
{
    new hash[BCRYPT_HASH_LENGTH];
    bcrypt_get_hash(hash);

    // Insert new master account into database
    mysql_format(db, DB_query, sizeof(DB_query),
        "INSERT INTO `MasterData` (`MasterID`, `Username`, `Password`, `Alias1`, `Alias2`, `Alias3`) VALUES (NULL, '%e', '%e', 'NULL', 'NULL', 'NULL')",
        gMasterData[playerid][msUsername], hash);
    mysql_tquery(db, DB_query, "RefreshMasterData", "i", playerid);

    // Create player log directory
    new string[128];
    format(string, sizeof(string), PLAYER_LOG_DIR"%s", gMasterData[playerid][msUsername]);
    fcreatedir(string);
    return 1;
}

// Callback for password verification
// Called after password is checked during login
CB:OnPasswordVerify(playerid, bool:success)
{
    if (success)
    {
        SSM(playerid, "Login successful! Welcome to the server.");

        // Show character selection dialog
        new string[128];
        format(string, sizeof(string),
            "Characters\n1. %s\n2. %s\n3. %s",
            strcmp(gMasterData[playerid][msAlias_1], "NULL", true) == 0 
                ? "Empty Slot" 
                : ReturnString(gMasterData[playerid][msAlias_1]),
            strcmp(gMasterData[playerid][msAlias_2], "NULL", true) == 0 
                ? "Empty Slot" 
                : ReturnString(gMasterData[playerid][msAlias_2]),
            strcmp(gMasterData[playerid][msAlias_3], "NULL", true) == 0 
                ? "Empty Slot" 
                : ReturnString(gMasterData[playerid][msAlias_3]));

        ShowDialog(playerid, DIALOG_LOGIN, string);
    }
    else
    {
        SEM(playerid, "Incorrect password. Please try again.");
        ShowDialog(playerid, DIALOG_PASSWORD);
    }
    return 1;
}

// Callback to load player data
// Loads character data from database
CB:LoadPlayerData(playerid)
{
    new rows;
    cache_get_row_count(rows);

    if (rows)
    {
        new health, armor;
        cache_get_value_name_int(0, "PlayerID", gPlayerData[playerid][pID]);
        cache_get_value_name(0, "Name", gPlayerData[playerid][pName], MAX_PLAYER_NAME);
        cache_get_value_name_int(0, "Registered", gPlayerData[playerid][pRegistered]);

        cache_get_value_name_int(0, "Skin", gPlayerData[playerid][pSkin]);
        cache_get_value_name_int(0, "Health", health);
        cache_get_value_name_int(0, "Armor", armor);
        cache_get_value_name_int(0, "Thirst", gPlayerData[playerid][pThirst]);
        cache_get_value_name_int(0, "Hunger", gPlayerData[playerid][pHunger]);
        cache_get_value_name_int(0, "Code", gPlayerData[playerid][pCode]);

        cache_get_value_name_float(0, "PosX", gPlayerData[playerid][pPos][0]);
        cache_get_value_name_float(0, "PosY", gPlayerData[playerid][pPos][1]);
        cache_get_value_name_float(0, "PosZ", gPlayerData[playerid][pPos][2]);
        cache_get_value_name_float(0, "PosA", gPlayerData[playerid][pPos][3]);

        // Set health/armor defaults if not registered
        if(gPlayerData[playerid][pRegistered]){
            gPlayerData[playerid][pHealth] = float(health);
            gPlayerData[playerid][pArmor]  = float(armor);
        }
        else{
            gPlayerData[playerid][pRegistered] = 1;
            gPlayerData[playerid][pHealth] = 100.0;
            gPlayerData[playerid][pArmor]  = 100.0;
        }

        // Set spawn info and spawn player
        SetSpawnInfo(playerid, 0, gPlayerData[playerid][pSkin],
            gPlayerData[playerid][pPos][0],
            gPlayerData[playerid][pPos][1],
            gPlayerData[playerid][pPos][2],
            gPlayerData[playerid][pPos][3],
            WEAPON_FIST);

        CallRemoteFunction("Spawn", "i", playerid);
    }
    return 1;
}

// Callback for character creation
// Called after a new character is created
CB:OnCharacterCreated(playerid)
{
    gPlayerData[playerid][pID] = cache_insert_id();
    gPlayerData[playerid][pRegistered] = 1;
    gPlayerData[playerid][pSkin] = 1;
    gPlayerData[playerid][pHealth] = 100.0;
    gPlayerData[playerid][pArmor] = 100.0;
    gPlayerData[playerid][pThirst] = 100;
    gPlayerData[playerid][pHunger] = 100;

    // Create character log directory
    format(logstr, sizeof(logstr), PLAYER_LOG_DIR"%s/%s", gMasterData[playerid][msUsername], gPlayerData[playerid][pName]);
    fcreatedir(logstr);

    // Update master data with new alias
    mysql_format(db, DB_query, sizeof(DB_query),
        "UPDATE `MasterData` SET `Alias%i` = '%e' WHERE `MasterID` = '%i'",
        gMasterData[playerid][msSelected], gPlayerData[playerid][pName], gMasterData[playerid][msID]);
    mysql_tquery(db, DB_query);

    CallRemoteFunction("Spawn", "i", playerid);
    SSM(playerid, "Character created successfully! Welcome to the server.");
    return 1;
}

// Callback to spawn player
// Actually spawns the player in-game
CB:Spawn(playerid)
{
    SetPlayerName(playerid, gPlayerData[playerid][pName]);
    SetPlayerHealthEx(playerid, gPlayerData[playerid][pHealth]);
    SetPlayerArmorEx(playerid, gPlayerData[playerid][pArmor]);
    SetPlayerColor(playerid, 0xFFFFFF00);
    TogglePlayerSpectating(playerid, false);
    gPlayerData[playerid][pLogged] = true;
    SpawnPlayer(playerid);
    SetPlayerSkinEx(playerid, gPlayerData[playerid][pSkin]);
    return 1;
}

// Dialog to show register dialog
// Handles password input for registration
Dialog:ShowRegisterDialog(playerid, response, listitem, inputtext[])
{
    if (response)
    {
        if (isnull(inputtext))
        {
            // Password empty, ask again
            return Dialog_Show(playerid, ShowRegisterDialog, DIALOG_STYLE_PASSWORD,
                COLOR_YELLOW "Set Password",
                "Password cannot be empty. Please set a strong password:",
                "Continue", "Cancel");
        }
        else if (strlen(inputtext) < 8 || !isStrongPassword(inputtext))
        {
            // Password not strong enough, ask again
            return Dialog_Show(playerid, ShowRegisterDialog, DIALOG_STYLE_PASSWORD,
                COLOR_YELLOW "Set Password",
                "Password must be at least 8 characters long and contain a mix of\nletters(at least one uppercase), numbers, and special characters.\nPlease enter a stronger password:",
                "Submit", "Cancel");
        }
        else
        {
            // Hash password and continue registration
            return bcrypt_hash(playerid, "OnPasswordHashed", inputtext, 12);
        }
    }
    else
    {
        // Cancelled, kick player
        CallRemoteFunction("KickPlayer", "i", playerid);
    }
    return 1;
}

// Dialog to show password box
// Handles password input for login
Dialog:ShowPasswordBox(playerid, response, listitem, inputtext[])
{
    if (response)
    {
        if (isnull(inputtext))
        {
            // Password empty, ask again
            return Dialog_Show(playerid, ShowPasswordBox, DIALOG_STYLE_PASSWORD,
                COLOR_YELLOW "Login",
                "Password field is required. Please enter your password:",
                "Submit", "Cancel");  
        }
        else
        {
            // Verify password
            bcrypt_verify(playerid, "OnPasswordVerify", inputtext, gMasterData[playerid][msPasswordHash]);
        }
    }
    else
    {
        // Cancelled, kick player
        CallRemoteFunction("KickPlayer", "i", playerid);
    }
    return 1;
}

// Dialog to show character box
// Handles character selection or creation
Dialog:ShowCharacterBox(playerid, response, listitem, inputtext[])
{
    if (!response) return 1;

    new alias[MAX_PLAYER_NAME];

    if (listitem >= 0 && listitem < 3)
    {
        gMasterData[playerid][msSelected] = listitem + 1;
        switch (listitem)
        {
            case 0: strmid(alias, gMasterData[playerid][msAlias_1], 0, sizeof(alias), sizeof(alias));
            case 1: strmid(alias, gMasterData[playerid][msAlias_2], 0, sizeof(alias), sizeof(alias));
            case 2: strmid(alias, gMasterData[playerid][msAlias_3], 0, sizeof(alias), sizeof(alias));
        }

        if (strcmp(alias, "NULL", true) == 0)
        {
            // Empty slot, show character creation dialog
            ShowDialog(playerid, DIALOG_CREATE_CHARACTER);
        }
        else
        {
            // Load character data
            mysql_format(db, DB_query, sizeof(DB_query),
                "SELECT * FROM `PlayerData` WHERE `Name` = '%e'",
                alias);
            mysql_tquery(db, DB_query, "LoadPlayerData", "i", playerid);
        }
    }
    return 1;
}

// Dialog to show character creation dialog
// Handles input for new character name
Dialog:ShowDialogCreate(playerid, response, listitem, inputtext[])
{
    if (!response) return CallRemoteFunction("KickPlayer", "i", playerid);

    if (isnull(inputtext))
    {
        // Name empty, ask again
        ShowDialog(playerid, DIALOG_CREATE_CHARACTER);
        return 1;
    }

    if (isValidUnderscoreString(inputtext))
    {
        // Name valid, continue to gender selection
        strcpy(gPlayerData[playerid][pName], inputtext, MAX_PLAYER_NAME);
        ShowDialog(playerid, DIALOG_GENDER);
        return 1;
    }

    // Name invalid, show error and ask again
    SEM(playerid, "The name you entered does not meet our required format.\nUse the format: John_Doe (letters and a single underscore).");
    ShowDialog(playerid, DIALOG_CREATE_CHARACTER);
    return 1;
}

// Dialog to show gender selection dialog
// Handles gender selection for new character
Dialog:ShowDialogGender(playerid, response, listitem, inputtext[])
{
    if (!response) return CallRemoteFunction("KickPlayer", "i", playerid);

    if (listitem == 0)
    {
        gPlayerData[playerid][pGender] = 0; // Male
    }
    else if (listitem == 1)
    {
        gPlayerData[playerid][pGender] = 1; // Female
    }
    else
    {
        // Invalid selection, ask again
        ShowDialog(playerid, DIALOG_GENDER);
        return 1;
    }

    ShowDialog(playerid, DIALOG_AGE); // Continue to age selection
    return 1;
}

// Dialog to show age selection dialog
// Handles age input for new character
Dialog:ShowDialogAge(playerid, response, listitem, inputtext[])
{
    if (!response) return CallRemoteFunction("KickPlayer", "i", playerid);

    new age = strval(inputtext);
    if (age < 18 || age > 100)
    {
        // Invalid age, show error and ask again
        SEM(playerid, "Please enter a valid age between 18 and 100.");
        ShowDialog(playerid, DIALOG_AGE);
        return 1;
    }

    gPlayerData[playerid][pAge] = age;

    // Insert new character into database
    mysql_format(db, DB_query, sizeof(DB_query),
        "INSERT INTO `PlayerData` (`Name`, `MasterID`, `Gender`, `Age`) VALUES ('%e', '%i', '%i', '%i')",
        gPlayerData[playerid][pName], gMasterData[playerid][msID], gPlayerData[playerid][pGender], gPlayerData[playerid][pAge]);
    mysql_tquery(db, DB_query, "OnCharacterCreated", "i", playerid);
    return 1;
}