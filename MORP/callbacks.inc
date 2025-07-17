// Prevent multiple inclusions of this file
#if defined _MORP_CALLBACKS_INCLUDED
	#endinput
#endif
#define _MORP_CALLBACKS_INCLUDED

// Callback to kick a player from the server
CB:KickPlayer(playerid) Kick(playerid);

// Callback to freeze a player (make them uncontrollable)
CB:Freeze(playerid)
{
	TogglePlayerControllable(playerid, false); // Disable player controls
	SetPVarInt(playerid, "Frozen", 1);         // Set 'Frozen' variable to 1
	return true;
}

// Callback to unfreeze a player (make them controllable again)
CB:Unfreeze(playerid)
{
	TogglePlayerControllable(playerid, true);  // Enable player controls
	SetPVarInt(playerid, "Frozen", 0);         // Set 'Frozen' variable to 0
	return true;
}