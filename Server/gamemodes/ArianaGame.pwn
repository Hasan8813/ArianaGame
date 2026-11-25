//								Be Name Parvardegar								//
//							   Game Mode Ariana Game							//
//					  Developer And Scripter by (Mamad Persian)                 //

// 							Includes								//
#include								<open.mp>
#include								<a_mysql>
#include								<Pawn.CMD>
#include								<sscanf2>
#include								<streamer>
#if defined MAX_PLAYERS
	#undef MAX_PLAYERS
#endif
#define 								MAX_PLAYERS 							500
#include 								<foreach>
#define 								PP_SYNTAX
#include								<PawnPlus>
#include 								<samp_bcrypt>
#include 								<Pawn.RakNet>
// 							******** 								//

// 								   Include made by Persian for Ariana Game 								//
#include 								<ArianaInclude/DefineInfo.inc>//Define ha va bazi az vatiable global
#include 								<ArianaInclude/ArianaStock.inc>//Stock haye por karbord
#include 								<ArianaInclude/AntiCheat/AntiCheatCallback.inc>//Anti cheat
#include 								<ArianaInclude/Security/Anti-Flood-Command.inc>//Systeme anti flood baraye jolo giri az spam dadane cmd ha
#include 								<ArianaInclude/EnterExitSystem.inc>//Systeme enter va exit makan ha
#include 								<ArianaInclude/CreateGovVehicle.inc>//Sakhte mashine goverment baraye bazikon
#include 								<ArianaInclude/CheckPlayerPermForEnterToVeh.inc>//Check haye bazikon moghe vorud be vehicle ha
#include 								<ArianaInclude/CheckPoints.inc>//Check point ha
#include 								<ArianaInclude/Dialogs.inc>//Dialog ha
#include 								<ArianaInclude/TextDraws.inc>//TextDraw ha
#include 								<ArianaInclude/ArianaPublic.inc>//Public haye por karbord
#include 								<ArianaInclude/ServerLogs.inc>//Systems haye log giriye server
#include 								<ArianaInclude/MySQLConnect.inc>//System sakht data base va log giriye khata haye data base 
#include 								<ArianaInclude/MoveCameraLogin.inc>//System mobe camera hengame login
#include 								<ArianaInclude/LoginAndRegister.inc>//System login va register
#include 								<ArianaInclude/SystemMushakArea69.inc>//Systeme ekhtar va partab mushak area 69
#include 								<ArianaInclude/SystemPremium.inc>//Systeme premium
#include 								<ArianaInclude/GiveItems.inc>//Systeme give dadane item haye server Gold Money ...
#include 								<ArianaInclude/PayCheck.inc>//Systeme paychecke saati
#include 								<ArianaInclude/PlayerUpdate.inc>//Systeme update etelaate bazikon
#include 								<ArianaInclude/SystemBans.inc>//Systeme temp ban(Ban movaghat)
#include 								<ArianaInclude/ItemsPrice.inc>//Systeme gheymat gozari mesle gheymate gold
#include 								<ArianaInclude/XpAndLevel.inc>//Systeme level va xp
#include 								<ArianaInclude/SystemeExam.inc>//Systeme exam
#include 								<ArianaInclude/SpecialBiz.inc>
// 									**************************************** 							//

// 								Security 								//
#include 								<ArianaInclude/Security/CheckBadNickName.inc>//Susteme check kardane nickname haye bad ke fosh tush hast ya ip hast
//								******** 								//

// 								Commands 								//
#include 								<ArianaInclude/Commands/AccountCMD.inc>//Systeme command haye marbut be accounte bazikon
#include 								<ArianaInclude/Commands/AdminCommands.inc>//Systeme command haye marbut be admin ha
// 								******** 							//

// 								Zone 								//
#include 								<ArianaInclude/SystemZones.inc>//System zone(Mantaghe ha)
// 								**** 								//
// 								Maps 								//
#include 								<ArianaInclude/Maps/LoadAllMap.inc>//Load all map
// 								**** 								//
main(){}

