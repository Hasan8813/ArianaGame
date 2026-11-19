#if defined _ZONES_BY_MAMAD_PERSIAN_INC
	#endinput
#endif
#define _ZONES_BY_MAMAD_PERSIAN_INC

stock LoadAllZoneArea(){
	LoadZoneArea69();
	return 1;
}

public OnPlayerEnterDynamicArea(playerid, STREAMER_TAG_AREA:areaid){
	CheckPlayerOnlineAndLogin(playerid);
	new Token = GetPlayerToken(playerid);
	if(areaid == MantagheyeMamnooArea) MushakShow(playerid, Token);//Area69
	return 1;
}
public OnPlayerLeaveDynamicArea(playerid, STREAMER_TAG_AREA:areaid){
	return 1;
}