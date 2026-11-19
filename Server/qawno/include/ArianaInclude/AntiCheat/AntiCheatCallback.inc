//                              Be name khoda                               //
#if defined _ANTICHEAT_BY_MAMAD_PERSIAN_INC
	#endinput
#endif
#define _ANTICHEAT_BY_MAMAD_PERSIAN_INC

forward OnCheatDetected(playerid, ip_address[], type, code);
#include "ArianaInclude/AntiCheat/nex-ac_fa.lang"
#include "ArianaInclude/AntiCheat/nex-ac"
#include "ArianaInclude/AntiCheat/Ariana_AntiCheat.inc"
public OnCheatDetected(playerid, ip_address[], type, code){
	SendClientMessage(playerid, -1, "Hooy Cheater %d, %d", code, type);
	return 1;
}