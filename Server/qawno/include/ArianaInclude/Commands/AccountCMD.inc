#if defined _ACCOUNTCMD_BY_MAMAD_PERSIAN_INC
	#endinput
#endif
#define _ACCOUNTCMD_BY_MAMAD_PERSIAN_INC

#define DialogShowAccount(%0) ShowPlayerDialog(%0,DIALOGID_ACOOUNT,DIALOG_STYLE_LIST,"Account","{FFFFFF}Information\nLicenses\nChange Password\nSettings","Select","Cancel");\
	SetShowingDialog(%0,DIALOGID_ACOOUNT)
#define DialogShowSettings(%0) new DLG[100];\
	format(DLG,sizeof(DLG),"{FFFFFF}Language: {49CAEB}%s\n{FFFFFF}Auto Login: %s",(GetPlayerPlanguage(%0) == 1) ? "Persian" : "English",(GetPlayerPAutoLogin(%0) == 1) ? "{00FF00}On" : "{FF0000}Off");\
	ShowPlayerDialog(%0,DIALOGID_SETTINGS,DIALOG_STYLE_LIST,"Settings",DLG,"Select","Back");\
	SetShowingDialog(%0,DIALOGID_SETTINGS)
#define DialogShowPassword(%0) LanguagePersian(%0) ShowPlayerDialog(%0,DIALOGID_CHANGEPASSWORD,DIALOG_STYLE_PASSWORD,"taghire ramz","{FFFFFF}Ramze khod ra vared konid:","Enter","Back");\
	LanguageEnglish(%0) ShowPlayerDialog(%0,DIALOGID_CHANGEPASSWORD,DIALOG_STYLE_PASSWORD,"Change Password","{FFFFFF}Enter your password:","Enter","Back");\
	SetShowingDialog(%0,DIALOGID_CHANGEPASSWORD)
#define DialogShowPasswordWrong(%0) LanguagePersian(%0) ShowPlayerDialog(%0,DIALOGID_CHANGEPASSWORD,DIALOG_STYLE_PASSWORD,"taghire ramz","{FFFFFF}Ramze khod ra vared konid:\n{FF0000}Password eshtebah ast.","Enter","Back");\
	LanguageEnglish(%0) ShowPlayerDialog(%0,DIALOGID_CHANGEPASSWORD,DIALOG_STYLE_PASSWORD,"Change Password","{FFFFFF}Enter your password:\n{FF0000}The password is incorrect.","Enter","Back");\
	SetShowingDialog(%0,DIALOGID_CHANGEPASSWORD)
#define DialogShowNewPass(%0) LanguagePersian(%0) ShowPlayerDialog(%0,DIALOGID_NEWPASSWORD,DIALOG_STYLE_PASSWORD,"Ramze jadid","{FFFFFF}Ramze jadide khod ra vared konid:","Enter","Cancel");\
    LanguageEnglish(%0) ShowPlayerDialog(%0,DIALOGID_NEWPASSWORD,DIALOG_STYLE_PASSWORD,"New Password","{FFFFFF}Enter your new password:","Enter","Cancel");\
	SetShowingDialog(%0,DIALOGID_NEWPASSWORD)
#define DialogShowNewPassKhata1(%0) LanguagePersian(%0) ShowPlayerDialog(%0,DIALOGID_NEWPASSWORD,DIALOG_STYLE_PASSWORD,"Ramze jadid","{FFFFFF}Ramze jadide khod ra vared konid:\n{FF0000}Ramz haye jadid bayad mesle ham bashand.","Enter","Cancel");\
    LanguageEnglish(%0) ShowPlayerDialog(%0,DIALOGID_NEWPASSWORD,DIALOG_STYLE_PASSWORD,"New Password","{FFFFFF}Enter your new password:\n{FF0000}The new passwords must match.","Enter","Cancel");\
	SetShowingDialog(%0,DIALOGID_NEWPASSWORD)
