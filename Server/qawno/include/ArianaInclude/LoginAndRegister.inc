#if defined _LoginAndRegister_BY_MAMAD_PERSIAN_INC
	#endinput
#endif
#define _LoginAndRegister_BY_MAMAD_PERSIAN_INC

forward CheckTempBanForLogin(playerid, Token);
public CheckTempBanForLogin(playerid, Token){
    CheckPlayerOnlineToCMD(playerid);
    CheckPlayerTokenCmp(playerid, Token);
    GetNameP(playerid);
    new query[188], GPC[200];
    GPCI(playerid, GPC);
    mysql_format(sql, query, sizeof(query), "SELECT Reason, ExpireAt FROM Temporary_Ban WHERE PlayerName = '%e' AND gpci = '%e' LIMIT 1 -- PID:%d:%d", Name, GPC, playerid, Token);
    mysql_tquery(sql, query, "CheckTempBan", "id", playerid, Token);
    return 1;
}forward CheckTempBan(playerid, Token);
public CheckTempBan(playerid, Token){
    CheckPlayerOnlineToCMD(playerid);
    CheckPlayerTokenCmp(playerid, Token);
    if(cache_num_rows() > 0){
        new Reason[88], UnbanTime[30], MSG[228];
        cache_get_value_name(0, "Reason", Reason, sizeof(Reason));
        cache_get_value_name(0, "ExpireAt", UnbanTime, sizeof(UnbanTime));
        format(MSG, sizeof(MSG), "Shoma be dalile: {FFFFFF}%s{FF0000}, ta {FFFFFF}%s {FF0000}nemitavanid varede bazi shavid.", Reason, UnbanTime);
        Skick(playerid, MSG, MSG, Token, true);
    }else CheckAccount(playerid, Token);
    return 1;
}forward CheckAccount(playerid, Token);
public CheckAccount(playerid, Token){
    CheckPlayerOnlineToCMD(playerid);
    CheckPlayerTokenCmp(playerid, Token);
    new query[400];
    GetNameP(playerid);
    mysql_format(sql, query, sizeof(query), "SELECT pid, pKey, pEmail, pMoney, pLevel, pXP, pGold, pWanted, pJobId, pTimePlay, pTimePlaymin, pAdmin, AutoLogin, pIP, pGPCI, pDrivLic, pFlyLic, pSailingLic, pWeaponLic, pLastLogin, pSex, pLang, pPer, pRefCode, pSaveSeq FROM users WHERE pName = '%e' LIMIT 1 -- PID:%d:%d", Name, playerid, Token);
    mysql_pquery(sql, query, "OnAccountCheck", "id", playerid, GetPlayerToken(playerid));
    PlayAudioStreamForPlayer(playerid, MUSIC_WELCOME);
    return 1;
}forward OnAccountCheck(playerid, Token);
public OnAccountCheck(playerid, Token){
    CheckPlayerOnlineToCMD(playerid);
    CheckPlayerTokenCmp(playerid, Token);
    if(mysql_errno(sql)) return Skick(playerid, "Server dar hale beroozresani ast lotfan ba'dan vared shavid.", "The server is currently being updated, please log in later.", Token, true);
    GetNameP(playerid);
    if(cache_num_rows() > 0){
        new PID;
        cache_get_value_name_int(0, "pid", PID);
        SetPlayerPID(playerid, PID);

        new PKey[61];
        cache_get_value_name(0, "pKey", PKey, sizeof(PKey));
        SetPlayerPassHash(playerid, PKey);

        new PEMail[256];
        cache_get_value_name(0, "pEmail", PEMail, sizeof(PEMail));
        SetPlayerPemail(playerid, PEMail);

        new MONEY;
        cache_get_value_name_int(0, "pMoney", MONEY);
        SetPlayerPmoney(playerid, MONEY);

        new LEVEL;
        cache_get_value_name_int(0, "pLevel", LEVEL);
        SetPlayerPlevel(playerid, LEVEL);
        SetPlayerScore(playerid, LEVEL);

        new XP;
        cache_get_value_name_int(0, "pXP", XP);
        SetPlayerPXP(playerid, XP);

        new GOLD;
        cache_get_value_name_int(0, "pGold", GOLD);
        SetPlayerPgold(playerid, GOLD);

        new WANTED;
        cache_get_value_name_int(0, "pWanted", WANTED);
        SetPlayerPwanted(playerid, WANTED);

        new JOB;
        cache_get_value_name_int(0, "pJobId", JOB);
        SetPlayerPjob(playerid, JOB);

        new TIMEPLAY;
        cache_get_value_name_int(0, "pTimePlay", TIMEPLAY);
        SetPlayerPtimeplay(playerid, TIMEPLAY);

        new TIMEPLAYMIN;
        cache_get_value_name_int(0, "pTimePlaymin", TIMEPLAYMIN);
        SetPlayerPtimeplaymin(playerid, TIMEPLAYMIN);

        new ADMIN;
        cache_get_value_name_int(0, "pAdmin", ADMIN);
        SetPlayerPadmin(playerid, ADMIN);

        new AUTOLOGIN, PIPP[50], PGPCII[50];
        cache_get_value_name_int(0, "AutoLogin", AUTOLOGIN);
        SetPlayerPAutoLogin(playerid, AUTOLOGIN);
        if(AUTOLOGIN == 1){
            cache_get_value_name(0, "pIP", PIPP, sizeof(PIPP));
            cache_get_value_name(0, "pGPCI", PGPCII, sizeof(PGPCII));
            SetPlayerPIP(playerid, PIPP);
            SetPlayerPGPCI(playerid, PGPCII);
        }
        
        new DRIVLIC;
        cache_get_value_name_int(0, "pDrivLic", DRIVLIC);
        SetPlayerPdrivlic(playerid, DRIVLIC);

        new FLYLIC;
        cache_get_value_name_int(0, "pFlyLic", FLYLIC);
        SetPlayerPflylic(playerid, FLYLIC);

        new SAILINGLIC;
        cache_get_value_name_int(0, "pSailingLic", SAILINGLIC);
        SetPlayerPsailinglic(playerid, SAILINGLIC);

        new WEAPONLIC;
        cache_get_value_name_int(0, "pWeaponLic", WEAPONLIC);
        SetPlayerPweaponlic(playerid, WEAPONLIC);

        new PLastLogin[30];
        cache_get_value_name(0, "pLastLogin", PLastLogin, sizeof(PLastLogin));
        SetPlayerPlastlogin(playerid, PLastLogin);

        new SEX;
        cache_get_value_name_int(0, "pSex", SEX);
        SetPlayerPsex(playerid, SEX);

        new LANG;
        cache_get_value_name_int(0, "pLang", LANG);
        SetPlayerPlanguage(playerid, LANG);

        new PPer[30];
        cache_get_value_name(0, "pPer", PPer, sizeof(PPer));
        SetPlayerPper(playerid, PPer);

        new Prefcode[10];
        cache_get_value_name(0, "pRefCode", Prefcode);
        SetPlayerRefCode(playerid, Prefcode);

        cache_get_value_name_int(0, "pSaveSeq", SaveSeq[playerid]);

        new IpPlayer[50], GPCIPlayer[50];
        GetPlayerIp(playerid, IpPlayer);
        GPCI(playerid, GPCIPlayer);
        if(ADMIN == 0 && AUTOLOGIN == 1 && strcmp(IpPlayer, PIPP, false) == 0 && strcmp(GPCIPlayer, PGPCII, false) == 0){
            SetInt(playerid, AutoLoginSuccessful, 1);
            CheckPasswordLogin(playerid, false, Token);
            return 1;
        }
        SetInt(playerid, WrongPassword, 0);
        StartCameraMoveConnect(playerid);
        new login[256];
        if(LANG == 1) format(login, sizeof(login), "{FFFFFF}Khoshoomadi be %sAriana Game, {BDECB6}%s{FFFFFF}!\nPassworde khod ra baraye vorud vared konid:\nAkharin vorud: {FF4000}%s", Color_ArianaGame, Name, PLastLogin);
        else if(LANG == 2) format(login, sizeof(login), "{FFFFFF}Welcome to %sAriana Game, {BDECB6}%s{FFFFFF}!\nEnter your password to log in:\nLast Login: {FF4000}%s", Color_ArianaGame, Name, PLastLogin);
        ShowPlayerDialog(playerid, DIALOGID_LOGIN, DIALOG_STYLE_PASSWORD,"{00FF00}Vorud", login,"Vorud", "Khorooj");
        SetShowingDialog(playerid, DIALOGID_LOGIN);
        SetInt(playerid, TimerVaredKardanePass, SetTimerEx("TimerPasswordForLogin", TimeForLogin, false, "id", playerid, Token));
    }else{
        StartCameraMoveConnect(playerid);
        SetInt(playerid, TimerVaredKardanePass, SetTimerEx("TimerPasswordForLogin", TimeForRegis, false, "id", playerid, Token));
        new reg[400];
        format(reg, sizeof(reg), "{FFFFFF}Khoshoomadi be {FF00FF}Ariana Game, {BDECB6}%s{FFFFFF}!\nBaraye sabte nam yek ramze ghavi vared konid:\nRamze ghavi shamele a'dad (1234...), horufe kuchak va bozorg (ABCD...) & (abcd...) va ashkal (@$&...) mishavad.\nHade aghal password 6 ragham va hade aksar 40 harf mibashad.", Name);
        ShowPlayerDialog(playerid, DIALOGID_REGISTER, DIALOG_STYLE_PASSWORD,"{00FF00}Sabte nam - 1/6",reg,"Sabt","Khorooj");
        SetShowingDialog(playerid, DIALOGID_REGISTER);
    }return 1;
}
//                              Dialog haye system login va register                                //
SetDialogInput(DIALOGID_LOGIN){
    CheckShowingDialog(playerid, DIALOGID_LOGIN);
    CheckPlayerOnlineToCMD(playerid);
    new Token = GetPlayerToken(playerid);
    if(!response){
        Skick(playerid, "Shoma az bazi kharej shodid.", "You have exited the game.", Token, true);
        KillTimer(GetInt(playerid, TimerVaredKardanePass));
        return 1;
    }
    GetNameP(playerid);
    new lastt[28];
    GetPlayerPlastlogin(playerid, lastt);
    if(strlen(inputtext) < 6 || strlen(inputtext) > 40){
        new login[350];
        format(login, sizeof(login), "{FFFFFF}Khoshoomadi be {FF00FF}Ariana Game, {BDECB6}%s{FFFFFF}!\nPassworde khod ra baraye vorud vared konid:\nAkharin vorud: {FF4000}%s\n{FF0000}Password hade aghal 6 ragham bayad bashad!", Name, lastt);
        ShowPlayerDialog(playerid, DIALOGID_LOGIN, DIALOG_STYLE_PASSWORD,"{00FF00}Vorud", login,"Vorud", "Khorooj");
        return SetShowingDialog(playerid, DIALOGID_LOGIN);
    }new PASSH[61];
    GetPlayerPassHash(playerid, PASSH);
    bcrypt_verify(playerid, "CheckPasswordLogin", inputtext, PASSH, "d", Token);
    ResetShowingDialog(playerid);
    return 1;
}SetDialogInput(DIALOGID_REGISTER){
    CheckShowingDialog(playerid, DIALOGID_REGISTER);
    CheckPlayerOnlineToCMD(playerid);
    GetNameP(playerid);
    if(!response){
        KillTimer(GetInt(playerid, TimerVaredKardanePass));
        return Skick(playerid, "Shoma az bazi kharej shodid.", "You have exited the game.", GetPlayerToken(playerid), true);
    }if(strlen(inputtext) < 6  || strlen(inputtext) > 40){
        new reg[500];
        format(reg, sizeof(reg), "{FFFFFF}Khoshoomadi be {FF00FF}Ariana Game, {BDECB6}%s{FFFFFF}!\nBaraye sabte nam yek ramze ghavi vared konid:\nRamze ghavi shamele a'dad (1234...), horufe kuchak va bozorg (ABCD...) & (abcd...) va ashkal (@$&...) mishavad.\n{FF0000}Hade aghal password 6 ragham va hade aksar 40 harf mibashad.", Name);
        ShowPlayerDialog(playerid, DIALOGID_REGISTER, DIALOG_STYLE_PASSWORD,"{00FF00}Sabte nam - 1/6",reg,"Ba'di","Khorooj");
        return SetShowingDialog(playerid, DIALOGID_REGISTER);
    }SetPlayerPassHash(playerid, inputtext);
	ShowPlayerDialog(playerid, DIALOGID_REGISTER2, DIALOG_STYLE_PASSWORD, "{00FF00}Sabte nam 2/6", "{FFFFFF}Password ra dobare vared konid:\nPassword bayad ba passworde ghabl motabeghat dashte bashad.", "Sabt", "Bazgasht");
    SetShowingDialog(playerid, DIALOGID_REGISTER2);
    return 1;
}SetDialogInput(DIALOGID_REGISTER2){
    CheckShowingDialog(playerid, DIALOGID_REGISTER2);
    CheckPlayerOnlineToCMD(playerid);
    GetNameP(playerid);
    if(!response){
        new reg[500];
        format(reg, sizeof(reg), "{FFFFFF}Khoshoomadi be {FF00FF}Ariana Game, {BDECB6}%s{FFFFFF}!\nBaraye sabte nam yek ramze ghavi vared konid:\nRamze ghavi shamele a'dad (1234...), horufe kuchak va bozorg (ABCD...) & (abcd...) va ashkal (@$&...) mishavad.\nHade aghal password 6 ragham va hade aksar 40 harf mibashad.", Name);
        ShowPlayerDialog(playerid, DIALOGID_REGISTER, DIALOG_STYLE_PASSWORD,"{00FF00}Sabte nam - 1/6",reg,"Ba'di","Khorooj");
        return SetShowingDialog(playerid, DIALOGID_REGISTER);
    }if(strlen(inputtext) < 6 || strlen(inputtext) > 40){
        new reg[500];
        format(reg, sizeof(reg), "{FFFFFF}Khoshoomadi be {FF00FF}Ariana Game, {BDECB6}%s{FFFFFF}!\nBaraye sabte nam yek ramze ghavi vared konid:\nRamze ghavi shamele a'dad (1234...), horufe kuchak va bozorg (ABCD...) & (abcd...) va ashkal (@$&...) mishavad.\n{FF0000}Hade aghal password 6 ragham va hade aksar 40 harf mibashad.", Name);
        ShowPlayerDialog(playerid, DIALOGID_REGISTER, DIALOG_STYLE_PASSWORD,"{00FF00}Sabte nam - 1/6",reg,"Ba'di","Khorooj");
        return SetShowingDialog(playerid, DIALOGID_REGISTER);
    }new PASS[61];
    GetPlayerPassHash(playerid, PASS);
    if(strcmp(inputtext, PASS, false) == 0) bcrypt_hash(playerid, "SetPassword", inputtext, AMNIYAT_HASH_PASS, "d", GetPlayerToken(playerid));
    else{
      	new reg[500];
        format(reg, sizeof(reg), "{FFFFFF}Khoshoomadi be {FF00FF}Ariana Game, {BDECB6}%s{FFFFFF}!\nBaraye sabte nam yek ramze ghavi vared konid:\nRamze ghavi shamele a'dad (1234...), horufe kuchak va bozorg (ABCD...) & (abcd...) va ashkal (@$&...) mishavad.\nHade aghal password 6 ragham va hade aksar 40 harf mibashad.\n{FF0000}Password ha bayad motabeghat dashte bashad, dobare vared monid!", Name);
        ShowPlayerDialog(playerid, DIALOGID_REGISTER, DIALOG_STYLE_PASSWORD,"{00FF00}Sabte nam - 1/6",reg,"Ba'di","Khorooj");
        SetShowingDialog(playerid, DIALOGID_REGISTER);
    }return 1;
}SetDialogInput(DIALOGID_EMAIL){
    CheckShowingDialog(playerid, DIALOGID_EMAIL);
    CheckPlayerOnlineToCMD(playerid);
    GetNameP(playerid);
    if(!response){
        new reg[500];
        format(reg, sizeof(reg), "{FFFFFF}Khoshoomadi be {FF00FF}Ariana Game, {BDECB6}%s{FFFFFF}!\nBaraye sabte nam yek ramze ghavi vared konid:\nRamze ghavi shamele a'dad (1234...), horufe kuchak va bozorg (ABCD...) & (abcd...) va ashkal (@$&...) mishavad.\nHade aghal password 6 ragham va hade aksar 40 harf mibashad.", Name);
        ShowPlayerDialog(playerid, DIALOGID_REGISTER, DIALOG_STYLE_PASSWORD,"{00FF00}Sabte nam - 1/6",reg,"Ba'di","Khorooj");
        return SetShowingDialog(playerid, DIALOGID_REGISTER);
    }if(strlen(inputtext) == 0){
        ShowPlayerDialog(playerid, DIALOGID_EMAIL, DIALOG_STYLE_INPUT,"{00FF00}Sabte nam - 3/6","{FFFFFF}Email khod ra vared konid:\n{FF0000}Email be dorosti vared nashod, Dobare talash konid!","Sabt", "Bazgasht");
        return SetShowingDialog(playerid, DIALOGID_EMAIL);
    }if(!IsValidEmail(inputtext)){
        ShowPlayerDialog(playerid, DIALOGID_EMAIL, DIALOG_STYLE_INPUT,"{00FF00}Sabte nam - 3/6","{FFFFFF}Email khod ra vared konid:\n{FF0000}Email be dorosti vared nashod, Dobare talash konid!","Sabt", "Bazgasht");
        return SetShowingDialog(playerid, DIALOGID_EMAIL);
    }SetPlayerPemail(playerid, inputtext);
    SetInt(playerid, WrongCode, 0);
    new info[500];
	new Code = 100000 + random(899999);
    SetInt(playerid, EmailCode, Code);
	format(info, sizeof(info), "email=%s&code=%d", inputtext, Code);
	HTTP(playerid, HTTP_POST, SendEmailLink, info, "CodeSended");
    SendPlayerTokenToCallback(playerid);
    SendPM(playerid, PMWhite, "Dar hale ersale code tayid...", "", GetPlayerToken(playerid));
    ResetShowingDialog(playerid);
    return 1;
}SetDialogInput(DIALOGID_VALIDATEEMAIL){
    CheckShowingDialog(playerid, DIALOGID_VALIDATEEMAIL);
    CheckPlayerOnlineToCMD(playerid);
    if(!response){
        ShowPlayerDialog(playerid, DIALOGID_EMAIL, DIALOG_STYLE_INPUT,"{00FF00}Sabte nam - 3/6","{FFFFFF}Email khod ra vared konid:","Sabt", "Bazgasht");
        return SetShowingDialog(playerid, DIALOGID_EMAIL);
    }if(GetInt(playerid, EmailCode) == strval(inputtext)){
        DeleteV(playerid, WrongCode);
        ShowPlayerDialog(playerid, DIALOGID_SEX, DIALOG_STYLE_MSGBOX, "{00FF00}Sabte nam - 5/6", "{FFFFFF}Jensiyate shoma chist?", "Mard", "Zan");
        SetShowingDialog(playerid, DIALOGID_SEX);
    }else{
        new WCode = GetInt(playerid, WrongCode) + 1;
        SetInt(playerid, WrongCode, WCode);
        if(WCode == 6) return TempBanMinute(playerid, "Eshtebah vared kardane bish az hade code taayide email", "Lotfan 5 daghighe digar talash konid.", 5, GetPlayerToken(playerid));
		new EMail[350], String[650];
        GetPlayerPemail(playerid, EMail);
        format(String, sizeof(String), "{FFFFFF}Code tayid be Emaile shoma ersal shod.\nDar surati ke code ra daryaf nakardid Spam Box (HarzName) khod ra check konid\n{00FF00}%s\n{FF0000}Code vared shode eshtebah ast deghat konid akharin code ersal shode bashad, dobare vared konid:", EMail);
        ShowPlayerDialog(playerid, DIALOGID_VALIDATEEMAIL, DIALOG_STYLE_INPUT, "{00FF00}Sabte nam - 4/6", String, "Enter", "Change Email");
        SetShowingDialog(playerid, DIALOGID_VALIDATEEMAIL);
    }return 1;
}SetDialogMSG(DIALOGID_SEX){
    CheckShowingDialog(playerid, DIALOGID_SEX);
    CheckPlayerOnlineToCMD(playerid);
	if(response){
        //Mard
		SetPlayerPsex(playerid, 1);
        ShowPlayerDialog(playerid, DIALOGID_LANGUAGE, DIALOG_STYLE_MSGBOX, "{00FF00}Language - 6/6", "{FFFFFF}Zabane (Language) khod ra entekhab konid:\n{FFFF00}Tavajoh dashte bashid ke bishtare matn ha be zabane entekhabiye shoma namayesh dade khahad shod!\nDar ayande niz mitavanid dar tanzimat zaban ra taghir dahid!", "Persian", "English");
        return SetShowingDialog(playerid, DIALOGID_LANGUAGE);
    }
	//Zan
	SetPlayerPsex(playerid, 2);
    ShowPlayerDialog(playerid, DIALOGID_LANGUAGE, DIALOG_STYLE_MSGBOX, "{00FF00}Language - 6/6", "{FFFFFF}Zabane (Language) khod ra entekhab konid:\n{FFFF00}Tavajoh dashte bashid ke boshtare matn ha be zabane entekhabiye shoma namayesh dade khahad shod!\nDar ayande niz mitavanid dar tanzimat zaban ra taghir dahid!", "Persian", "English");
    SetShowingDialog(playerid, DIALOGID_LANGUAGE);
    return 1;
}SetDialogMSG(DIALOGID_LANGUAGE){
    CheckShowingDialog(playerid, DIALOGID_LANGUAGE);
    CheckPlayerOnlineToCMD(playerid);
    GetNameP(playerid);
	new PassH[61], PEmail[256];
    GetPlayerPassHash(playerid, PassH);
	GetString(playerid, Pemail, PEmail);
    new query[708];
    new Tok = GetPlayerToken(playerid);
    new IPPP[50], GPCIPP[50];
    GetPlayerIp(playerid, IPPP);
    GPCI(playerid, GPCIPP);
    if(response){
        SetPlayerPlanguage(playerid, 1);
		mysql_format(sql, query, sizeof(query), "INSERT INTO users (pName, pKey, pEmail, pMoney, pIP, pGPCI, pSex, pLang) VALUES ('%e', '%e', '%e', 500, '%e', '%e', %d, 1) -- PID:%d:%d", Name, PassH, PEmail, IPPP, GPCIPP, GetPlayerPsex(playerid), playerid, Tok);
        mysql_pquery(sql, query, "OnPlayerRegistered", "id", playerid, Tok);
        Querys++;
        return ResetShowingDialog(playerid);
    }SetPlayerPlanguage(playerid, 2);
    mysql_format(sql, query, sizeof(query), "INSERT INTO users (pName, pKey, pEmail, pMoney, pIP, pGPCI, pSex, pLang) VALUES ('%e', '%e', '%e', 500, '%e', '%e', %d, 2) -- PID:%d:%d", Name, PassH, PEmail, IPPP, GPCIPP, GetPlayerPsex(playerid), playerid, Tok);
    mysql_pquery(sql, query, "OnPlayerRegistered", "id", playerid, Tok);
    Querys++;
    ResetShowingDialog(playerid);
    return 1;
}forward SetPassword(playerid, Token);
public SetPassword(playerid, Token){
    CheckPlayerOnlineToCMD(playerid);
    CheckPlayerTokenCmp(playerid, Token);
    new PassH[61];
    bcrypt_get_hash(PassH);
    SetPlayerPassHash(playerid, PassH);
    ShowPlayerDialog(playerid, DIALOGID_EMAIL, DIALOG_STYLE_INPUT,"{00FF00}Sabte nam - 3/6","{FFFFFF}Email khod ra vared konid:","Sabt", "Bazgasht");
    SetShowingDialog(playerid, DIALOGID_EMAIL);
    return 1;
}forward CheckPasswordLogin(playerid, bool:success, Token);
public CheckPasswordLogin(playerid, bool:success, Token){
    CheckPlayerOnlineToCMD(playerid);
    CheckPlayerTokenCmp(playerid, Token);
    new bool:PassCMP;
    if(GetInt(playerid, AutoLoginSuccessful) == 1) PassCMP = true;
    else PassCMP = success;
    GetNameP(playerid);
    new lastt[28];
    GetPlayerPlastlogin(playerid, lastt);
	if(PassCMP){
        SetPlayerLogin(playerid, 1);
        KillTimer(GetInt(playerid, TimerVaredKardanePass));
        new query[200];
        LogAccountLogin(playerid, Token);
        if(GetInt(playerid, AutoLoginSuccessful) == 1){
            mysql_format(sql, query, sizeof(query), "UPDATE users SET pLastLogin = NOW() WHERE pid = %d -- PID:%d:%d", GetPlayerPID(playerid), playerid, GetPlayerToken(playerid));
            mysql_pquery(sql, query, "QueryUpdateLastLoginBazikon");
        }else{
            new IPPP[50], GPCIPP[50];
            GetPlayerIp(playerid, IPPP);
            GPCI(playerid, GPCIPP);
            SetPlayerPIP(playerid, IPPP);
            SetPlayerPGPCI(playerid, GPCIPP);
            mysql_format(sql, query, sizeof(query), "UPDATE users SET pLastLogin = NOW(), pIP = '%e', pGPCI = '%e' WHERE pid = %d -- PID:%d:%d", IPPP, GPCIPP, GetPlayerPID(playerid), playerid, GetPlayerToken(playerid));
            mysql_pquery(sql, query, "QueryUpdateLastLoginBazikon");
        }Querys++;
        StopAudioStreamForPlayer(playerid);
        TogglePlayerSpectating(playerid, false);
        SpawnPlayer(playerid);
        DeleteV(playerid, WrongPassword);
        DeleteV(playerid, TimerVaredKardanePass);
        new MSG[68], MSG2[72];
        format(MSG, sizeof(MSG), "Welcome to %sAriana Game {E20000}%s.", Color_ArianaGame, Name);
        format(MSG2, sizeof(MSG2), "Khoshoomadi be %sAriana Game {E20000}%s.", Color_ArianaGame, Name);
        SendPM(playerid, PMKahrobA, MSG2, MSG, Token);
        CheckPremium(playerid, Token);
        ResetPlayerMoney(playerid);
        GivePlayerMoney(playerid, GetPlayerPmoney(playerid));
        UpdateAllTD(playerid, Token);
        SetPlayerStartTimePlay(playerid, GetTickCount());
        DeleteV(playerid, AutoLoginSuccessful);
	}else{
        new WPASS = GetInt(playerid, WrongPassword) + 1;
        SetInt(playerid, WrongPassword, WPASS);
        if(WPASS == 4){
            KillTimer(GetInt(playerid, TimerVaredKardanePass));
            SendPM(playerid, PMRed, "Shoma ramze khod ra bish az had eshtebah vared kardid.", "You have entered your password incorrectly too many times.", Token);
            DeleteV(playerid, WrongPassword);
            TempBanMinute(playerid, "4 talashe namovafagh baraye vorud", "Lotfan 15 daghighe digar talash konid.", 15, Token);
            return 1;
        }new login[350];
        format(login, sizeof(login), "{FFFFFF}Khoshoomadi be {FF00FF}Ariana Game, {BDECB6}%s{FFFFFF}!\nPassworde khod ra baraye vorud vared konid:\nAkharin vorud: {FF4000}%s\nPassword eshtebah: %d/4", Name, lastt, WPASS);
        ShowPlayerDialog(playerid, DIALOGID_LOGIN, DIALOG_STYLE_PASSWORD,"{00FF00}Vorud", login,"Vorud", "Khorooj");
        SetShowingDialog(playerid, DIALOGID_LOGIN);
	}return 1;
}forward OnPlayerRegistered(playerid, Token);
public OnPlayerRegistered(playerid, Token){
    Querys--;
    CheckPlayerOnlineToCMD(playerid);
    CheckPlayerTokenCmp(playerid, Token);
    LogAccountLogin(playerid, Token);
    SetPlayerLogin(playerid, 1);
    KillTimer(GetInt(playerid, TimerVaredKardanePass));
    DeleteV(playerid, TimerVaredKardanePass);
    if(!IsPlayerConnected(playerid)) return 1;
    StopAudioStreamForPlayer(playerid);
    TogglePlayerSpectating(playerid, false);
    SetPlayerPID(playerid, cache_insert_id());
    SpawnPlayer(playerid);
    SetPlayerPmoney(playerid, 500);
    MoneyLog(500, playerid, -1, -1, "Register", "None");
    SetPlayerPlevel(playerid, 1);
    SetPlayerScore(playerid, 1);
    SetPlayerRefCode(playerid, "Creating");
    SendPM(playerid, PMKahrobA, "Sabte nam ba movafaghiyat anjam shod.", "Registration was successful.", Token);
    GetNameP(playerid);
    new MSG[68], MSG2[72];
    format(MSG, sizeof(MSG), "Welcome to %sAriana Game {E20000}%s.", Color_ArianaGame, Name);
    format(MSG2, sizeof(MSG2), "Khoshoomadi be %sAriana Game {E20000}%s.", Color_ArianaGame, Name);
    SendPM(playerid, PMKahrobA, MSG2, MSG, Token);
	CheckPremium(playerid, Token);
    ResetPlayerMoney(playerid);
    GivePlayerMoney(playerid, GetPlayerPmoney(playerid));
    UpdateAllTD(playerid, Token);
    SetPlayerStartTimePlay(playerid, GetTickCount());
    return 1;
}forward TimerPasswordForLogin(playerid, Token);
public TimerPasswordForLogin(playerid, Token){
    CheckPlayerOnlineToCMD(playerid);
    CheckPlayerTokenCmp(playerid, Token);
    DeleteV(playerid, TimerVaredKardanePass);
    Skick(playerid, "Mohlate shoma baraye vorud ya sabte nam be payan resid.", "Your time limit for logging in or signing up has expired.", Token, true);
    return 1;
}forward CodeSended(playerid, Response, Data[]);
public CodeSended(playerid, Response, Data[]){
    CheckPlayerOnlineToCMD(playerid);
    CheckPlayerTokenCallback(playerid);
    new EMail[350], String[500];
    GetPlayerPemail(playerid, EMail);
    if(Response == 200 && strfind(Data, "OK") != -1){
        format(String, sizeof(String), "{FFFFFF}Code tayid be Emaile shoma ersal shod.\nDar surati ke code ra daryaf nakardid Spam Box (HarzName) khod ra check konid\n{00FF00}%s", EMail);
        ShowPlayerDialog(playerid, DIALOGID_VALIDATEEMAIL, DIALOG_STYLE_INPUT, "{00FF00}Sabte nam - 4/6", String, "Enter", "Change Email");
        SetShowingDialog(playerid, DIALOGID_VALIDATEEMAIL);
        if(GetInt(playerid, Send2) == 1) DeleteV(playerid, Send2);
    }else{
        if(GetInt(playerid, Send2) == 1) return Skick(playerid, "Lotfan ba'dan sabte nam konid, Ma dar hale berooz resani va raf'e moshkel hastim.", "", GetPlayerToken(playerid), true);
	    new Code = 100000 + random(899999);
        SetInt(playerid, EmailCode, Code);
	    format(String, sizeof(String), "email=%s&code=%d", EMail, Code);
	    HTTP(playerid, HTTP_POST, SendEmailLink2, String, "CodeSended");
	    SetInt(playerid, Send2, 1);
	}return 1;
}