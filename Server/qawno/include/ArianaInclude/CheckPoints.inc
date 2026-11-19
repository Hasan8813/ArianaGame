#if defined _CHECKPOINTS_BY_MAMAD_PERSIAN_INC
	#endinput
#endif
#define _CHECKPOINTS_BY_MAMAD_PERSIAN_INC


#define 								SetPlayerCheckPointID(%0,%1) PlayerCheckPoint[%0] = %1, PlayerActiveCheckPoint[%0] = true
#define 								GetPlayerChechPointID(%0) PlayerCheckPoint[%0]
#define 								ResetPlayerCheckPointID(%0) PlayerCheckPoint[%0] = 0, PlayerActiveCheckPoint[%0] = false
#define 								CancelPlayerCheckPoint(%0) DisablePlayerCheckpoint(%0), ResetPlayerCheckPointID(%0)
#define 								CancelPlayerRaceCheckPoint(%0) DisablePlayerRaceCheckpoint(%0), ResetPlayerCheckPointID(%0)
#define 								GetPlayerCheckPointActive(%0) PlayerActiveCheckPoint[%0]
#define 								CheckPlayerCheckPointActiveAndError(%0) if(PlayerActiveCheckPoint[%0]) return SendPM(%0, PMError, "Shoma checkpointe faal darid, az \"/Cancel checkpoint\" baraye laghve an estefade konid", "You have an active checkpoint, use \"/Cancel checkpoint\" to cancel it", GetPlayerToken(%0))
#define 								CreateCheckPointStock(%0) stock CH%0(playerid)
#define 								ActiveCheckPoint(%0) case %0: return CH%0(playerid)



// 								CheckPointID 								//
#define 								CHECKPOINTID_ExamLic 								1



public OnPlayerEnterCheckpoint(playerid){
	switch(PlayerCheckPoint[playerid]){
	}
	return 1;
}
public OnPlayerLeaveCheckpoint(playerid){
	return 1;
}

#define 								CreateRaceCheckPointStock(%0) stock RCH%0(playerid)
#define 								ActiveRaceCheckPoint(%0) case %0: return RCH%0(playerid)
public OnPlayerEnterRaceCheckpoint(playerid){
	switch(PlayerCheckPoint[playerid]){
		ActiveRaceCheckPoint(CHECKPOINTID_ExamLic);
	}
	return 1;
}
public OnPlayerLeaveRaceCheckpoint(playerid){
	return 1;
}