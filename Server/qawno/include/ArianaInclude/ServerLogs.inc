#if defined _LOG_GIRI_BY_MAMAD_PERSIAN_INC
	#endinput
#endif
#define _LOG_GIRI_BY_MAMAD_PERSIAN_INC

//Log giri money
forward MoneyLog(Money, playertarget, playergive, admin, const reason[], const command[]);
public MoneyLog(Money, playertarget, playergive, admin, const reason[], const command[]){
    new Name1[25], Name2[25], Name3[25], query[800], PON, GiveRef, AdminRef;
    if(Money < 0) PON = 2;
    else if(Money > 0) PON = 1;
    GetPlayerName(playertarget, Name1, sizeof(Name1));
    if(playergive == -1){
        Name2 = "None";
        GiveRef = 0;
    }else{
        GetPlayerName(playergive, Name2, sizeof(Name2));
        GiveRef = GetPlayerPID(playergive);
    }if(admin == -1){
        Name3 = "None";
        AdminRef = 0;
    }else{
        GetPlayerName(admin, Name3, sizeof(Name3));
        AdminRef = GetPlayerPID(admin);
    }mysql_format(sql, query, sizeof(query), "INSERT INTO MoneyLog (Money, PlayerTarget, PlayerTargetRef, PlayerGive, PlayerGiveRef, Admin, AdminRef, Command, Reason, PON) VALUES (%d, '%e', %d, '%e', %d, '%e', %d, '%e', '%e', %d)", Money, Name1, (playertarget != -1) ? GetPlayerPID(playertarget) : 0, Name2, GiveRef, Name3, AdminRef, command, reason, PON);
    mysql_pquery(sql, query, "MoneyLogCallback");
    Querys++;
    return 1;
}forward MoneyLogCallback(); public MoneyLogCallback() return Querys--;
//Log giri Gold
forward GoldLog(Gold, playertarget, playergive, admin, const reason[], const command[]);
public GoldLog(Gold, playertarget, playergive, admin, const reason[], const command[]){
    new Name1[25], Name2[25], Name3[25], query[800], PON, GiveRef, AdminRef;
    if(Gold < 0) PON = 2;
    else if(Gold > 0) PON = 1;
    GetPlayerName(playertarget, Name1, sizeof(Name1));
    if(playergive == -1){
        Name2 = "None";
        GiveRef = 0;
    }else{
        GetPlayerName(playergive, Name2, sizeof(Name2));
        GiveRef = GetPlayerPID(playergive);
    }if(admin == -1){
        Name3 = "None";
        AdminRef = 0;
    }else{
        GetPlayerName(admin, Name3, sizeof(Name3));
        AdminRef = GetPlayerPID(admin);
    }mysql_format(sql, query, sizeof(query), "INSERT INTO GoldLog (Gold, PlayerTarget, PlayerTargetRef, PlayerGive, PlayerGiveRef, Admin, AdminRef, Command, Reason, PON) VALUES (%d, '%e', %d, '%e', %d, '%e', %d, '%e', '%e', %d)", Gold, Name1, (playertarget != -1) ? GetPlayerPID(playertarget) : 0, Name2, GiveRef, Name3, AdminRef, command, reason, PON);
    mysql_pquery(sql, query, "GoldLogCallback");
    Querys++;
    return 1;
}forward GoldLogCallback(); public GoldLogCallback() return Querys--;
//Log giriye query ha
stock SQLLogError(const message[]){
    new filename[64];
    new year, month, day;
    getdate(year, month, day);
    format(filename, sizeof(filename), "SQL.ERROR/QUERY.ERROR_%04d-%02d-%02d.txt", year, month, day);
    new File:file = fopen(filename, io_append);
    if(!file) return printf("[ERROR] LogError: Unable to open file '%s'.", filename), 0;
    new timestamp[32];
    new hourr, minutee, second;
    gettime(hourr, minutee, second);
    format(timestamp, sizeof(timestamp), "[%02d:%02d:%02d] ", hourr, minutee, second);
    new logLine[256];
    format(logLine, sizeof(logLine), "%s%s\n", timestamp, message);
    fwrite(file, logLine);
    fclose(file);
    return 1;
}
//Log giriye error haye sql
stock SQLError(const message[]){
    new filename[64];
    new year, month, day;
    getdate(year, month, day);
    format(filename, sizeof(filename), "SQL.ERROR/SQL.ERROR_%04d-%02d-%02d.txt", year, month, day);
    new File:file = fopen(filename, io_append);
    if(!file) return printf("[ERROR] LogError: Unable to open file '%s'.", filename), 0;
    new timestamp[32];
    new hourr, minutee, second;
    gettime(hourr, minutee, second);
    format(timestamp, sizeof(timestamp), "[%02d:%02d:%02d] ", hourr, minutee, second);
    new logLine[256];
    format(logLine, sizeof(logLine), "%s%s\n", timestamp, message);
    fwrite(file, logLine);
    fclose(file);
    return 1;
}
//Log hameye error ha
stock ErrorLog(const message[]){
    new filename[64];
    new year, month, day;
    getdate(year, month, day);
    format(filename, sizeof(filename), "ERROR_%04d-%02d-%02d.txt", year, month, day);
    new File:file = fopen(filename, io_append);
    if(!file) return printf("[ERROR] LogError: Unable to open file '%s'.", filename), 0;
    new timestamp[32];
    new hourr, minutee, second;
    gettime(hourr, minutee, second);
    format(timestamp, sizeof(timestamp), "[%02d:%02d:%02d] ", hourr, minutee, second);
    new logLine[256];
    format(logLine, sizeof(logLine), "%s%s\n", timestamp, message);
    fwrite(file, logLine);
    fclose(file);
    return 1;
}
//log giriye ip ha moghe login
stock LogAccountLogin(playerid, Token){
    CheckPlayerOnlineToCMD(playerid);
    CheckPlayerTokenCmp(playerid, Token);
    new ip[16], gpcii[200], query[400];
    GetPlayerIp(playerid, ip, sizeof(ip));
    GPCI(playerid, gpcii);
    GetNameP(playerid);
    mysql_format(sql, query, sizeof(query), "INSERT INTO AccountLoginLog (AccountName, AccountPID, IP, GPCI, AutoLogin) VALUES ('%e', %d, '%e', '%e', %d)", Name, GetPlayerPID(playerid), ip, gpcii, GetInt(playerid, AutoLoginSuccessful));
    mysql_pquery(sql, query, "AccountLoginLogCallback");
    Querys++;
    return 1;
}forward AccountLoginLogCallback(); public AccountLoginLogCallback() return Querys--;