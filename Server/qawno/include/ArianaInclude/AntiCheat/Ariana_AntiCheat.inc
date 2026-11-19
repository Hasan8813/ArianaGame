#if defined _ARIANA_ANTICHEAT_BY_MAMAD_PERSIAN_INC
	#endinput
#endif
#define _ARIANA_ANTICHEAT_BY_MAMAD_PERSIAN_INC

new AntiEnterAllCar[MAX_PLAYERS];
new RemovePlayerVehVariable[MAX_PLAYERS];
stock ResetAntiCheatVariable(playerid){
    AntiEnterAllCar[playerid] = 0;
	RemovePlayerVehVariable[playerid] = 0;
    return 1;
}
#define EjectPlayerVehicle(%0) RemovePlayerFromVehicle(%0), RemovePlayerVehVariable[%0] = 1
#define ResetPlayerAntiRemoveVehVariable(%0) AntiEnterAllCar[%0] = 0, RemovePlayerVehVariable[%0] = 0
IPacket:200(playerid, BitStream:bs){
	if(RemovePlayerVehVariable[playerid] == 1){
		AntiEnterAllCar[playerid]++;
		if(AntiEnterAllCar[playerid] >= 90){
            new IP[46];
            GetPlayerIp(playerid, IP);
			OnCheatDetected(playerid, IP, 0, 101);
			AntiEnterAllCar[playerid] = 0;
		}return 0;
	}
	return 1;
} 