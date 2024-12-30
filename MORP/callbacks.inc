CB:KickPlayer(playerid) Kick(playerid);

CB:Freeze(playerid)
{
	TogglePlayerControllable(playerid, false);
	SetPVarInt(playerid, "Frozen", 1);
	return 1;
}

CB:Unfreeze(playerid)
{
	TogglePlayerControllable(playerid, true);
	SetPVarInt(playerid, "Frozen", 0);
	return 1;
}

CB:VehicleUnfreeze(playerid, vehicleid, Float:x, Float:y, Float:z, interior, world){
    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && IsPlayerInRangeOfPoint(playerid, 100.0, x, y, z) && GetPlayerInterior(playerid) == interior && GetPlayerVirtualWorld(playerid) == world)
	{
		SetVehiclePos(vehicleid, x, y, z);
	}

	Unfreeze(playerid);
}