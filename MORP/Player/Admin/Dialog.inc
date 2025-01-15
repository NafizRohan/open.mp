#include <Player\ShowDialog>
Dialog:ShowAdminPanel(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    switch (listitem) {
        case 0: {// Admin
            ShowDialog(playerid, DIALOG_ADMIN);
        }
        case 1: {// Admin Business
            ShowDialog(playerid, DIALOG_ADMIN_BUSINESS);
        }
        case 2: {// Admin Players
            ShowDialog(playerid, DIALOG_ADMIN_PLAYERS);
        }
        case 3: {// Admin Gates
            ShowDialog(playerid, DIALOG_ADMIN_GATES);
        }
        case 4: {// Admin Organizations
            ShowDialog(playerid, DIALOG_ADMIN_ORGANIZATIONS);
        }
        case 5: {// Admin SERVER
            ShowDialog(playerid, DIALOG_ADMIN_SERVER);
        }
    }
    return 1;
}

Dialog:ShowDialogAdmin(playerid, response, listitem, inputtext[]){
    if(!response) return ShowDialog(playerid, DIALOG_ADMIN_PANEL);

    switch (listitem) {
        case 0: {// Teleport
            ShowDialog(playerid, DIALOG_ADMIN_TELEPORT);
            return 1;
        }
        case 1: {// Check Admins
            ShowDialog(playerid, DIALOG_ADMIN_CHECK_ADMINS);
            return 1;
        }
        case 2: {// Set Admin
            ShowDialog(playerid, DIALOG_ADMIN_SET_ADMIN);
            return 1;
        }
    }
    return 1;
}

Dialog:ShowDialogAdminTeleport(playerid, response, listitem, inputtext[]){
    if(!response) return 1;

    switch (listitem) {
        case 0: {// Teleport to Player
            ShowDialog(playerid, DIALOG_ADMIN_TELEPORT_PLAYER);
            return 1;
        }
        case 1: {// Teleport to MAP
            if(MapX[playerid] == 0.0 && MapY[playerid] == 0.0 && MapZ[playerid] == 0.0){
                SEM(playerid, "You have not selected a location on the map.");
                return 1;
            }
            TeleportToCoords(playerid, MapX[playerid], MapY[playerid], MapZ[playerid]);
            return 1;
        }
        case 2: {// Teleport to Business
            ShowDialog(playerid, DIALOG_ADMIN_TELEPORT_BUSINESS);
            return 1;
        }
        case 3: {// Teleport to Gate
            return 1;
        }
        case 4: {// Teleport to Organization
            return 1;
        }
    }
    return 1;
}

Dialog:ShowDialogAdminTeleportPlayer(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(isnull(inputtext)) return ShowDialog(playerid, DIALOG_ADMIN_TELEPORT_PLAYER);
    if(!IsPlayerConnected(strval(inputtext))) return ShowDialog(playerid, DIALOG_ADMIN_TELEPORT_PLAYER);
    TeleportPlayer(playerid, strval(inputtext));
    return 1;
}

Dialog:ShowDialogAdminTeleportBusiness(playerid, response, listitem, inputtext[]){
    new bizid;
    if(!response) return 1;
    if(isnull(inputtext)) return ShowDialog(playerid, DIALOG_ADMIN_TELEPORT_BUSINESS);
    bizid = strval(inputtext);
    if(!IsBusiness(bizid)) return ShowDialog(playerid, DIALOG_ADMIN_TELEPORT_BUSINESS);
    //TeleportToCoords(playerid, gBusinessData[bizid][bPos][0], gBusinessData[bizid][bPos][1], gBusinessData[bizid][bPos][2]);
    return 1;
}

Dialog:ShowDialogAdminBusiness(playerid, response, listitem, inputtext[]){
    if(!response) return ShowDialog(playerid, DIALOG_ADMIN_PANEL);

    switch (listitem) {
        case 0: {// Create Business
            return 1;
        }
        case 1: {// Edit Business
            return 1;
        }
        case 2: {// Delete Business
            return 1;
        }
    }
    return 1;
}

Dialog:ShowDialogAdminPlayers(playerid, response, listitem, inputtext[]){
    if(!response) return ShowDialog(playerid, DIALOG_ADMIN_PANEL);

    switch (listitem) {
        case 0: {// Ban Player
            return 1;
        }
        case 1: {// Kick Player
            return 1;
        }
        case 2: {// Mute Player
            return 1;
        }
        case 3: {// Unmute Player
            return 1;
        }
    }
    return 1;
}

Dialog:ShowDialogAdminGates(playerid, response, listitem, inputtext[]){
    if(!response) return ShowDialog(playerid, DIALOG_ADMIN_PANEL);

    switch (listitem) {
        case 0: {// Create Gate
            return 1;
        }
        case 1: {// Edit Gate
            return 1;
        }
        case 2: {// Delete Gate
            return 1;
        }
    }
    return 1;
}

Dialog:ShowDialogAdminOrg(playerid, response, listitem, inputtext[]){
    if(!response) return ShowDialog(playerid, DIALOG_ADMIN_PANEL);

    switch (listitem) {
        case 0: {// Create Organization
            return 1;
        }
        case 1: {// Edit Organization
            return 1;
        }
        case 2: {// Delete Organization
            return 1;
        }
    }
    return 1;
}

Dialog:ShowDialogAdminServer(playerid, response, listitem, inputtext[]){
    if(!response) return ShowDialog(playerid, DIALOG_ADMIN_PANEL);

    switch (listitem) {
        case 0: {// Set Server Time
            return 1;
        }
        case 1: {// Set Server Weather
            return 1;
        }
        case 2: {// Set Server Name
            return 1;
        }
        case 3: {// Set Server Password
            return 1;
        }
        case 4: {// Set Server Tag
            return 1;
        }
        case 5: {// Set Server Maintainer
            return 1;
        }
        case 6: {// Change Server Variables
            ShowDialog(playerid, DIALOG_SERVER_VARIABLES);
            return 1;
        }
    }
    return 1;
}

