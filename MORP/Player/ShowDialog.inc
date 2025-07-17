#if defined _MORP_PLAYER_SHOWDIALOG_INCLUDED
    #endinput
#endif
#define _MORP_PLAYER_SHOWDIALOG_INCLUDED

// Dialog IDs for various dialogs in the system
enum {
    DIALOG_REGISTER,                // Registration dialog
    DIALOG_PASSWORD,                // Password input dialog
    DIALOG_CREATE_CHARACTER,        // Character creation dialog
    DIALOG_GENDER,                  // Gender selection dialog
    DIALOG_AGE,                     // Age input dialog
    DIALOG_LOGIN,                   // Character selection dialog
    // Admin Stuff
    DIALOG_ADMIN_PANEL,             // Main admin panel
    DIALOG_ADMIN,                   // Admin options
    DIALOG_ADMIN_BUSINESS,          // Business management
    DIALOG_ADMIN_PLAYERS,           // Player management
    DIALOG_ADMIN_GATES,             // Gates management
    DIALOG_ADMIN_ENTRANCES,         // Entrances management
    DIALOG_ADMIN_ORGANIZATIONS,     // Organizations management
    DIALOG_ADMIN_SERVER,            // Server settings
    DIALOG_SERVER_VARIABLES,        // Server variables
    DIALOG_ADMIN_TELEPORT,          // Teleport options
    DIALOG_ADMIN_TELEPORT_PLAYER,   // Teleport to player
    DIALOG_ADMIN_TELEPORT_BUSINESS, // Teleport to business
    DIALOG_ADMIN_CHECK_ADMINS,      // Check admins
    DIALOG_ADMIN_SET_ADMIN,         // Set admin
    // Server Details
    DIALOG_SERVER_DETAILS,          // Server details dialog
    // Functions
    DIALOG_CREATE_JOB1,             // Job creation 1
    DIALOG_CREATE_JOB2              // Job creation 2
};