public OnGameModeInit(){
	DisableInteriorEnterExits();//Off kardane enter/exit interior haye default samp
	EnableStuntBonusForAll(false);//Off kardane padash money hengame harakate namayeshi mesle drift zadan ke zayize mode behesh
    UsePlayerPedAnims();//Off kardane nahveye rah raftane vagheyie har skin, ba in hame mesle cj rah miran
	SetGameModeText("RPG");//Set kardane no'e game mode mesle rpg, rp va...
	MySQLConnectAndLogAndCreateTable();//Vaghti server roshan beshe check mikone age bare avvale server roshan shode bashe data base haro misaze
	bcrypt_set_thread_limit(1);//Set kardane thread baraye hash kardan password
	LoadAllTextDraws();//Sakhte textdraw ha ke tu include marbut be textdraw hast
	UpdateTimeAndWeather(); SetTimer("UpdateTimeAndWeather", 8000, true);//Timer update doreyi ab va havaye server
	StartTimerUpdateData();
	LoadAllZoneArea();//Sakhte zone(Mantaghe ha) mesle area69 ke vaghti beri tush ekhtar migiri
	LoadAllBiz();//Load kardane hameye special biz ha
	SetTimer("RefreshDataBase", 60000, true);//Recresh data base mesle time premium ha
	//StartRefreshGoldPrice();//Start gheymat gozari bar asase gheymate lahzeyiye tala
	LoadAllMap();//Load All Maperis
	return 1;
}

public OnGameModeExit(){
	mysql_close(sql);
	return 1;
}

public OnPlayerConnect(playerid){
	if(IsPlayerNPC(playerid)) return 1;
	PlayerConnect++;//Afzundane be shomarandeye bazikonane online server
	SetPlayerToken(playerid, PlayerConnect);//Dadane shenaseye yekta be har bazikon
	ResetPlayerVariable(playerid);
	ResetAntiCheatVariable(playerid);
	SetPlayerPlanguage(playerid, 1);//Language bazikonan taze ke default be zabane persian yani adade 1 set mishe
	new Tok = GetPlayerToken(playerid);
	if(CheckNick(playerid, Tok) == 0) return 1;
	SetSpawnInfo(playerid, 0, 0, spawnx, spawny, spawnz, spawnr, WEAPON_FIST, 0, WEAPON_FIST, 0, WEAPON_FIST, 0);//Set kardane spawn bazikon
	SetInt(playerid, DarHaleKillShodan, 0);
	SetPlayerColor(playerid, ColorName_CivilHex);//Set kardane range esme bazikon civil
	SetPlayerVirtualWorld(playerid, 145000 + random(5001));//Set kardane world random baraye lag nashodan moghe login
	CCP(playerid, 48);//Pak kardane chate bazikon vaghti varede bazi shod
	new Namee[MAX_PLAYER_NAME + 1];
	GetPlayerName(playerid, Namee, sizeof(Namee));
	SetPlayerPname(playerid, Namee);
	SetInt(playerid,TimerVaredKardanePass, -1);
	CheckTempBanForLogin(playerid, Tok);//Check kardane ban nabudan bazikon va badesh login ya register
	ShowServerLogo(playerid);//Namayesh lohoye server be bazikon
	//SetTimerCommand(playerid);//Set kardane time baghi munde baraye estefade az command
	InfoTextDraw(playerid);//Beruz resaniye update meghdar textdraw ha mesle meghdar gold ke be bazikon namayesh mide
	return 1;
}

public OnPlayerDisconnect(playerid, reason){
	if(IsPlayerNPC(playerid)) return 1;
	if(IsValidDynamicObject(GetInt(playerid, ObjectMushakAre))){
		DestroyDynamicObject(GetInt(playerid, ObjectMushakAre));
		KillTimer(GetInt(playerid, TimerMushakArea));
	}KillTimer(GetInt(playerid, TimerVaredKardanePass));
	if(GetInt(playerid, TimerPremium) > 0) KillTimer(GetInt(playerid, TimerPremium));
	UpdatePlayerDataDisconnect(playerid, GetPlayerToken(playerid));
	DestroyVehicleGov(playerid);
	StopTestDMV(playerid, true);
	ResetPlayerVariable(playerid);
	ResetAntiCheatVariable(playerid);
	PlayerPlace[playerid] = -1;
	return 1;
}

public OnPlayerRequestClass(playerid, classid){
	SetSpawnInfo(playerid, 0, 0, spawnx, spawny, spawnz, spawnr, WEAPON_FIST, 0, WEAPON_FIST, 0, WEAPON_FIST, 0);
	if(GetInt(playerid, DarHaleKillShodan) == 1) return SpawnPlayer(playerid);
	return 0;
}

