#include <Player\ShowDialog>

// Shows the main admin panel dialog
Dialog:ShowAdminPanel(playerid, response, listitem, inputtext[])
{
    if(!response) return true; // If dialog was cancelled, do nothing
    switch (listitem)
    {
        case 0: ShowDialog(playerid, DIALOG_ADMIN); // Open admin main dialog
        case 1: ShowDialog(playerid, DIALOG_ADMIN_BUSINESS); // Open business admin dialog
        case 2: ShowDialog(playerid, DIALOG_ADMIN_PLAYERS); // Open players admin dialog
        case 3: ShowDialog(playerid, DIALOG_ADMIN_GATES); // Open gates admin dialog
        case 4: ShowDialog(playerid, DIALOG_ADMIN_ORGANIZATIONS); // Open organizations admin dialog
        case 5: ShowDialog(playerid, DIALOG_ADMIN_SERVER); // Open server admin dialog
    }
    return true;
}

// Shows the admin dialog with various options
Dialog:ShowDialogAdmin(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowDialog(playerid, DIALOG_ADMIN_PANEL); // Go back to admin panel if cancelled
    switch (listitem)
    {
        case 0: ShowDialog(playerid, DIALOG_ADMIN_TELEPORT); // Teleport options
        case 1: ShowDialog(playerid, DIALOG_ADMIN_CHECK_ADMINS); // Check online admins
        case 2: ShowDialog(playerid, DIALOG_ADMIN_SET_ADMIN); // Set admin level
    }
    return true;
}

// Shows teleport options for admin
Dialog:ShowDialogAdminTeleport(playerid, response, listitem, inputtext[])
{
    if(!response) return true; // Cancelled
    switch (listitem)
    {
        case 0: ShowDialog(playerid, DIALOG_ADMIN_TELEPORT_PLAYER); // Teleport to player
        case 5:
        {
            // Teleport to map location if selected
            if(MapX[playerid] == 0.0 && MapY[playerid] == 0.0 && MapZ[playerid] == 0.0)
            {
                SEM(playerid, "You have not selected a location on the map.");
            }
            else
            {
                TeleportToCoords(playerid, MapX[playerid], MapY[playerid], MapZ[playerid]);
                SSM(playerid, "You have been teleported to the selected location.");
            }
        }
    }
    return true;
}

// Teleport admin to another player by ID
Dialog:ShowDialogAdminTeleportPlayer(playerid, response, listitem, inputtext[])
{
    if(!response) return true; // Cancelled
    if(isnull(inputtext)) return ShowDialog(playerid, DIALOG_ADMIN_TELEPORT_PLAYER); // No input
    new targetid = strval(inputtext);
    if(!IsPlayerConnected(targetid)) return ShowDialog(playerid, DIALOG_ADMIN_TELEPORT_PLAYER); // Invalid player
    TeleportPlayer(playerid, targetid); // Teleport to player
    return true;
}

// Shows admin players dialog (stub for future features)
Dialog:ShowDialogAdminPlayers(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowDialog(playerid, DIALOG_ADMIN_PANEL); // Go back if cancelled
    // Add player management features here
    return true;
}

// Shows admin gates dialog (stub for future features)
Dialog:ShowDialogAdminGates(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowDialog(playerid, DIALOG_ADMIN_PANEL); // Go back if cancelled
    // Add gate management features here
    return true;
}

// Shows admin organizations dialog (stub for future features)
Dialog:ShowDialogAdminOrg(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowDialog(playerid, DIALOG_ADMIN_PANEL); // Go back if cancelled
    // Add organization management features here
    return true;
}

// Shows admin server dialog with options
Dialog:ShowDialogAdminServer(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowDialog(playerid, DIALOG_ADMIN_PANEL); // Go back if cancelled
    switch (listitem)
    {
        case 6: ShowDialog(playerid, DIALOG_SERVER_VARIABLES); // Show server variables dialog
    }
    return true;
}
