#if defined _MOVECAMERALOGINSYSTEM_BY_MAMAD_PERSIAN_INC
	#endinput
#endif
#define _MOVECAMERALOGINSYSTEM_BY_MAMAD_PERSIAN_INC

stock StartCameraMoveConnect(playerid){
	if(!IsPlayerConnected(playerid)) return 1;
	TogglePlayerSpectating(playerid, true);
	InterpolateCameraPos(playerid, 731.7502, -2124.1875, 4.5508, 722.3354, -1625.1458, 4.3728, 30000, CAMERA_MOVE);
	InterpolateCameraLookAt(playerid, 716.5193, -1640.8947, 2.4297, 700.2443, -1638.6643, 2.4297, 35000, CAMERA_MOVE);
	return 1;
}