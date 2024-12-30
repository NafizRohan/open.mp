#include <YSI_Coding\y_hooks>


CB:VehicleCameraStart(playerid, Float:pos_x, Float:pos_y, Float:pos_z, Float:angle, time)
{
	// Define the distance for the camera behind the vehicle
	new Float:distance = 8.0;

	// Convert the angle from degrees to radians
	new Float:angle_rad = angle * (3.141592653589793 / 180.0); // π/180 converts degrees to radians

	// Calculate the X and Y offsets for behind-camera position using trigonometry
	new Float:offset_x = distance * floatcos(angle_rad/2); // Add π to angle for "behind" the vehicle
	new Float:offset_y = distance * floatsin(angle_rad/2); // Add π to angle for "behind" the vehicle

	// Set the camera to interpolate to the new position
	InterpolateCameraPos(
		playerid,
		pos_x, pos_y, pos_z + 10.0, // Initial camera position (above)
		pos_x + offset_x, pos_y + offset_y, pos_z + 1.4, // Target camera position (behind)
		time
	);

	// Set the camera to look at the vehicle's position
	InterpolateCameraLookAt(
		playerid,
		pos_x, pos_y, pos_z, // Start looking at vehicle center
		pos_x, pos_y, pos_z, // End looking at the same vehicle position
		time
	);

	// Set a timer to reset the camera after the animation ends
	SetTimerEx("VehicleCameraEnd", time, false, "i", playerid);

	return 1;
}



CB:VehicleCameraEnd(playerid)
{
	SetCameraBehindPlayer(playerid);
	return 1;
}

hook OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	if(ispassenger) return 1;

	new Float:pos_x, Float:pos_y, Float:pos_z, Float:angle;
	GetVehiclePos(vehicleid, pos_x, pos_y, pos_z);
	GetVehicleZAngle(vehicleid, angle);
	printf("%f", angle);

	SetTimerEx("VehicleCameraStart", 3000, false, "iffffi", playerid, pos_x, pos_y, pos_z, angle, 3000);
	return 1;
}

CMD:veh(playerid, const params[]){
	new Float:x, Float:y, Float:z, Float:angle;
	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, angle);

	CreateVehicle(541, x, y, z, angle, -1, -1, -1, -1);
	return 1;
}