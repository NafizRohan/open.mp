#if defined _MORP_CORE_ENUMS_INCLUDED
    #endinput
#endif
#define _MORP_CORE_ENUMS_INCLUDED


// enum BusinessData{
//     bID,
//     bExists,
//     bName[64],
//     bOwnerID,
//     bOwner[64],
//     bType,
//     bMoney
// };
// new gBusinessData[MAX_BUSINESS][BusinessData];

enum MasterAccount{
    msID,
    msUsername[MAX_PLAYER_NAME],
    msPasswordHash[BCRYPT_HASH_LENGTH],
    msAlias_1[MAX_PLAYER_NAME],
    msAlias_2[MAX_PLAYER_NAME],
    msAlias_3[MAX_PLAYER_NAME],
    msSelected
};
new gMasterData[MAX_PLAYERS][MasterAccount];

enum PlayerData{
    pID,
    pName[MAX_PLAYER_NAME],
    pMasterID,
    pRegistered,
    pCode,
    pSkin,
    pGender,
    pAge,
    Float:pHealth,
    Float:pArmor,
    pHunger,
    pThirst,
    Float:pPos[4],
    bool:pLogged,
    pAdmin,
    pMoney
};
new gPlayerData[MAX_PLAYERS][PlayerData];

// enum JobData{
//     jID,
//     jName[64],
//     jType,
//     jSkin,
//     jSalary,
//     jOwnerID,
//     jOwner[64],
//     Float:jPos[3],
//     STREAMER_TAG_PICKUP:jPickup,
//     STREAMER_TAG_3D_TEXT_LABEL:jLabel,
//     bool:jExists
// };
// new gJobData[MAX_JOBS][JobData];
