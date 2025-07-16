#if !defined(MORP_CORE_SERVERDATA_INC)
    #endinput
#endif
#define MORP_CORE_SERVERDATA_INC
#include <YSI_Coding\y_hooks>
new SERVER_NAME[32];
new SERVER_TAG[8];
new DEVELOPER[32];


new MySQL:db;
new db_host[64], db_user[64], db_password[64], db_name[64];
new DB_query[2048];

new MaxWealth;
new MaxDiamond;
new MaxGold;
new TotalWealth;
new TotalDiamond;
new TotalGold;
stock LoadServerData(){
    //Server Info
    format(SERVER_NAME, sizeof(SERVER_NAME), "%s", dini_Get("server.properties.cfg", "name"));
    format(SERVER_TAG, sizeof(SERVER_TAG), "%s", dini_Get("server.properties.cfg", "tag"));
    format(DEVELOPER, sizeof(DEVELOPER), "%s", dini_Get("server.properties.cfg", "dev"));
    //Mysql Informations
    format(db_host, sizeof(db_host), "%s", dini_Get("server.properties.cfg", "hostname"));
    format(db_user, sizeof(db_user), "%s", dini_Get("server.properties.cfg", "user"));
    format(db_password, sizeof(db_password), "%s", dini_Get("server.properties.cfg", "password"));
    format(db_name, sizeof(db_name), "%s", dini_Get("server.properties.cfg", "database"));
    //City Info
    MaxWealth = dini_Int("server.properties.cfg", "MaxWealth");
    MaxDiamond = dini_Int("server.properties.cfg", "MaxDiamond");
    MaxGold = dini_Int("server.properties.cfg", "MaxGold");
    TotalWealth = dini_Int("server.properties.cfg", "TotalWealth");
    TotalDiamond = dini_Int("server.properties.cfg", "TotalDiamond");
    TotalGold = dini_Int("server.properties.cfg", "TotalGold");
}

stock SaveServerData(){
    //Server Info
    dini_Set("server.properties.cfg", "name", SERVER_NAME);
    dini_Set("server.properties.cfg", "tag", SERVER_TAG);
    dini_Set("server.properties.cfg", "dev", DEVELOPER);
    //MySQL Information
    dini_Set("server.properties.cfg", "hostname", db_host);
    dini_Set("server.properties.cfg", "user", db_user);
    dini_Set("server.properties.cfg", "password", db_password);
    dini_Set("server.properties.cfg", "database", db_name);
    //City Info
    dini_IntSet("server.properties.cfg", "MaxWealth", MaxWealth);
    dini_IntSet("server.properties.cfg", "MaxDiamond", MaxDiamond);
    dini_IntSet("server.properties.cfg", "MaxGold", MaxGold);
    dini_IntSet("server.properties.cfg", "TotalWealth", TotalWealth);
    dini_IntSet("server.properties.cfg", "TotalDiamond", TotalDiamond);
    dini_IntSet("server.properties.cfg", "TotalGold", TotalGold);
}

hook OnGameModeInit()
{
    printf("Initializing server configuration: server.properties.cfg...");
    LoadServerData();

    printf("\n\n");
    printf("  __  __      _                ____       _       _         _____       _      _____  _             ");
    printf(" |  \\/  |    | |              / __ \\     (_)     (_)       |  __ \\     | |    |  __ \\| |            ");
    printf(" | \\  / | ___| |_ _ __ ___   | |  | |_ __ _  __ _ _ _ __   | |__) |___ | | ___| |__) | | __ _ _   _ ");
    printf(" | |\\/| |/ _ \\ __| '__/ _ \\  | |  | | '__| |/ _` | | '_ \\  |  _  // _ \\| |/ _ \\  ___/| |/ _` | | | |");
    printf(" | |  | |  __/ |_| | | (_) | | |__| | |  | | (_| | | | | | | | \\ \\ (_) | |  __/ |    | | (_| | |_| |");
    printf(" |_|  |_|\\___|\\__|_|  \\___/   \\____/|_|  |_|\\__, |_|_| |_| |_|  \\_\\___/|_|\\___|_|    |_|\\__,_|\\__, |");
    printf("                                             __/ |                                             __/ |");
    printf("                                            |___/                                             |___/ ");
    
    printf("\n\n");
    printf("Server Name: %s", SERVER_NAME);
    printf("Tag: %s", SERVER_TAG);
    printf("Maintainer: %s", DEVELOPER);
    printf("Original Developer: Nafiz Rohan");
    printf("Max Players: %d", MAX_PLAYERS);
    
    printf("\n");
    printf("Server Limits:");
    printf("  - Maximum Money Allowed: %i", MaxWealth);
    printf("  - Maximum Diamonds Allowed: %i", MaxDiamond);
    printf("  - Maximum Gold Allowed: %i", MaxGold);
    
    printf("\n");
    printf("Current Total Holdings (All Players):");
    printf("  - Total Money: %i", TotalWealth);
    printf("  - Total Diamonds: %i", TotalDiamond);
    printf("  - Total Gold: %i", TotalGold);
    printf("\n\n");

    printf("Establishing connection to the database server...");
    db = mysql_connect(db_host, db_user, db_password, db_name);
    mysql_log(ERROR | WARNING);
    
    if(mysql_errno(db)){
        printf("Unable to connect to the database server. Please verify the database details in the **scriptfiles/server.properties.cfg** file.");
        SendRconCommand("exit");
    }
    else
        printf("Successfully connected to the database server.\n");
    
    SendRconCommand("name %s", SERVER_NAME);
    SendRconCommand("game.mode %s", SERVER_TAG);
}


hook OnGameModeExit(){
    SaveServerData();
    dini_Timeout("server.properties.cfg");
    mysql_close(db);
}