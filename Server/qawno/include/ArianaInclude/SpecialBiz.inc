#if defined _SPECIAL_BIZ_BY_MAMAD_PERSIAN_INC
	#endinput
#endif
#define _SPECIAL_BIZ_BY_MAMAD_PERSIAN_INC

#define                                 MAX_BIZ                            500
new BizCount;


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
        if(BizCount >= MAX_BIZ){print("[Warning]: Biz haye sakhte shode bishtar az meghdare ta'rif shode hastand!"); break;}
        new bid, Float:x, Float:y, Float:z, Float:a, Float:tx, Float:ty, Float:tz, Float:ta, intid, mapicon, type, NameeB[41];
        cache_get_value_name_int(i, "bid", bid);
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
        cache_get_value_name_int(i, "type", type);
        cache_get_value_name(i, "bname", NameeB, sizeof(NameeB));
        Create3DTextLabel("Business ID %d\n{F3F3F3}%s\n{36F5A5}The owner of this business: {F3F3F3}None\nUse /Enter to enter", 0x36F5A5FF, x, y, z, 8.0, 0, true, i, NameeB);
        if(mapicon > 0) CreateDynamicMapIcon(x, y, z, mapicon, 0, 0, 0, -1, 2000.0);
        CreateDynamicPickup(1239, 1, x, y, z, 0, 0, -1, 150.0);
        AddPlace(x, y, z, a, tx, ty, tz, ta, intid, type);
    }return 1;
}