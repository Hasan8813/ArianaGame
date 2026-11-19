#if defined _UPDATEBAZIKONDATA_BY_MAMAD_PERSIAN_INC
	#endinput
#endif
#define _UPDATEBAZIKONDATA_BY_MAMAD_PERSIAN_INC


stock StartTimerUpdateData(){
    SetTimer("UpdatePlayerData", 5000, true);
    return 1;
}
stock FlagUpdate(playerid){
    VersionUpdate[playerid] += 1;
    return 1;
}
new ERRORSAVE;
forward UpdatePlayerData();
public UpdatePlayerData(){
    if(Querys > 800){
        ERRORSAVE++;
        print("[Warning]: The number of querys has increased significantly!");
        if(ERRORSAVE < 4) return 1;
        else ERRORSAVE = 0;
    }
    foreach(new PL : Player){
        if(GetPlayerLogin(PL) == 0) continue;
        new TK = GetPlayerToken(PL);
        LastUpdatePayCheck[PL]++;
        if(LastUpdatePayCheck[PL] >= 60){
            LastUpdatePayCheck[PL] = 0;
            UpdatePayCheck(PL, true, TK);
            FlagUpdate(PL);
        }
        if(VersionUpdate[PL] <= LastVersionUpdate[PL]) continue;
        SaveSeq[PL]++;
        new query[500];
        mysql_format(sql, query, sizeof(query), "UPDATE users SET pMoney = %d, pGold = %d, pLevel = %d, pXP = %d, pTimeplay = %d, pTimeplaymin = %d, pLang = %d, pSex = %d, AutoLogin = %d, pDrivLic = %d, pFlyLic = %d, pSailingLic = %d, pWeaponLic = %d, pWanted = %d, pJobId = %d, pSaveSeq = %d WHERE pid = %d AND pSaveSeq < %d -- PID:%d:%d", GetPlayerPmoney(PL), GetPlayerPgold(PL), GetPlayerPlevel(PL), GetPlayerPXP(PL), GetPlayerPtimeplay(PL), GetPlayerPtimeplaymin(PL), GetPlayerPlanguage(PL), GetPlayerPsex(PL), GetPlayerPAutoLogin(PL), GetPlayerPdrivlic(PL), GetPlayerPflylic(PL), GetPlayerPsailinglic(PL), GetPlayerPweaponlic(PL), GetPlayerPwanted(PL), GetPlayerPjob(PL), SaveSeq[PL], GetPlayerPID(PL), SaveSeq[PL], PL, TK);
        mysql_pquery(sql, query, "UpdateDataCallback", "iii", PL, VersionUpdate[PL], TK);
        Querys++;
        SendClientMessage(PL, -1, "Updated!");
    }return 1;
}forward UpdateDataCallback(playerid, Version, Token); 
public UpdateDataCallback(playerid, Version, Token){
    Querys--;
    CheckPlayerTokenCmp(playerid, Token);
    if(Version < LastVersionUpdate[playerid]) return 1;
    LastVersionUpdate[playerid] = Version;
    return 1;
}
forward UpdatePlayerDataDisconnect(playerid, token);
public UpdatePlayerDataDisconnect(playerid, token){
    if(GetPlayerLogin(playerid) == 0) return 1;
    CheckPlayerTokenCmp(playerid, token);
    UpdatePayCheck(playerid, false, token);
    SaveSeq[playerid]++;
    new query[500];
    mysql_format(sql, query, sizeof(query), "UPDATE users SET pMoney = %d, pGold = %d, pLevel = %d, pXP = %d, pTimeplay = %d, pTimeplaymin = %d, pLang = %d, pSex = %d, AutoLogin = %d, pDrivLic = %d, pFlyLic = %d, pSailingLic = %d, pWeaponLic = %d, pWanted = %d, pJobId = %d, pSaveSeq = %d WHERE pid = %d AND pSaveSeq < %d -- PID:%d:%d", GetPlayerPmoney(playerid), GetPlayerPgold(playerid), GetPlayerPlevel(playerid), GetPlayerPXP(playerid), GetPlayerPtimeplay(playerid), GetPlayerPtimeplaymin(playerid), GetPlayerPlanguage(playerid), GetPlayerPsex(playerid), GetPlayerPAutoLogin(playerid), GetPlayerPdrivlic(playerid), GetPlayerPflylic(playerid), GetPlayerPsailinglic(playerid), GetPlayerPweaponlic(playerid), GetPlayerPwanted(playerid), GetPlayerPjob(playerid), SaveSeq[playerid], GetPlayerPID(playerid), SaveSeq[playerid], playerid, token);
    mysql_pquery(sql, query, "UpdateDataCallbackDisconnect");
    Querys++;
    SetPlayerLogin(playerid, 0);
    return 1;
}forward UpdateDataCallbackDisconnect(); public UpdateDataCallbackDisconnect() return Querys--;