enum{
    DIALOG_REGISTER,
    DIALOG_PASSWORD,
    DIALOG_CREATE_CHARACTER,
    DIALOG_LOGIN,
    // Admin Stuff
    DIALOG_ADMIN_PANEL,
    DIALOG_ADMIN,
    DIALOG_ADMIN_BUSINESS,
    DIALOG_ADMIN_PLAYERS,
    DIALOG_ADMIN_GATES,
    DIALOG_ADMIN_ORGANIZATIONS,
    DIALOG_ADMIN_SERVER,
    DIALOG_SERVER_VARIABLES,
    DIALOG_ADMIN_TELEPORT,
    DIALOG_ADMIN_TELEPORT_PLAYER,
    DIALOG_ADMIN_TELEPORT_BUSINESS,
    DIALOG_ADMIN_CHECK_ADMINS,
    DIALOG_ADMIN_SET_ADMIN,
    // Server Details
    DIALOG_SERVER_DETAILS
};


stock ShowDialog(playerid, dialogid, const string[] = ""){
    #pragma unused string
    switch(dialogid){
        case DIALOG_REGISTER:{
            Dialog_Show(playerid, ShowRegisterDialog, DIALOG_STYLE_PASSWORD, 
            COLOR_YELLOW "Set Password", 
            "Please set a strong password to proceed:", 
            "Continue", "Cancel");
        }
        case DIALOG_PASSWORD:{
            Dialog_Show(playerid, ShowPasswordBox, DIALOG_STYLE_PASSWORD, 
            COLOR_YELLOW "Login", 
            "Please enter your password to proceed:", 
            "Submit", "Cancel");
        }
        case DIALOG_LOGIN:{
            Dialog_Show(playerid, ShowCharacterBox, DIALOG_STYLE_TABLIST_HEADERS, 
            COLOR_YELLOW "Select Character", string, "Select", "Cancel");
        }
        case DIALOG_CREATE_CHARACTER:{
            Dialog_Show(playerid, ShowDialogCreate, DIALOG_STYLE_INPUT,
            "Create Character",WHITE "Enter your character name (Example: John_Doe).\nUse only letters and an underscore (_):",
            "Submit", "Cancel");
        }
        // Admin Stuff
        case DIALOG_ADMIN_PANEL:{
            Dialog_Show(playerid, ShowAdminPanel, DIALOG_STYLE_TABLIST_HEADERS, 
            COLOR_YELLOW "Admin Panel", "Options\nAdmins\nBusinesses\nPlayers\nGates & Entrances\nOrganizations\nServer Settings",
            "Select", "Cancel");
        }
        case DIALOG_ADMIN:{
            Dialog_Show(playerid, ShowDialogAdmin, DIALOG_STYLE_TABLIST_HEADERS, 
            COLOR_YELLOW "Admin Panel", "Options\nTeleport\nCheck Admins\nSet Admin", 
            "Select", "Cancel");
        }
        case DIALOG_ADMIN_TELEPORT:{
            Dialog_Show(playerid, ShowDialogAdminTeleport, DIALOG_STYLE_TABLIST_HEADERS, 
            COLOR_YELLOW "Admin Panel", "Options\nTeleport to Player\nTeleport to Location\nTeleport to Business\nTeleport to Gate\nTeleport to Organization\nTeleport to Map", 
            "Select", "Cancel");
        }
        case DIALOG_ADMIN_TELEPORT_PLAYER:{
            Dialog_Show(playerid, ShowDialogAdminTeleportPlayer, DIALOG_STYLE_INPUT, 
            COLOR_YELLOW "Admin Panel", 
            "Enter the player ID to teleport to:", 
            "Select", "Cancel");
        }
        case DIALOG_ADMIN_TELEPORT_BUSINESS:{
            Dialog_Show(playerid, ShowDialogAdminTeleportBusiness, DIALOG_STYLE_INPUT, 
            COLOR_YELLOW "Admin Panel", "Enter the business ID to teleport to:", 
            "Select", "Cancel");
        }
        case DIALOG_ADMIN_CHECK_ADMINS:{
            Dialog_Show(playerid, ShowDialogAdminCheckAdmins, DIALOG_STYLE_TABLIST_HEADERS, 
            COLOR_YELLOW "Admin Panel", "Options\nCheck Admins\nCheck Admins Online", 
            "Select", "Cancel");
        }
        case DIALOG_ADMIN_SET_ADMIN:{
            Dialog_Show(playerid, ShowDialogAdminSetAdmin, DIALOG_STYLE_TABLIST_HEADERS, 
            COLOR_YELLOW "Admin Panel", "Options\nSet Admin\nRemove Admin", 
            "Select", "Cancel");
        }
        
        case DIALOG_ADMIN_BUSINESS:{
            Dialog_Show(playerid, ShowDialogAdminBusiness, DIALOG_STYLE_TABLIST_HEADERS, 
            COLOR_YELLOW "Admin Panel", "Options\nCreate Business\nEdit Business\nDelete Business", 
            "Select", "Cancel");
        }
        case DIALOG_ADMIN_PLAYERS:{
            Dialog_Show(playerid, ShowDialogAdminPlayers, DIALOG_STYLE_TABLIST_HEADERS, 
            COLOR_YELLOW "Admin Panel", "Options\nTeleport\nKick\nBan\nUnban\nMute\nUnmute\nSet Health\nSet Armor\nSet Money\nSet Hunger\nSet Thirst", 
            "Select", "Cancel");
        }
        case DIALOG_ADMIN_GATES:{
            Dialog_Show(playerid, ShowDialogAdminGates, DIALOG_STYLE_TABLIST_HEADERS, 
            COLOR_YELLOW "Admin Panel", "Options\nCreate Gate\nEdit Gate\nDelete Gate", 
            "Select", "Cancel");
        }
        case DIALOG_ADMIN_ORGANIZATIONS:{
            Dialog_Show(playerid, ShowDialogAdminOrg, DIALOG_STYLE_TABLIST_HEADERS, 
            COLOR_YELLOW "Admin Panel", "Options\nCreate Organization\nEdit Organization\nDelete Organization", 
            "Select", "Cancel");
        }
        case DIALOG_ADMIN_SERVER:{
            Dialog_Show(playerid, ShowDialogAdminServer, DIALOG_STYLE_TABLIST_HEADERS, 
            COLOR_YELLOW "Admin Panel", "Options\nSet Server Time\nSet Server Weather\nSet Server Name\nSet Server Password\nSet Server Tag\nSet Server Maintainer\nChange Server Variables", 
            "Select", "Cancel");
        }
        case DIALOG_SERVER_VARIABLES:{
            Dialog_Show(playerid, ShowDialogServerVars, DIALOG_STYLE_TABLIST_HEADERS, 
            COLOR_YELLOW "Admin Panel", "Options\nSet Server Money\nSet Server Diamonds\nSet Server Golds", 
            "Select", "Cancel");
        }
        
    }
    return 1;
}