#define DialogShowNewPassKhata2(%0) LanguagePersian(%0) ShowPlayerDialog(%0,DIALOGID_NEWPASSWORD,DIALOG_STYLE_PASSWORD,"Ramze jadid","{FFFFFF}Ramze jadide khod ra vared konid:\n{FF0000}Toole ramze jadid bayad beyne 6 ta 40 harf bashad.","Enter","Cancel");\
    LanguageEnglish(%0) ShowPlayerDialog(%0,DIALOGID_NEWPASSWORD,DIALOG_STYLE_PASSWORD,"New Password","{FFFFFF}Enter your new password:\n{FF0000}The new password must be between 6 and 40 characters long.","Enter","Cancel");\
	SetShowingDialog(%0,DIALOGID_NEWPASSWORD)
#define DialogShowNextNewPass(%0) LanguagePersian(%0) ShowPlayerDialog(%0,DIALOGID_NEWPASSWORD1,DIALOG_STYLE_PASSWORD,"Tekrare ramz","{FFFFFF}Ramze jadide khod ra dobare vared konid:","Enter","Back");\
    LanguageEnglish(%0) ShowPlayerDialog(%0,DIALOGID_NEWPASSWORD1,DIALOG_STYLE_PASSWORD,"Confirm password","{FFFFFF}Enter your new password again:","Enter","Back");\
	SetShowingDialog(%0,DIALOGID_NEWPASSWORD1)
