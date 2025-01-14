#include <Player\playerdata>

stock bool:IsPlayerServerAdmin(playerid){
    if(gPlayerData[playerid][pAdmin]) return true;
    return false;
}

stock TeleportToCoords(playerid, Float:x, Float:y, Float:z, Float:angle = 0.0, interiorid = 0, worldid = 0, bool:freeze = false, bool:vehicle = true)
{
	new vehicleid = GetPlayerVehicleID(playerid);

	if(vehicle && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		foreach(new i : Player)
		{
			if(IsPlayerInVehicle(i, vehicleid))
			{
				SetPlayerInterior(i, interiorid);
				SetPlayerVirtualWorld(i, worldid);
			}
		}

		SetVehiclePos(vehicleid, x, y, z);
		SetVehicleZAngle(vehicleid, angle);
		SetVehicleVirtualWorld(vehicleid, worldid);
		LinkVehicleToInterior(vehicleid, interiorid);
	}
	else
	{
		SetPlayerPos(playerid, x, y, z);
		SetPlayerFacingAngle(playerid, angle);
		SetPlayerInterior(playerid, interiorid);
		SetPlayerVirtualWorld(playerid, worldid);
		SetCameraBehindPlayer(playerid);
	}

	if(freeze)
	{
		Freeze(playerid);
		SetTimerEx("Unfreeze", 5000, false, "i", playerid);
	}

	if(vehicle && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		SetTimerEx("VehicleUnfreeze", 5000, false, "iifffii", playerid, GetPlayerVehicleID(playerid), x, y, z, interiorid, worldid);
		Freeze(playerid);
	}
}

stock bool:TeleportPlayer(playerid, targetid){
    new Float:x, Float:y, Float:z, worldid, interiorid;
    GetPlayerPos(targetid, x, y, z);
    interiorid = GetPlayerInterior(targetid);
    worldid = GetPlayerVirtualWorld(targetid);

    TeleportToCoords(playerid, x, y, z, 0.0, interiorid, worldid, true, false);
    return true;
}

stock bool:SetPlayerHealthEx(playerid, Float:health){
	SetPlayerHealth(playerid, health);
	gPlayerData[playerid][pHealth] = health;

	mysql_format(db, DB_query, sizeof(DB_query), "UPDATE `PlayerData` SET `Health` = '%i' WHERE `ID` = %i",
	floatround(gPlayerData[playerid][pHealth]), gPlayerData[playerid][pID]);
	mysql_tquery(db, DB_query);
	return true;
}

stock bool:SetPlayerArmorEx(playerid, Float:armor){
    SetPlayerArmour(playerid, armor);
    gPlayerData[playerid][pArmor] = armor;

    mysql_format(db, DB_query, sizeof(DB_query), "UPDATE `PlayerData` SET `Armor` = '%i' WHERE `ID` = %i",
    floatround(gPlayerData[playerid][pArmor]), gPlayerData[playerid][pID]);
    mysql_tquery(db, DB_query);
    return true;
}

stock bool:IsBusiness(bizid){
	if(gBusinessData[bizid][bID] != 0) return true;
	return false;
}

stock SendMessage(playerid, color, const text[], {Float,_}:...)
{
	static
  	    args,
	    str[192];

	if((args = numargs()) <= 3)
	{
	    SCM(playerid, color, text);
	}
	else
	{
		while(--args >= 3)
		{
			#emit LCTRL 	5
			#emit LOAD.alt 	args
			#emit SHL.C.alt 2
			#emit ADD.C 	12
			#emit ADD
			#emit LOAD.I
			#emit PUSH.pri
		}
		#emit PUSH.S 	text
		#emit PUSH.C 	192
		#emit PUSH.C 	str
		#emit PUSH.S	8
		#emit SYSREQ.C 	format
		#emit LCTRL 	5
		#emit SCTRL 	4

		SCM(playerid, color, str);

		#emit RETN
	}
	return 1;
}

stock SendServerMessage(playerid, const message[])
{
	return SendMessage(playerid, -1, ""AQUA"Server: "WHITE"%s", message);
}
stock SendErrorMessage(playerid, const message[])
{
    return SendMessage(playerid, -1, ""RED"Error: "WHITE"%s", message);
}

stock SendAdminMessage(playerid, const message[])
{
	return SendMessage(playerid, -1, ""GREEN"Admin: "WHITE"%s", message);
}

stock SendAdminMessageToAll(const message[])
{
	new i;
	for(i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i) && IsPlayerServerAdmin(i))
		{
			SendAdminMessage(i, message);
		}
	}
	return 1;
}

stock SendServerMessageToAll(const message[])
{
	new i;
	for(i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
			SendServerMessage(i, message);
		}
	}
	return 1;
}

stock SendErrorMessageToAll(const message[])
{
	new i;
	for(i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
			SendErrorMessage(i, message);
		}
	}
	return 1;
}




