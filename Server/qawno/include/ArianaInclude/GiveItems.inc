#if defined _GIVEITEMS_BY_MAMAD_PERSIAN_INC
	#endinput
#endif
#define _GIVEITEMS_BY_MAMAD_PERSIAN_INC

//dadane gold
forward GiveGold(playerid, GiveSet1or2, amount, token);
public GiveGold(playerid, GiveSet1or2, amount, token){
    CheckPlayerOnlineAndLogin(playerid);
    CheckPlayerTokenCmp(playerid, token);
    new MSG[58], MSG1[158], MSG2[158];
    if(GiveSet1or2 == 2){
        SetPlayerPgold(playerid, amount);
        format(MSG1, sizeof(MSG1), "{EECD0F}Meghdar golde shoma be {FFFFFF}%d {EECD0F}taghir yaft.", amount);
        format(MSG2, sizeof(MSG2), "{EECD0F}Your gold amount has changed to {FFFFFF}%d {EECD0F}.", amount);
        format(MSG, sizeof(MSG), "~h~%d GOLD", amount);
    }else if(GiveSet1or2 == 1){
        SetPlayerPgold(playerid, GetPlayerPgold(playerid) + amount);
        if(amount >= 0){
            format(MSG1, sizeof(MSG1), "{EECD0F}Shoma {FFFFFF}%d {EECD0F}gold daryaft kardid.", amount);
            format(MSG2, sizeof(MSG2), "{EECD0F}You received {FFFFFF}%d {EECD0F}gold.", amount);
            format(MSG, sizeof(MSG), "~h~+%d GOLD", amount);
        }else if(amount < 0){
            format(MSG1, sizeof(MSG1), "%d {FF0000}gold az hesabe shoma kam shod.", abs(amount));
            format(MSG2, sizeof(MSG2), "%d {FF0000}gold has been deducted from your account.", abs(amount));
            format(MSG, sizeof(MSG), "~r~%d GOLD", amount);
        }
    }else return 1;
    FlagUpdate(playerid);
    GameTextForPlayer(playerid, MSG, 1000, 1);
    SendPM(playerid, PMWhite, MSG1, MSG2, token);
    PlayerPlaySound(playerid, 1137, 0.0, 0.0, 0.0);
    UpdateGoldTD(playerid, token);
    return 1;
}
//Dadane money
forward GiveMoney(playerid, GiveSet1or2, amount, token);
public GiveMoney(playerid, GiveSet1or2, amount, token){
    CheckPlayerOnlineAndLogin(playerid);
    CheckPlayerTokenCmp(playerid, token);
    new MSG[58], MSG1[158], MSG2[158];
    if(GiveSet1or2 == 2){
        SetPlayerPmoney(playerid, amount);
        if(amount >= 0){
            format(MSG1, sizeof(MSG1), "{1A7936}Dollare shoma be $%d taghir yaft.", amount);
            format(MSG2, sizeof(MSG2), "{1A7936}Your dollar amount has changed to $%d .", amount);
            format(MSG, sizeof(MSG), "~g~$%d", amount);
        }else if(amount < 0){
            format(MSG1, sizeof(MSG1), "{FF0000}Dollare shoma be $%d taghir yaft.", amount);
            format(MSG2, sizeof(MSG2), "{FF0000}Your dollar amount has changed to $%d.", amount);
            format(MSG, sizeof(MSG), "~r~$%d", amount);
        }
    }else if(GiveSet1or2 == 1){
        SetPlayerPmoney(playerid, GetPlayerPmoney(playerid) + amount);
        if(amount >= 0){
            format(MSG1, sizeof(MSG1), "{1A7936}Shoma $%d dollar daryaft kardid.", amount);
            format(MSG2, sizeof(MSG2), "{1A7936}You received $%d dollar.", amount);
            format(MSG, sizeof(MSG), "~g~+$%d", amount);
        }else if(amount < 0){
            format(MSG1, sizeof(MSG1), "{FF0000}$%d dollar az hesabe shoma kam shod.", abs(amount));
            format(MSG2, sizeof(MSG2), "{FF0000}$%d dollar was deducted from your account.", abs(amount));
            format(MSG, sizeof(MSG), "~r~$%d", amount);
        }
    }else return 1;
    FlagUpdate(playerid);
    SendPM(playerid, PMWhite, MSG1, MSG2, token);
    GameTextForPlayer(playerid, MSG, 1000, 1);
    PlayerPlaySound(playerid, 1150, 0.0, 0.0, 0.0);
    ResetPlayerMoney(playerid);
    GivePlayerMoney(playerid, GetPlayerPmoney(playerid));
    return 1;
}