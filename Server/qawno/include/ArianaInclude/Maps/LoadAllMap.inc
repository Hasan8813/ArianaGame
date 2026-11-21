#if defined _LOAD_ALL_MAP_BY_MAMAD_PERSIAN_INC
	#endinput
#endif
#define _LOAD_ALL_MAP_BY_MAMAD_PERSIAN_INC

#include 								<ArianaInclude/Maps/MapSpawn.inc>//Systeme mapperi spawn
#include 								<ArianaInclude/Maps/MapIcons.inc>//Systeme mapperi spawn

stock LoadAllMap(){
    LoadAllMapIcon();
    LoadMapSpawn();
    LoadMapExam();
    return 1;
}