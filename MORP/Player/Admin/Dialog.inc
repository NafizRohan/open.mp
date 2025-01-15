#include <Player\ShowDialog>

Dialog:ShowAdminPanel(playerid, response, listitem, inputtext[])
{
    if(!response) return true;
    switch (listitem)
    {
        case 0:
        {
            ShowDialog(playerid, DIALOG_ADMIN);
            return true;
        }
        case 1:
        {
            ShowDialog(playerid, DIALOG_ADMIN_BUSINESS);
            return true;
        }
        case 2:
        {
            ShowDialog(playerid, DIALOG_ADMIN_PLAYERS);
            return true;
        }
        case 3:
        {
            ShowDialog(playerid, DIALOG_ADMIN_GATES);
            return true;
        }
        case 4:
        {
            ShowDialog(playerid, DIALOG_ADMIN_ORGANIZATIONS);
            return true;
        }
        case 5:
        {
            ShowDialog(playerid, DIALOG_ADMIN_SERVER);
            return true;
        }
        default: return true;
    }
    return true;
}

Dialog:ShowDialogAdmin(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowDialog(playerid, DIALOG_ADMIN_PANEL);
    switch (listitem)
    {
        case 0:
        {
            ShowDialog(playerid, DIALOG_ADMIN_TELEPORT);
            return true;
        }
        case 1:
        {
            ShowDialog(playerid, DIALOG_ADMIN_CHECK_ADMINS);
            return true;
        }
        case 2:
        {
            ShowDialog(playerid, DIALOG_ADMIN_SET_ADMIN);
            return true;
        }
        default: return true;
    }
    return true;
}

Dialog:ShowDialogAdminTeleport(playerid, response, listitem, inputtext[])
{
    if(!response) return true;
    switch (listitem)
    {
        case 0:
        {
            ShowDialog(playerid, DIALOG_ADMIN_TELEPORT_PLAYER);
            return true;
        }
        case 1:
        {
            if(MapX[playerid] == 0.0 && MapY[playerid] == 0.0 && MapZ[playerid] == 0.0)
            {
                SEM(playerid, "You have not selected a location on the map.");
                return true;
            }
            TeleportToCoords(playerid, MapX[playerid], MapY[playerid], MapZ[playerid]);
            return true;
        }
        case 2:
        {
            ShowDialog(playerid, DIALOG_ADMIN_TELEPORT_BUSINESS);
            return true;
        }
        case 3:
        {
            return true;
        }
        case 4:
        {
            return true;
        }
        default: return true;
    }
    return true;
}

Dialog:ShowDialogAdminTeleportPlayer(playerid, response, listitem, inputtext[])
{
    if(!response) return true;
    if(isnull(inputtext)) return ShowDialog(playerid, DIALOG_ADMIN_TELEPORT_PLAYER);
    if(!IsPlayerConnected(strval(inputtext))) return ShowDialog(playerid, DIALOG_ADMIN_TELEPORT_PLAYER);
    TeleportPlayer(playerid, strval(inputtext));
    return true;
}

Dialog:ShowDialogAdminTeleportBusiness(playerid, response, listitem, inputtext[])
{
    new bizid;
    if(!response) return true;
    if(isnull(inputtext)) return ShowDialog(playerid, DIALOG_ADMIN_TELEPORT_BUSINESS);
    bizid = strval(inputtext);
    if(!IsBusiness(bizid)) return ShowDialog(playerid, DIALOG_ADMIN_TELEPORT_BUSINESS);
    //TeleportToCoords(playerid, gBusinessData[bizid][bPos][0], gBusinessData[bizid][bPos][1], gBusinessData[bizid][bPos][2]);
    return true;
}

Dialog:ShowDialogAdminBusiness(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowDialog(playerid, DIALOG_ADMIN_PANEL);
    switch (listitem)
    {
        case 0:
        {
            return true;
        }
        case 1:
        {
            return true;
        }
        case 2:
        {
            return true;
        }
        default: return true;
        
    }
    return true;
}

Dialog:ShowDialogAdminPlayers(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowDialog(playerid, DIALOG_ADMIN_PANEL);
    switch (listitem)
    {
        case 0:
        {
            return true;
        }
        case 1:
        {
            return true;
        }
        case 2:
        {
            return true;
        }
        case 3:
        {
            return true;
        }
        default: return true;
    }
    return true;
}

Dialog:ShowDialogAdminGates(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowDialog(playerid, DIALOG_ADMIN_PANEL);
    switch (listitem)
    {
        case 0:
        {
            return true;
        }
        case 1:
        {
            return true;
        }
        case 2:
        {
            return true;
        }
        default: return true;
    }
    return true;
}

Dialog:ShowDialogAdminOrg(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowDialog(playerid, DIALOG_ADMIN_PANEL);
    switch (listitem)
    {
        case 0:
        {
            return true;
        }
        case 1:
        {
            return true;
        }
        case 2:
        {
            return true;
        }
        default: return true;
    }
    return true;
}

Dialog:ShowDialogAdminServer(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowDialog(playerid, DIALOG_ADMIN_PANEL);
    switch (listitem)
    {
        case 0:
        {
            return true;
        }
        case 1:
        {
            return true;
        }
        case 2:
        {
            return true;
        }
        case 3:
        {
            return true;
        }
        case 4:
        {
            return true;
        }
        case 5:
        {
            return true;
        }
        case 6:
        {
            ShowDialog(playerid, DIALOG_SERVER_VARIABLES);
            return true;
        }
        default: return true;
    }
    return true;
}

