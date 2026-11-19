#if defined _CHECKNICKNAME_BY_MAMAD_PERSIAN_INC
	#endinput
#endif
#define _CHECKNICKNAME_BY_MAMAD_PERSIAN_INC

#define MAX_NORM_LEN     24
new const BadDomainTLD[][] = {
    ".ir", ".com", ".net", ".org", ".ru", ".info", ".biz", ".tv", ".io",
    ".co", ".me", ".cc", ".ws", ".gg", ".xyz", ".top", ".online", ".site"
};
new const BadNickName[][] = {
	"ariana", "arana", "arianagame", "aranagame", "arianagames", "arinagames", "aranagames", "server",
	"kir", "kar", "cir", "car", "kiri", "kari", "kira", "ciri", "cari", "cira", "cara", "kara",
	"kos", "kus", "cos", "cus", "kon", "kun", "kuni",
	"koni", "kona", "kuna", "con", "cun", "coni", "cuni", "cona", "cuna", "koskesh", "coskesh", "koscesh", "coscesh", "madar", "nadareto", "baba", "jende", "jendeh", "jinde", "jindeh", "Jande", "jandeh", "gayidan", "gayadam", "gayidametun", "gayidameton", "gayadametun", "gayadameton", "gayesh", "gay", "trans",
    "haromi", "harumi", "haruma", "haroma", "haromzade", "harumzade", "haramzade", "dashagh", "kirkoloft", "karkoloft", "cirkoloft", "carkoloft", "circoloft", "kircoloft", "karcoloft", "kirkoioft", "karkoioft", "cirkoioft", "carkoioft", "circoioft", "kircoioft", "karcoioft", "fuck", "fock", "fucker", "focker", "fuckyou", "fockyou", "koskash", "coskash", "koscash", "coscash", "dashagh",
    "khaye", "khayemal", "khayemai", "tokhm", "tokhmi", "tokhma", "tokhmdar", "goshad", "lashi", "lasha", "iashi", "iasha", "hashari", "hashara", "jagh", "jaq", "jaghi", "jagha", "jaqa", "sik", "sic", "sak", "sac", "siktir", "saktir", "siktar", "ciktir", "caktir", "ciktar", "as",
	"jakesh", "gaed", "chink", "bitch", "chank", "batch", "whore", "awore", "cunt", "cont", "dick", "pusy", "bastard", "motherfucker", "cock"
};
stock NormalizeName(const src[], dest[], maxlen){
    new p = 0;
    new lastchar = 0;
    for(new i = 0; src[i] != 0 && p < maxlen - 1; i++){
        new c = src[i];
        if(c >= 'A' && c <= 'Z') c += 32;
        switch(c){
            case '0': c = 'o';
            case '1': c = 'a';
            case '4': c = 'a';
            case '@': c = 'a';
			case '|': c = 'a';
            case '$': c = 's';
			case '3': c = 's';
            case '!': c = 'i';
			case 'l': c = 'i';
			case '&': c = 'g';
            case 'w': c = 'a';
		}
        if(c < 'a' || c > 'z') continue;
        if(c == lastchar) continue;
        dest[p++] = c;
        lastchar = c;
    }dest[p] = 0;
}stock bool:HasIPPattern(const name[]){
    new len = strlen(name);
    new digitCount = 0, dotCount = 0;
    for(new i = 0; i < len; i++){
        if(name[i] >= '0' && name[i] <= '9') digitCount++; else if(name[i] == '.') dotCount++;
    }if(dotCount >= 2 && digitCount >= 4) return true;
    return false;
}stock bool:HasPortPattern(const name[]){
    new len = strlen(name);
    for(new i = 0; i < len - 1; i++){
        if(name[i] == ':'){
            new digits = 0;
            for(new j = i + 1; j < len && name[j] >= '0' && name[j] <= '9'; j++) digits++;
            if(digits >= 2) return true;
        }
    }return false;
}stock bool:HasDomainPattern(const name[]){
    for(new i = 0; i < sizeof(BadDomainTLD); i++){
        if(strfind(name, BadDomainTLD[i], true) != -1) return true;
    }return false;
}stock CheckNick(playerid, Token){
	CheckPlayerOnlineToCMD(playerid);
	CheckPlayerTokenCmp(playerid, Token);
    new name[MAX_PLAYER_NAME];
    GetPlayerName(playerid, name, sizeof(name));
    if(HasIPPattern(name) || HasPortPattern(name) || HasDomainPattern(name)){
    	ShowPlayerDialog(playerid, 871, DIALOG_STYLE_MSGBOX, "{C13B00}Ekhtar", "{C13B00}Shoma az esme mamnu'e estefade kardid.\nEsme monaseb bayad {FFFFFF}3 {C13B00}ta {FFFFFF}20 {C13B00}harf ke shamele tohin va alfaze rakik va address haye interneti nabashad.", "Ok", "");
    	Skick(playerid, "Shoma az esme mamnu'e estefade kardeyid", "Shoma az esme mamnu'e estefade kardeyid", Token, true);
    	return 0;
	}new normalized[MAX_NORM_LEN];
    NormalizeName(name, normalized, sizeof(normalized));
    for(new i = 0; i < sizeof(BadNickName); i++){
        if(strcmp(normalized, BadNickName[i], true) == 0){
            ShowPlayerDialog(playerid, 871, DIALOG_STYLE_MSGBOX, "{C13B00}Ekhtar", "{C13B00}Shoma az esme mamnu'e estefade kardid.\nEsme monaseb bayad {FFFFFF}3 {C13B00}ta {FFFFFF}20 {C13B00}harf ke shamele tohin va alfaze rakik va address haye interneti nabashad.", "Ok", "");
			Skick(playerid, "Shoma az esme mamnu'e estefade kardeyid", "Shoma az esme mamnu'e estefade kardeyid", Token, true);
            return 0;
        }
    }return 1;
}
