#if defined ALLTEXTURES
	#endinput
#endif
#define ALLTEXTURES

#define GetTModel(%0) ObjectTextures[%0][TModel]
#define GetTXDName(%0) ObjectTextures[%0][TXDName]
#define GetTextureName(%0) ObjectTextures[%0][TextureName]

new MAX_TEXTURES;

enum TEXTUREDEF { TModel, TXDName[32], TextureName[32] }

new ObjectTextures[][TEXTUREDEF] =
{
////////////////////////////////////////////////////////////////////////////////
// Original SA textures ////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
	{ 0, "INVALID", "INVALID" },
	{ 19004, "roundbuilding1", "capitolwin1_lawn2" },
	{ 19004, "roundbuilding1", "stonewalltile4" },
	{ 18835, "mickytextures", "arrow-blue-outline-up" },
	{ 18835, "mickytextures", "brick008" },
	{ 18835, "mickytextures", "brown013" },
	{ 18835, "mickytextures", "dancea" },
	{ 18835, "mickytextures", "gg_end_lod_3" },
	{ 18835, "mickytextures", "grey002" },
	{ 18835, "mickytextures", "marb002" },
	{ 18835, "mickytextures", "metal013" },
	{ 18835, "mickytextures", "metal061" },
	{ 18835, "mickytextures", "orang006" },
	{ 18835, "mickytextures", "red032" },
	{ 18835, "mickytextures", "smileyface1" },
	{ 18835, "mickytextures", "smileyface2" },
	{ 18835, "mickytextures", "whiteforletters" },
	{ 18835, "mickytextures", "wood051" },
	{ 18835, "mickytextures", "yello007" },
};

#if defined FILTERSCRIPT
	public OnFilterScriptInit()
	{
		MAX_TEXTURES = sizeof(ObjectTextures);
		printf("LOADED %i texture definitions", MAX_TEXTURES);
		return CallLocalFunction("Texture_ALS_OnFilterScriptInit", "");
	}
	#if defined _ALS_OnFilterScriptInit
		#undef OnFilterScriptInit
	#else
		#define _ALS_OnFilterScriptInit
	#endif
	#define OnFilterScriptInit Texture_ALS_OnFilterScriptInit

	forward Texture_ALS_OnFilterScriptInit();
#else
	public OnGameModeInit()
	{
		MAX_TEXTURES = sizeof(ObjectTextures);
		printf("LOADED %i texture definitions", MAX_TEXTURES);
		return CallLocalFunction("Texture_ALS_OnGameModeInit", "");
	}
	#if defined _ALS_OnGameModeInit
		#undef OnGameModeInit
	#else
		#define _ALS_OnGameModeInit
	#endif
	#define OnGameModeInit Texture_ALS_OnGameModeInit

	forward Texture_ALS_OnGameModeInit();
#endif