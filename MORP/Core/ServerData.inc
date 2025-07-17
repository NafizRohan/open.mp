#include <YSI_Coding\y_hooks>
#if defined _MORP_CORE_SERVERDATA_INCLUDED
    #endinput
#endif
#define _MORP_CORE_SERVERDATA_INCLUDED
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
     // Fetch server data from the database table 'ServerConfig' according to city.sql
    new Cache:result, rows;
    result = mysql_query(db, "SELECT * FROM ServerConfig LIMIT 1");
    cache_get_row_count(rows);
    if(rows > 0)
    {
        cache_get_value_name(0, "Name", SERVER_NAME, sizeof(SERVER_NAME));
        cache_get_value_name(0, "Tag", SERVER_TAG, sizeof(SERVER_TAG));
        cache_get_value_name(0, "Developer", DEVELOPER, sizeof(DEVELOPER));
        cache_get_value_name_int(0, "MaxWealth", MaxWealth);
        cache_get_value_name_int(0, "MaxDiamond", MaxDiamond);
        cache_get_value_name_int(0, "MaxGold", MaxGold);
        cache_get_value_name_int(0, "TotalWealth", TotalWealth);
        cache_get_value_name_int(0, "TotalDiamond", TotalDiamond);
        cache_get_value_name_int(0, "TotalGold", TotalGold);
    }
    cache_delete(result);
    
    //City Info
    MaxWealth = dini_Int("server.properties.cfg", "MaxWealth");
    MaxDiamond = dini_Int("server.properties.cfg", "MaxDiamond");
    MaxGold = dini_Int("server.properties.cfg", "MaxGold");
    TotalWealth = dini_Int("server.properties.cfg", "TotalWealth");
    TotalDiamond = dini_Int("server.properties.cfg", "TotalDiamond");
    TotalGold = dini_Int("server.properties.cfg", "TotalGold");
}

stock SaveServerData() {
    // Save to SQL database instead of dini
    mysql_format(db, DB_query, sizeof(DB_query),
        "UPDATE `ServerConfig` SET \
        `Name` = '%e', `Tag` = '%e', `Developer` = '%e', \
        `MaxWealth` = %d, `MaxDiamond` = %d, `MaxGold` = %d, \
        `TotalWealth` = %d, `TotalDiamond` = %d, `TotalGold` = %d \
        LIMIT 1",
        SERVER_NAME, SERVER_TAG, DEVELOPER,
        MaxWealth, MaxDiamond, MaxGold,
        TotalWealth, TotalDiamond, TotalGold
    );
    mysql_query(db, DB_query, false); // Use non-blocking query for better performance
}

hook OnGameModeInit()
{
    print("MORP Core(ServerData) Initialized.");
    //Mysql Informations
    format(db_host, sizeof(db_host), "%s", dini_Get("db.cfg", "hostname"));
    format(db_user, sizeof(db_user), "%s", dini_Get("db.cfg", "user"));
    format(db_password, sizeof(db_password), "%s", dini_Get("db.cfg", "password"));
    format(db_name, sizeof(db_name), "%s", dini_Get("db.cfg", "database"));
    // Connect to the database
    printf("Establishing connection to the database server...");
    db = mysql_connect(db_host, db_user, db_password, db_name);
    mysql_log(ERROR | WARNING);
    
    if(mysql_errno(db)){
        printf("Unable to connect to the database server. Please verify the database details in the **scriptfiles/server.properties.cfg** file.");
        SendRconCommand("exit");
    }
    else
        printf("Successfully connected to the database server.\n");
    // Load server data
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

    
    
    SendRconCommand("name %s", SERVER_NAME);
    SendRconCommand("game.mode %s", SERVER_TAG);
}


hook OnGameModeExit(){
    SaveServerData();
    dini_Timeout("server.properties.cfg");
    mysql_close(db);
    print("MORP Core(ServerData) Unloaded.");
    return true;
}