//                              Be name khoda                               //
#if defined _BAN_SYSTEMS_BY_MAMAD_PERSIAN_INC
	#endinput
#endif
#define _BAN_SYSTEMS_BY_MAMAD_PERSIAN_INC

forward TempBanHour(playerid, const Reason[], const MessageForPlayer[], hours, Token);
public TempBanHour(playerid, const Reason[], const MessageForPlayer[], hours, Token){
	CheckPlayerOnlineToCMD(playerid);
	CheckPlayerTokenCmp(playerid, Token);
	new PMM[200], PMM1[200];
	format(PMM, sizeof(PMM), "Shoma %d saat az server mahrum shodid, Dalil: %s.", hours, MessageForPlayer);
	format(PMM1, sizeof(PMM1), "You have been banned from the server for %d hours, Reason: %s.", hours, MessageForPlayer);
	SendPM(playerid, PMRed, PMM, PMM1, Token);
    new GPC[200];
    GPCI(playerid, GPC);
    GetNameP(playerid);
    new query[300];
    mysql_format(sql, query, sizeof(query), "INSERT INTO Temporary_Ban (PlayerName, Reason, gpci, ExpireAt) VALUES ('%e', '%e', '%e', NOW() + INTERVAL %d HOUR)", Name, Reason, GPC, hours);
    mysql_pquery(sql, query, "TempBanCallback");
	Querys++;
	Skick(playerid, MessageForPlayer, MessageForPlayer, Token, true);
    return 1;
}forward TempBanMinute(playerid, const Reason[], const MessageForPlayer[], minutes, Token);
public TempBanMinute(playerid, const Reason[], const MessageForPlayer[], minutes, Token){
	CheckPlayerOnlineToCMD(playerid);
	CheckPlayerTokenCmp(playerid, Token);
	new PMM[200], PMM1[200];
	format(PMM, sizeof(PMM), "Shoma %d daghighe az server mahrum shodid, Dalil: %s.", minutes, Reason);
	format(PMM1, sizeof(PMM1), "You have been banned from the server for %d minutes, Reason: %s.", minutes, Reason);
	SendPM(playerid, PMRed, PMM, PMM1, Token);
    new GPC[200];
	GPCI(playerid, GPC);
    GetNameP(playerid);
    new query[300];
    mysql_format(sql, query, sizeof(query), "INSERT INTO Temporary_Ban (PlayerName, Reason, gpci, ExpireAt) VALUES ('%e', '%e', '%e', NOW() + INTERVAL %d MINUTE)", Name, Reason, GPC, minutes);
    mysql_pquery(sql, query, "TempBanCallback");
	Querys++;
	Skick(playerid, MessageForPlayer, MessageForPlayer, Token, true);
    return 1;
}forward TempBanCallback(); public TempBanCallback() return Querys --;