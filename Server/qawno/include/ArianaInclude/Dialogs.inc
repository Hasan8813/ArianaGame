#if defined _DIALOGSS_BY_MAMAD_PERSIAN_INC
	#endinput
#endif
#define _DIALOGSS_BY_MAMAD_PERSIAN_INC



// 								Dialogs 							//
//Baraye estefade az SetDialog...(NameID) ha bad az gharar dadane esm {} va dar in code ra gharar dahid
//Baraye estefade az SetDialogID...(DialogID, NameID) ha avval dialogid ke dar define ha taarif shode ke yek adad bast ra gharar dahid sepas...
//NameID ke ba SetDialpg...(NameID) sakhtid ra vared konid va in kara dar switch ke dar OnDialogResponse hast gharar dahid
#define 								SetDialogMSG(%0) stock DLGMSG%0(playerid, response)
#define 								SetDialogIDMSG(%0) case %0: return DLGMSG%0(playerid, response)

#define 								SetDialogInput(%0) stock DLGINPUT%0(playerid, response, const inputtext[])
#define 								SetDialogIDInput(%0) case %0: return DLGINPUT%0(playerid, response, inputtext)

#define 								SetDialogList(%0) stock DLGLIST%0(playerid, response, listitem)
#define 								SetDialogIDList(%0) case %0: return DLGLIST%0(playerid, response, listitem)
#define 								DIALOGID_LOGIN 								1001
#define 								DIALOGID_REGISTER 								1002
#define 								DIALOGID_REGISTER2 								 1003
#define 								DIALOGID_EMAIL 								1004
#define 								DIALOGID_SEX 								1005
#define 								DIALOGID_LANGUAGE 								1006
#define 								DIALOGID_STATS 								1007
#define 								DIALOGID_ACOOUNT 								1008
#define 								DIALOGID_CHANGEPASSWORD 								1009
#define 								DIALOGID_NEWPASSWORD 								1010
#define 								DIALOGID_NEWPASSWORD1 								 1011
#define 								DIALOGID_VALIDATEEMAIL 								1012
#define 								DIALOGID_SETTINGS 								1013
#define 								DIALOGID_LICENSES 								1014

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]){
	switch(dialogid){
		SetDialogIDInput(DIALOGID_LOGIN);
		SetDialogIDInput(DIALOGID_REGISTER);
		SetDialogIDInput(DIALOGID_REGISTER2);
		SetDialogIDInput(DIALOGID_EMAIL);
		SetDialogIDMSG(DIALOGID_SEX);
		SetDialogIDMSG(DIALOGID_LANGUAGE);
		SetDialogIDList(DIALOGID_ACOOUNT);
		SetDialogIDInput(DIALOGID_CHANGEPASSWORD);
		SetDialogIDInput(DIALOGID_NEWPASSWORD);
		SetDialogIDInput(DIALOGID_NEWPASSWORD1);
		SetDialogIDInput(DIALOGID_VALIDATEEMAIL);
		SetDialogIDList(DIALOGID_SETTINGS);
		SetDialogIDMSG(DIALOGID_STATS);
		SetDialogIDMSG(DIALOGID_LICENSES);
	}     
	return 1;
}
