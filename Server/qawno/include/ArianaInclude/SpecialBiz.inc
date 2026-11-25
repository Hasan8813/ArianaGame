#if defined _SPECIAL_BIZ_BY_MAMAD_PERSIAN_INC
	#endinput
#endif
#define _SPECIAL_BIZ_BY_MAMAD_PERSIAN_INC

#define                                 MAX_BIZ                            500
new BizCount;

stock LoadAllBiz(){
    mysql_tquery(sql, "SELECT bid, x, y, z, a, tx, ty, tz, ta, intid, type FROM biz ORDER by bid", "LoadedAllBiz");
    return 1;
}
forward LoadedAllBiz();
public LoadedAllBiz(){
    new rows = cache_num_rows();
    for(new i; i < rows; i++){
        if(BizCount >= MAX_BIZ){print("[Warning]: Biz haye sakhte shode bishtar az meghdare ta'rif shode hastand!"); break;}
        new bid, Float:x, Float:y, Float:z, Float:a, Float:tx, Float:ty, Float:tz, Float:ta, intid, type;
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
        cache_get_value_name_int(i, "type", type);
        AddPlace(x, y, z, a, tx, ty, tz, ta, intid, type);
        printf("Biz id: %d loaded", i);
    }return 1;
}