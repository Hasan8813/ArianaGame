//                              Be name khoda                               /
#if defined _DEFINEINFO_BY_MAMAD_PERSIAN_INC
	#endinput
#endif
#define _DEFINEINFO_BY_MAMAD_PERSIAN_INC

#pragma dynamic 524288
//MySQL variable
new MySQL:sql;
new MySQLOpt:sqlopt;
new Querys = 0;
//MySQL
#define									SQL_HOST									"127.0.0.1"
#define									SQL_USER									"ArianaGames"
#define									SQL_DB									"ariana"
#define									SQL_PASS									"88Mohamad13@"
//Position civil spawn
#define 								spawnx 								1448.214843//Position X
#define 								spawny 								-2287.178710 //Position Y
#define 								spawnz 								15.0 //Position Z
#define 								spawnr 								271.0 //Position Rotation
#define 								spawnf								269.0 //FacingAngle
//Message
#define 								SCM 								SendClientMessage



// 								Define Colors 								//
#define 								ColorName_CivilHex 								0xDDD6C900
#define 								ColorName_Civil 								"{DDD6C9}"
#define 								Color_ArianaGame 								"{FF00FF}"
#define 								Color_ArianaGameHex 								0xFF00FFFF



#define GetInt(%0,%1) GetPVarInt(%0, #%1)
#define SetInt(%0,%1,%2) SetPVarInt(%0, #%1, %2)

#define GetFloat(%0,%1) GetPVarFloat(%0, #%1)
#define SetFloat(%0,%1,%2) SetPVarFloat(%0, #%1, %2)

#define GetString(%0,%1,%2) GetPVarString(%0, #%1, %2, sizeof(%2))
#define SetString(%0,%1,%2) SetPVarString(%0, #%1, %2)

#define DeleteV(%0,%1) DeletePVar(%0, #%1)



#define 								AMNIYAT_HASH_PASS 								9

#define 								DESTROY_VEHICLE_TIME 								900

#define 								SendEmailLink 								"http://127.0.0.1/Email/send1.php"
#define 								SendEmailLink2 								"http://127.0.0.1/Email/send2.php"

#define 								MUSIC_WELCOME 								"http://3.139.105.193/ArianaGame.mp3"

//Timer baraye login ke age tu in time password ro nazane kick mishe
#define 								TimeForLogin 								45000
//Timer baraye register ke age tu in time register nakard kick beshe
#define 								TimeForRegis 								360000

#define SetPlayerPname(%0,%1) SetString(%0, PName, %1)
#define GetPlayerPname(%0,%1) GetString(%0, PName, %1)
#define 								GetNameP(%0)							new Name[MAX_PLAYER_NAME + 1]; GetPlayerPname(%0, Name)

#define SetPlayerPID(%0,%1) SetInt(%0, Pid, %1)
#define GetPlayerPID(%0) GetInt(%0, Pid)

#define SetPlayerPassHash(%0,%1) SetString(%0, Passhash, %1)
#define GetPlayerPassHash(%0,%1) GetString(%0, Passhash, %1)

#define SetPlayerPemail(%0,%1) SetString(%0, Pemail, %1)
#define GetPlayerPemail(%0,%1) GetString(%0, Pemail, %1)

#define SetPlayerPmoney(%0,%1) SetInt(%0, Pmoney, %1)
#define GetPlayerPmoney(%0) GetInt(%0, Pmoney)

#define SetPlayerPlevel(%0,%1) SetInt(%0, Plevel, %1)
#define GetPlayerPlevel(%0) GetInt(%0, Plevel)

#define SetPlayerPXP(%0,%1) SetInt(%0, Pxp, %1)
#define GetPlayerPXP(%0) GetInt(%0, Pxp)

#define SetPlayerPgold(%0,%1) SetInt(%0, Pgold, %1)
#define GetPlayerPgold(%0) GetInt(%0, Pgold)

#define SetPlayerPwanted(%0,%1) SetInt(%0, Pwanted, %1)
#define GetPlayerPwanted(%0) GetInt(%0, Pwanted)

#define SetPlayerPjob(%0,%1) SetInt(%0, Pjob, %1)
#define GetPlayerPjob(%0) GetInt(%0, Pjob)

#define SetPlayerPtimeplay(%0,%1) SetInt(%0, Ptimeplay, %1)
#define GetPlayerPtimeplay(%0) GetInt(%0, Ptimeplay)

#define SetPlayerPtimeplaymin(%0,%1) SetInt(%0, Ptimeplaymin, %1)
#define GetPlayerPtimeplaymin(%0) GetInt(%0, Ptimeplaymin)

#define SetPlayerPadmin(%0,%1) SetInt(%0, Padmin, %1)
#define GetPlayerPadmin(%0) GetInt(%0, Padmin)

#define SetPlayerPAutoLogin(%0,%1) SetInt(%0, PAutoLogin, %1)
#define GetPlayerPAutoLogin(%0) GetInt(%0, PAutoLogin)

#define SetPlayerPIP(%0,%1) SetString(%0, PIP, %1)
#define GetPlayerPIP(%0,%1) GetString(%0, PIP, %1)

#define SetPlayerPGPCI(%0,%1) SetString(%0, PGPCI, %1)
#define GetPlayerPGPCI(%0,%1) GetString(%0, PGPCI, %1)

new PDriveLicense[MAX_PLAYERS];
#define SetPlayerPdrivlic(%0,%1) PDriveLicense[%0] = %1
#define GetPlayerPdrivlic(%0) PDriveLicense[%0]

new PFlyLicense[MAX_PLAYERS];
#define SetPlayerPflylic(%0,%1) PFlyLicense[%0] = %1
#define GetPlayerPflylic(%0) PFlyLicense[%0]

