#if defined _SPECIAL_BIZ_BY_MAMAD_PERSIAN_INC
	#endinput
#endif
#define _SPECIAL_BIZ_BY_MAMAD_PERSIAN_INC

#define                                 MAX_BIZ                            500
new BizID[MAX_BIZ], BizType[MAX_BIZ], BizName[MAX_BIZ][41], Text3D:BizLabel[MAX_BIZ], PlaceForThisBiz[MAX_BIZ];


//Type Enter Exit interiors
#define                 INT_TYPE_GUNSHOP                1


stock LoadAllBiz(){
    mysql_tquery(sql, "SELECT bid, x, y, z, a, tx, ty, tz, ta, intid, mapicon, type, bname FROM biz ORDER by bid", "LoadedAllBiz");
    return 1;
}
forward LoadedAllBiz();
public LoadedAllBiz(){
    new rows = cache_num_rows();
    for(new i; i < rows; i++){
        new Float:x, Float:y, Float:z, Float:a, Float:tx, Float:ty, Float:tz, Float:ta, intid, mapicon;
        cache_get_value_name_int(i, "bid", BizID[i]);
        cache_get_value_name_float(i, "x", x);
        cache_get_value_name_float(i, "y", y);
        cache_get_value_name_float(i, "z", z);
        cache_get_value_name_float(i, "a", a);
        cache_get_value_name_float(i, "tx", tx);
        cache_get_value_name_float(i, "ty", ty);
        cache_get_value_name_float(i, "tz", tz);
        cache_get_value_name_float(i, "ta", ta);
        cache_get_value_name_int(i, "intid", intid);
        cache_get_value_name_int(i, "mapicon", mapicon);
        cache_get_value_name_int(i, "type", BizType[i]);
        cache_get_value_name(i, "bname", BizName[i]);
        new StrLabel[200];
        format(StrLabel, sizeof(StrLabel), "Business ID %d\n{F3F3F3}%s\n{36F5A5}The owner of this business: {F3F3F3}None\nUse /Enter to enter", i, BizName[i]);
        BizLabel[i] =  CreateDynamic3DTextLabel(StrLabel, 0x36F5A5FF, x, y, z, 8.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, true, 0, 0, -1, 150.0);
        if(mapicon > 0) CreateDynamicMapIcon(x, y, z, mapicon, 0, 0, 0, -1, 2000.0);
        CreateDynamicPickup(1239, 1, x, y, z, 0, 0, -1, 150.0);
        PlaceForThisBiz[i] = AddPlace(x, y, z, a, tx, ty, tz, ta, intid, BizType[i], i);
    }return 1;
}
stock UpdateBizLabel(BID){
    new StrLabel[200];
    format(StrLabel, sizeof(StrLabel), "Business ID %d\n{F3F3F3}%s\n{36F5A5}The owner of this business: {F3F3F3}None\nUse /Enter to enter", BID, BizName[BID]);
    UpdateDynamic3DTextLabelText(BizLabel[BID], 0x36F5A5FF, StrLabel);
    return 1;
}
CMD:bizinfo(playerid){
    new bid = FindPlaceForEnter(playerid);
    if(bid == -1) return SendClientMessage(playerid, -1, "Nazdik hichi nistiiii");
    if(BizForThisPlace[bid] == -1) return SendClientMessage(playerid, -1, "Nazdik hichi bizi nisti");
    SendClientMessage(playerid, -1, "Id in biz: %d", BizForThisPlace[bid]);
    return 1;
}