#if !defined(MORP_CORE_DEFINES_INC)
    #endinput
#endif
#define MORP_CORE_DEFINES_INC


#define SERVER_COLOR        0xFF0ABAB5
#define SECONDARY_COLOR     0xFF121212

#define WHITE				"{FFFFFF}"
#define GREY				"{AFAFAF}"
#define RED					"{FF0000}"
#define GREEN				"{006400}"
#define YELLOW              "{FFFF00}"
#define ORANGE    			"{FFA500}"
#define AQUA				"{24F0FF}"

#define COLOR_YELLOW            "{FFFF00}"
#define COLOR_WHITE				"{FFFFFF}"

#define SCM         SendClientMessage
#define SEM         SendErrorMessage
#define SSM         SendServerMessage

#define CB:%0(%1) \
forward %0(%1);public %0(%1)

#define PLAYER_LOG_DIR "Logs/Player/Master Accounts/"

#define MAX_BUSINESS            100
#define MAX_ORGANIZATIONS       100
#define MAX_GATES               100
#define MAX_ADMINS              10
#define MAX_JOBS                10
