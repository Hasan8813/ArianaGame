#if defined _SYSTEMAREAMUSHAK_BY_MAMAD_PERSIAN_INC
	#endinput
#endif
#define _SYSTEMAREAMUSHAK_BY_MAMAD_PERSIAN_INC

new MantagheyeMamnooArea;
stock LoadZoneArea69(){
	MantagheyeMamnooArea = CreateDynamicCircle(175.8009, 1885.7312, 350.0, 0, 0, -1);
	return 1;
}
stock MushakShow(playerid, Token){
	CheckPlayerOnlineAndLogin(playerid);
	CheckPlayerTokenCmp(playerid, Token);
	StartEkhtarArea(playerid, GetPlayerToken(playerid));
	return 1;
}
//Shelike mushak az area 69 be samte bazikon
stock FireRocketArea(playerid, Token){
	CheckPlayerOnlineAndLogin(playerid);
	CheckPlayerTokenCmp(playerid, Token);
	if(IsValidDynamicObject(GetInt(playerid, ObjectMushakAre))) return 1;
	switch(random(4)){
		case 0: SetInt(playerid, ObjectMushakAre, CreateDynamicObject(345, 237.7179, 1697.6321, 25.9300, 0.0, 0.0, 0.0, 0, 0, -1, 400.0, 400.0));
		case 1: SetInt(playerid, ObjectMushakAre, CreateDynamicObject(345, 15.6231, 1720.0946, 25.8082, 0.0, 0.0, 0.0,0, 0, -1, 400.0, 400.0 ));
		case 2: SetInt(playerid, ObjectMushakAre, CreateDynamicObject(345, 188.1736, 2082.8469, 25.5383, 0.0, 0.0, 0.0,0, 0, -1, 400.0, 400.0 ));
		case 3: SetInt(playerid, ObjectMushakAre, CreateDynamicObject(345,  354.4084, 2029.5145, 25.7265, 0.0, 0.0, 0.0,0, 0, -1, 400.0, 400.0 ));
	}SetInt(playerid, TimerMushakArea, SetTimerEx("RahGiriBazikonArea", 100, true, "id", playerid, Token));
	PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
	return 1;
}
//Shoro'e ekhtar be bazikon hengami ke bazikon be mantaghrye area 69 mire
stock StartEkhtarArea(playerid, Token){
	CheckPlayerOnlineAndLogin(playerid);
	CheckPlayerTokenCmp(playerid, Token);
	if(IsValidDynamicObject(GetInt(playerid, ObjectMushakAre))) return 1;
	if(GetInt(playerid, DarHaleRahgiri) == 1) return 1;
	SetInt(playerid, DarHaleRahgiri, 1);
	SendPM(playerid, PMRed, "Az in mantaghe fasele begirid; dar gheyre in surat hadaf gharar khahid gereft.", "Stay away from this area; otherwise, you will be targeted.", Token);
	PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
	yield 1;
	task_await(task_ms(5000));
	CheckPlayerOnlineAndLogin(playerid);
	CheckPlayerTokenCmp(playerid, Token);
	if(!IsPlayerInDynamicArea(playerid, MantagheyeMamnooArea)) return DeleteV(playerid, DarHaleRahgiri);
	if(IsValidDynamicObject(GetInt(playerid, ObjectMushakAre))) return 1;
	SendPM(playerid, PMRed, "Az in mantaghe fasele begirid; dar gheyre in surat hadaf gharar khahid gereft.", "Stay away from this area; otherwise, you will be targeted.", Token);
	PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
	task_await(task_ms(5000));
	CheckPlayerOnlineAndLogin(playerid);
	CheckPlayerTokenCmp(playerid, Token);
	if(!IsPlayerInDynamicArea(playerid, MantagheyeMamnooArea)) return DeleteV(playerid, DarHaleRahgiri);
	if(IsValidDynamicObject(GetInt(playerid, ObjectMushakAre))) return 1;
	SendPM(playerid, PMRed, "In akharin hoshdar ast; ta 10 saniyeye digar agar in mantaghe ra tark nakarde bashid, nabud khahid shod.", "This is the final warning; if you do not leave this area within 10 seconds, you will be destroyed.", Token);
	PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
	task_await(task_ms(10000));
	CheckPlayerOnlineAndLogin(playerid);
	CheckPlayerTokenCmp(playerid, Token);
	if(!IsPlayerInDynamicArea(playerid, MantagheyeMamnooArea)) return DeleteV(playerid, DarHaleRahgiri);
	if(IsValidDynamicObject(GetInt(playerid, ObjectMushakAre))) return 1;
	DeleteV(playerid, DarHaleRahgiri);
	FireRocketArea(playerid, Token);
	SendPM(playerid, PMRed, "Mushak hayi baraye nabudiye shoma dar hale partab hastand.", "Missiles are being launched to destroy you.", Token);
	PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
	return 1;
}
//Hedayate mushak bad az partab ba stock FireRocketArea be samte bazikon
forward RahGiriBazikonArea(playerid, Token);
public RahGiriBazikonArea(playerid, Token){
	CheckPlayerToken(playerid, Token){
		DestroyDynamicObject(GetInt(playerid, ObjectMushakAre));
		KillTimer(GetInt(playerid, TimerMushakArea));
		return 1;
	}if(!IsPlayerConnected(playerid)){
		DestroyDynamicObject(GetInt(playerid, ObjectMushakAre));
		KillTimer(GetInt(playerid, TimerMushakArea));
		return 1;
	}new Float:PX, Float:PY, Float:PZ;
	GetPlayerPos(playerid, PX, PY, PZ);
	new Float:OX, Float:OY, Float:OZ;
	GetDynamicObjectPos(GetInt(playerid, ObjectMushakAre), OX, OY, OZ);
	MoveDynamicObject(GetInt(playerid, ObjectMushakAre), PX, PY, PZ, 80.0);
	SetPlayerMapIcon(playerid, 0, OX, OY, OZ, 0, 0xFF0505FF);
	new Float:Distance = GetDistanceVasat(OX, OY, OZ, PX, PY, PZ);
	if(Distance < 7.0){
		CreateExplosion(OX, OY, OZ, 6, 20.0);
		CreateExplosion(PX, PY, PZ, 6, 20.0);
		DestroyDynamicObject(GetInt(playerid, ObjectMushakAre));
		RemovePlayerMapIcon(playerid, 0);
		KillTimer(GetInt(playerid, TimerMushakArea));
		SendPM(playerid, PMRed, "Mushake partab shode be shoma barkhord kard.", "The missile that had been fired struck you.", GetPlayerToken(playerid));
		DeleteV(playerid, TimerMushakArea);
		yield 1;
		task_await(task_ms(10000));
		if(!IsPlayerConnected(playerid)) return 1;
		if(IsPlayerInDynamicArea(playerid, MantagheyeMamnooArea, 1)){
			new Float:hpppp;
			GetPlayerHealth(playerid, hpppp);
			if(hpppp > 1.0) FireRocketArea(playerid, GetPlayerToken(playerid));
		}
	}return 1;
}

