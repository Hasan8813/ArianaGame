#if defined _ENTER_EXIT_SYSTEME_BY_MAMAD_PERSIAN_INC
	#endinput
#endif
#define _ENTER_EXIT_SYSTEME_BY_MAMAD_PERSIAN_INC


#define MAX_PLACES   1000

//***********Dast kari nashe*************//
#define CELL_SIZE    100.0
#define CELL_ORIGIN  10000.0
#define CELL_ALL       200
new CellHead[CELL_ALL * CELL_ALL] = {-1, ...}; 
new PlaceNextFind[MAX_PLACES], bool:PlaceActive[MAX_PLACES];
stock GridXID(Float:Val){
    new Cl = floatround((Val + CELL_ORIGIN) / CELL_SIZE, floatround_floor);
    if(Cl < 0) return 0;
    if(Cl >= CELL_ALL) return CELL_ALL - 1;
    return Cl;
}
//*******************************************************//

new Float:PlaceX[MAX_PLACES], Float:PlaceY[MAX_PLACES], Float:PlaceZ[MAX_PLACES], Float:PlaceA[MAX_PLACES];
new Float:PlaceToX[MAX_PLACES], Float:PlaceToY[MAX_PLACES], Float:PlaceToZ[MAX_PLACES], Float:PlaceToA[MAX_PLACES];
new PlaceInt[MAX_PLACES], PlaceType[MAX_PLACES], PlaceCount;
new PlayerPlace[MAX_PLAYERS] = {-1, ...};
stock FindPlaceForEnter(playerid){
    new Float:px, Float:py, Float:pz;
    GetPlayerPos(playerid, px, py, pz);
    new cx = GridXID(px), cy = GridXID(py);
    for(new gy = cy - 1; gy <= cy + 1; gy++){
        if(gy < 0 || gy >= CELL_ALL) continue;
        for(new gx = cx - 1; gx <= cx + 1; gx++){
            if(gx < 0 || gx >= CELL_ALL) continue;
            for(new id = CellHead[gy * CELL_ALL + gx]; id != -1; id = PlaceNextFind[id]){
                if(!PlaceActive[id]) continue;
                if(IsPlayerInRangeOfPoint(playerid, 2.0, PlaceX[id], PlaceY[id], PlaceZ[id])) return id;
            }
        }
    }return -1;
}
stock AddPlace(Float:x, Float:y, Float:z, Float:a, Float:tox, Float:toy, Float:toz, Float:toa, int_id, type){
    if(PlaceCount >= MAX_PLACES) return -1;
    new pid = PlaceCount++;
    PlaceX[pid] = x; PlaceY[pid] = y; PlaceZ[pid] = z; PlaceA [pid] = a;
    PlaceToX[pid] = tox; PlaceToY[pid] = toy; PlaceToZ[pid] = toz, PlaceToA[pid] = toa;
    PlaceInt[pid] = int_id;
    PlaceType[pid] = type;
    PlaceActive[pid] = true;
    new cell = GridXID(y) * CELL_ALL + GridXID(x);
    PlaceNextFind[pid] = CellHead[cell];
    CellHead[cell] = pid;
    return pid;
}

CMD:enter(playerid){
    new Tok = GetPlayerToken(playerid);
    if(PlayerPlace[playerid] != -1) return SendPM(playerid, PMError, "Shoma nazdike hich dare vorudi nistid", "You are not near any entrance valley", Tok);
    new pid = FindPlaceForEnter(playerid);
    if(pid == -1) return SendPM(playerid, PMError, "Shoma nazdike hich dare vorudi nistid", "You are not near any entrance valley", Tok);
    PlayerPlace[playerid] = pid;
    SetPlayerInterior(playerid, PlaceInt[pid]);
    SetPlayerVirtualWorld(playerid, 1000+pid);
    SetPlayerPos(playerid, PlaceToX[pid], PlaceToY[pid], PlaceToZ[pid]);
    SetPlayerFacingAngle(playerid, PlaceToA[pid]);
    SetCameraBehindPlayer(playerid);
    return 1;
}

CMD:exit(playerid){
    new Int = PlayerPlace[playerid];
    new Tok = GetPlayerToken(playerid);
    if(Int == -1) return SendPM(playerid, PMError, "Shoma be hich noghteye khoruji nazdik nistid", "You are not close to any exit point", Tok);
    if(GetPlayerVirtualWorld(playerid) != 1000+Int) return 1;
    if(!IsPlayerInRangeOfPoint(playerid, 3.0, PlaceToX[Int], PlaceToY[Int], PlaceToZ[Int])) return SendPM(playerid, PMError, "Shoma be hich noghteye khoruji nazdik nistid", "You are not close to any exit point", Tok);
    PlayerPlace[playerid] = -1;
    SetPlayerInterior(playerid, 0);
    SetPlayerVirtualWorld(playerid, 0);
    SetPlayerPos(playerid, PlaceX[Int], PlaceY[Int], PlaceZ[Int]);
    SetPlayerFacingAngle(playerid, PlaceA[Int]);
    SetCameraBehindPlayer(playerid);
    return 1;
}
CMD:create(playerid){
	AddPlace(1438.953735, -2282.733398, 13.546875, 90.0, 2233.918945, 1713.641967, 1012.194641, 0.0, 1, 0);
	AddPlace(1439.229248, -2291.389648, 13.546875, 90.0, 2017.879882, 1017.817138, 996.875000, 270.0, 10, 0);

    AddPlace(2461.323486, 1682.649658, 11.023437, 0.0, 235.254180, 1187.189086, 1080.257812, 180.0, 3, 0);
    AddPlace(2466.310791, 1682.646484, 11.023437, 0.0, 227.061462, 1114.255004, 1080.989257, 90.0, 5, 0);
    AddPlace(2471.316650, 1682.639404, 11.023437, 0.0, 223.081375, 1287.534423, 1082.140625, 180.0, 1, 0);
    AddPlace(2476.399658, 1682.675170, 11.023437, 0.0, 226.080780, 1239.959838, 1082.140625, 270, 2, 0);
    return 1;
}