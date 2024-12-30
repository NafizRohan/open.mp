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
    pCode,
    pSkin,
    Float:pHealth,
    Float:pArmor,
    pHunger,
    pThirst,
    Float:pPos[4],
    bool:pLogged,
    pAdmin
};
new gPlayerData[MAX_PLAYERS][PlayerData];