public OnPlayerSpawn(playerid){
	if(IsPlayerNPC(playerid)) return 1;
	CheckPlayerLogin(playerid) return Skick(playerid, "Shoma be dalile mashkuk budan be cheat ya lag az server kick shodid.", "You have been kicked from the server due to suspected cheating or lag.", GetPlayerToken(playerid), true), 0;
	SetInt(playerid, DarHaleKillShodan, 1);
	TogglePlayerSpectating(playerid, false);
	SetPlayerColor(playerid, ColorName_CivilHex);
	SetPlayerInterior(playerid, 0);
	ShowPlayerAllTextDraw(playerid, GetPlayerToken(playerid));
	SetPlayerVirtualWorld(playerid, 0);
	if(GetPlayerPsex(playerid) == 1) SetPlayerSkin(playerid, NewPlayerSkinMard);
	else if(GetPlayerPsex(playerid) == 2) SetPlayerSkin(playerid, NewPlayerSkinZan);
	ResetPlayerMoney(playerid);
	GivePlayerMoney(playerid, GetPlayerPmoney(playerid));
	PlayerPlace[playerid] = -1;
	return 1;
}

public OnPlayerDeath(playerid, killerid, WEAPON:reason){
	HidePlayerAllTextDraw(playerid, GetPlayerToken(playerid));
	SetInt(playerid, DarHaleKillShodan, 1);
	if(IsValidDynamicObject(GetInt(playerid, ObjectMushakAre))){
		DestroyDynamicObject(GetInt(playerid, ObjectMushakAre));
		KillTimer(GetInt(playerid, TimerMushakArea));
		RemovePlayerMapIcon(playerid, 0);
	}
	PlayerPlace[playerid] = -1;
	return 1;
}

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger){
	new Tok = GetPlayerToken(playerid);
	if(!ispassenger){
		if(CheckPermissionForEnterToVehicle(playerid, vehicleid, false, Tok)) return 1;
		if(CheckVehicleOwnerForEnterPlayer(playerid, vehicleid, false, Tok)) return 1;
		if(CheckPlayerLicenseForEnterToVehicle(playerid, vehicleid, false, Tok)) return 1;
	}
	return 1;
}

public OnPlayerExitVehicle(playerid, vehicleid){
	return 1;
}

public OnVehicleSpawn(vehicleid){
	if(GetVehicleGovType(vehicleid) != VEH_TYPE_NONE) DestroyVehicleGov(GetVehicleGovOwner(vehicleid));
	return 1;
}

public OnVehicleDeath(vehicleid, killerid){
	if(GetVehicleGovType(vehicleid) != VEH_TYPE_NONE) DestroyVehicleGov(GetVehicleGovOwner(vehicleid));
	return 1;
}

public OnFilterScriptInit(){
	return 1;
}

public OnFilterScriptExit(){
	return 1;
}

public OnPlayerRequestSpawn(playerid){
	return 0;
}

public OnPlayerCommandText(playerid, cmdtext[]){
	return 0;
}

public OnPlayerCommandPerformed(playerid, cmd[], params[], result, flags){
	if(result == -1){
		SendPM(playerid, PMError, "In dastur vojud nadarad", "This command does not exist", GetPlayerToken(playerid));
		return 1;
	}else if(result == 0){
		//Vaghti dastu ejra nashod be dalayeli mese sytax ya ...
		return 1;
	}
	return 1;
}
public OnPlayerCommandReceived(playerid, cmd[], params[], flags){
	if(!IsPlayerConnected(playerid) || GetPlayerLogin(playerid) == 0) return 0;
	return 1;
}
public OnPlayerText(playerid, text[]){
	CheckPlayerLogin(playerid) return 0;
	return 1;
}

public OnPlayerUpdate(playerid){
	return 1;
}

public OnPlayerKeyStateChange(playerid, KEY:newkeys, KEY:oldkeys){
	return 1;
}

public OnPlayerStateChange(playerid, PLAYER_STATE:newstate, PLAYER_STATE:oldstate){
	new Tok = GetPlayerToken(playerid);
	if(newstate == PLAYER_STATE_DRIVER){
		new vehicleid = GetPlayerVehicleID(playerid);
		if(CheckPermissionForEnterToVehicle(playerid, vehicleid, true, Tok)) return 1;
		if(CheckVehicleOwnerForEnterPlayer(playerid, vehicleid, true, Tok)) return 1;
		if(CheckPlayerLicenseForEnterToVehicle(playerid, vehicleid, true, Tok)) return 1;
	}else if(newstate == PLAYER_STATE_ONFOOT){
		ResetPlayerAntiRemoveVehVariable(playerid);
		return 1;
	}
	return 1;
}

