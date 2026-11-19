#if defined _ADMINCMD_BY_MAMAD_PERSIAN_INC
	#endinput
#endif
#define _ADMINCMD_BY_MAMAD_PERSIAN_INC


CMD:codelog(playerid){
    new ip[50];
    GetPlayerIp(playerid, ip, sizeof(ip));
    GetNameP(playerid);
    new code[7];
    format(code, sizeof(code), "%06d", random(1000000));
    new query[256];
    mysql_format(sql, query, sizeof(query), "INSERT INTO AdminLogAccess (AdminName, IP, Code, ExpireAt) VALUES ('%e', '%e', '%e', NOW() + INTERVAL 1 HOUR)", Name, ip, code);
    mysql_pquery(sql, query, "CodeLogCallback", "isd", playerid, code, GetPlayerToken(playerid));
    return 1;
}forward CodeLogCallback(playerid, const code[], Token);
public CodeLogCallback(playerid, const code[], Token){
    if(cache_affected_rows() == 0) return SendPM(playerid, PMError, "Lotfan ba'dan talash konid", "Please try again later", Token);
	CheckPlayerOnlineAndLogin(playerid);
	CheckPlayerTokenCmp(playerid, Token);
	new msg[150], msg1[150];
    format(msg, sizeof(msg), "Code vorude shoma be ghesmat log ha: {FFFFFF}%s%s, Modat zamane mo'tabar budan: {FFFFFF}1%s saat.", code, RangPMKahroba, RangPMKahroba);
	format(msg1, sizeof(msg1), "Your access code for the logs section: {FFFFFF}%s%s, Validity period: {FFFFFF}1%s hour.", code, RangPMKahroba, RangPMKahroba);
	SendPM(playerid, PMKahrobA, msg, msg1, Token);
	return 1;
}