//                              Be Name khoda                               //
#if defined _CREATE_GOVERMENT_VEHICLE_BY_MAMAD_PERSIAN_INC
	#endinput
#endif
#define _CREATE_GOVERMENT_VEHICLE_BY_MAMAD_PERSIAN_INC



new PlayerGovVeh[MAX_PLAYERS];
#define SetPlayerVehicleGov(%0,%1) PlayerGovVeh[%0] = %1
#define GetPlayerVehicleGov(%0) PlayerGovVeh[%0]

new VehGovType[MAX_VEHICLES];
#define SetVehicleGovType(%0,%1) VehGovType[%0] = %1
#define GetVehicleGovType(%0) VehGovType[%0]

new VehGovOwner[MAX_VEHICLES] = {INVALID_PLAYER_ID, ...};
#define SetVehicleGovOwner(%0,%1) VehGovOwner[%0] = %1
#define GetVehicleGovOwner(%0) VehGovOwner[%0]

#define CheckPlayerCreatedVehicleGov(%0) if(GetPlayerVehicleGov(%0) != 0) return SendPM(%0, PMError, "Shoma az ghabl yek vasileye naghliye bardashte'id, ba /deleteveh mitavanid an ra hazf konid", "You have already taken a vehicle, you can remove it using /deleteveh", GetPlayerToken(%0))


//Vehicle type
#define                                 VEH_TYPE_NONE                               0
#define 								VEH_TYPE_DMV                               1
#define 								VEH_TYPE_FLYSCHOOL                               2
#define 								VEH_TYPE_HARBORSAILTEST                               3


stock DestroyVehicleGov(playerid){
    if(playerid == INVALID_PLAYER_ID) return false;
    new V = GetPlayerVehicleGov(playerid);
    if(V == 0) return false;
    SetPlayerVehicleGov(playerid, 0);
    if(GetVehicleGovType(V) == VEH_TYPE_NONE || GetVehicleGovOwner(V) != playerid) return false;
    if(IsValidVehicle(V)) DestroyVehicle(V);
    SetVehicleGovType(V, VEH_TYPE_NONE);
    SetVehicleGovOwner(V, INVALID_PLAYER_ID);
    return true;
}
stock CreateVehicleGov(playerid, Type, Model, Float:X, Float:Y, Float:Z, Float:Angle, CL1, CL2, bool:Siren){
    DestroyVehicleGov(playerid);
    new V = CreateVehicle(Model, X, Y, Z, Angle, CL1, CL2, DESTROY_VEHICLE_TIME, Siren);
    if(V == INVALID_VEHICLE_ID) return INVALID_VEHICLE_ID;
    SetVehicleGovType(V, Type);
    SetVehicleGovOwner(V, playerid);
    SetPlayerVehicleGov(playerid, V);
    return V;
}
CMD:deleteveh(playerid){
    new Tok = GetPlayerToken(playerid);
    new VehId = GetPlayerVehicleGov(playerid);
    if(VehId == 0) return SendPM(playerid, PMError, "Shoma vasileye naghliye'i barnadashte'id", "You did not pick up a vehicle", Tok);
    if(!DestroyVehicleGov(playerid)) return 1;
    SendPM(playerid, PMWhite, "Vasileye naghliyeye shoma hazf shod.", "Your vehicle has been removed.", Tok);
    return 1;
}