public OnPlayerGiveDamageActor(playerid, damaged_actorid, Float:amount, WEAPON:weaponid, bodypart){
	return 1;
}

public OnActorStreamIn(actorid, forplayerid){
	return 1;
}

public OnActorStreamOut(actorid, forplayerid){
	return 1;
}

public OnPlayerEnterGangZone(playerid, zoneid){
	return 1;
}

public OnPlayerLeaveGangZone(playerid, zoneid){
	return 1;
}

public OnPlayerEnterPlayerGangZone(playerid, zoneid){
	return 1;
}

public OnPlayerLeavePlayerGangZone(playerid, zoneid){
	return 1;
}

public OnPlayerClickGangZone(playerid, zoneid){
	return 1;
}

public OnPlayerClickPlayerGangZone(playerid, zoneid){
	return 1;
}

public OnPlayerSelectedMenuRow(playerid, row){
	return 1;
}

public OnPlayerExitedMenu(playerid){
	return 1;
}

public OnClientCheckResponse(playerid, actionid, memaddr, retndata){
	return 1;
}

public OnRconLoginAttempt(ip[], password[], success){
	return 1;
}

public OnPlayerFinishedDownloading(playerid, virtualworld){
	return 1;
}

public OnPlayerRequestDownload(playerid, DOWNLOAD_REQUEST:type, crc){
	return 1;
}

public OnRconCommand(cmd[]){
	return 0;
}

public OnPlayerSelectObject(playerid, SELECT_OBJECT:type, objectid, modelid, Float:fX, Float:fY, Float:fZ){
	return 1;
}

public OnPlayerEditObject(playerid, playerobject, objectid, EDIT_RESPONSE:response, Float:fX, Float:fY, Float:fZ, Float:fRotX, Float:fRotY, Float:fRotZ){
	return 1;
}

public OnPlayerEditAttachedObject(playerid, EDIT_RESPONSE:response, index, modelid, boneid, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fScaleX, Float:fScaleY, Float:fScaleZ){
	return 1;
}

public OnObjectMoved(objectid){
	return 1;
}

public OnPlayerObjectMoved(playerid, objectid){
	return 1;
}

public OnPlayerPickUpPickup(playerid, pickupid){
	return 1;
}

public OnPlayerPickUpPlayerPickup(playerid, pickupid){
	return 1;
}

public OnPickupStreamIn(pickupid, playerid){
	return 1;
}

public OnPickupStreamOut(pickupid, playerid){
	return 1;
}

public OnPlayerPickupStreamIn(pickupid, playerid){
	return 1;
}

public OnPlayerPickupStreamOut(pickupid, playerid){
	return 1;
}

public OnPlayerStreamIn(playerid, forplayerid){
	return 1;
}

public OnPlayerStreamOut(playerid, forplayerid){
	return 1;
}

public OnPlayerTakeDamage(playerid, issuerid, Float:amount, WEAPON:weaponid, bodypart){
	return 1;
}

public OnPlayerGiveDamage(playerid, damagedid, Float:amount, WEAPON:weaponid, bodypart){
	return 1;
}

public OnPlayerClickPlayer(playerid, clickedplayerid, CLICK_SOURCE:source){
	return 1;
}

public OnPlayerWeaponShot(playerid, WEAPON:weaponid, BULLET_HIT_TYPE:hittype, hitid, Float:fX, Float:fY, Float:fZ){
	return 1;
}

public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ){
	SetPlayerPos(playerid, fX, fY, fZ);
	return 1;
}

public OnIncomingConnection(playerid, ip_address[], port){
	return 1;
}

public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid){
	return 1;
}

public OnPlayerClickTextDraw(playerid, Text:clickedid){
	return 1;
}

public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid){
	return 1;
}

public OnTrailerUpdate(playerid, vehicleid){
	return 1;
}

public OnVehicleSirenStateChange(playerid, vehicleid, newstate){
	return 1;
}

public OnVehicleStreamIn(vehicleid, forplayerid){
	return 1;
}