CMD:account(playerid){
	DialogShowAccount(playerid);
	return 1;
}SetDialogList(DIALOGID_ACOOUNT){
	CheckPlayerOnlineAndLogin(playerid);
	CheckShowingDialog(playerid, DIALOGID_ACOOUNT);
	if(!response) return ResetShowingDialog(playerid);
	if(listitem < 0 || listitem > 3) return 1;
	switch(listitem){
		case 0:{
			new String[1024], Gmaill[256], PERM[60], RefCode[10];
			GetPlayerPper(playerid, PERM);
			if(GetPlayerPperBool(playerid) == 1) format(PERM, sizeof(PERM), "{00FF00}Yes, %s", PERM);
			else format(PERM, sizeof(PERM), "{FF0000}No");
			GetNameP(playerid);
			GetPlayerPemail(playerid, Gmaill);
			GetPlayerRefCode(playerid, RefCode);
			new required = RequiredXP(GetPlayerPlevel(playerid));
			format(String, sizeof(String), "{FFFFFF}Account Information\nName: %s\nGmail: %s\nMoney: %d\nLevel: %d\nXP: %d/%d\nGold: %d\nSex: %s\nLanguage: %s\nPremium: %s\n {FFFFFF}Time play: %d hours\nReferral: %s", Name, Gmaill, GetPlayerPmoney(playerid), GetPlayerPlevel(playerid), GetPlayerPXP(playerid), required, GetPlayerPgold(playerid), (GetPlayerPsex(playerid) == 2) ? ("Zan") : ("Mard"), (GetPlayerPlanguage(playerid) == 1) ? ("Persian") : ("English"), PERM, GetPlayerPtimeplay(playerid), RefCode);
			ShowPlayerDialog(playerid, DIALOGID_STATS, DIALOG_STYLE_MSGBOX, "Information", String, "Ok", "");
			SetShowingDialog(playerid, DIALOGID_STATS);
		}case 1:{
			new DrivLice[80], DrivLiceHour = GetPlayerPdrivlic(playerid);
			if(DrivLiceHour > 0) format(DrivLice, sizeof(DrivLice), "{00FF00}Yes, %d hours", DrivLiceHour);
			else if(DrivLiceHour == 0) format(DrivLice, sizeof(DrivLice), "{FF0000}No");
			else if(DrivLiceHour < 0) format(DrivLice, sizeof(DrivLice), "{FF0000}No, it has been suspended for %d hours", abs(DrivLiceHour));
			new FlyLic[80], FlyLiceHour = GetPlayerPflylic(playerid);
			if(FlyLiceHour > 0) format(FlyLic, sizeof(FlyLic), "{00FF00}Yes, %d hours", FlyLiceHour);
			else if(FlyLiceHour == 0) format(FlyLic, sizeof(FlyLic), "{FF0000}No");
			else if(FlyLiceHour < 0) format(FlyLic, sizeof(FlyLic), "{FF0000}No, it has been suspended for %d hours", abs(FlyLiceHour));
			new SailingLic[80], SailingLiceHour = GetPlayerPsailinglic(playerid);
			if(SailingLiceHour > 0) format(SailingLic, sizeof(SailingLic), "{00FF00}Yes, %d hours", SailingLiceHour);
			else if(SailingLiceHour == 0) format(SailingLic, sizeof(SailingLic), "{FF0000}No");
			else if(SailingLiceHour < 0) format(SailingLic, sizeof(SailingLic), "{FF0000}No, it has been suspended for %d hours", abs(SailingLiceHour));
			new WeaponLic[80], WeaponLiceHour = GetPlayerPweaponlic(playerid);
			if(WeaponLiceHour > 0) format(WeaponLic, sizeof(WeaponLic), "{00FF00}Yes, %d hours", WeaponLiceHour);
			else if(WeaponLiceHour == 0) format(WeaponLic, sizeof(WeaponLic), "{FF0000}No");
			else if(WeaponLiceHour < 0) format(WeaponLic, sizeof(WeaponLic), "{FF0000}No, it has been suspended for %d hours", abs(WeaponLiceHour));
			new string[300];
			format(string, sizeof(string), "{FFFFFF}Driving license: %s.\n{FFFFFF}Flying license: %s.\n{FFFFFF}Sailing license: %s.\n{FFFFFF}Weapon license: %s.", DrivLice, FlyLic, SailingLic, WeaponLic);
			ShowPlayerDialog(playerid, DIALOGID_LICENSES, DIALOG_STYLE_MSGBOX, "Licenses", string, "Ok", "");
			SetShowingDialog(playerid, DIALOGID_LICENSES);
		}case 2:{DialogShowPassword(playerid);}
		case 3:{DialogShowSettings(playerid);}
	}return 1;
}SetDialogMSG(DIALOGID_STATS){
	CheckPlayerOnlineAndLogin(playerid);
	CheckShowingDialog(playerid, DIALOGID_STATS);
	if(!response){
		DialogShowAccount(playerid);
		return 1;
	}
	DialogShowAccount(playerid);
	return 1;
}SetDialogMSG(DIALOGID_LICENSES){
	CheckPlayerOnlineAndLogin(playerid);
	CheckShowingDialog(playerid, DIALOGID_LICENSES);
	if(!response){
		DialogShowAccount(playerid);
		return 1;
	}
	DialogShowAccount(playerid);
	return 1;
}SetDialogList(DIALOGID_SETTINGS){
	CheckPlayerOnlineAndLogin(playerid);
	CheckShowingDialog(playerid, DIALOGID_SETTINGS);
	if(!response){
		DialogShowAccount(playerid);
		return 1;
	} 
	new TOK = GetPlayerToken(playerid);
	if(listitem < 0 || listitem > 1) return 1;
	switch(listitem){
		case 0:{
			new Lan = GetPlayerPlanguage(playerid);
			if(Lan == 1)SetPlayerPlanguage(playerid, 2);
			else if(Lan == 2) SetPlayerPlanguage(playerid, 1);
			SendPM(playerid, PMKahrobA, "Zabane shoma ba movafaghiyat taghir kard.", "Your language has been successfully changed.", TOK);
			DialogShowSettings(playerid);
		}case 1:{
			new ALG = GetPlayerPAutoLogin(playerid);
			if(ALG == 0)SetPlayerPAutoLogin(playerid, 1);
			else if(ALG == 1) SetPlayerPAutoLogin(playerid, 0);
			DialogShowSettings(playerid);
		}
	}FlagUpdate(playerid);
	return 1;
}SetDialogInput(DIALOGID_CHANGEPASSWORD){
	CheckShowingDialog(playerid, DIALOGID_CHANGEPASSWORD);
	CheckPlayerOnlineAndLogin(playerid);
	if(!response){
		DialogShowAccount(playerid);
		return 1;
	}
	if(strlen(inputtext) < 6 || strlen(inputtext) > 40){
		DialogShowPasswordWrong(playerid);
		return 1;
	}new PASSH[61];
    GetPlayerPassHash(playerid, PASSH);
	bcrypt_verify(playerid, "CheckChangePassword", inputtext, PASSH, "d", GetPlayerToken(playerid));
	return ResetShowingDialog(playerid);
}SetDialogInput(DIALOGID_NEWPASSWORD){
	CheckShowingDialog(playerid, DIALOGID_NEWPASSWORD);
	CheckPlayerOnlineAndLogin(playerid);
	if(!response){
		DialogShowAccount(playerid);
		return 1;
	}
	if(strlen(inputtext) < 6 || strlen(inputtext) > 40){
		DialogShowNewPassKhata2(playerid);
		return 1;
	}SetString(playerid, NewPassword, inputtext);
	DialogShowNextNewPass(playerid);
	return 1;
}SetDialogInput(DIALOGID_NEWPASSWORD1){
	CheckShowingDialog(playerid, DIALOGID_NEWPASSWORD1);
	CheckPlayerOnlineAndLogin(playerid);
	if(!response){
		DialogShowNewPass(playerid);
		DeleteV(playerid, NewPassword);
		return 1;
	}if(strlen(inputtext) < 6 || strlen(inputtext) > 40){
		DialogShowNewPassKhata1(playerid);
		return 1;
	}new NewPass[61];
	GetString(playerid, NewPassword, NewPass);
	if(strcmp(inputtext, NewPass) == 0){
		bcrypt_hash(playerid, "NewPasswordSave", inputtext, AMNIYAT_HASH_PASS, "d", GetPlayerToken(playerid));
		ResetShowingDialog(playerid);
	}else{
		DialogShowNewPassKhata1(playerid);
	}
	return 1;
}forward CheckChangePassword(playerid, bool:success, Token);
public CheckChangePassword(playerid, bool:success, Token){
	CheckPlayerOnlineAndLogin(playerid);
	CheckPlayerTokenCmp(playerid, Token);
	if(success){
		DialogShowNewPass(playerid);
		DeleteV(playerid, WrongPassword);
	}else{
		new WPA = GetInt(playerid, WrongPassword) + 1;
		SetInt(playerid, WrongPassword, WPA);
		if(WPA >= 3){
			SendPM(playerid, PMRed, "Shoma ramze khod ra bish az had eshtebah vared kardid.", "You have entered your password incorrectly more times than allowed.", Token);
			TempBanMinute(playerid, "3 talashe namovafagh baraye taghire ramz", "Lotfan 10 daghighe digar talash konid.", 10, Token);
			return 1;
		}DialogShowPasswordWrong(playerid);
	}return 1;
}forward NewPasswordSave(playerid, Token);
public NewPasswordSave(playerid, Token){
	CheckPlayerOnlineAndLogin(playerid);
	CheckPlayerTokenCmp(playerid, Token);
	new Hashhh[61];
	bcrypt_get_hash(Hashhh);
	new query[140];
	new Tok = GetPlayerToken(playerid);
	mysql_format(sql, query, sizeof(query), "UPDATE users SET pKey = '%e', pGPCI = 'Password Changed' WHERE pid = %d -- PID:%d:%d", Hashhh, GetPlayerPID(playerid), playerid, Tok);
	mysql_pquery(sql, query, "SaveShod", "isd", playerid, Hashhh, Tok);
	DeleteV(playerid, NewPassword);
	Querys++;
	return 1;
}forward SaveShod(playerid, const HashPass[], Token);
public SaveShod(playerid, const HashPass[], Token){
	Querys--;
	if(cache_affected_rows() == 0) return SendPM(playerid, PMError, "Lotfan ba'dan talash konid", "Please try again later", Token);
	CheckPlayerOnlineAndLogin(playerid);
	CheckPlayerTokenCmp(playerid, Token);
	SetPlayerPassHash(playerid, HashPass);
	SendPM(playerid, PMKahrobA, "Ramze shoma ba movafaghiyat taghir kard.", "Your password has been successfully changed.", Token);
	return 1;
}