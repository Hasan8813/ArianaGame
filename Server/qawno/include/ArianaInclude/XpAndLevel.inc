#if defined _XPANDLEVEL_BY_MAMAD_PERSIAN_INC
	#endinput
#endif
#define _XPANDLEVEL_BY_MAMAD_PERSIAN_INC

stock GiveXp(playerid, amount, Token){
    CheckPlayerOnlineAndLogin(playerid);
    CheckPlayerTokenCmp(playerid, Token);
    SetPlayerPXP(playerid, GetPlayerPXP(playerid) + amount);
    new PM1[100], PM2[100];
    format(PM1, sizeof(PM1), "{A56D6E}Shoma {FFFFFF}%d {A56D6E}XP daryaft kardid.", amount);
    format(PM2, sizeof(PM2), "{A56D6E}You received {FFFFFF}%d {A56D6E}XP.", amount);
    SendPM(playerid, PMWhite, PM1, PM2, Token);
    CheckLevelUP(playerid, true, Token);
    return 1;
}stock GiveLevel(playerid, amount, Token){
    CheckPlayerOnlineAndLogin(playerid);
    CheckPlayerTokenCmp(playerid, Token);
    SetPlayerPlevel(playerid, GetPlayerPlevel(playerid) + amount);
    new PM1[100], PM2[100];
    PlayerPlaySound(playerid, 1139);
    format(PM1, sizeof(PM1), "{FFB0A0}Levele shoma {FFFFFF}%d {FFB0A0}adad ertegha peyda kard.", amount);
    format(PM2, sizeof(PM2), "{FFB0A0}Your level increased by {FFFFFF}%d{FFB0A0} units.", amount);
    SendPM(playerid, PMWhite, PM1, PM2, Token);
    CheckLevelUP(playerid, true, Token);
    return 1;
}stock RequiredXP(Level) return XP_FOR_LEVEL_1 + (Level * XP_FOR_LEVEL_UP);
stock CheckLevelUP(playerid, bool:FlagUpdateSet, Token){
    CheckPlayerOnlineAndLogin(playerid);
    CheckPlayerTokenCmp(playerid, Token);
    new Levelp = GetPlayerPlevel(playerid);
    new required = RequiredXP(Levelp);
    new LevelUped;
    while(GetPlayerPXP(playerid) >= required && GetPlayerPXP(playerid) > 0){
        SetPlayerPXP(playerid, GetPlayerPXP(playerid) - required);
        Levelp++;
        required = RequiredXP(Levelp);
        LevelUped++;
    }if(LevelUped > 0){
        CheckPlayerTokenCmp(playerid, Token);
        new PM1[130], PM2[130];
        SetPlayerPlevel(playerid, GetPlayerPlevel(playerid) + LevelUped);
        format(PM1, sizeof(PM1), "{FFB0A0}Levele shoma be {FFFFFF}%d {FFB0A0}ertegha peyda kard.", GetPlayerPlevel(playerid));
        format(PM2, sizeof(PM2), "{FFB0A0}Your level has been upgraded to {FFFFFF}%d{FFB0A0}.", GetPlayerPlevel(playerid));
        SendPM(playerid, PMWhite, PM1, PM2, Token);
        PlayerPlaySound(playerid, 1139);
        SetPlayerScore(playerid, GetPlayerPlevel(playerid));
    }if(FlagUpdateSet || LevelUped > 0) FlagUpdate(playerid);
    UpdateLevelAndXPTD(playerid, Token);
    return 1;
}