public OnVehicleStreamOut(vehicleid, forplayerid){
	return 1;
}

public OnVehicleMod(playerid, vehicleid, componentid){
	return 1;
}

public OnEnterExitModShop(playerid, enterexit, interiorid){
	return 1;
}

public OnVehiclePaintjob(playerid, vehicleid, paintjobid){
	return 1;
}

public OnVehicleRespray(playerid, vehicleid, color1, color2){
	return 1;
}

public OnVehicleDamageStatusUpdate(vehicleid, playerid){
	return 1;
}

public OnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat, Float:new_x, Float:new_y, Float:new_z, Float:vel_x, Float:vel_y, Float:vel_z){
	return 1;
}
CMD:mypos(playerid){
	new Float:mp[4];
	GetPlayerPos(playerid, mp[0], mp[1], mp[2]);
	GetPlayerFacingAngle(playerid, mp[3])
	printf("%f, %f, %f, %f", mp[0], mp[1], mp[2], mp[3]);
	return 1;
}
new gov;
CMD:gov(playerid, params[]){
	new vehid;
	if(sscanf(params, "d", vehid)) return SCM(playerid , -1, "/Veh [VehID]");
	new Float:pos[3];
	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	gov = CreateVehicleGov(playerid, VEH_TYPE_DMV, vehid, pos[0], pos[1], pos[2]+3.0, 88.8, 0, 0, true);
	PutPlayerInVehicle(playerid, gov, 0);
	return 1;
}
new veh;
CMD:veh(playerid, params[]){
	new vehid;
	if(sscanf(params, "d", vehid)) return SCM(playerid , -1, "/Veh [VehID]");
	DestroyVehicle(veh);
	new Float:pos[3];
	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	veh = CreateVehicle(vehid, pos[0], pos[1], pos[2], 180.0, 8, 8, 20000, true);
	PutPlayerInVehicle(playerid, veh, 0);
	return 1;
}
CMD:pos(playerid){
	new Float:Pos[4];
	GetVehiclePos(veh, Pos[0], Pos[1], Pos[2]);
	GetVehicleZAngle(veh, Pos[3]);
	SendClientMessage(playerid, -1, "X: %f, Y: %f, Z: %f, A: %f", Pos[0], Pos[1], Pos[2], Pos[3]);
	return 1;
}
CMD:cancel(playerid, params[]){
	new CNID[50], Tok = GetPlayerToken(playerid);
	if(sscanf(params, "s[50]", CNID)){
		SendSyntaxCommand(playerid, "/Cancel <Name>", Tok);
		SendLongMessage(playerid, -1, "Name: [C]eck[P]oint", Tok);
		return 1;
	}
	if(strcmp(CNID, "checkpoint", true) == 0|| strcmp(CNID, "cp", true) == 0){
		if(!GetPlayerCheckPointActive(playerid)) return SendPM(playerid, PMError, "Shoma checkpointe faal nadarid", "You do not have an active checkpoint", Tok);
		switch(GetPlayerChechPointID(playerid)){
			case CHECKPOINTID_ExamLic:{
				SendPM(playerid, PMError, "Shoma nemitavanid checkpointe azmun ra cancel konid", "You cannot cancel the checkpoint exam", Tok);
			}
			default:{
				CancelPlayerCheckPoint(playerid);
			}
		}return 1;
	}else{
		SendPM(playerid, PMError, "Name mo'tabar nist", "Name is not valid", Tok);
	}
	return 1;
}
CMD:int1(playerid){
	SetPlayerInterior(playerid, 7);
	SetPlayerPos(playerid, 315.244, -140.8858, 999.6016);
	return 1;
}
CMD:int2(playerid){
	SetPlayerInterior(playerid, 1);
	SetPlayerPos(playerid, 285.8361, -39.0166, 1001.5156);
	return 1;
}
CMD:int3(playerid){
	SetPlayerInterior(playerid, 4);
	SetPlayerPos(playerid, 291.7626, -80.1306, 1001.5156);
	return 1;
}
CMD:int4(playerid){
	SetPlayerInterior(playerid, 6);
	SetPlayerPos(playerid, 297.144, -109.8702, 1001.5156);
	return 1;
}
CMD:int5(playerid){
	SetPlayerInterior(playerid, 6);
	SetPlayerPos(playerid, 316.5025, -167.6272, 999.5938);
	return 1;
}