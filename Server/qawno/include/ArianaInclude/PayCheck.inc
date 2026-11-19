//                              Be name khoda                               //
#if defined _SYSTEME_PAYCHECK_BY_MAMAD_PERSIAN_INC
	#endinput
#endif
#define _SYSTEME_PAYCHECK_BY_MAMAD_PERSIAN_INC

stock UpdatePayCheck(playerid, bool:CheckXP, Token){
    CheckPlayerOnlineAndLogin(playerid);
    CheckPlayerTokenCmp(playerid, Token);
	new Seconds = (GetTickCount() - GetPlayerStartTimePlay(playerid)) / 1000;
	new Minutes = GetPlayerPtimeplaymin(playerid) + Seconds;
    new Whilee = 0;
	if(CheckXP){
		while(Minutes >= 3600){
			Minutes -= 3600;
            Whilee++;
		}
	}if(Whilee > 0){
        SendPM(playerid, PMWhite, "{19D8E6}************  Hoghughe saati  ************", "{19D8E6}************  Hourly pay check  ************", Token);
        new PM1[60], PM2[60];
        format(PM1, sizeof(PM1), "{19D8E6}- Saate bazi kardan: {FFFFFF}%d + %d{19D8E6} saat.", GetPlayerPtimeplay(playerid), Whilee);
        format(PM2, sizeof(PM2), "{19D8E6}- Time play: {FFFFFF}%d + %d{19D8E6} hour.", GetPlayerPtimeplay(playerid), Whilee);
        SendPM(playerid, PMWhite, PM1, PM2, Token);
        SetPlayerPtimeplay(playerid, GetPlayerPtimeplay(playerid) + Whilee);
		GiveXp(playerid, Whilee, Token);
        new DRL = GetPlayerPdrivlic(playerid); if(DRL > 0) SetPlayerPdrivlic(playerid, DRL - Whilee); else if(DRL < 0) SetPlayerPdrivlic(playerid, DRL + 1);
        new FLL = GetPlayerPflylic(playerid); if(FLL > 0) SetPlayerPflylic(playerid, FLL - Whilee); else if(FLL < 0) SetPlayerPflylic(playerid, FLL + 1);
        new SAL = GetPlayerPsailinglic(playerid); if(SAL > 0) SetPlayerPsailinglic(playerid, SAL - Whilee); else if(SAL < 0) SetPlayerPsailinglic(playerid, SAL + 1);
        new WPL = GetPlayerPweaponlic(playerid); if(WPL > 0) SetPlayerPweaponlic(playerid, WPL - Whilee); else if(WPL < 0) SetPlayerPweaponlic(playerid, WPL + 1);
        PlayerPlaySound(playerid, 1139);
        FlagUpdate(playerid);
        if(IsPlayerInAnyVehicle(playerid) && GetPlayerVehicleSeat(playerid) == 0){
            new Vehid = GetPlayerVehicleID(playerid);
            if(CheckAirAndHeliVeh(Vehid) && GetPState(playerid) != STATE_FLYSCHOOL_TEST){
                if(GetPlayerPflylic(playerid) == 0){
                    EjectPlayerVehicle(playerid);
                    SendPM(playerid, PMBlueA, "Tarikhe mojaveze parvaze shoma be payan resid.", "Your fly license has expired.", Token);
                }
            }else if(CheckSailingVeh(Vehid) && GetPState(playerid) != STATE_SAILING_TEST){
                if(GetPlayerPsailinglic(playerid) == 0){
                    EjectPlayerVehicle(playerid);
                    SendPM(playerid, PMBlueA, "Tarikhe mojaveze ghayegh raniye shoma be payan resid.", "Your sailing license has expired.", Token);
                }
            }else if(!CheckBikeAndRcVeh(Vehid) && GetPlayerPdrivlic(playerid) == 0 && GetPState(playerid) != STATE_DMV_TEST){
                EjectPlayerVehicle(playerid);
                SendPM(playerid, PMBlueA, "Tarikhe govahinameye ranandegiye shoma be payan resid.", "Your driving license has expired.", Token);
            }
        }
    }SetPlayerPtimeplaymin(playerid, Minutes);
	SetPlayerStartTimePlay(playerid, GetTickCount());
	return 1;
}