#if defined _SYSTEME_EXAM_BY_MAMAD_PERSIAN_INC
	#endinput
#endif
#define _SYSTEME_EXAM_BY_MAMAD_PERSIAN_INC

stock LoadMapExam(){
    //Mape exam
	CreateDynamicObject(4641,1354.067,-2341.873,14.175,0.000,0.000,0.000,0,0,-1,200.000,200.000);
	CreateDynamicObject(4641,-1770.851,-184.421,4.224,0.000,0.000,97.999,0,0,-1,200.000,200.000);
	CreateDynamicObject(982,1368.513,-2355.785,13.246,0.000,0.000,0.000,0,0,-1,200.000,200.000);
	CreateDynamicObject(984,1362.096,-2342.849,13.246,0.000,0.000,90.000,0,0,-1,200.000,200.000);
	CreateDynamicPickup(1581, 1, 1353.544921, -2343.492187, 13.546875, 0, 0, -1, 200.0);
	CreateDynamicPickup(1581, 1, -1769.167480, -184.762985, 3.554687, 0, 0, -1, 200.0);
	CreateDynamicPickup(1581, 1, 415.045288, 2535.450683, 19.058437, 0, 0, -1, 200.0);
	Create3DTextLabel("To obtain a driving license\nuse /exam", 0x70D8F8FF, 1353.544921, -2343.492187, 13.546875, 5.0, 0, true);
	Create3DTextLabel("To obtain a sailing license\nuse /exam", 0x70D8F8FF, -1769.167480, -184.762985, 3.554687, 5.0, 0, true);
	Create3DTextLabel("To obtain a flying license\nuse /exam", 0x70D8F8FF, 415.045288, 2535.450683, 19.058437, 5.0, 0, true);
    return 1;
}
new ParkinPosAct[3], Iterator:ExamLic<MAX_PLAYERS>, TimerExamLic = -1;
new const Float:ParkingPosExam[3][7][4] = {
	{//Driving test
		{1365.685791, -2344.500000, 14.000000, 90.471687},
		{1365.706298, -2347.927490, 14.000000, 89.103027},
		{1365.661621, -2351.502685, 14.000000, 89.293655},
		{1365.705810, -2355.169433, 14.000000, 88.941917},
		{1365.664550, -2358.608642, 14.000000, 89.235282},
		{1365.656250, -2362.066894, 14.000000, 88.850135},
		{1365.653686, -2365.659179, 14.000000, 91.168823}
	},
	{//Flying test
		{388.242950, 2532.047363, 16.539180, 180.000},
		{376.242950, 2532.047363, 16.539180, 180.000},
		{364.242950, 2532.047363, 16.539180, 180.000},
		{352.242950, 2532.047363, 16.539180, 180.000},
		{382.242950, 2549.811279, 16.539062, 180.000},
		{370.242950, 2549.811279, 16.539062, 180.000},
		{358.242950, 2549.811279, 16.539062, 180.000}
	},
	{//Sailing test
		{-1766.022827, -197.953018, 1.200000, 270.000},
		{-1766.022827, -206.614196, 1.200000, 270.000},
		{-1766.022827, -215.953018, 1.200000, 270.000},
		{-1766.022827, -224.953018, 1.200000, 270.000},
		{-1766.022827, -233.953018, 1.200000, 270.000},
		{-1766.022827, -242.953018, 1.200000, 270.000},
		{-1766.022827, -251.953018, 1.200000, 270.000}
	}
};
new const Float:DmvCpPos[3][23][3] = {
	{//Driving test
		{1346.816284, -2346.997070, 13.375000},
		{1353.794677, -2303.753417, 13.382812},
		{1395.959228, -2286.412353, 13.361654},
		{1426.721313, -2290.993164, 13.382812},
		{1455.629760, -2331.273925, 13.382812},
		{1511.103149, -2320.582763, 13.382812},
		{1526.857177, -2288.221679, 13.382812},
		{1574.814575, -2290.114746, 13.289109},
		{1578.574462, -2316.872314, 13.382812},
		{1689.742919, -2319.321044, 13.382812},
		{1795.903808, -2316.761718, 13.382812},
		{1794.152099, -2254.163330, 6.265625},
		{1718.042236, -2253.814941, -2.851562},
		{1577.400146, -2259.175537, -2.851562},
		{1570.192260, -2285.702392, -2.992187},
		{1522.513061, -2282.014404, -2.992187},
		{1484.724853, -2240.596923, -2.992187},
		{1429.146240, -2271.532958, -2.992187},
		{1428.435546, -2349.938476, 1.274291},
		{1421.463623, -2434.114013, 6.039062},
		{1358.909301, -2443.945800, 7.656250},
		{1350.204101, -2381.500976, 13.375000},
		{1348.563720, -2347.033203, 13.375000}
	},
	{//Flying test
		{371.654052, 2494.878173, 29.242391},
		{358.435546, 2433.535400, 37.868827},
		{308.920410, 2348.318603, 46.183887},
		{222.074371, 2298.235107, 54.981258},
		{126.978729, 2291.038574, 55.826930},
		{6.541852, 2313.141845, 64.692588},
		{-85.912048, 2334.815673, 81.945930},
		{-143.662261, 2349.655517, 100.078300},
		{-225.468322, 2376.242919, 123.549850},
		{-288.054412, 2396.750732, 121.922172},
		{-396.450561, 2437.903320, 99.078689},
		{-484.822143, 2487.183593, 83.800476},
		{-551.828369, 2573.847656, 91.410064},
		{-553.497375, 2707.229492, 99.474075},
		{-470.395355, 2831.699707, 117.972167},
		{-329.256439, 2935.779785, 117.209197},
		{-141.317626, 2985.982421, 115.144599},
		{-28.629167, 2986.437011, 115.518035},
		{140.558822, 2980.244873, 108.976638},
		{369.573822, 2822.880126, 103.127365},
		{425.693115, 2704.231933, 86.017585},
		{423.690521, 2617.559570, 62.421981},
		{394.679107, 2503.496582, 16.484375}
	},
	{//Sailing test
		{-1729.790283, -183.706756, 0.080000},
		{-1644.605834, -93.499664, 0.080000},
		{-1496.767211, 62.041088, 0.080000},
		{-1308.802978, 262.037506, 0.080000},
		{-1209.962646, 406.131958, 0.080000},
		{-1181.604003, 559.159423, 0.080000},
		{-1243.118408, 787.394470, 0.080000},
		{-1329.591918, 1021.961975, 0.080000},
		{-1413.964965, 1137.961181, 0.080000},
		{-1445.540161, 1217.858032, 0.080000},
		{-1446.508544, 1300.292480, 0.080000},
		{-1404.781005, 1379.655151, 0.080000},
		{-1333.629760, 1437.489501, 0.080000},
		{-1266.719848, 1445.031372, 0.080000},
		{-1207.567382, 1417.690307, 0.080000},
		{-1167.167846, 1373.869995, 0.080000},
		{-1135.505737, 1304.370361, 0.080000},
		{-1138.724243, 1223.813110, 0.080000},
		{-1172.931884, 1029.200561, 0.080000},
		{-1144.309326, 599.645019, 0.080000},
		{-1169.714843, 407.444427, 0.080000},
		{-1426.203247, 131.017013, 0.080000},
		{-1721.541015, -171.014022, 0.080000}
	}
};
stock StopTestDMV(playerid, bool:RMLIST){
	DestroyVehicleGov(playerid);
	if(RMLIST && Iter_Contains(ExamLic, playerid)) Iter_Remove(ExamLic, playerid);
	SetPState(playerid, 0);
	CancelPlayerRaceCheckPoint(playerid);
	DeleteV(playerid, CheckPointNumberDMV);
	DeleteV(playerid, PlayerPersonalUseDMV);
	PlayerTextDrawDestroy(playerid, PlayerText:GetInt(playerid, ExamCpNumTd));
	DeleteV(playerid, ExamCpNumTd);
}
CreateRaceCheckPointStock(CHECKPOINTID_ExamLic){
	new DMVCPID = GetInt(playerid, CheckPointNumberDMV);
	if(DMVCPID <= 0) return 1;
	if(!IsPlayerInAnyVehicle(playerid) || GetPlayerVehicleSeat(playerid) != 0) return 1;
	new VI = GetPlayerVehicleID(playerid), CpId = GetPState(playerid) - 1;
	if(GetVehicleGovType(VI) != GetPState(playerid) || GetVehicleGovOwner(VI) != playerid) return 1;
	if(!IsPlayerInRangeOfPoint(playerid, 20.0, DmvCpPos[CpId][DMVCPID-1][0], DmvCpPos[CpId][DMVCPID-1][1], DmvCpPos[CpId][DMVCPID-1][2])) return 1;
	PlayerPlaySound(playerid, 1056);
	new DMVCPIDMAX = sizeof(DmvCpPos[])-1;
	if(DMVCPID == DMVCPIDMAX+1){
		switch(GetPState(playerid)){
			case 1: SetPlayerPdrivlic(playerid, 60);
			case 2: SetPlayerPflylic(playerid, 60), SetPlayerPos(playerid, 415.045288, 2535.450683, 19.108437);
			case 3: SetPlayerPsailinglic(playerid, 60), SetPlayerPos(playerid, -1769.167480, -184.762985, 3.554687);
		}
		StopTestDMV(playerid, true);
		SendPM(playerid, PMBlueA, "Tabrik! Shoma azmun ra ba movafaghiyat poshte sar gozashtid, ba dasture \"/Account\" mitavanid mojavez haye khod ra moshahede konid.", "Congratulations! You have successfully passed the test, You can view your licenses using the \"/Account\" command.", GetPlayerToken(playerid));
		FlagUpdate(playerid);
		return 1;
	}else if(DMVCPID == DMVCPIDMAX){
		DisablePlayerRaceCheckpoint(playerid);
		switch(CpId){
			case 0: SetPlayerRaceCheckpoint(playerid, CP_TYPE_GROUND_FINISH, DmvCpPos[CpId][DMVCPIDMAX][0], DmvCpPos[CpId][DMVCPIDMAX][1], DmvCpPos[CpId][DMVCPIDMAX][2], 0.0, 0.0, 0.0, 4.0);
			case 1: SetPlayerRaceCheckpoint(playerid, CP_TYPE_AIR_BOBBING, DmvCpPos[CpId][DMVCPIDMAX][0], DmvCpPos[CpId][DMVCPIDMAX][1], DmvCpPos[CpId][DMVCPIDMAX][2], 394.679107, 2503.496582, 30.484375, 10.0);
			case 2: SetPlayerRaceCheckpoint(playerid, CP_TYPE_AIR_FINISH, DmvCpPos[CpId][DMVCPIDMAX][0], DmvCpPos[CpId][DMVCPIDMAX][1], DmvCpPos[CpId][DMVCPIDMAX][2], -1743.958984, -194.754257, 0.080000, 8.0);
		}
		SetInt(playerid, CheckPointNumberDMV, DMVCPID+1);
		return 1;
	}
	DisablePlayerRaceCheckpoint(playerid);
	switch(CpId){
		case 0: SetPlayerRaceCheckpoint(playerid, CP_TYPE_GROUND_NORMAL, DmvCpPos[CpId][DMVCPID][0], DmvCpPos[CpId][DMVCPID][1], DmvCpPos[CpId][DMVCPID][2], DmvCpPos[CpId][DMVCPID+1][0], DmvCpPos[CpId][DMVCPID+1][1], DmvCpPos[CpId][DMVCPID+1][2], 4.0);
		case 1: SetPlayerRaceCheckpoint(playerid, CP_TYPE_AIR_NORMAL, DmvCpPos[CpId][DMVCPID][0], DmvCpPos[CpId][DMVCPID][1], DmvCpPos[CpId][DMVCPID][2], DmvCpPos[CpId][DMVCPID+1][0], DmvCpPos[CpId][DMVCPID+1][1], DmvCpPos[CpId][DMVCPID+1][2], 8.0);
		case 2: SetPlayerRaceCheckpoint(playerid, CP_TYPE_AIR_BOBBING, DmvCpPos[CpId][DMVCPID][0], DmvCpPos[CpId][DMVCPID][1], DmvCpPos[CpId][DMVCPID][2], DmvCpPos[CpId][DMVCPID+1][0], DmvCpPos[CpId][DMVCPID+1][1], DmvCpPos[CpId][DMVCPID+1][2], 8.0);
	}
	new PlayerText:PlayerTdCp = PlayerText:GetInt(playerid, ExamCpNumTd);
	PlayerTextDrawSetString(playerid, PlayerTdCp, "~r~%d/23", DMVCPID);
	PlayerTextDrawShow(playerid, PlayerTdCp);
	SetInt(playerid, CheckPointNumberDMV, DMVCPID+1);
	return 1;
}
stock StartTestLicense(playerid, TestNumber, Token){
	CheckPlayerOnlineAndLogin(playerid);
	CheckPlayerTokenCmp(playerid, Token);
	new Level = GetPlayerPlevel(playerid);
	if(TestNumber == 2 && Level < 3) return SendPM(playerid, PMError, "Baraye in mojavez, levele shoma bayad hadeaghal 3 bashad", "For this license, your level must be at least 3", Token);
	if(TestNumber == 3 && Level < 2) return SendPM(playerid, PMError, "Baraye in mojavez, levele shoma bayad hadeaghal 2 bashad", "For this license, your level must be at least 2", Token);
	new LIC, VehTestId, LicNameP[30], LicNameE[20];
	switch(TestNumber){
		case 1: LIC = GetPlayerPdrivlic(playerid), VehTestId = 589, LicNameP = "govahinameye ranandegi", LicNameE = "driving license";
		case 2: LIC = GetPlayerPflylic(playerid), VehTestId = 469, LicNameP = "mojaveze parvaz", LicNameE = "flying license";
		case 3: LIC = GetPlayerPsailinglic(playerid), VehTestId = 446, LicNameP = "mojaveze ghayegh rani", LicNameE = "sailing license";
	}
	if(LIC >= 0 && LIC <= 10){
		CheckPlayerCheckPointActiveAndError(playerid);
		CheckPlayerCreatedVehicleGov(playerid);
		new i, bool:PARKINGP;
		if(ParkinPosAct[TestNumber-1] >= 7) i = (ParkinPosAct[TestNumber-1] = 0), PARKINGP = true;
		else i = (ParkinPosAct[TestNumber-1]++);
		new DMVV = CreateVehicleGov(playerid, TestNumber, VehTestId, ParkingPosExam[TestNumber-1][i][0], ParkingPosExam[TestNumber-1][i][1],  ParkingPosExam[TestNumber-1][i][2], ParkingPosExam[TestNumber-1][i][3], 130, 130, false);
		if(DMVV == INVALID_VEHICLE_ID) return SendPM(playerid, PMError, "Lotfan chand daghighe digar dobare talash konid", "Please try again in a few minutes", Token);
		new PlayerText:ExamLicTd = CreatePlayerTextDraw(playerid, 300.0, 370.0, "0/23"); PlayerTextDrawFont(playerid, ExamLicTd, TEXT_DRAW_FONT_1); PlayerTextDrawLetterSize(playerid, ExamLicTd, 0.6, 3.5); PlayerTextDrawColour(playerid, ExamLicTd, 0xFFFFFFFF); PlayerTextDrawSetOutline(playerid, ExamLicTd, 1); PlayerTextDrawSetProportional(playerid, ExamLicTd, true); PlayerTextDrawSetShadow(playerid, ExamLicTd, true);
		PlayerTextDrawShow(playerid, ExamLicTd);
		SetInt(playerid, ExamCpNumTd, _:ExamLicTd);
		SetVehicleNumberPlate(DMVV, "Exam");
		SetVehicleParamsEx(DMVV, 1, 0, 0, 1, 0, 0, 0);
		SetPState(playerid, TestNumber);
		PutPlayerInVehicle(playerid, DMVV, 0);
		if(PARKINGP) ParkinPosAct[TestNumber-1]++;
		Iter_Add(ExamLic, playerid);
		if(!IsValidTimer(TimerExamLic)) TimerExamLic = SetTimer("CheckPlayerExamLic", 3000, true);
		switch(TestNumber-1){
			case 0: SetPlayerRaceCheckpoint(playerid, CP_TYPE_GROUND_NORMAL, DmvCpPos[TestNumber-1][0][0], DmvCpPos[TestNumber-1][0][1], DmvCpPos[TestNumber-1][0][2], DmvCpPos[TestNumber-1][1][0], DmvCpPos[TestNumber-1][1][1], DmvCpPos[TestNumber-1][1][2], 4.0);
			case 1: SetPlayerRaceCheckpoint(playerid, CP_TYPE_AIR_NORMAL, DmvCpPos[TestNumber-1][0][0], DmvCpPos[TestNumber-1][0][1], DmvCpPos[TestNumber-1][0][2], DmvCpPos[TestNumber-1][1][0], DmvCpPos[TestNumber-1][1][1], DmvCpPos[TestNumber-1][1][2], 8.0);
			case 2: SetPlayerRaceCheckpoint(playerid, CP_TYPE_AIR_BOBBING, DmvCpPos[TestNumber-1][0][0], DmvCpPos[TestNumber-1][0][1], DmvCpPos[TestNumber-1][0][2], DmvCpPos[TestNumber-1][1][0], DmvCpPos[TestNumber-1][1][1], DmvCpPos[TestNumber-1][1][2], 8.0);
		}
		SetPlayerCheckPointID(playerid, CHECKPOINTID_ExamLic);
		SetInt(playerid, CheckPointNumberDMV, 1);
	}else if(LIC > 10){
		new MSG1[150], MSG2[100];
		format(MSG1, sizeof(MSG1), "Shoma dar hale hazer %s darid, baraye tamdide an zamane enghezaye an bayad hadeaghal 10 saat bashad", LicNameP);
		format(MSG2, sizeof(MSG2), "You currently hold a %s, The expiration period must be 10 hours for you to be able to extend it", LicNameE);
		SendPM(playerid, PMError, MSG1, MSG2, Token);
	}else if(LIC < 0){
		new MSG1[80], MSG2[70];
		format(MSG1, sizeof(MSG1), "%s shoma baraye %d saat masdud shode ast", LicNameP, abs(LIC));
		format(MSG2, sizeof(MSG2), "Your %s has been suspended for %d hours", LicNameE, abs(LIC));
		SendPM(playerid, PMError, MSG1, MSG2, Token);
	}return 1;
}
forward CheckPlayerExamLic();
public CheckPlayerExamLic(){
	if(Iter_Count(ExamLic) == 0) return KillTimer(TimerExamLic), TimerExamLic = -1;
	foreach(new PL : ExamLic){
		new TOK = GetPlayerToken(PL), RJ;
		if(IsPlayerInAnyVehicle(PL) && GetPlayerVehicleSeat(PL) == 0){
			new VehIn = GetPlayerVehicleID(PL), Float:VehHealth;
			GetVehicleHealth(VehIn, VehHealth);
			new PPUSE = GetInt(PL, PlayerPersonalUseDMV)+1;
			SetInt(PL, PlayerPersonalUseDMV, PPUSE);
			if(PPUSE >= 55) RJ = 3;
			if(GetVehicleGovType(VehIn) == GetPState(PL) && GetVehicleGovOwner(VehIn) == PL){if(VehHealth <= 850.0) RJ = 1;}
			else RJ = 2;
		}else RJ = 2;
		if(RJ >= 1){
			if(RJ == 1) SendPM(PL, PMBlueA, "Shoma asibe ziyadi be vasileye naghliye vared kardid va dar azmun mardud shodid, dobare dar azmun mitavanid sherkat konid.", "You caused too much damage to the vehicle and failed the test, you can take the test again.", TOK);
			else if(RJ == 2) SendPM(PL, PMBlueA, "Shoma az vasileye naghliyeye khod kharej shodid va dar azmun mardud shodid, dobare mitavanid dar azmun sherkat konid.", "You got out of your vehicle and failed the test, you can take the test again.", TOK);
			else if(RJ == 3) SendPM(PL, PMBlueA, "Zamane shoma be payan resid va dar azmun mardud shodid, dobare mitavanid dar azmun sherkat konid.", "Your time has run out and you have failed the exam, you may take the exam again.", TOK);
			switch(GetPState(PL)){
				case 1: SetPlayerPos(PL, 1353.544921, -2343.492187, 13.546875);
				case 2: SetPlayerPos(PL, 415.045288, 2535.450683, 19.058437);
				case 3: SetPlayerPos(PL, -1769.167480, -184.762985, 3.554687);
			}
			StopTestDMV(PL, false);
			if(IsPlayerInAnyVehicle(PL) && GetPlayerVehicleSeat(PL) == 0) CheckPlayerLicenseForEnterToVehicle(PL, GetPlayerVehicleID(PL), true, TOK);
			Iter_SafeRemove(ExamLic, PL, PL); continue;
		}
	}return 1;
}
CMD:exam(playerid){
	new TOK = GetPlayerToken(playerid);
	if(GetPState(playerid) >= 1 && GetPState(playerid) <= 3) return SendPM(playerid, PMError, "Shoma dar azmun hastid", "You are in an exam", TOK);
	if(GetPlayerVirtualWorld(playerid) != 0 || GetPlayerInterior(playerid) != 0) return SendPM(playerid, PMError, "Shoma dar makane hich yek az azmun ha nistid", "You are not at the location of any exam", TOK);
	if(IsPlayerInAnyVehicle(playerid)) return SendPM(playerid, PMError, "Baraye estefade az in dastur bayad piyade bashid", "You must be on foot to use the command", TOK);
	if(IsPlayerInRangeOfPoint(playerid, 2.0, 1353.544921, -2343.492187, 13.546875)){
		StartTestLicense(playerid, 1, TOK);
	}else if(IsPlayerInRangeOfPoint(playerid, 2.0, 415.045288, 2535.450683, 19.058437)){
		StartTestLicense(playerid, 2, TOK);
	}else if(IsPlayerInRangeOfPoint(playerid, 2.0, -1769.167480, -184.762985, 3.554687)){
		StartTestLicense(playerid, 3, TOK);
	}else{
		SendPM(playerid, PMError, "Shoma dar makane hich yek az azmun ha nistid", "You are not at the location of any exam", TOK);
	}return 1;
}