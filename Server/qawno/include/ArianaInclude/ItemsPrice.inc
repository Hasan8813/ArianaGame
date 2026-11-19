//                              Be name khoda                               //
#if defined _ITEMSPRICE_BY_MAMAD_PERSIAN_INC
	#endinput
#endif
#define _ITEMSPRICE_BY_MAMAD_PERSIAN_INC

/*
new Float:GoldPriceOunce = 0.0;
new Float:GoldPriceGram = 0.0;
new GoldPriceLastUpdate = 0;
new bool:GoldPriceReady = false;
#define GOLD_PRICE_API_URL  "https://api.goldprice.dev/v1/prices?symbol=XAU-USD-SPOT"
#define GOLD_OUNCE_TO_GRAM  31.1034768
#define GOLD_UPDATE_INTERVAL 600000

stock StartRefreshGoldPrice(){
	FetchGoldPrice();
    SetTimer("FetchGoldPrice", GOLD_UPDATE_INTERVAL, true);
    return 1;
}forward FetchGoldPrice();
public FetchGoldPrice(){
    HTTP(0, HTTP_GET, GOLD_PRICE_API_URL, "", "OnGoldPriceReceived");
    return 1;
}forward OnGoldPriceReceived(index, response_code, data[]);
public OnGoldPriceReceived(index, response_code, data[]){
    if(response_code != 200) return ErrorLog("Error 200 update price gold");
    new pos = strfind(data, "\"price\":\"");
    if(pos == -1) return ErrorLog("Peyda nakardane price gold ba strfind");
    pos += 9;
    new endPos = pos;
    while(data[endPos] != '"' && data[endPos] != '\0') endPos++;
    new priceStr[16];
    strmid(priceStr, data, pos, endPos);
    GoldPriceOunce = floatstr(priceStr);
    GoldPriceGram = GoldPriceOunce / GOLD_OUNCE_TO_GRAM;
    GoldPriceLastUpdate = gettime();
    GoldPriceReady = true;
    return 1;
}
    //Gereftane gheymat ha be in shekle
    new secondsAgo = gettime() - GoldPriceLastUpdate;
    new msg[256];
    format(msg, sizeof(msg), "{FFFF00}Gheymate lahzeyiye gold; Onse: {FF0000}%d dollar, {FFFF00} Gram: {FF0000}%d, {00FF00}Akharin berooz resaniye gheymat: %d saniye pish.", floatround(GoldPriceOunce, floatround_floor), floatround(GoldPriceGram, floatround_floor), secondsAgo);
    SendClientMessage(playerid, -1, msg);
*/