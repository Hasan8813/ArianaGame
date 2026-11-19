#if defined _PREMIUMSYSTEM_BY_MAMAD_PERSIAN_INC
	#endinput
#endif
#define _PREMIUMSYSTEM_BY_MAMAD_PERSIAN_INC

#define PREMIUM_CHECK_THRESHOLD_SEC   1800
#define PREMIUM_BUFFER_MS             8000

forward CheckPremium(playerid, Token);
public CheckPremium(playerid, Token){
	CheckPlayerOnlineToCMD(playerid);
	CheckPlayerTokenCmp(playerid, Token);
	new query[150];
    mysql_format(sql, query, sizeof(query), "SELECT pPer, TIMESTAMPDIFF(SECOND, NOW(), pPer) AS Remaining FROM `users` WHERE pid = %d -- PID:%d:%d", GetPlayerPID(playerid), playerid, Token);
    mysql_pquery(sql, query, "CheckPremiums", "id", playerid, Token);
	return 1;
}forward CheckPremiums(playerid, Token);
public CheckPremiums(playerid, Token){
	CheckPlayerOnlineToCMD(playerid);
	CheckPlayerTokenCmp(playerid, Token);
	new PPer[30];
    cache_get_value_name(0, "pPer", PPer, sizeof(PPer));
    SetPlayerPper(playerid, PPer);
	if(strcmp(PPer, "0000-00-00 00:00:00")){
		new Remaining;
		cache_get_value_name_int(0, "Remaining", Remaining);
		SetPlayerPperBool(playerid, 1);
		SetInt(playerid, PremiumKnownRemaining, Remaining);
		SetInt(playerid, PremiumKnownAt, gettime());
		if(Remaining <= PREMIUM_CHECK_THRESHOLD_SEC) StartTimerCheckPremium(playerid, Token, Remaining);
	}else{
		if(IsValidTimer(GetInt(playerid, TimerPremium))){
			KillTimer(GetInt(playerid, TimerPremium));
			SetPlayerPperBool(playerid, 0);
			DeleteV(playerid, TimerPremium);
		}
	}return 1;
}forward CheckPre(playerid, Token);
public CheckPre(playerid, Token){
	CheckPlayerOnlineAndLogin(playerid);
	CheckPlayerTokenCmp(playerid, Token);
	new query[150];
    mysql_format(sql, query, sizeof(query), "SELECT pPer, TIMESTAMPDIFF(SECOND, NOW(), pPer) AS Remaining FROM `users` WHERE pid = %d -- PID:%d:%d", GetPlayerPID(playerid), playerid, Token);
    mysql_pquery(sql, query, "CheckPrem", "id", playerid, Token);
	return 1;
}forward CheckPrem(playerid, Token);
public CheckPrem(playerid, Token){
	CheckPlayerOnlineAndLogin(playerid);
	CheckPlayerTokenCmp(playerid, Token);
	new PPer[30];
    cache_get_value_name(0, "pPer", PPer, sizeof(PPer));
    SetPlayerPper(playerid, PPer);
	if(!strcmp(PPer, "0000-00-00 00:00:00")){
		if(IsValidTimer(GetInt(playerid, TimerPremium))){
			KillTimer(GetInt(playerid, TimerPremium));
			SetPlayerPperBool(playerid, 0);
			DeleteV(playerid, TimerPremium);
		}
	}else{
		new Remaining;
		cache_get_value_name_int(0, "Remaining", Remaining);
		SetInt(playerid, PremiumKnownRemaining, Remaining);
		SetInt(playerid, PremiumKnownAt, gettime());
		if(Remaining <= PREMIUM_CHECK_THRESHOLD_SEC) StartTimerCheckPremium(playerid, Token, Remaining);
	}return 1;
}stock SetPer(playerid, days){
	new query[130];
	new Tok = GetPlayerToken(playerid);
	mysql_format(sql, query, sizeof(query), "UPDATE users SET pPer = DATE_ADD(NOW(), INTERVAL %d DAY) WHERE pid = %d; -- PID:%d:%d", days, GetPlayerPID(playerid), playerid, Tok); //Baraye set kardan be ruz
	mysql_pquery(sql, query, "CheckPremium", "id", playerid, Tok);
	return 1;
}stock GivePer(playerid, days){
	new Tok = GetPlayerToken(playerid);
	if(GetPlayerPperBool(playerid) == 1){
		new query[130];
		mysql_format(sql, query, sizeof(query), "UPDATE users SET pPer = DATE_ADD(pPer, INTERVAL %d DAY) WHERE pid = %d; -- PID:%d:%d", days, GetPlayerPID(playerid), playerid, Tok); //baraye ezafe kardan be ruz
		mysql_pquery(sql, query, "CheckPremium", "id", playerid, Tok);
	}else SetPer(playerid, days);
	return 1;
}
stock StartTimerCheckPremium(playerid, Token, Remaining){
	if(IsValidTimer(GetInt(playerid, TimerPremium))) KillTimer(GetInt(playerid, TimerPremium));
	if(Remaining <= 0){
		SetPlayerPperBool(playerid, 0);
		DeleteV(playerid, TimerPremium);
		return 1;
	}
	new WaitMs = (Remaining * 1000) + PREMIUM_BUFFER_MS;
	SetInt(playerid, TimerPremium, SetTimerEx("CheckPre", WaitMs, false, "id", playerid, Token));
	return 1;
}stock CheckPremiumForTimer(playerid, token){
	if(GetPlayerPperBool(playerid) == 0) return 1;      //premium nist, lazem nakard check konim
	if(IsValidTimer(GetInt(playerid, TimerPremium))) return 1;    //timere daghigh az ghabl dare karMikone, lazem nist tahmin bezanim
	new EstRemaining = GetInt(playerid, PremiumKnownRemaining) - (gettime() - GetInt(playerid, PremiumKnownAt));
	if(EstRemaining <= PREMIUM_CHECK_THRESHOLD_SEC) CheckPremium(playerid, token);
	return 1;
}