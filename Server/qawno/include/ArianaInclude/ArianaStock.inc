// 								Be name Khoda 								//
// 								Hameye stock haye estefade shode dar Ariana Game 								//
#if defined _STOCK_BY_MAMAD_PERSIAN_INC
	#endinput
#endif
#define _STOCK_BY_MAMAD_PERSIAN_INC
// 								Variables 								//

// 								Stocks 								//
//Nahveye estefade: new Float:Distance = GetDistanceVasat(OX, OY, OZ, PX, PY, PZ);
//3 taye avval float 1 va e taue dovvom float 2 ke faselasho besanje
stock Float:GetDistanceVasat(Float:x1, Float:y1, Float:z1, Float:x2, Float:y2, Float:z2) return floatsqroot((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1) + (z2 - z1)*(z2 - z1));
//Gereftane time baghi mundeye yek timer ta ejraye on  a timer id
stock GetTimer(TimerID, dest[], len = sizeof dest){
    new TimerS = GetTimerRemaining(TimerID);
    if(TimerS <= 0) return format(dest, len, "00:00"), 0;
    new TimerA = TimerS / 1000;
    new TimerH = TimerA / 3600;
    new TimerM = (TimerA % 3600) / 60;
    new TimerSec = TimerA % 60;
    if(TimerH < 1) format(dest, len, "%02d:%02d", TimerM, TimerSec);
    else format(dest, len, "%02d:%02d:%02d", TimerH, TimerM, TimerSec);
    return TimerS;
}
//CCP Clear chat player
stock CCP(playerid, tedadspam){
	for(new a=0;a<tedadspam;a++){
		if(!IsPlayerConnected(playerid)) return 0;
		SendClientMessage(playerid, -1, "        ");
	}return 1;
}
//Check kardane dorost budane email
stock IsValidEmail(const email[]){
    if(strlen(email) < 8) return 0;
    new at_pos = strfind(email, "@");
    if(at_pos == -1) return 0;
    if(at_pos == 0) return 0;
    if(at_pos == strlen(email)-1) return 0;
    new dot_pos = strfind(email, ".", false, at_pos + 1);
    if(dot_pos == -1) return 0;
    if(dot_pos - at_pos < 2) return 0;
    if(strlen(email) - dot_pos < 3) return 0;
    return 1;
}
//Ersal payam agar toolani bashe tabdil be chand khat mishe
stock SendLongMessage(playerid, color, const message[], Token){
    CheckPlayerOnlineToCMD(playerid);
    CheckPlayerTokenCmp(playerid, Token);
    new msg[144];
    new pos = 0;
    new len = strlen(message);
    new chunkSize = 100;
    while(pos < len){
        new remaining = len - pos;
        new copyLen;
        new isLast;
        if(remaining <= chunkSize){
            copyLen = remaining;
            isLast = 1;
        }else{
            copyLen = chunkSize;
            isLast = 0;
            new cutPos = copyLen;
            while(cutPos > 0 && message[pos + cutPos] != ' ') cutPos--;
            if(cutPos > 0) copyLen = cutPos;
        }strmid(msg, message, pos, pos + copyLen);
        msg[copyLen] = '\0';
        if(!isLast) strcat(msg, "...");
        SendClientMessage(playerid, color, msg);
        pos += copyLen;
        if(pos < len && message[pos] == ' ') pos++;
    }return 1;
}
//Payam ha
#define RangPMKahroba "{FFBF00}"
#define RangPMError "{FF8700}"
#define RangPMRed "{B63838}"
#define RangPMBlueA "{70D8F8}"
#define PMWhite 0
#define PMKahrobA 1
#define PMError 2
#define PMRed 3
#define PMBlueA 4
stock SendPM(playerid, pmid, const PersianPM[], const EnglishPM[], Token){
    CheckPlayerOnlineToCMD(playerid);
    CheckPlayerTokenCmp(playerid, Token);
    new MSG[200];
    //Persian
    if(GetPlayerPlanguage(playerid) == 1){
        switch(pmid){
            case 0: SendLongMessage(playerid, -1, PersianPM, Token);
            case 1: SendLongMessage(playerid, 0xFFBF00FF, PersianPM, Token);
            case 2:{
                format(MSG, sizeof(MSG), "Khata: %s.", PersianPM);
                SendLongMessage(playerid, 0xFF8700FF, MSG, Token);
                PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
            }case 3: SendLongMessage(playerid, 0xB63838FF, PersianPM, Token);
            case 4: SendLongMessage(playerid, 0x70D8F8FF, PersianPM, Token);
        }return 1;
    }
    //English
    if(GetPlayerPlanguage(playerid) == 2){
        switch(pmid){
            case 0: SendLongMessage(playerid, -1, EnglishPM, Token);
            case 1: SendLongMessage(playerid, 0xFFBF00FF, EnglishPM, Token);
            case 2:{
                format(MSG, sizeof(MSG), "Error: %s.", EnglishPM);
                SendLongMessage(playerid, 0xFF8700FF, MSG, Token);
                PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
            }case 3: SendLongMessage(playerid, 0xB63838FF, EnglishPM, Token);
            case 4: SendLongMessage(playerid, 0x70D8F8FF, EnglishPM, Token);
        }
    }return 1;
}
stock SendSyntaxCommand(playerid, const Syntax[], Token){
    CheckPlayerOnlineToCMD(playerid);
    CheckPlayerTokenCmp(playerid, Token);
    new PMM[200];
    format(PMM, sizeof(PMM), "Syntax: %s", Syntax);
    SendLongMessage(playerid, 0xA5C9D3FF, PMM, Token);
    PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
    return 1;
}
//Kick bazikon ba payam
stock Skick(playerid, const MessageForPersian[], const MessageForEnglish[], Token, bool:SendMessage = false){
    CheckPlayerOnlineToCMD(playerid);
    CheckPlayerTokenCmp(playerid, Token);
    if(SendMessage == false) return Kick(playerid);
    else if(SendMessage == true){
        SendPM(playerid, PMRed, MessageForPersian, MessageForEnglish, Token);
        SetTimerEx("KPM", 400, false, "id", playerid, Token);
    }return 1;
}
forward KPM(playerid, token);
public KPM(playerid, token){
    CheckPlayerOnlineToCMD(playerid);
    CheckPlayerTokenCmp(playerid, token);
    Kick(playerid);
    return 1;
}
//Checke ertefa'e bazikon baraye vaghtayi ke mikhay check koni tu abe ya na
stock IsPlayerWater(playerid){
    new Float:XXW, Float:YYW, Float:ZZW;
    GetPlayerPos(playerid, XXW, YYW, ZZW);
    if(ZZW < 2.5) return 1;
    return 0;
}stock GetPlayerColorNameHex(playerid){
    new rang = GetPlayerColor(playerid);
	rang = (rang & 0xFFFFFF00) | 0xFF;
    return rang;
}stock GetPlayerColorNameMSG(playerid, dest[], len = sizeof(dest)){
    new rang = GetPlayerColor(playerid);
    rang = (rang >>> 8) & 0xFFFFFF;
    format(dest, len, "{%06x}", rang);
    return 1;
}

