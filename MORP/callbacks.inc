CB:KickPlayer(playerid) Kick(playerid);

CB:Freeze(playerid)
{
	TogglePlayerControllable(playerid, false);
	SetPVarInt(playerid, "Frozen", 1);
	return true;
}

CB:Unfreeze(playerid)
{
	TogglePlayerControllable(playerid, true);
	SetPVarInt(playerid, "Frozen", 0);
	return true;
}