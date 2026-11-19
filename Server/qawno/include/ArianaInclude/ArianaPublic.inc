// 								Be name khoda 								//
#if defined _PUBLIC_BY_MAMAD_PERSIAN_INC
	#endinput
#endif
#define _PUBLIC_BY_MAMAD_PERSIAN_INC

//Time
new worldtime_override = 0, worldtime_overridehour = 0, worldtime_overridemin  = 0, hour, minute, dd, mm, yy, timestr[12], timest[12];
//Namayesh va hazfe textdraw ha dar zamane spawn va mordane bazikon
stock ShowPlayerAllTextDraw(playerid, Token){
	CheckPlayerOnlineAndLogin(playerid);
	CheckPlayerTokenCmp(playerid, Token);
	//Time
   	TextDrawShowForPlayer(playerid,txtTimeDisp); TextDrawShowForPlayer(playerid,txtTimeDis);
	if(!worldtime_override){
		gettime(hour, minute); getdate(yy, mm, dd);
	}else{
		hour = worldtime_overridehour;
		minute = worldtime_overridemin;
	}
	SetPlayerTime(playerid,hour,minute);
	UpdateAllTD(playerid, Token);
	return 1;
}stock HidePlayerAllTextDraw(playerid, Token){
	CheckPlayerOnlineAndLogin(playerid);
	CheckPlayerTokenCmp(playerid, Token);
	//Time
	TextDrawHideForPlayer(playerid,txtTimeDisp); TextDrawHideForPlayer(playerid,txtTimeDis);
	//Gold
	PlayerTextDrawHide(playerid, GoldText[playerid]);
	PlayerTextDrawHide(playerid, XPText[playerid]);
	PlayerTextDrawHide(playerid, LevelText[playerid]);
	PlayerTextDrawHide(playerid, NameText[playerid]);
	return 1;
}
//Time And Weather
forward UpdateTimeAndWeather();
public UpdateTimeAndWeather(){
	if(!worldtime_override) {
    	gettime(hour, minute);
    	getdate(yy, mm, dd);
	}else{
		hour = worldtime_overridehour;
		minute = worldtime_overridemin;
	}format(timest, 12,"%d-%02d-%02d",yy,mm,dd);
   	TextDrawSetString(txtTimeDis,timest);
   	format(timestr, 12,"%02d:%02d",hour,minute);
   	TextDrawSetString(txtTimeDisp,timestr);
   	SetWorldTime(hour);
	new x=0;
	while(x!=MAX_PLAYERS) {
	     if(IsPlayerConnected(x) && GetPlayerState(x) != PLAYER_STATE_NONE) SetPlayerTime(x,hour,minute);
		 x++;
	}return 1;
}

