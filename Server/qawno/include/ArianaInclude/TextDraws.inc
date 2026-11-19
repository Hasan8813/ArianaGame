#if defined _ALLTEXTDRAWS_BY_MAMAD_PERSIAN_INC
	#endinput
#endif
#define _ALLTEXTDRAWS_BY_MAMAD_PERSIAN_INC



//Show va hide textdraw ha dar include arianapublic hast



//Time server
new Text:txtTimeDisp, Text:txtTimeDis;
new Text:fstd[14];
new PlayerText:NameText[MAX_PLAYERS];
new PlayerText:GoldText[MAX_PLAYERS];
new PlayerText:XPText[MAX_PLAYERS];
new PlayerText:LevelText[MAX_PLAYERS];
stock LoadAllTextDraws(){
	//Time server
   	txtTimeDis = TextDrawCreate(92.5, 434.0,"00-00-00"); TextDrawUseBox(txtTimeDis, false); TextDrawFont(txtTimeDis, TEXT_DRAW_FONT_1); TextDrawSetShadow(txtTimeDis,0); TextDrawSetOutline(txtTimeDis,2); TextDrawBackgroundColour(txtTimeDis,0x000000FF); TextDrawColour(txtTimeDis,0xFFFFFFFF); TextDrawAlignment(txtTimeDis, TEXT_DRAW_ALIGN_RIGHT); TextDrawLetterSize(txtTimeDis,0.3,1.0);
	txtTimeDisp = TextDrawCreate(88.0, 417.0,"00:00"); TextDrawUseBox(txtTimeDisp, false); TextDrawFont(txtTimeDisp, TEXT_DRAW_FONT_3);
	TextDrawSetShadow(txtTimeDisp,0); TextDrawSetOutline(txtTimeDisp,2); TextDrawBackgroundColour(txtTimeDisp,0x000000FF); TextDrawColour(txtTimeDisp,0xFFFFFFFF); TextDrawAlignment(txtTimeDisp, TEXT_DRAW_ALIGN_RIGHT); TextDrawLetterSize(txtTimeDisp,0.5,1.5);
    
	//TextDraw logo server
	fstd[13] = TextDrawCreate(555.565796, 5.192500, "A"); TextDrawLetterSize(fstd[13], 0.306800, 1.442100); TextDrawTextSize(fstd[13], 1280.000000, 1280.000000); TextDrawAlignment(fstd[13], TEXT_DRAW_ALIGN_CENTER); TextDrawColour(fstd[13], 0xB800B8FF); TextDrawUseBox(fstd[13], false); TextDrawBoxColour(fstd[13], 0x80808080);TextDrawSetShadow(fstd[13], 0); TextDrawSetOutline(fstd[13], 1); TextDrawBackgroundColour(fstd[13], 0x00000006); TextDrawFont(fstd[13], TEXT_DRAW_FONT_1); TextDrawSetProportional(fstd[13], true);
	fstd[12] = TextDrawCreate(545.333130, 0.273900, ""); TextDrawLetterSize(fstd[12], 0.000000, 0.000000); TextDrawTextSize(fstd[12], 20.000000, 24.000000); TextDrawAlignment(fstd[12], TEXT_DRAW_ALIGN_LEFT); TextDrawColour(fstd[12], 0xD8D8D8FF); TextDrawUseBox(fstd[12], false); TextDrawBoxColour(fstd[12], 0x80808080); TextDrawSetShadow(fstd[12], 0);TextDrawSetOutline(fstd[12], 0); TextDrawBackgroundColour(fstd[12], 0x00000000); TextDrawFont(fstd[12], TEXT_DRAW_FONT_MODEL_PREVIEW); TextDrawSetProportional(fstd[12], false); TextDrawSetPreviewModel(fstd[12], 1316); TextDrawSetPreviewRot(fstd[12], 90.000000, 0.000000, 0.000000, 1.000000);
	fstd[11] = TextDrawCreate(557.932312, 10.659296, "-"); TextDrawLetterSize(fstd[11], 0.335000, 1.010900); TextDrawTextSize(fstd[11], 1280.000000, 1280.000000); TextDrawAlignment(fstd[11], TEXT_DRAW_ALIGN_CENTER); TextDrawColour(fstd[11], 0xB800B8FF); TextDrawUseBox(fstd[11], false); TextDrawBoxColour(fstd[11], 0x80808080); TextDrawSetShadow(fstd[11], 0); TextDrawSetOutline(fstd[11], 1); TextDrawBackgroundColour(fstd[11], 0x00000006); TextDrawFont(fstd[11], TEXT_DRAW_FONT_1); TextDrawSetProportional(fstd[11], true);
	fstd[10] = TextDrawCreate(553.631958, 10.659296, "-"); TextDrawLetterSize(fstd[10], 0.335000, 1.010900); TextDrawTextSize(fstd[10], 1280.000000, 1280.000000); TextDrawAlignment(fstd[10], TEXT_DRAW_ALIGN_CENTER); TextDrawColour(fstd[10], 0xB800B8FF); TextDrawUseBox(fstd[10], false); TextDrawBoxColour(fstd[10], 0x80808080); TextDrawSetShadow(fstd[10], 0); TextDrawSetOutline(fstd[10], 1); TextDrawBackgroundColour(fstd[10], 0x00000006); TextDrawFont(fstd[10], TEXT_DRAW_FONT_1); TextDrawSetProportional(fstd[10], true);
	fstd[9] = TextDrawCreate(567.633728, 13.489000, ""); TextDrawLetterSize(fstd[9], 0.000000, 0.000000); TextDrawTextSize(fstd[9], -25.000000, 9.000000); TextDrawAlignment(fstd[9], TEXT_DRAW_ALIGN_LEFT); TextDrawColour(fstd[9], 0xB800B8FF); TextDrawUseBox(fstd[9], false); TextDrawBoxColour(fstd[9], 0x80808080); TextDrawSetShadow(fstd[9], 0); TextDrawSetOutline(fstd[9], 0); TextDrawBackgroundColour(fstd[9], 0x00000000); TextDrawFont(fstd[9], TEXT_DRAW_FONT_MODEL_PREVIEW); TextDrawSetProportional(fstd[9], false); TextDrawSetPreviewModel(fstd[9], 1316); TextDrawSetPreviewRot(fstd[9], 227.000000, 124.000000, 0.000000, 0.427500);
	fstd[8] = TextDrawCreate(555.766724, 17.970301, ""); TextDrawLetterSize(fstd[8], 0.000000, 0.000000); TextDrawTextSize(fstd[8], 8.000000, 10.000000); TextDrawAlignment(fstd[8], TEXT_DRAW_ALIGN_LEFT); TextDrawColour(fstd[8], 0xB800B8FF); TextDrawUseBox(fstd[8], false); TextDrawBoxColour(fstd[8], 0x80808080); TextDrawSetShadow(fstd[8], 0); TextDrawSetOutline(fstd[8], 0); TextDrawBackgroundColour(fstd[8], 0x00000000); TextDrawFont(fstd[8], TEXT_DRAW_FONT_MODEL_PREVIEW); TextDrawSetProportional(fstd[8], false); TextDrawSetPreviewModel(fstd[8], 19177); TextDrawSetPreviewRot(fstd[8], 0.000000, 209.000000, 0.000000, 0.187600);
	fstd[7] = TextDrawCreate(562.233215, 8.444196, ""); TextDrawLetterSize(fstd[7], 0.000000, 0.000000); TextDrawTextSize(fstd[7], 4.110000, 3.319900); TextDrawAlignment(fstd[7], TEXT_DRAW_ALIGN_LEFT); TextDrawColour(fstd[7], 0xB800B8FF); TextDrawUseBox(fstd[7], false); TextDrawBoxColour(fstd[7], 0x80808080); TextDrawSetShadow(fstd[7], 0); TextDrawSetOutline(fstd[7], 0); TextDrawBackgroundColour(fstd[7], 0x00000000); TextDrawFont(fstd[7], TEXT_DRAW_FONT_MODEL_PREVIEW); TextDrawSetProportional(fstd[7], false); TextDrawSetPreviewModel(fstd[7], 19201); TextDrawSetPreviewRot(fstd[7], 110.000000, 221.000000, 115.000000, 0.192900);
	fstd[6] = TextDrawCreate(562.133179, 12.166296, ""); TextDrawLetterSize(fstd[6], 0.000000, 0.000000); TextDrawTextSize(fstd[6], 4.000000, 7.000000); TextDrawAlignment(fstd[6], TEXT_DRAW_ALIGN_LEFT); TextDrawColour(fstd[6], 0xB800B8FF); TextDrawUseBox(fstd[6], false); TextDrawBoxColour(fstd[6], 0x80808080); TextDrawSetShadow(fstd[6], 0); TextDrawSetOutline(fstd[6], 0); TextDrawBackgroundColour(fstd[6], 0x00000000); TextDrawFont(fstd[6], TEXT_DRAW_FONT_MODEL_PREVIEW); TextDrawSetProportional(fstd[6], false); TextDrawSetPreviewModel(fstd[6], 19201); TextDrawSetPreviewRot(fstd[6], 52.000000, 360.000000, 93.000000, 0.187600);
	fstd[5] = TextDrawCreate(560.333130, 17.584900, ""); TextDrawLetterSize(fstd[5], 0.000000, 0.000000); TextDrawTextSize(fstd[5], 4.000000, 4.000000); TextDrawAlignment(fstd[5], TEXT_DRAW_ALIGN_LEFT); TextDrawColour(fstd[5], 0xB800B8FF); TextDrawUseBox(fstd[5], false); TextDrawBoxColour(fstd[5], 0x80808080); TextDrawSetShadow(fstd[5], 0); TextDrawSetOutline(fstd[5], 0); TextDrawBackgroundColour(fstd[5], 0x00000000); TextDrawFont(fstd[5], TEXT_DRAW_FONT_MODEL_PREVIEW); TextDrawSetProportional(fstd[5], false); TextDrawSetPreviewModel(fstd[5], 19201); TextDrawSetPreviewRot(fstd[5], 302.000000, 134.000000, 0.000000, 0.192900);
	fstd[4] = TextDrawCreate(568.899475, 3.085200, "Ariana"); TextDrawLetterSize(fstd[4], 0.263000, 1.359200); TextDrawTextSize(fstd[4], 1280.000000, 1280.000000); TextDrawAlignment(fstd[4], TEXT_DRAW_ALIGN_LEFT); TextDrawColour(fstd[4], 0xB800B8FF); TextDrawUseBox(fstd[4], false); TextDrawBoxColour(fstd[4], 0x80808080); TextDrawSetShadow(fstd[4], 0); TextDrawSetOutline(fstd[4], 0); TextDrawBackgroundColour(fstd[4], 0x0000000D); TextDrawFont(fstd[4], TEXT_DRAW_FONT_1); TextDrawSetProportional(fstd[4], true);
	fstd[3] = TextDrawCreate(589.100098, 12.673996, "Game"); TextDrawLetterSize(fstd[3], 0.245600, 1.105298); TextDrawTextSize(fstd[3], 1280.000000, 1280.000000); TextDrawAlignment(fstd[3], TEXT_DRAW_ALIGN_CENTER); TextDrawColour(fstd[3],  0xD8D8D8FF); TextDrawUseBox(fstd[3], false); TextDrawBoxColour(fstd[3], 0x80808080); TextDrawSetShadow(fstd[3], 0); TextDrawSetOutline(fstd[3], 0); TextDrawBackgroundColour(fstd[3], 0x0000000A); TextDrawFont(fstd[3], TEXT_DRAW_FONT_1); TextDrawSetProportional(fstd[3], true);
	fstd[2] = TextDrawCreate(549.333130, 25.703800, ""); TextDrawLetterSize(fstd[2], 0.000000, 0.000000); TextDrawTextSize(fstd[2], 12.000000, -23.000000); TextDrawAlignment(fstd[2], TEXT_DRAW_ALIGN_LEFT); TextDrawColour(fstd[2], 0xB800B8FF); TextDrawUseBox(fstd[2], false); TextDrawBoxColour(fstd[2], 0x80808080); TextDrawSetShadow(fstd[2], 0); TextDrawSetOutline(fstd[2], 0); TextDrawBackgroundColour(fstd[2], 0x00000000); TextDrawFont(fstd[2], TEXT_DRAW_FONT_MODEL_PREVIEW); TextDrawSetProportional(fstd[2], false); TextDrawSetPreviewModel(fstd[2], 1316); TextDrawSetPreviewRot(fstd[2], 136.000000, 0.000000, 0.000000, 0.500500);
	fstd[1] = TextDrawCreate(549.466370, 21.740900, ""); TextDrawLetterSize(fstd[1], 0.000000, 0.000000); TextDrawTextSize(fstd[1], 15.100000, -13.000000); TextDrawAlignment(fstd[1], TEXT_DRAW_ALIGN_LEFT); TextDrawColour(fstd[1], 0xB800B8FF); TextDrawUseBox(fstd[1], false); TextDrawBoxColour(fstd[1], 0x80808080); TextDrawSetShadow(fstd[1], 0); TextDrawSetOutline(fstd[1], 0); TextDrawBackgroundColour(fstd[1], 0x00000000); TextDrawFont(fstd[1], TEXT_DRAW_FONT_MODEL_PREVIEW); TextDrawSetProportional(fstd[1], false); TextDrawSetPreviewModel(fstd[1], 1316); TextDrawSetPreviewRot(fstd[1], 290.000000, 318.000000, 0.000000, 0.474400);
	fstd[0] = TextDrawCreate(566.133728, 13.489000, ""); TextDrawLetterSize(fstd[0], 0.000000, 0.000000); TextDrawTextSize(fstd[0], -25.000000, 9.000000); TextDrawAlignment(fstd[0], TEXT_DRAW_ALIGN_LEFT); TextDrawColour(fstd[0], 0xB800B8FF); TextDrawUseBox(fstd[0], false); TextDrawBoxColour(fstd[0], 0x80808080); TextDrawSetShadow(fstd[0], 0); TextDrawSetOutline(fstd[0], 0); TextDrawBackgroundColour(fstd[0], 0x00000000); TextDrawFont(fstd[0], TEXT_DRAW_FONT_MODEL_PREVIEW); TextDrawSetProportional(fstd[0], false); TextDrawSetPreviewModel(fstd[0], 1316); TextDrawSetPreviewRot(fstd[0], 227.000000, 124.000000, 0.000000, 0.427500);
	return 1;
}stock ShowServerLogo(playerid){
	TextDrawShowForPlayer(playerid, fstd[13]); TextDrawShowForPlayer(playerid, fstd[12]); TextDrawShowForPlayer(playerid, fstd[11]); TextDrawShowForPlayer(playerid, fstd[10]); TextDrawShowForPlayer(playerid, fstd[9]); TextDrawShowForPlayer(playerid, fstd[8]); TextDrawShowForPlayer(playerid, fstd[7]); TextDrawShowForPlayer(playerid, fstd[6]); TextDrawShowForPlayer(playerid, fstd[5]); TextDrawShowForPlayer(playerid, fstd[4]); TextDrawShowForPlayer(playerid, fstd[3]); TextDrawShowForPlayer(playerid, fstd[2]); TextDrawShowForPlayer(playerid, fstd[1]); TextDrawShowForPlayer(playerid, fstd[0]);
	return 1;
}stock InfoTextDraw(playerid){
	GoldText[playerid] = CreatePlayerTextDraw(playerid, 38.0, 403.0, "");
	PlayerTextDrawFont(playerid, GoldText[playerid], TEXT_DRAW_FONT_1);
	PlayerTextDrawLetterSize(playerid, GoldText[playerid], 0.3, 1.1);
	PlayerTextDrawColour(playerid, GoldText[playerid], 0xEECD0FFF);
	PlayerTextDrawSetOutline(playerid, GoldText[playerid], 1);
	PlayerTextDrawSetProportional(playerid, GoldText[playerid], true);
	PlayerTextDrawSetShadow(playerid, GoldText[playerid], true);

	XPText[playerid] = CreatePlayerTextDraw(playerid, 38.5, 379.0, "");
	PlayerTextDrawFont(playerid, XPText[playerid], TEXT_DRAW_FONT_1);
	PlayerTextDrawLetterSize(playerid, XPText[playerid], 0.3, 1.1);
	PlayerTextDrawColour(playerid, XPText[playerid], 0xFFB2B3B2);
	PlayerTextDrawSetOutline(playerid, XPText[playerid], 1);
	PlayerTextDrawSetProportional(playerid, XPText[playerid], true);
	PlayerTextDrawSetShadow(playerid, XPText[playerid], true);

	LevelText[playerid] = CreatePlayerTextDraw(playerid, 38.5, 391.0, "");
	PlayerTextDrawFont(playerid, LevelText[playerid], TEXT_DRAW_FONT_1);
	PlayerTextDrawLetterSize(playerid, LevelText[playerid], 0.3, 1.1);
	PlayerTextDrawColour(playerid, LevelText[playerid], 0xFFB0A0FF);
	PlayerTextDrawSetOutline(playerid, LevelText[playerid], 1);
	PlayerTextDrawSetProportional(playerid, LevelText[playerid], true);
	PlayerTextDrawSetShadow(playerid, LevelText[playerid], true);

	NameText[playerid] = CreatePlayerTextDraw(playerid, 108.0, 432.0, "");
	PlayerTextDrawFont(playerid, NameText[playerid], TEXT_DRAW_FONT_1);
	PlayerTextDrawLetterSize(playerid, NameText[playerid], 0.3, 1.3);
	PlayerTextDrawColour(playerid, NameText[playerid], GetPlayerColorNameHex(playerid));
	PlayerTextDrawSetOutline(playerid, NameText[playerid], 1);
	PlayerTextDrawSetProportional(playerid, NameText[playerid], true);
	PlayerTextDrawSetShadow(playerid, NameText[playerid], true);
	return 1;
}stock UpdateGoldTD(playerid, Token){
	CheckPlayerOnlineAndLogin(playerid);
	CheckPlayerTokenCmp(playerid, Token);
	PlayerTextDrawSetString(playerid, GoldText[playerid], "Gold: %d", GetPlayerPgold(playerid));
	PlayerTextDrawShow(playerid, GoldText[playerid]);
	return 1;
}stock UpdateLevelAndXPTD(playerid, Token){
	CheckPlayerOnlineAndLogin(playerid);
	CheckPlayerTokenCmp(playerid, Token);
	new required = RequiredXP(GetPlayerPlevel(playerid));
	PlayerTextDrawSetString(playerid, XPText[playerid], "XP: %d/%d", GetPlayerPXP(playerid), required);
	PlayerTextDrawShow(playerid, XPText[playerid]);
	PlayerTextDrawSetString(playerid, LevelText[playerid], "Level: %d", GetPlayerPlevel(playerid));
	PlayerTextDrawShow(playerid, LevelText[playerid]);
	return 1;
}stock UpdateNameTD(playerid, Token){
	CheckPlayerOnlineAndLogin(playerid);
	CheckPlayerTokenCmp(playerid, Token);
	GetNameP(playerid);
	PlayerTextDrawSetString(playerid, NameText[playerid], "%s(%d)", Name, playerid);
	PlayerTextDrawColour(playerid, NameText[playerid], GetPlayerColorNameHex(playerid));
	PlayerTextDrawShow(playerid, NameText[playerid]);
	return 1;
}stock UpdateAllTD(playerid, Token){
	CheckPlayerOnlineAndLogin(playerid);
	CheckPlayerTokenCmp(playerid, Token);
	CheckLevelUP(playerid, false, Token);
	UpdateGoldTD(playerid, Token);
	UpdateNameTD(playerid, Token);
	return 1;
}