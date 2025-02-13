enum {
    DIALOG_REGISTER,
    DIALOG_PASSWORD,
    DIALOG_CREATE_CHARACTER,
    DIALOG_GENDER,
    DIALOG_AGE,
    DIALOG_LOGIN,
    // Admin Stuff
    DIALOG_ADMIN_PANEL,
    DIALOG_ADMIN,
    DIALOG_ADMIN_BUSINESS,
    DIALOG_ADMIN_PLAYERS,
    DIALOG_ADMIN_GATES,
    DIALOG_ADMIN_ENTRANCES,
    DIALOG_ADMIN_ORGANIZATIONS,
    DIALOG_ADMIN_SERVER,
    DIALOG_SERVER_VARIABLES,
    DIALOG_ADMIN_TELEPORT,
    DIALOG_ADMIN_TELEPORT_PLAYER,
    DIALOG_ADMIN_TELEPORT_BUSINESS,
    DIALOG_ADMIN_CHECK_ADMINS,
    DIALOG_ADMIN_SET_ADMIN,
    // Server Details
    DIALOG_SERVER_DETAILS,
    // Funtions
    DIALOG_CREATE_JOB1,
    DIALOG_CREATE_JOB2
};

stock bool:ShowDialog(playerid, dialogid, const string[] = "") {
    #pragma unused string
    switch (dialogid) {
        // Login-Register
        case DIALOG_REGISTER:
        {
            Dialog_Show(playerid, ShowRegisterDialog, DIALOG_STYLE_PASSWORD, 
                COLOR_YELLOW "Set Password", 
                "Password must be at least 8 characters long and contain a mix of\
                \nletters(at least one uppercase), numbers, and special characters.\
                \nPlease enter a stronger password:", 
                "Continue", "Cancel");
            return true;
        }
        case DIALOG_PASSWORD:
        {
            Dialog_Show(playerid, ShowPasswordBox, DIALOG_STYLE_PASSWORD, 
                COLOR_YELLOW "Login", 
                "Please enter your password to proceed:", 
                "Submit", "Cancel");
            return true;
        }
        case DIALOG_LOGIN:
        {
            Dialog_Show(playerid, ShowCharacterBox, DIALOG_STYLE_TABLIST_HEADERS, 
                COLOR_YELLOW "Select Character", string, "Select", "Cancel");
            return true;
        }
        case DIALOG_CREATE_CHARACTER:
        {
            Dialog_Show(playerid, ShowDialogCreate, DIALOG_STYLE_INPUT,
                COLOR_YELLOW "Create Character",
                "Enter your character name (format: John_Doe):",
                "Continue", "Cancel");
            return true;
        }
        case DIALOG_GENDER:
        {
            Dialog_Show(playerid, ShowDialogGender, DIALOG_STYLE_TABLIST_HEADERS,
                COLOR_YELLOW "Select Gender",
                "Select your character's gender\nMale\nFemale", "Select", "Cancel");
            return true;
        }
        case DIALOG_AGE:
        {
            Dialog_Show(playerid, ShowDialogAge, DIALOG_STYLE_INPUT,
                COLOR_YELLOW "Enter Age",
                "Enter your character's age (18-100):",
                "Continue", "Cancel");
            return true;
        }
        // Admin Stuff
        case DIALOG_ADMIN_PANEL:
        {
            Dialog_Show(playerid, ShowAdminPanel, DIALOG_STYLE_TABLIST_HEADERS, 
                COLOR_YELLOW "Admin Panel", "Options\nAdmins\nBusinesses\nPlayers\nGates\nEntrances\nOrganizations\nServer Settings",
                "Select", "Cancel");
            return true;
        }
        case DIALOG_ADMIN:
        {
            Dialog_Show(playerid, ShowDialogAdmin, DIALOG_STYLE_TABLIST_HEADERS, 
                COLOR_YELLOW "Admin Panel", "Options:Admin\nTeleport\nCheck Admins\nSet Admin", 
                "Select", "Cancel");
            return true;
        }
        case DIALOG_ADMIN_BUSINESS:
        {
            Dialog_Show(playerid, ShowDialogAdminBusiness, DIALOG_STYLE_TABLIST_HEADERS, 
                COLOR_YELLOW "Admin Panel", "Options:Business\nCreate Business\nEdit Business\nDelete Business", 
                "Select", "Cancel");
            return true;
        }
        case DIALOG_ADMIN_PLAYERS:
        {
            Dialog_Show(playerid, ShowDialogAdminPlayers, DIALOG_STYLE_TABLIST_HEADERS, 
                COLOR_YELLOW "Admin Panel", "Options:Players\nTeleport\nKick\nBan\nUnban\nMute\nUnmute\nSet Health\nSet Armor\nSet Money\nSet Hunger\nSet Thirst", 
                "Select", "Cancel");
            return true;
        }
        case DIALOG_ADMIN_GATES:
        {
            Dialog_Show(playerid, ShowDialogAdminGates, DIALOG_STYLE_TABLIST_HEADERS, 
                COLOR_YELLOW "Admin Panel", "Options:Gates\nCreate Gate\nEdit Gate\nDelete Gate", 
                "Select", "Cancel");
            return true;
        }
        case DIALOG_ADMIN_ENTRANCES:
        {
            Dialog_Show(playerid, ShowDialogAdminEntrances, DIALOG_STYLE_TABLIST_HEADERS, 
                COLOR_YELLOW "Admin Panel", "Options:Entrances\nCreate Entrance\nEdit Entrance\nDelete Entrance", 
                "Select", "Cancel");
            return true;
        }
        case DIALOG_ADMIN_ORGANIZATIONS:
        {
            Dialog_Show(playerid, ShowDialogAdminOrg, DIALOG_STYLE_TABLIST_HEADERS, 
                COLOR_YELLOW "Admin Panel", "Options:Organizations\nCreate Organization\nEdit Organization\nDelete Organization", 
                "Select", "Cancel");
            return true;
        }
        case DIALOG_ADMIN_SERVER:
        {
            Dialog_Show(playerid, ShowDialogAdminServer, DIALOG_STYLE_TABLIST_HEADERS, 
                COLOR_YELLOW "Admin Panel", "Options:Server\nSet Server Time\nSet Server Weather\nSet Server Name\nSet Server Password\nSet Server Tag\nSet Server Maintainer\nChange Server Variables", 
                "Select", "Cancel");
            return true;
        }
        case DIALOG_SERVER_VARIABLES:
        {
            Dialog_Show(playerid, ShowDialogServerVars, DIALOG_STYLE_TABLIST_HEADERS, 
                COLOR_YELLOW "Admin Panel", "Options:Server vars\nSet Server Money\nSet Server Diamonds\nSet Server Golds", 
                "Select", "Cancel");
            return true;
        }
        case DIALOG_ADMIN_CHECK_ADMINS:
        {
            Dialog_Show(playerid, ShowDialogAdminCheckAdmins, DIALOG_STYLE_TABLIST_HEADERS, 
                COLOR_YELLOW "Admin Panel", "Options:Admins\nCheck Admins\nCheck Admins Online", 
                "Select", "Cancel");
            return true;
        }
        case DIALOG_ADMIN_SET_ADMIN:
        {
            Dialog_Show(playerid, ShowDialogAdminSetAdmin, DIALOG_STYLE_TABLIST_HEADERS, 
                COLOR_YELLOW "Admin Panel", "Options:Admins\nSet Admin\nRemove Admin", 
                "Select", "Cancel");
            return true;
        }
        // DIALOG_ADMIN_TELEPORT
        case DIALOG_ADMIN_TELEPORT:
        {
            Dialog_Show(playerid, ShowDialogAdminTeleport, DIALOG_STYLE_TABLIST_HEADERS, 
                COLOR_YELLOW "Admin Panel", "Options:Teleport\nTeleport to Player\nTeleport to Location\nTeleport to Business\nTeleport to Gate\nTeleport to Organization\nTeleport to Map", 
                "Select", "Cancel");
            return true;
        }
        case DIALOG_ADMIN_TELEPORT_PLAYER:
        {
            Dialog_Show(playerid, ShowDialogAdminTeleportPlayer, DIALOG_STYLE_INPUT, 
                COLOR_YELLOW "Admin Panel", 
                "Enter the player ID to teleport to:", 
                "Select", "Cancel");
            return true;
        }
        case DIALOG_ADMIN_TELEPORT_BUSINESS:
        {
            Dialog_Show(playerid, ShowDialogAdminTeleportBusiness, DIALOG_STYLE_INPUT, 
                COLOR_YELLOW "Admin Panel", "Enter the business ID to teleport to:", 
                "Select", "Cancel");
            return true;
        }
        // Functions
        case DIALOG_CREATE_JOB1:
        {
            Dialog_Show(playerid, ShowDialogCreateJob1, DIALOG_STYLE_INPUT, COLOR_YELLOW\
            "Create Job", "Provide a Descriptive Job Name:", "Continue", "Cancel");
            return true;
        }
        case DIALOG_CREATE_JOB2:
        {
            Dialog_Show(playerid, ShowDialogCreateJob2, DIALOG_STYLE_INPUT, COLOR_YELLOW\
            "Create Job", "Provide the Job Data\
            \n(Type[1-2], Skin, Salary, Ownerid[-1 for govt.]):", "Continue", "Cancel");
            return true;
        }
        default:
            return false;
    }
    return true;
}