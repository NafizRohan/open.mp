#include <YSI_Coding\y_hooks>

// Prevent multiple inclusion of this file
#if defined _MORP_CORE_DEFINES_INCLUDED
    #endinput
#endif
#define _MORP_CORE_DEFINES_INCLUDED

// Color definitions (RGBA)
#define SERVER_COLOR        0xFF0ABAB5    // Main server color
#define SECONDARY_COLOR     0xFF121212    // Secondary color

// Text color codes for messages
#define WHITE				"{FFFFFF}"
#define GREY				"{AFAFAF}"
#define RED					"{FF0000}"
#define GREEN				"{006400}"
#define YELLOW              "{FFFF00}"
#define ORANGE    			"{FFA500}"
#define AQUA				"{24F0FF}"

// Alternative color defines (for compatibility)
#define COLOR_YELLOW        "{FFFF00}"
#define COLOR_WHITE			"{FFFFFF}"

// Message sending function aliases
#define SCM         SendClientMessage     // Shortcut for SendClientMessage
#define SEM         SendErrorMessage      // Shortcut for SendErrorMessage
#define SSM         SendServerMessage     // Shortcut for SendServerMessage

// Callback macro for quick forward/public declaration
#define CB:%0(%1) \
forward %0(%1);public %0(%1)

// Directory for player logs
#define PLAYER_LOG_DIR "Logs/Player/Master Accounts/"

// Limits for various entities
#define MAX_BUSINESS            100       // Maximum number of businesses
#define MAX_ORGANIZATIONS       100       // Maximum number of organizations
#define MAX_GATES               100       // Maximum number of gates
#define MAX_ADMINS              10        // Maximum number of admins
#define MAX_JOBS                10        // Maximum number of jobs

// Initialization hook
hook OnGameModeInit()
{
    print("MORP Core(Defines) Initialized.");
    return true;
}

// Cleanup hook
hook OnGameModeExit()
{
    print("MORP Core(Defines) Unloaded.");
    return true;
}