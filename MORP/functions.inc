#if defined _MORP_FUNCTIONS_INCLUDED
	#endinput
#endif
#define _MORP_FUNCTIONS_INCLUDED

// Checks if a player is a server admin
stock bool:IsPlayerServerAdmin(playerid){
	if(gPlayerData[playerid][pAdmin]) return true;
	return false;
}

// Teleports a player (and optionally their vehicle) to specified coordinates
stock TeleportToCoords(playerid, Float:x, Float:y, Float:z, Float:angle = 0.0, interiorid = 0, worldid = 0, bool:freeze = false, bool:vehicle = true)
{
	new vehicleid = GetPlayerVehicleID(playerid);

	// If player is driving a vehicle and 'vehicle' is true, teleport the vehicle and all passengers
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
		// Otherwise, teleport only the player
		SetPlayerPos(playerid, x, y, z);
		SetPlayerFacingAngle(playerid, angle);
		SetPlayerInterior(playerid, interiorid);
		SetPlayerVirtualWorld(playerid, worldid);
		SetCameraBehindPlayer(playerid);
	}

	// Optionally freeze the player after teleporting
	if(freeze)
	{
		Freeze(playerid);
		SetTimerEx("Unfreeze", 5000, false, "i", playerid);
	}

	// Optionally freeze the vehicle after teleporting
	if(vehicle && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		SetTimerEx("VehicleUnfreeze", 5000, false, "iifffii", playerid, GetPlayerVehicleID(playerid), x, y, z, interiorid, worldid);
		Freeze(playerid);
	}
}

// Teleports player to another player's position
stock bool:TeleportPlayer(playerid, targetid){
	new Float:x, Float:y, Float:z, worldid, interiorid;
	GetPlayerPos(targetid, x, y, z);
	interiorid = GetPlayerInterior(targetid);
	worldid = GetPlayerVirtualWorld(targetid);

	TeleportToCoords(playerid, x, y, z, 0.0, interiorid, worldid, true, false);
	return true;
}

// Sets player health and updates the database
stock bool:SetPlayerHealthEx(playerid, Float:health){
	SetPlayerHealth(playerid, health);
	gPlayerData[playerid][pHealth] = health;

	mysql_format(db, DB_query, sizeof(DB_query), "UPDATE `PlayerData` SET `Health` = '%i' WHERE `PlayerID` = %i",
	floatround(gPlayerData[playerid][pHealth]), gPlayerData[playerid][pID]);
	mysql_tquery(db, DB_query);
	return true;
}

// Sets player armor and updates the database
stock bool:SetPlayerArmorEx(playerid, Float:armor){
	SetPlayerArmour(playerid, armor);
	gPlayerData[playerid][pArmor] = armor;

	mysql_format(db, DB_query, sizeof(DB_query), "UPDATE `PlayerData` SET `Armor` = '%i' WHERE `PlayerID` = %i",
	floatround(gPlayerData[playerid][pArmor]), gPlayerData[playerid][pID]);
	mysql_tquery(db, DB_query);
	return true;
}

// Sets player skin and updates the database
stock bool:SetPlayerSkinEx(playerid, skinid) {
	SetPlayerSkin(playerid, skinid);
	gPlayerData[playerid][pSkin] = skinid;

	mysql_format(db, DB_query, sizeof(DB_query), "UPDATE `PlayerData` SET `Skin` = '%i' WHERE `PlayerID` = %i",
	gPlayerData[playerid][pSkin], gPlayerData[playerid][pID]);
	mysql_tquery(db, DB_query);
	return true;
}

// Sends a formatted message to a player (supports variable arguments)
stock bool:SendMessage(playerid, color, const text[], {Float,_}:...)
{
	static
		args,
		str[192];

	// If no formatting arguments, send the message directly
	if((args = numargs()) <= 3)
	{
		SCM(playerid, color, text);
	}
	else
	{
		// Format the message with additional arguments
		while(--args >= 3)
		{
			#emit LCTRL     5
			#emit LOAD.alt  args
			#emit SHL.C.alt 2
			#emit ADD.C     12
			#emit ADD
			#emit LOAD.I
			#emit PUSH.pri
		}
		#emit PUSH.S  text
		#emit PUSH.C  192
		#emit PUSH.C  str
		#emit PUSH.S  8
		#emit SYSREQ.C    format
		#emit LCTRL   5
		#emit SCTRL   4

		SCM(playerid, color, str);

		#emit RETN
	}
	return true;
}

// Sends a server message to a player
stock bool:SendServerMessage(playerid, const message[])
{
	return SendMessage(playerid, -1, ""AQUA"Server: "WHITE"%s", message);
}

// Sends an error message to a player
stock bool:SendErrorMessage(playerid, const message[])
{
	return SendMessage(playerid, -1, ""RED"Error: "WHITE"%s", message);
}

// Sends an admin message to a player
stock bool:SendAdminMessage(playerid, const message[])
{
	return SendMessage(playerid, -1, ""GREEN"Admin: "WHITE"%s", message);
}

// Sends an admin message to all connected admins
stock bool:SendAdminMessageToAll(const message[])
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

// Sends a server message to all connected players
stock bool:SendServerMessageToAll(const message[])
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

// Sends an error message to all connected players
stock bool:SendErrorMessageToAll(const message[])
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
