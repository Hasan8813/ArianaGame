//                              Be name khoda                               //
#if defined _ENTERVEHICLE_DRIVERSTATE_BY_MAMAD_PERSIAN_INC
	#endinput
#endif
#define _ENTERVEHICLE_DRIVERSTATE_BY_MAMAD_PERSIAN_INC

stock CheckPermissionForEnterToVehicle(playerid, vehicleid, bool:entered, Tok){
    switch(GetVehicleGovType(vehicleid)){
		case VEH_TYPE_DMV:{
			if(GetPState(playerid) != STATE_DMV_TEST){
                if(entered) EjectPlayerVehicle(playerid);
                else ClearAnimations(playerid);
				SendPM(playerid, PMError, "Shoma dar azmun nistid", "You are not in an exam", Tok);
				return true;
			}
		}
		case VEH_TYPE_FLYSCHOOL:{
			if(GetPState(playerid) != STATE_FLYSCHOOL_TEST){
				if(entered) EjectPlayerVehicle(playerid);
                else ClearAnimations(playerid);
				SendPM(playerid, PMError, "Shoma dar azmun nistid", "You are not in an exam", Tok);
				return true;
			}
		}	
        case VEH_TYPE_HARBORSAILTEST:{
		if(GetPState(playerid) != STATE_SAILING_TEST){
				if(entered) EjectPlayerVehicle(playerid);
                else ClearAnimations(playerid);
				SendPM(playerid, PMError, "Shoma dar azmun nistid", "You are not in an exam", Tok);
				return true;
			}
		}
	}
    return false;
}
stock CheckVehicleOwnerForEnterPlayer(playerid, vehicleid, bool:entered, Tok){
	if(GetVehicleGovType(vehicleid) != VEH_TYPE_NONE && GetVehicleGovOwner(vehicleid) != playerid){
		if(entered) EjectPlayerVehicle(playerid);
        else ClearAnimations(playerid);
		new MSGP[100], MSGE[100];
		GetNameP(GetVehicleGovOwner(vehicleid));
		format(MSGP, sizeof(MSGP), "In vasileye naghliye tavasote %s bardashte shode ast", Name);
		format(MSGE, sizeof(MSGE), "This vehicle has been taken by %s", Name);
		SendPM(playerid, PMError, MSGP, MSGE, Tok);
		return true;
	}
	return false;
}
stock CheckPlayerLicenseForEnterToVehicle(playerid, vehicleid, bool:entered, Tok){
	if(CheckAirAndHeliVeh(vehicleid)){
		new PFlyLic = GetPlayerPflylic(playerid);
		if(PFlyLic == 0 && (GetVehicleGovType(vehicleid) != VEH_TYPE_FLYSCHOOL || GetVehicleGovOwner(vehicleid) != playerid)){
			if(entered) EjectPlayerVehicle(playerid);
        	else ClearAnimations(playerid);
			SendPM(playerid, PMBlueA, "Shoma mojaveze parvaz nadarid, be fly school beravid va mojaveze parvaz begirid.", "You do not have a flying license, go to fly school and get one.", Tok);
			return true;
		}else if(PFlyLic < 0){
			if(entered) EjectPlayerVehicle(playerid);
        	else ClearAnimations(playerid);
			new MSG1[80], MSG2[70];
			format(MSG1, sizeof(MSG1), "Mojaveze parvaze shoma baraye %d saat masdud shode ast", abs(PFlyLic));
			format(MSG2, sizeof(MSG2), "Your flying license has been suspended for %d hours", abs(PFlyLic));
			SendPM(playerid, PMError, MSG1, MSG2, Tok);
			return true;
		}return false;
	}else if(CheckSailingVeh(vehicleid)){
		new PSailLic = GetPlayerPsailinglic(playerid);
		if(PSailLic == 0 && (GetVehicleGovType(vehicleid) != VEH_TYPE_HARBORSAILTEST || GetVehicleGovOwner(vehicleid) != playerid)){
			if(entered) EjectPlayerVehicle(playerid);
        	else ClearAnimations(playerid);
			SendPM(playerid, PMBlueA, "Shoma mojaveze ghayegh rani nadarid, be harbor beravid va mojaveze ghayegh rani begirid.", "You do not have a sailing license, go to harbor and get one.", Tok);
			return true;
		}else if(PSailLic < 0){
			if(entered) EjectPlayerVehicle(playerid);
        	else ClearAnimations(playerid);
			new MSG1[80], MSG2[70];
			format(MSG1, sizeof(MSG1), "Mojaveze ghayegh raniye shoma baraye %d saat masdud shode ast", abs(PSailLic));
			format(MSG2, sizeof(MSG2), "Your sailing license has been suspended for %d hours", abs(PSailLic));
			SendPM(playerid, PMError, MSG1, MSG2, Tok);
			return true;
		}
		return false;
	}
	new PDrivLic = GetPlayerPdrivlic(playerid);
	if(PDrivLic == 0 && !CheckBikeAndRcVeh(vehicleid) && (GetVehicleGovType(vehicleid) != VEH_TYPE_DMV || GetVehicleGovOwner(vehicleid) != playerid)){
		if(entered) EjectPlayerVehicle(playerid);
        else ClearAnimations(playerid);
		SendPM(playerid, PMBlueA, "Shoma govahinameye ranandegi nadarid, be DMV beravid va govahiname begirid.", "You don't have a driver's license, go to the DMV and get one.", Tok);
		return true;
	}else if(PDrivLic < 0 && !CheckBikeAndRcVeh(vehicleid)){
		if(entered) EjectPlayerVehicle(playerid);
        else ClearAnimations(playerid);
		new MSG1[80], MSG2[70];
		format(MSG1, sizeof(MSG1), "Govahinameye ranandegiye shoma baraye %d saat masdud shode ast", abs(PDrivLic));
		format(MSG2, sizeof(MSG2), "Your driving license has been suspended for %d hours", abs(PDrivLic));
		SendPM(playerid, PMError, MSG1, MSG2, Tok);
		return true;
	}
	return false;
}