#if defined _SPECIAL_BIZ_BY_MAMAD_PERSIAN_INC
	#endinput
#endif
#define _SPECIAL_BIZ_BY_MAMAD_PERSIAN_INC

#define                                 MAX_BIZ                            500
new BizID[MAX_BIZ], BizType[MAX_BIZ], BizName[MAX_BIZ][41], Text3D:BizLabel[MAX_BIZ], PlaceForThisBiz[MAX_BIZ], BizStandardPrice[MAX_BIZ], BizForSellPrice[MAX_BIZ], BizOwnerPID[MAX_BIZ], BizOwnerName[MAX_BIZ][25], BizFund[MAX_BIZ], BizReqLevel[MAX_BIZ];


//Type Enter Exit interiors
#define                 INT_TYPE_GUNSHOP                1


stock LoadAllBiz(){
    mysql_tquery(sql, "SELECT bid, x, y, z, a, tx, ty, tz, ta, intid, mapicon, type, bname, stanprice, reqlevel, owner_pid, owner_name, bizfsprice, bizfund FROM biz ORDER by bid", "LoadedAllBiz");
    return 1;
}
stock UpdateBizLabel(BID, bool:create = false){
    new StrLabel[400];
    if(BizOwnerPID[BID] == -1) format(StrLabel, sizeof(StrLabel), "Business ID %d\n{36F5A5}Business Price: {1A7936}$%d\n{36F5A5}Required Level: {F3F3F3}%d\n{36F5A5}Use the {F3F3F3}/buybiz {36F5A5}command to purchase this business\n{F3F3F3}Use /Enter to enter", BizID[BID], BizStandardPrice[BID], BizReqLevel[BID]);
    else if(BizOwnerPID[BID] >= 0 && BizForSellPrice[BID] > 0) format(StrLabel, sizeof(StrLabel), "Business ID %d\n{F3F3F3}%s\n{36F5A5}The owner of this business: {F3F3F3}%s\n{36F5A5}Business Price: {1A7936}$%d\n{36F5A5}Required Level: {F3F3F3}%d\n{36F5A5}Use the {F3F3F3}/buybiz {36F5A5}command to purchase this business\n{F3F3F3}Use /Enter to enter", BizID[BID], BizName[BID], BizOwnerName[BID], BizForSellPrice[BID], BizReqLevel[BID]);
    else format(StrLabel, sizeof(StrLabel), "Business ID %d\n{F3F3F3}%s\n{36F5A5}The owner of this business: {F3F3F3}%s\n{F3F3F3}Use /Enter to enter", BizID[BID], BizName[BID], BizOwnerName[BID]);
    if(create) BizLabel[BID] =  CreateDynamic3DTextLabel(StrLabel, 0x36F5A5FF, PlaceX[PlaceForThisBiz[BID]], PlaceY[PlaceForThisBiz[BID]], PlaceZ[PlaceForThisBiz[BID]], 8.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, true, 0, 0, -1, 150.0);
    else UpdateDynamic3DTextLabelText(BizLabel[BID], 0x36F5A5FF, StrLabel);
    return 1;
}
stock FindBizIndexID(Biz){
    for(new i; i < MAX_BIZ; i++){
        if(BizID[i] == Biz) return i;
    }return -1;
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
        cache_get_value_name_int(i, "stanprice", BizStandardPrice[i]);
        cache_get_value_name_int(i, "reqlevel", BizReqLevel[i]);
        cache_get_value_name_int(i, "owner_pid", BizOwnerPID[i]);
        cache_get_value_name(i, "owner_name", BizOwnerName[i]);
        cache_get_value_name_int(i, "bizfsprice", BizForSellPrice[i]);
        cache_get_value_name_int(i, "bizfund", BizFund[i]);
        if(mapicon > 0) CreateDynamicMapIcon(x, y, z, mapicon, 0, 0, 0, -1, 2000.0);
        CreateDynamicPickup(1239, 1, x, y, z, 0, 0, -1, 150.0);
        PlaceForThisBiz[i] = AddPlace(x, y, z, a, tx, ty, tz, ta, intid, BizType[i], BizID[i]);
        UpdateBizLabel(i, true);
    }return 1;
}
stock SetBizName(Biz, const NameB[]){
    format(BizName[Biz], sizeof(BizName[Biz]), "%s", NameB);
    UpdateBizLabel(Biz);
    return 1;
}
stock SetBizStandardPrice(Biz, Price){
    BizStandardPrice[Biz] = Price;
    UpdateBizLabel(Biz);
    return 1;
}
stock SendPmBizNotExist(playerid, Tok) return SendPM(playerid, PMError, "Shoma nazdike hich Businessi nistid", "You are not near any business", Tok);
CMD:bizstatus(playerid){
    new Tok = GetPlayerToken(playerid);
    new bid = FindPlaceForEnter(playerid);
    if(bid == -1 || BizForThisPlace[bid] == -1 ) return SendPmBizNotExist(playerid, Tok);
    new BI = FindBizIndexID(BizForThisPlace[bid]);
    if(BI == -1) return SendPmBizNotExist(playerid, Tok);
    new MSG1[100], FundsStr[16], ValueStr[16];
    FormatNumber(BizFund[BI], FundsStr);
    format(MSG1, sizeof(MSG1), "Business Name: %s", BizName[BI]);
    SendLongMessage(playerid, -1, MSG1, Tok);
    FormatNumber(BizStandardPrice[BI], ValueStr);
    format(MSG1, sizeof(MSG1), "Fund: {1A7936}$%s {FFFFFF}| Value: {1A7936}$%s", FundsStr, ValueStr);
    SendLongMessage(playerid, -1, MSG1, Tok);
    return 1;
}
CMD:buybiz(playerid){
    new Tok = GetPlayerToken(playerid);
    new bid = FindPlaceForEnter(playerid);
    if(bid == -1 || BizForThisPlace[bid] == -1) return SendPmBizNotExist(playerid, Tok);
    new BI = FindBizIndexID(BizForThisPlace[bid]);
    if(BI == -1) return SendPmBizNotExist(playerid, Tok);
    if(BizOwnerPID[BI] >= 0 && BizForSellPrice[BI] > 0){
        CheckPlayerMoneyForBuyAndSendError(playerid, BizForSellPrice[BI], Tok);
        GiveMoney(playerid, 1, -BizForSellPrice[BI], Tok);
        new Res[50];
        format(Res, sizeof(Res), "Buybiz ID %d", BizID[BI]);
        MoneyLog(-BizForSellPrice[BI], playerid, -1, -1, Res, "/Buybiz");
    }else if(BizOwnerPID[BI] == -1){
        CheckPlayerMoneyForBuyAndSendError(playerid, BizStandardPrice[BI], Tok);
        GiveMoney(playerid, 1, -BizStandardPrice[BI], Tok);
        new Res[50];
        format(Res, sizeof(Res), "Buybiz ID %d", BizID[BI]);
        MoneyLog(-BizStandardPrice[BI], playerid, -1, -1, Res, "/Buybiz");
        new query[100];
        GetNameP(playerid);
        mysql_format(sql, query, sizeof(query), "UPDATE biz SET owner_pid = %d, owner_name = '%e' WHERE bid = %d", GetPlayerPID(playerid), Name, BizID[BI]);
        mysql_pquery(sql, query, "BizBuyed", "idd", playerid, BI, Tok);
    }else SendPM(playerid, PMError, "In Business forushi nist", "This business is not for sale", Tok);
    return 1;
}
CMD:bizinfo(playerid){
    new bid = FindPlaceForEnter(playerid);
    if(bid == -1) return SendClientMessage(playerid, -1, "Nazdik hichi nistiiii");
    if(BizForThisPlace[bid] == -1) return SendClientMessage(playerid, -1, "Nazdik hichi bizi nisti");
    new BI = FindBizIndexID(BizForThisPlace[bid]);
    if(BI == -1) return SendClientMessage(playerid, -1, "Nazdik hichi bizi nisti");
    SendClientMessage(playerid, -1, "Id in biz: %d", BizForThisPlace[bid]);
    SetBizStandardPrice(BI, 88888888);
    return 1;
}