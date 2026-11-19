
#if defined _MAPSPAWN_BY_MAMAD_PERSIAN_INC
	#endinput
#endif
#define _MAPSPAWN_BY_MAMAD_PERSIAN_INC

stock LoadMapSpawn(){
	//Gooye charkhan
	CreateDynamicObject(18844,1474.745,-2286.785,69.834,0.000,0.000,0.000,0,0,-1,300.000,300.000);
	new ArianaGameObjectText;
	ArianaGameObjectText = CreateDynamicObject(7912, 1451.342, -2286.984, 17.352, 0.000, 0.000, -90.000, 0, 0, -1, 200.000, 200.000);
	SetDynamicObjectMaterialText(ArianaGameObjectText, 0, "{660066}A{800080}r{990099}i{B300B3}a{CC00CC}n{E600E6}a {CC00CC}G{B300B3}a{990099}m{800080}e", 130, "Arial", 80, 1, 0xFFFF00FF, 0, 1);
    return 1;
}