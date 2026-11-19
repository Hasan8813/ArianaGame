//                              Be name khoda                               //
#if defined _ANTO_FLOOD_COMMAND_BY_MAMAD_PERSIAN_INC
	#endinput
#endif
#define _ANTO_FLOOD_COMMAND_BY_MAMAD_PERSIAN_INC

//1. Baraye estefade avval yek define ba esme cmd yani #define CMDTIME_inja emse cmd va dakhele "esme daghighe cmd baraye zakhireye pvar" misazi mesal: (#define CMDTIME_TEST "Test")
//2. Sepas miyay dakhele stock SetTimerCommand age niyaz bud bazikon vaghti varede server shod timer cmd shoru beshe pvar bazikon ru zet midi be GetTockCount yani intori mesal: SetPVarInt(playerid, CMDTIME_TEST, GetTickCount()); intori misazi esme pvar mishe hamun define ke sakhtim mesle bala
//3. Badesh miyay tu commandi ke mikhay bezari be in shekl check mizarim if(CheckCommandFloodTime(playerid, CMDTIME_TEST, 180000, GetPlayerToken(playerid))) return 1; parametrr 2 ke hamun define ke sakhtim va patametre 3 time hast ke bazikon bayad sabr kone vase estefade
//Nokte baraye har cmd define va tu settimercommand sakhte beshe magar inke 2 3 ta cmd bekhay 1 timer bezari ke agar yekishun ro zad chand daghighe hame cmd haro dige nemitune estfade kone ta timersh tamum beshe
#define 								SetCommandAntiFloodTime(%0,%1,%2) if(CheckCommandFloodTime(%0,%1,%2,GetPlayerToken(%0)))

stock SetTimerCommand(playerid){
    return 1;
}stock bool:CheckCommandFloodTime(playerid, const cmdID[], waitms, Token){
	CheckPlayerOnline(playerid) return true;
	CheckPlayerLogin(playerid) return true;
	CheckPlayerToken(playerid, Token) return true;
    new Timesss = waitms - (GetTickCount() - GetPVarInt(playerid, cmdID));
    if(Timesss > 0){
        new MSG[100], MSG1[100];
        new TimerA = Timesss / 1000;
    	new TimerH = TimerA / 3600;
    	new TimerM = (TimerA % 3600) / 60;
    	new TimerSec = TimerA % 60;
		if(TimerH >= 1){
			format(MSG, sizeof(MSG), "Shoma mitavanid pas az gozashte %02d:%02d:%02d saat az in dastur estefade konid", TimerH, TimerM, TimerSec);
			format(MSG1, sizeof(MSG1), "You can use this command after %02d:%02d:%02d hours have passed", TimerH, TimerM, TimerSec);
		}else{
			if(TimerM >= 1){
				format(MSG, sizeof(MSG), "Shoma mitavanid pas az gozashte %d daghighe va %d saniye az in dastur estfde konid", TimerM, TimerSec);
				format(MSG1, sizeof(MSG1), "You can use this command after %d minutes and %d seconds have passed", TimerM, TimerSec);
			}else{
				format(MSG, sizeof(MSG), "Shoma pas az gozashte %d saniye mitavanid az in dastur estefde konid", TimerSec);
				format(MSG1, sizeof(MSG1), "You can use this command after %d seconds have passed", TimerSec);
			}
		}SendPM(playerid, PMError, MSG, MSG1, Token);
        return true;
    }SetPVarInt(playerid, cmdID, GetTickCount());
    return false;
}