#if defined _MYSQLCONNECTANDLOG_BY_MAMAD_PERSIAN_INC
	#endinput
#endif
#define _MYSQLCONNECTANDLOG_BY_MAMAD_PERSIAN_INC

stock MySQLConnectAndLogAndCreateTable(){
    sqlopt = mysql_init_options();
	mysql_set_option(sqlopt, AUTO_RECONNECT, true);
	mysql_set_option(sqlopt, MULTI_STATEMENTS, false);
    mysql_set_option(sqlopt, POOL_SIZE, 16);
    mysql_log(ERROR | WARNING);
	sql = mysql_connect(SQL_HOST, SQL_USER, SQL_PASS, SQL_DB, sqlopt);
	if(mysql_errno(sql)) printf("[MySQL][Error]: Error, Connect, %s", SQL_USER);
	else{
		printf("[MySQL]: MySQL connected to %s, Database: [%s]", SQL_USER, SQL_DB);
		mysql_tquery(sql, "CREATE TABLE IF NOT EXISTS users (\
            pid INT AUTO_INCREMENT PRIMARY KEY,\
            pName VARCHAR(25) NOT NULL UNIQUE,\
            pKey VARCHAR(61) NOT NULL,\
            pEmail VARCHAR(256) NOT NULL,\
            pMoney INT DEFAULT 0,\
            pLevel INT DEFAULT 1,\
            pXP INT DEFAULT 0,\
            pGold INT DEFAULT 0,\
            pWanted INT DEFAULT 0,\
			pJobId INT DEFAULT 0,\
			pTimePlay INT DEFAULT 0,\
			pTimePlaymin INT DEFAULT 0,\
            pAdmin INT DEFAULT 0,\
			AutoLogin INT DEFAULT 0,\
			pIP VARCHAR(50) NOT NULL,\
			pGPCI VARCHAR(50) NOT NULL,\
			pDrivLic INT DEFAULT 0,\
			pFlyLic INT DEFAULT 0,\
			pSailingLic INT DEFAULT 0,\
			pWeaponLic INT DEFAULT 0,\
            pLastLogin TIMESTAMP DEFAULT CURRENT_TIMESTAMP,\
            pSex INT DEFAULT 0,\
            pLang INT DEFAULT 1,\
            pPer DATETIME DEFAULT 0,\
            created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,\
            pRefCode VARCHAR(10) UNIQUE,\
			pSaveSeq INT DEFAULT 0\
        )");
		mysql_tquery(sql, "CREATE TABLE IF NOT EXISTS biz (\
            bid INT AUTO_INCREMENT PRIMARY KEY,\
            x FLOAT NOT NULL,\
            y FLOAT NOT NULL,\
			z FLOAT NOT NULL,\
			a FLOAT NOT NULL,\
			tx FLOAT NOT NULL,\
			ty FLOAT NOT NULL,\
			tz FLOAT NOT NULL,\
			ta FLOAT NOT NULL,\
			intid INT NOT NULL,\
			type INT DEFAULT 0\
        )");
        mysql_tquery(sql, "CREATE TABLE IF NOT EXISTS MoneyLog (\
    		id INT AUTO_INCREMENT PRIMARY KEY,\
			Money INT DEFAULT 0,\
    		PlayerTarget VARCHAR(25) NOT NULL,\
    		PlayerTargetRef INT DEFAULT 0,\
    		PlayerGive VARCHAR(25) DEFAULT NULL,\
    		PlayerGiveRef INT DEFAULT 0,\
			Admin VARCHAR(25) DEFAULT NULL,\
    		AdminRef INT DEFAULT 0,\
    		Command TEXT DEFAULT NULL,\
            Reason TEXT DEFAULT NULL,\
			PON INT DEFAULT 0,\
			TimeLog TIMESTAMP DEFAULT CURRENT_TIMESTAMP\
		)");
		mysql_tquery(sql, "CREATE TABLE IF NOT EXISTS GoldLog (\
    		id INT AUTO_INCREMENT PRIMARY KEY,\
			Gold INT DEFAULT 0,\
    		PlayerTarget VARCHAR(25) NOT NULL,\
    		PlayerTargetRef INT DEFAULT 0,\
    		PlayerGive VARCHAR(25) DEFAULT NULL,\
    		PlayerGiveRef INT DEFAULT 0,\
			Admin VARCHAR(25) DEFAULT NULL,\
    		AdminRef INT DEFAULT 0,\
    		Command TEXT DEFAULT NULL,\
            Reason TEXT DEFAULT NULL,\
			PON INT DEFAULT 0,\
			TimeLog TIMESTAMP DEFAULT CURRENT_TIMESTAMP\
		)");
		mysql_tquery(sql, "CREATE TABLE IF NOT EXISTS AdminLogAccess (\
    		id INT AUTO_INCREMENT PRIMARY KEY,\
    		AdminName VARCHAR(24) NOT NULL,\
    		IP VARCHAR(50) NOT NULL,\
    		Code VARCHAR(6) NOT NULL,\
    		CreatedAt TIMESTAMP DEFAULT CURRENT_TIMESTAMP,\
    		ExpireAt TIMESTAMP NOT NULL\
		);")
		mysql_tquery(sql, "CREATE TABLE IF NOT EXISTS Temporary_Ban (\
    		id INT AUTO_INCREMENT PRIMARY KEY,\
    		PlayerName VARCHAR(24) NOT NULL,\
			Reason VARCHAR(88) NOT NULL,\
    		gpci VARCHAR(200) NOT NULL,\
    		CreatedAt TIMESTAMP DEFAULT CURRENT_TIMESTAMP,\
    		ExpireAt TIMESTAMP NOT NULL\
		);")
        mysql_tquery(sql, "CREATE TABLE IF NOT EXISTS AccountLoginLog (\
            id INT AUTO_INCREMENT PRIMARY KEY,\
            AccountName VARCHAR(24) NOT NULL,\
            AccountPID INT NOT NULL,\
            IP VARCHAR(50) NOT NULL,\
            GPCI VARCHAR(200) NOT NULL,\
			AutoLogin INT NOT NULL,\
            LoginTime TIMESTAMP DEFAULT CURRENT_TIMESTAMP,\
            INDEX(AccountName),\
            INDEX(IP),\
            INDEX(GPCI)\
        );")
        mysql_tquery(sql, "DROP TRIGGER IF EXISTS CreateRefCode");
        mysql_tquery(sql, "CREATE TRIGGER CreateRefCode BEFORE INSERT ON users \
            FOR EACH ROW \
            BEGIN \
            DECLARE new_code VARCHAR(10); \
            DECLARE code_exists INT DEFAULT 1; \
            DECLARE attempts INT DEFAULT 0; \
            WHILE code_exists > 0 AND attempts < 20 DO \
            SET new_code = UPPER(SUBSTRING(MD5(RAND()), 1, 8)); \
            SELECT COUNT(*) INTO code_exists FROM users WHERE pRefCode = new_code; \
            SET attempts = attempts + 1; \
            END WHILE; \
            IF code_exists = 0 THEN \
           SET NEW.pRefCode = new_code; \
           ELSE \
           SET NEW.pRefCode = NULL; \
           END IF; \
        END");
        mysql_tquery(sql, "CREATE INDEX IF NOT EXISTS idx_pPer ON users (pPer)");
		mysql_tquery(sql, "SET GLOBAL event_scheduler = ON;");
    	mysql_tquery(sql, "CREATE EVENT IF NOT EXISTS delete_old_moneylog \
        	ON SCHEDULE EVERY 1 DAY STARTS CURRENT_TIMESTAMP \
        	DO DELETE FROM MoneyLog WHERE TimeLog < (NOW() - INTERVAL 3 MONTH);");
		mysql_tquery(sql, "CREATE EVENT IF NOT EXISTS delete_old_goldlog \
        	ON SCHEDULE EVERY 1 DAY STARTS CURRENT_TIMESTAMP \
        	DO DELETE FROM GoldLog WHERE TimeLog < (NOW() - INTERVAL 3 MONTH);");
        mysql_tquery(sql, "CREATE EVENT IF NOT EXISTS delete_old_accountloginlog \
            ON SCHEDULE EVERY 1 DAY STARTS CURRENT_TIMESTAMP \
            DO DELETE FROM AccountLoginLog WHERE LoginTime < (NOW() - INTERVAL 2 MONTH);");
		mysql_tquery(sql, "CREATE EVENT IF NOT EXISTS delete_expired_admin_codes \
    		ON SCHEDULE EVERY 5 MINUTE STARTS CURRENT_TIMESTAMP \
    		DO DELETE FROM AdminLogAccess WHERE ExpireAt < NOW();");
		mysql_tquery(sql, "CREATE EVENT IF NOT EXISTS delete_expired_Temporary_Ban \
    		ON SCHEDULE EVERY 1 MINUTE STARTS CURRENT_TIMESTAMP \
    		DO DELETE FROM Temporary_Ban WHERE ExpireAt < NOW();");
		mysql_tquery(sql, "UPDATE users SET pSaveSeq = 0 WHERE pSaveSeq > 0;");
	}return 1;
}stock bool:ParseQueryPIDToken(const query[], &pid, &token){
	new pos = strfind(query, "-- PID:");
	if(pos == -1) return false;
	new len = strlen(query);
	new start = pos + 7;
	if(start >= len) return false;
	new buf[12]; new i = 0;
	while(start < len && query[start] != ':' && i < 11) buf[i++] = query[start++];
	buf[i] = '\0';
	pid = strval(buf);
	token = 0;
	if(start < len && query[start] == ':'){
		start++;
		i = 0; new buf2[12];
		while(start < len && i < 11) buf2[i++] = query[start++];
		buf2[i] = '\0';
		token = strval(buf2);
	}return true;
}
#define KickForHardWare(%0) Skick(%0,"Vaghfeye zamaniye sakht afzari.","Hardware timeout.",TOKEN,true)
#define KickForKhata(%0) Skick(%0,"Khatayi rokh dad, teame scripter Ariana Game dar hale raf'e in moshkel hastand lotfan daghayeghi digar talash konid.","An error occurred, Our programming team is working to resolve the issue, please try again later.",TOKEN,true)
public OnQueryError(errorid, const error[], const callback[], const query[], MySQL:handle){
	SQLError(error);
	new LogsError[888];
	//Bedune token va id
	if(strcmp(callback, "UpdateDataCallbackDisconnect", true) == 0){
		format(LogsError, sizeof(LogsError), "UpdateDataDisconnect: %s", query);
		SQLLogError(LogsError);
		Querys--;
	}else if(strcmp(callback, "MoneyLogCallback", true) == 0){
		format(LogsError, sizeof(LogsError), "MoneyLog: %s", query);
		SQLLogError(LogsError);
		Querys--;
	}else if(strcmp(callback, "GoldLogCallback", true) == 0){
		format(LogsError, sizeof(LogsError), "GoldLog: %s", query);
		SQLLogError(LogsError);
		Querys--;
	}else if(strcmp(callback, "TempBanCallback", true) == 0){
		format(LogsError, sizeof(LogsError), "TempBans: %s", query);
		SQLLogError(LogsError);
		Querys--;
	}else if(strcmp(callback, "CodeLogCallback", true) == 0){
		format(LogsError, sizeof(LogsError), "Admin CodeLog: %s", query);
		SQLLogError(LogsError);
	}else if(strcmp(callback, "RefreshPermiumsTime", true) == 0){
		format(LogsError, sizeof(LogsError), "RefreshPremiumTimes: %s", query);
		SQLLogError(LogsError);
		Querys--;
	}else if(strcmp(callback,"AccountLoginLogCallback" , true) == 0){
		format(LogsError, sizeof(LogsError), "AccountLoginIp: %s", query);
		SQLLogError(LogsError);
		Querys--;
	}new ID, TOKEN;
	if(!ParseQueryPIDToken(query, ID, TOKEN)){
		return 1;
	}if(strcmp(callback, "UpdateDataCallback", true) == 0){
		format(LogsError, sizeof(LogsError), "UpdateData: %s", query);
		SQLLogError(LogsError);
		Querys--;
		CheckPlayerOnlineToCMD(ID);
		CheckPlayerTokenCmp(ID, TOKEN);
		KickForHardWare(ID);
	}else if(strcmp(callback, "CheckTempBan", true) == 0){
		format(LogsError, sizeof(LogsError), "TempBan: %s", query);
		SQLLogError(LogsError);
		CheckPlayerOnlineToCMD(ID);
		CheckPlayerTokenCmp(ID, TOKEN);
		KickForHardWare(ID);
	}else if(strcmp(callback, "GoldChanged", true) == 0){
		format(LogsError, sizeof(LogsError), "GiveGold: %s", query);
		SQLLogError(LogsError);
		Querys--;
		CheckPlayerOnlineToCMD(ID);
		CheckPlayerTokenCmp(ID, TOKEN);
		KickForHardWare(ID);
	}else if(strcmp(callback, "MoneyChanged", true) == 0){
		format(LogsError, sizeof(LogsError), "GiveMoney: %s", query);
		SQLLogError(LogsError);
		Querys--;
		CheckPlayerOnlineToCMD(ID);
		CheckPlayerTokenCmp(ID, TOKEN);
		KickForHardWare(ID);
	}else if(strcmp(callback, "CheckPremiums", true) == 0){
		format(LogsError, sizeof(LogsError), "CheckPremiums: %s", query);
		SQLLogError(LogsError);
		CheckPlayerOnlineToCMD(ID);
		CheckPlayerTokenCmp(ID, TOKEN);
		KickForHardWare(ID);
	}else if(strcmp(callback, "CheckPrem", true) == 0){
		format(LogsError, sizeof(LogsError), "CheckPrem: %s", query);
		SQLLogError(LogsError);
		CheckPlayerOnlineToCMD(ID);
		CheckPlayerTokenCmp(ID, TOKEN);
		KickForHardWare(ID);
	}else if(strcmp(callback, "CheckPremium", true) == 0){
		format(LogsError, sizeof(LogsError), "CheckPremium: %s", query);
		SQLLogError(LogsError);
		CheckPlayerOnlineToCMD(ID);
		CheckPlayerTokenCmp(ID, TOKEN);
		KickForHardWare(ID);
	}else if(strcmp(callback, "OnAccountCheck", true) == 0){
		format(LogsError, sizeof(LogsError), "OnAccountCheck: %s", query);
		SQLLogError(LogsError);
		CheckPlayerOnlineToCMD(ID);
		CheckPlayerTokenCmp(ID, TOKEN);
		KickForKhata(ID);
	}else if(strcmp(callback, "OnPlayerRegistered", true) == 0){
		format(LogsError, sizeof(LogsError), "OnPlayerRegistered: %s", query);
		SQLLogError(LogsError);
		Querys--;
		CheckPlayerOnlineToCMD(ID);
		CheckPlayerTokenCmp(ID, TOKEN);
		KickForKhata(ID);
	}else if(strcmp(callback, "QueryUpdateLastLoginBazikon", true) == 0){
		format(LogsError, sizeof(LogsError), "UpdateLastLohin: %s", query);
		SQLLogError(LogsError);
		Querys--;
	}else if(strcmp(callback, "SaveShod", true) == 0){
		format(LogsError, sizeof(LogsError), "SaveShod: %s", query);
		SQLLogError(LogsError);
		Querys--;
		CheckPlayerOnlineAndLogin(ID);
		CheckPlayerTokenCmp(ID, TOKEN);
		KickForKhata(ID);
	}return 1;
}forward QueryUpdateLastLoginBazikon(); public QueryUpdateLastLoginBazikon() return Querys--;
forward RefreshDataBase();
public RefreshDataBase(){
 	new query[60];
    mysql_format(sql, query, sizeof(query), "UPDATE users SET pPer = 0 WHERE pPer <= NOW()");
    mysql_pquery(sql, query, "RefreshPermiumsTime");
	Querys++;
	return 1;
}forward RefreshPermiumsTime(); public RefreshPermiumsTime() return Querys--;