new PSailingLicense[MAX_PLAYERS];
#define SetPlayerPsailinglic(%0,%1) PSailingLicense[%0] = %1
#define GetPlayerPsailinglic(%0) PSailingLicense[%0]

new PWeaponLicense[MAX_PLAYERS];
#define SetPlayerPweaponlic(%0,%1) PWeaponLicense[%0] = %1
#define GetPlayerPweaponlic(%0)	PWeaponLicense[%0]

#define SetPlayerPsex(%0,%1) SetInt(%0, Psex, %1)
#define GetPlayerPsex(%0) GetInt(%0, Psex)

#define SetPlayerPlanguage(%0,%1) SetInt(%0, Planguage, %1)
#define GetPlayerPlanguage(%0) GetInt(%0, Planguage)

#define SetPlayerPper(%0,%1) SetString(%0, Pper, %1)
#define GetPlayerPper(%0,%1) GetString(%0, Pper, %1)
#define SetPlayerPperBool(%0,%1) SetInt(%0, PperBool, %1)
#define GetPlayerPperBool(%0) GetInt(%0, PperBool)

#define SetPlayerPlastlogin(%0,%1) SetString(%0, Plastlogin, %1)
#define GetPlayerPlastlogin(%0,%1) GetString(%0, Plastlogin, %1)

#define SetPlayerRefCode(%0,%1) SetString(%0, PrefCode, %1)
#define GetPlayerRefCode(%0,%1) GetString(%0, PrefCode, %1)

#define SetPlayerLogin(%0,%1) SetInt(%0, LoginBool, %1)
#define GetPlayerLogin(%0) GetInt(%0, LoginBool)
#define CheckPlayerLogin(%0) if(GetPlayerLogin(%0) == 0)
#define CheckPlayerLoginToCMD(%0) if(GetPlayerLogin(%0) == 0) return SendPM(%0, PMError, "Shoma vared nashodid", "You are not logged in", GetPlayerToken(%0))


#define LanguagePersian(%0) if(GetPlayerPlanguage(%0) == 1)
#define LanguageEnglish(%0) if(GetPlayerPlanguage(%0) == 2)


#define SetPlayerToken(%0,%1) SetInt(%0,Ptoken,%1)
#define GetPlayerToken(%0) GetInt(%0,Ptoken)


#define CheckPlayerOnline(%0) if(!IsPlayerConnected(%0))
#define CheckPlayerOnlineToCMD(%0) if(!IsPlayerConnected(%0)) return 1
#define CheckPlayerOnlineAndLogin(%0) if(!IsPlayerConnected(%0) || GetPlayerLogin(%0) == 0) return 1
#define CheckPlayerToken(%0,%1) if(GetPlayerToken(%0) != %1)
#define CheckPlayerTokenCmp(%0,%1) if(GetPlayerToken(%0) != %1) return 1
#define SendPlayerTokenToCallback(%0) SetInt(%0, TokenCallback, GetPlayerToken(%0))
#define CheckPlayerTokenCallback(%0) CheckPlayerTokenCmp(%0, GetInt(%0, TokenCallback))

//Vaziyate bazikon
#define		STATE_DMV_TEST 1
#define 	STATE_FLYSCHOOL_TEST 2
#define 	STATE_SAILING_TEST 3

#define SetPState(%0,%1) SetInt(%0, PState, %1)
#define GetPState(%0) GetInt(%0, PState)
//****************
// 								Baraye mohasebeye time play bazikon va xp saati 								//
#define SetPlayerStartTimePlay(%0,%1)   SetInt(%0, PTimeStartTimePlay, %1)
#define GetPlayerStartTimePlay(%0)      GetInt(%0, PTimeStartTimePlay)
// 								*********************************************** 								//

//Skine new player
#define 								NewPlayerSkinMard 								184
#define 								NewPlayerSkinZan 								56


//Systeme securitye dialogs ha
#define SetShowingDialog(%0,%1) SetInt(%0,DialogShowing,%1)
#define ResetShowingDialog(%0) SetInt(%0,DialogShowing,-1)
#define CheckShowingDialog(%0,%1) if(GetInt(%0,DialogShowing)!=%1)return ResetShowingDialog(%0);ResetShowingDialog(%0)

// 								Xp for level up 						//
#define XP_FOR_LEVEL_1 8
#define XP_FOR_LEVEL_UP 11



// 								Variable 								//
//Baraye systeme token dadan be bazikonan
new PlayerConnect;

//In baraye zakhire taghirate accounte ke age adadesh taghir kone tu include PlayerUpdate tu halghe zakhire sazi anjam mishe
new VersionUpdate[MAX_PLAYERS], LastVersionUpdate[MAX_PLAYERS], LastUpdatePayCheck[MAX_PLAYERS], SaveSeq[MAX_PLAYERS];

//Zakhireye check point faal va id check point bazikon
new bool:PlayerActiveCheckPoint[MAX_PLAYERS], PlayerCheckPoint[MAX_PLAYERS];


//Reset kardane meghdarr vatiable moghe connect va disconnect
stock ResetPlayerVariable(playerid){
	VersionUpdate[playerid] = 0, LastVersionUpdate[playerid] = 0, LastUpdatePayCheck[playerid] = 0, SaveSeq[playerid] = 0;
	PlayerActiveCheckPoint[playerid] = false, PlayerCheckPoint[playerid] = 0;
	SetPlayerPdrivlic(playerid, 0);
	SetPlayerPflylic(playerid, 0);
	SetPlayerPsailinglic(playerid, 0);
	SetPlayerPweaponlic(playerid, 0);
	return 1;
}