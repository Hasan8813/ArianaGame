#if defined _ENTER_EXIT_SYSTEME_BY_MAMAD_PERSIAN_INC
	#endinput
#endif
#define _ENTER_EXIT_SYSTEME_BY_MAMAD_PERSIAN_INC


#define MAX_PLACES   1000

//***********Dast kari nashe*************//
#define GRID_SIZE    100.0
#define GRID_ORIGIN  10000.0
#define GRID_W       200
new CellHead[GRID_W * GRID_W] = {-1, ...}; 
new PlaceNext[MAX_PLACES], bool:PlaceActive[MAX_PLACES];
stock GridIdx(Float:v){
    new c = floatround((v + GRID_ORIGIN) / GRID_SIZE, floatround_floor);
    if(c < 0) return 0;
    if(c >= GRID_W) return GRID_W - 1;
    return c;
}
//*******************************************************//

new Float:PlaceX[MAX_PLACES], Float:PlaceY[MAX_PLACES], Float:PlaceZ[MAX_PLACES];
new Float:PlaceToX[MAX_PLACES], Float:PlaceToY[MAX_PLACES], Float:PlaceToZ[MAX_PLACES];
new PlaceInt[MAX_PLACES], PlaceCount;
new PlayerPlace[MAX_PLAYERS] = {-1, ...};
stock AddPlace(Float:x, Float:y, Float:z, Float:tox, Float:toy, Float:toz, int_id){
    if(PlaceCount >= MAX_PLACES) return -1;
    new id = PlaceCount++;
    PlaceX[id] = x; PlaceY[id] = y; PlaceZ[id] = z;
    PlaceToX[id] = tox; PlaceToY[id] = toy; PlaceToZ[id] = toz;
    PlaceInt[id] = int_id;
    PlaceActive[id] = true;
    new cell = GridIdx(y) * GRID_W + GridIdx(x);
    PlaceNext[id] = CellHead[cell];
    CellHead[cell] = id;
    return id;
}
stock FindPlaceForEnter(playerid){
    new Float:px, Float:py, Float:pz;
    GetPlayerPos(playerid, px, py, pz);
    new cx = GridIdx(px), cy = GridIdx(py);
    for(new gy = cy - 1; gy <= cy + 1; gy++){
        if(gy < 0 || gy >= GRID_W) continue;
        for(new gx = cx - 1; gx <= cx + 1; gx++){
            if(gx < 0 || gx >= GRID_W) continue;
            for(new id = CellHead[gy * GRID_W + gx]; id != -1; id = PlaceNext[id]){
                if(!PlaceActive[id]) continue;
                if(IsPlayerInRangeOfPoint(playerid, 2.5, PlaceX[id], PlaceY[id], PlaceZ[id])) return id;
            }
        }
    }
    return -1;
}
CMD:enter(playerid){
    if(PlayerPlace[playerid] != -1) return 1;
    new pid = FindPlaceForEnter(playerid);
    if(pid == -1) return 1;
    PlayerPlace[playerid] = pid;
    SetPlayerInterior(playerid, PlaceInt[pid]);
    SetPlayerVirtualWorld(playerid, 1000+pid);
    SetPlayerPos(playerid, PlaceToX[pid], PlaceToY[pid], PlaceToZ[pid]);
    return 1;
}

CMD:exit(playerid){
    new Int = PlayerPlace[playerid];
    if(Int == -1) return 1;
    if(!IsPlayerInRangeOfPoint(playerid, 3.0, PlaceToX[Int], PlaceToY[Int], PlaceToZ[Int])) return 1;
    PlayerPlace[playerid] = -1;
    SetPlayerInterior(playerid, 0);
    SetPlayerVirtualWorld(playerid, 0);
    SetPlayerPos(playerid, PlaceX[Int], PlaceY[Int], PlaceZ[Int]);
    return 1;
}
CMD:create(playerid){
	AddPlace(1438.953735, -2282.733398, 13.546875, 2233.918945, 1713.641967, 1012.194641, 1);
	AddPlace(1439.229248, -2291.389648, 13.546875, 2017.879882, 1017.817138, 996.875000, 10);
    return 1;
}