// Shows a dialog to the player based on dialogid
stock bool:ShowDialog(playerid, dialogid, const string[] = "") {
    #pragma unused string
    switch (dialogid) {
        // Login-Register dialogs
        case DIALOG_REGISTER:
        {
            // Show registration dialog
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
            // Show password input dialog
            Dialog_Show(playerid, ShowPasswordBox, DIALOG_STYLE_PASSWORD, 
                COLOR_YELLOW "Login", 
                "Please enter your password to proceed:", 
                "Submit", "Cancel");
            return true;
        }
        case DIALOG_LOGIN:
        {
            // Show character selection dialog
            Dialog_Show(playerid, ShowCharacterBox, DIALOG_STYLE_TABLIST_HEADERS, 
                COLOR_YELLOW "Select Character", string, "Select", "Cancel");
            return true;
        }
        case DIALOG_CREATE_CHARACTER:
        {
            // Show character creation dialog
            Dialog_Show(playerid, ShowDialogCreate, DIALOG_STYLE_INPUT,
                COLOR_YELLOW "Create Character",
                "Enter your character name (format: John_Doe):",
                "Continue", "Cancel");
            return true;
        }
        case DIALOG_GENDER:
        {
            // Show gender selection dialog
            Dialog_Show(playerid, ShowDialogGender, DIALOG_STYLE_TABLIST_HEADERS,
                COLOR_YELLOW "Select Gender",
                "Select your character's gender\nMale\nFemale", "Select", "Cancel");
            return true;
        }
        case DIALOG_AGE:
        {
            // Show age input dialog
            Dialog_Show(playerid, ShowDialogAge, DIALOG_STYLE_INPUT,
                COLOR_YELLOW "Enter Age",
                "Enter your character's age (18-100):",
                "Continue", "Cancel");
            return true;
        }
        // Admin Stuff dialogs
        case DIALOG_ADMIN_PANEL:
        {
            // Show main admin panel
            Dialog_Show(playerid, ShowAdminPanel, DIALOG_STYLE_TABLIST_HEADERS, 
                COLOR_YELLOW "Admin Panel", "Options\nAdmins\nBusinesses\nPlayers\nGates\nEntrances\nOrganizations\nServer Settings",
                "Select", "Cancel");
            return true;
        }
        case DIALOG_ADMIN:
        {
            // Show admin options
            Dialog_Show(playerid, ShowDialogAdmin, DIALOG_STYLE_TABLIST_HEADERS, 
                COLOR_YELLOW "Admin Panel", "Options:Admin\nTeleport\nCheck Admins\nSet Admin", 
                "Select", "Cancel");
            return true;
        }
        case DIALOG_ADMIN_BUSINESS:
        {
            // Show business management options
            Dialog_Show(playerid, ShowDialogAdminBusiness, DIALOG_STYLE_TABLIST_HEADERS, 
                COLOR_YELLOW "Admin Panel", "Options:Business\nCreate Business\nEdit Business\nDelete Business", 
                "Select", "Cancel");
            return true;
        }
        case DIALOG_ADMIN_PLAYERS:
        {
            // Show player management options
            Dialog_Show(playerid, ShowDialogAdminPlayers, DIALOG_STYLE_TABLIST_HEADERS, 
                COLOR_YELLOW "Admin Panel", "Options:Players\nTeleport\nKick\nBan\nUnban\nMute\nUnmute\nSet Health\nSet Armor\nSet Money\nSet Hunger\nSet Thirst", 
                "Select", "Cancel");
            return true;
        }
        case DIALOG_ADMIN_GATES:
        {
            // Show gates management options
            Dialog_Show(playerid, ShowDialogAdminGates, DIALOG_STYLE_TABLIST_HEADERS, 
                COLOR_YELLOW "Admin Panel", "Options:Gates\nCreate Gate\nEdit Gate\nDelete Gate", 
                "Select", "Cancel");
            return true;
        }
        case DIALOG_ADMIN_ENTRANCES:
        {
            // Show entrances management options
            Dialog_Show(playerid, ShowDialogAdminEntrances, DIALOG_STYLE_TABLIST_HEADERS, 
                COLOR_YELLOW "Admin Panel", "Options:Entrances\nCreate Entrance\nEdit Entrance\nDelete Entrance", 
                "Select", "Cancel");
            return true;
        }
        case DIALOG_ADMIN_ORGANIZATIONS:
        {
            // Show organizations management options
            Dialog_Show(playerid, ShowDialogAdminOrg, DIALOG_STYLE_TABLIST_HEADERS, 
                COLOR_YELLOW "Admin Panel", "Options:Organizations\nCreate Organization\nEdit Organization\nDelete Organization", 
                "Select", "Cancel");
            return true;
        }
        case DIALOG_ADMIN_SERVER:
        {
            // Show server settings options
            Dialog_Show(playerid, ShowDialogAdminServer, DIALOG_STYLE_TABLIST_HEADERS, 
                COLOR_YELLOW "Admin Panel", "Options:Server\nSet Server Time\nSet Server Weather\nSet Server Name\nSet Server Password\nSet Server Tag\nSet Server Maintainer\nChange Server Variables", 
                "Select", "Cancel");
            return true;
        }
        case DIALOG_SERVER_VARIABLES:
        {
            // Show server variables options
            Dialog_Show(playerid, ShowDialogServerVars, DIALOG_STYLE_TABLIST_HEADERS, 
                COLOR_YELLOW "Admin Panel", "Options:Server vars\nSet Server Money\nSet Server Diamonds\nSet Server Golds", 
                "Select", "Cancel");
            return true;
        }
        case DIALOG_ADMIN_CHECK_ADMINS:
        {
            // Show check admins options
            Dialog_Show(playerid, ShowDialogAdminCheckAdmins, DIALOG_STYLE_TABLIST_HEADERS, 
                COLOR_YELLOW "Admin Panel", "Options:Admins\nCheck Admins\nCheck Admins Online", 
                "Select", "Cancel");
            return true;
        }
        case DIALOG_ADMIN_SET_ADMIN:
        {
            // Show set admin options
            Dialog_Show(playerid, ShowDialogAdminSetAdmin, DIALOG_STYLE_TABLIST_HEADERS, 
                COLOR_YELLOW "Admin Panel", "Options:Admins\nSet Admin\nRemove Admin", 
                "Select", "Cancel");
            return true;
        }
        // Teleport dialogs
        case DIALOG_ADMIN_TELEPORT:
        {
            // Show teleport options
            Dialog_Show(playerid, ShowDialogAdminTeleport, DIALOG_STYLE_TABLIST_HEADERS, 
                COLOR_YELLOW "Admin Panel", "Options:Teleport\nTeleport to Player\nTeleport to Location\nTeleport to Business\nTeleport to Gate\nTeleport to Organization\nTeleport to Map", 
                "Select", "Cancel");
            return true;
        }
        case DIALOG_ADMIN_TELEPORT_PLAYER:
        {
            // Show teleport to player input
            Dialog_Show(playerid, ShowDialogAdminTeleportPlayer, DIALOG_STYLE_INPUT, 
                COLOR_YELLOW "Admin Panel", 
                "Enter the player ID to teleport to:", 
                "Select", "Cancel");
            return true;
        }
        case DIALOG_ADMIN_TELEPORT_BUSINESS:
        {
            // Show teleport to business input
            Dialog_Show(playerid, ShowDialogAdminTeleportBusiness, DIALOG_STYLE_INPUT, 
                COLOR_YELLOW "Admin Panel", "Enter the business ID to teleport to:", 
                "Select", "Cancel");
            return true;
        }
        default:
            // Unknown dialogid
            return false;
    }
    return true;
}