//in adade - ro tabdil be + mikone masalan ahe adad -8 hast tabdil mishe be 8
stock abs(value) return (value < 0) ? -value : value;

//Checke inke savare havapeyma hast ya na
stock CheckAirAndHeliVeh(vehid){
    new m = GetVehicleModel(vehid);
    if(m == 417 || m == 425 || m == 447 || m == 460 || m == 464 || m == 465 || m == 469 || m == 476 || m == 487 || m == 488 || m == 497 || m == 501 || (m >= 511 && m <= 513) || m == 519 || m == 520 || m == 548 || m == 553 || m == 563 || m == 577 || m == 592 || m == 593) return true;
    return false;
}
stock CheckSailingVeh(vehid){
    new s = GetVehicleModel(vehid);
    if(s == 430 || s == 446 || (s >= 452 && s <= 454) || s == 472 || s == 473 || s == 484 || s == 493 || s == 595) return true;
    return false;
}
stock CheckBikeAndRcVeh(vehid){
    new br = GetVehicleModel(vehid);
    if(br == 481 || br == 509 || br == 510 || br == 441 || br == 564 || br == 594) return true;
    return false;
}
stock FormatNumber(number, dest[], len = sizeof(dest)){
    new src[16], out[24], pos;
    format(src, sizeof(src), "%d", number);
    new neg = (src[0] == '-') ? 1 : 0;
    new digits = strlen(src) - neg;
    if(neg) out[pos++] = '-';
    for(new i = 0; i < digits; i++){
        if(i > 0 && (digits - i) % 3 == 0) out[pos++] = ',';
        out[pos++] = src[neg + i];
    }out[pos] = '\0';
    format(dest, len, "%s", out);
    return pos;
}
