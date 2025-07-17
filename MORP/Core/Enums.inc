#include <YSI_Coding\y_hooks>
#if defined _MORP_CORE_ENUMS_INCLUDED
    #endinput
#endif
#define _MORP_CORE_ENUMS_INCLUDED
/*
    MORP Core Enums
    This file defines enums and global variables for master account and player data.
    Author: Nafiz Rohan
    Date: 2024-06-09
*/

// Enum for master account data structure
enum MasterAccount{
    msID,                               // Unique master account ID
    msUsername[MAX_PLAYER_NAME],        // Master account username
    msPasswordHash[BCRYPT_HASH_LENGTH], // Hashed password
    msAlias_1[MAX_PLAYER_NAME],         // First alias
    msAlias_2[MAX_PLAYER_NAME],         // Second alias
    msAlias_3[MAX_PLAYER_NAME],         // Third alias
    msSelected                         // Selected alias index or status
};
new gMasterData[MAX_PLAYERS][MasterAccount];

// Enum for player data structure
enum PlayerData{
    pID,                // Player ID
    pName[MAX_PLAYER_NAME], // Player name
    pMasterID,          // Linked master account ID
    pRegistered,        // Registration status
    pCode,              // Registration/verification code
    pSkin,              // Player skin/model
    pGender,            // Player gender
    pAge,               // Player age
    Float:pHealth,      // Player health
    Float:pArmor,       // Player armor
    pHunger,            // Player hunger level
    pThirst,            // Player thirst level
    Float:pPos[4],      // Player position (x, y, z, angle)
    bool:pLogged,       // Login status
    pAdmin,             // Admin level/status
    pMoney              // Player money
};
new gPlayerData[MAX_PLAYERS][PlayerData];

hook OnGameModeInit()
{
    print("MORP Core(Enums) Initialized.");
    return true;
}
hook OnGameModeExit()
{
    print("MORP Core(Enums) Unloaded.");
    return true;
}