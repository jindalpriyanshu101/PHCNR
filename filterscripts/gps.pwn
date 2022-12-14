#include <a_samp>
#include <a_sampdb>

#define dcmd(%1,%2,%3) if ((strcmp((%3)[1], #%1, true, (%2)) == 0) && ((((%3)[(%2) + 1] == 0) && (dcmd_%1(playerid, "")))||(((%3)[(%2) + 1] == 32) && (dcmd_%1(playerid, (%3)[(%2) + 2]))))) return 1

#define GPSFile ("dbs/Positions.db")
#define MAX_LOCATIONS 50 
#define GPSDialogID 1111
enum FGPS
{
	ID,
	Float: LocationX,
	Float: LocationY,
	Float: LocationZ,
	PlaceName[128]
};

new GPSInfo[MAX_LOCATIONS][FGPS];
new DB:GPSDB;
new gValue[128];
new GPSObject[MAX_PLAYERS];
new GlobalGpsTimer;

stock Float:PointAngle(playerid, Float:xa, Float:ya, Float:xb, Float:yb)
{
	new Float:carangle;
	new Float:xc, Float:yc;
	new Float:angle;
	xc = floatabs(floatsub(xa,xb));
	yc = floatabs(floatsub(ya,yb));
	if (yc == 0.0 || xc == 0.0)
	{
		if(yc == 0 && xc > 0) angle = 0.0;
		else if(yc == 0 && xc < 0) angle = 180.0;
		else if(yc > 0 && xc == 0) angle = 90.0;
		else if(yc < 0 && xc == 0) angle = 270.0;
		else if(yc == 0 && xc == 0) angle = 0.0;
	}
	else
	{
		angle = atan(xc/yc);
		if(xb > xa && yb <= ya) angle += 90.0;
		else if(xb <= xa && yb < ya) angle = floatsub(90.0, angle);
		else if(xb < xa && yb >= ya) angle -= 90.0;
		else if(xb >= xa && yb > ya) angle = floatsub(270.0, angle);
	}
	GetVehicleZAngle(GetPlayerVehicleID(playerid), carangle);
	return floatadd(angle, -carangle);
}

stock fcreate(filename[])
{
    if (fexist(filename)){return false;}
    new File:fhandle = fopen(filename,io_write);
    fclose(fhandle);
    return true;
}

stock Float:GetDistanceBetweenPoints(Float:X, Float:Y, Float:Z, Float:PointX, Float:PointY, Float:PointZ)
{
	new Float:Distance;Distance = floatabs(floatsub(X, PointX)) + floatabs(floatsub(Y, PointY)) + floatabs(floatsub(Z, PointZ));
	return Distance;
}

public OnFilterScriptInit()
{
	print("\n--------------------------------------");
	print("GPS System Loaded");
	if(!fexist(GPSFile))
	{
		fcreate(GPSFile);
		printf("Files are creating, mate.", GPSFile);
	}
	GPSDB = db_open(GPSFile);
	LoadFGPS();
	// Start the gpstimer (to check if players have reached their destination
	GlobalGpsTimer = SetTimer("GpsTimer", 1000, true);
	return 1;
}

forward GpsTimer();
public GpsTimer()
{
	// Setup local variables
	new playerid, Float:x, Float:y, Float:z;

	// Loop through all players
	for (playerid = 0; playerid < MAX_PLAYERS; playerid++)
	{
		// Check if this player is connected
		if (IsPlayerConnected(playerid))
		{
			// Check if this player started his gps command
		    if (GetPVarInt(playerid,"YEAH") == 1)
			{
			    // Get the coordinates
			    x = GetPVarFloat(playerid, "Spongebob");
			    y = GetPVarFloat(playerid, "Mario");
			    z = GetPVarFloat(playerid, "SpiderPig");

				// Check if the player has reached his destination
				if (IsPlayerInRangeOfPoint(playerid, 10.0, x, y, z))
				{
			   		DestroyObject(GPSObject[playerid]);
			   		SetPVarInt(playerid,"YEAH",0);
			   		DeletePVar(playerid,"Spongebob");
			   		DeletePVar(playerid,"Mario");
			   		DeletePVar(playerid,"SpiderPig");
			   		DeletePVar(playerid,"FAIL");

                    SendClientMessage(playerid, 0xFFFFFFFF, "{B7B7B7}[GPS] {FFFFFF}You have reached your destination.");
				}
			}
		}
	}

    return 1;
}
public OnFilterScriptExit()
{
    db_close(GPSDB);
	print("\n--------------------------------------");
	print("GPS System Unloaded..");
    print("\n--------------------------------------");
	return 1;
}

public OnPlayerCommandText(playerid, cmdtext[])
{
    dcmd(turnoff,7,cmdtext);  
    dcmd(gps,3,cmdtext);     
    dcmd(fsave,5,cmdtext);   
    dcmd(fedit,5,cmdtext);    
	return 0;
}

dcmd_gps(playerid, params[])
{
    #pragma unused params
    if(!IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, 0xE60000FF, "{B7B7B7}[GPS] {FFFFFF}You must be in a vehicle to use the gps.");
    if(GetPVarInt(playerid,"YEAH") == 1) return SendClientMessage(playerid, 0xE60000FF, "{B7B7B7}[GPS] {FFFFFF}Use /turnoff to disable your current route.");
	new string[128], var[2048];
	for(new g = 0; g < sizeof(GPSInfo); g++)
 	{
 		format(string, 128, "%s\n", GPSInfo[g][PlaceName]);
 		strcat(var,string);
 	}
  if(!strlen(GPSInfo[0][PlaceName])) return SendClientMessage(playerid, 0xE60000FF, "{B7B7B7}[GPS] {FFFFFF}There's no locations available.");
 	ShowPlayerDialog(playerid, GPSDialogID, DIALOG_STYLE_LIST, "GPS", var, "OK", "Close");
	return 1;
}

dcmd_turnoff(playerid, params[])
{
    #pragma unused params

    if(GetPVarInt(playerid, "YEAH") == 0)
    {
		SendClientMessage(playerid, 0xFFFFFFFF, "{B7B7B7}[GPS] {FFFFFF}Your GPS is not enabled.");
	}

   	DestroyObject(GPSObject[playerid]);
   	SetPVarInt(playerid, "YEAH", 0);
   	DeletePVar(playerid, "Spongebob");
   	DeletePVar(playerid, "Mario");
   	DeletePVar(playerid, "SpiderPig");
   	DeletePVar(playerid, "FAIL");

   	SendClientMessage(playerid, 0xFFFFFFFF, "Your GPS is now disabled!");

	return 1;
}

dcmd_fsave(playerid, params[])
{
    if(!IsPlayerAdmin(playerid)) return SendClientMessage(playerid, 0xE60000FF, "{B7B7B7}[SERVER] {FFFFFF}You don't have permission to use this command.");
	new Float:PPos[3], string[128], query[256];
  	GetPlayerPos(playerid, PPos[0], PPos[1], PPos[2]);
    if(!strlen(params)) return SendClientMessage(playerid, 0xE60000FF, "{FFFFFF}Usage: /fsave [LOCATION]");
    GetLastID();
   	new NewID = strval(gValue);
	format(query, sizeof(query), "INSERT INTO `FGPSSystem` (`ID`,`LocationX`,`LocationY`,`LocationZ`, `Name`) VALUES('%d','%f','%f','%f','%s');",NewID,PPos[0],PPos[1],PPos[2],params);
	db_query(GPSDB,query);
	ReloadDatabase();
	format(string,sizeof(string),"{B7B7B7}[SERVER] {FFFFFF}You have set: {00FF33}%s's{FFFFFF} location in the GPS.", params);
	SendClientMessage(playerid, 0xFFFFFFFF, string);
	return 1;
}

dcmd_fedit(playerid, params[])
{
    if(!IsPlayerAdmin(playerid)) return SendClientMessage(playerid, 0xE60000FF, "{B7B7B7}[SERVER] {FFFFFF}You don't have permission to use this command.");
	new string[128], query[256], tmp[2][128];
    if(!strlen(params)) return SendClientMessage(playerid, 0xE60000FF, "Usage: /fsave [OLD_LOCATION] [NEW_LOCATION]");
    split(params, tmp, ',');
	format(query, sizeof(query), "UPDATE `FGPSSystem` SET `Name` = '%s' WHERE `Name` = '%s'",tmp[1],tmp[0]);
	db_query(GPSDB,query);
	ReloadDatabase();
	format(string,sizeof(string),"{B7B7B7}[SERVER] {FFFFFF}You have edited: {00FF33}%s {FFFFFF}to {00FF33}%s", tmp[0],tmp[1]);
	SendClientMessage(playerid, 0xFFFFFFFF, string);
	return 1;
}

public OnPlayerUpdate(playerid)
{
	if(GetPVarInt(playerid,"YEAH") == 1)
	{
		new
			Float:VPos[3],
			Float:Rotation
		;

 		GetVehiclePos(GetPlayerVehicleID(playerid), VPos[0], VPos[1], VPos[2]);
 		Rotation = PointAngle(playerid, VPos[0], VPos[1], GetPVarFloat(playerid, "Spongebob"), GetPVarFloat(playerid, "Mario"));
		AttachObjectToVehicle(GPSObject[playerid], GetPlayerVehicleID(playerid), 0.0, 0.0, 1.5, 0.0, 90.0, Rotation);
	}
    return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
	if(GetPVarInt(playerid, "YEAH") == 1)
	{
    	DestroyObject(GPSObject[playerid]);
    	SetPVarInt(playerid, "YEAH",0);
    	DeletePVar(playerid, "Spongebob");
    	DeletePVar(playerid, "Mario");
    	DeletePVar(playerid, "SpiderPig");
    	DeletePVar(playerid, "FAIL");
	}

    return 1;
}

stock LoadFGPS()
{
	new query[256], DBResult:qresult, count = 0, value[128];
	if(!db_query(DB: GPSDB, "SELECT * FROM `FGPSSystem`"))
	{
		print("??????? ?? ???????... ???????? ???????!");
		format(query,sizeof(query),"CREATE TABLE IF NOT EXISTS `FGPSSystem` (`ID`, `LocationX`, `LocationY`, `LocationZ`, `Name`)");
	 	db_query(GPSDB,query);
		print("GPS System Loaded...");
		print("--------------------------------------\n");
		SendRconCommand("exit");
	}
	else
	{
		qresult = db_query(GPSDB,  "SELECT * FROM `FGPSSystem`");
		count = db_num_rows(qresult);
		for(new a=0;a<count;a++)
		{
			if(count >= 1 && count <= MAX_LOCATIONS)
			{
		    	db_get_field_assoc(qresult, "ID", value, 5);	 			GPSInfo[a][ID] = strval(value);
				db_get_field_assoc(qresult, "LocationX", value, 20);	 	GPSInfo[a][LocationX] = floatstr(value);
				db_get_field_assoc(qresult, "LocationY", value, 20);	 	GPSInfo[a][LocationY] = floatstr(value);
				db_get_field_assoc(qresult, "LocationZ", value, 20); 	 	GPSInfo[a][LocationZ] = floatstr(value);
				db_get_field(qresult,4,value,128);                          strmid(GPSInfo[a][PlaceName], value, 0, strlen(value), 128);
				printf("%d, %f, %f, %f, %s", GPSInfo[a][ID],GPSInfo[a][LocationX],GPSInfo[a][LocationY],GPSInfo[a][LocationZ],GPSInfo[a][PlaceName]);
				db_next_row(qresult);
			}
		}
		db_free_result(qresult);
		print("GPS System Loaded...");
		print("--------------------------------------\n");
	}
	return 1;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    if(dialogid == GPSDialogID && response)
    {
        GetPlayerLocationFromId(playerid, listitem);
        return 1;
    }
    return 0;
}

stock GetPlayerLocationFromId(playerid, id)
{
	new
		Query[128],
		DBResult:qresult,
		string[128],
		string2[128],
		NameStore[128]
	;

	format(Query, sizeof(Query), "SELECT `LocationX`, `LocationY`, `LocationZ`, `Name` FROM `FGPSSystem` WHERE ID = '%d'", id);
	qresult = db_query(GPSDB, Query);

	db_get_field_assoc(qresult, "LocationX", string,128);		SetPVarFloat(playerid, "Spongebob", floatstr(string));
	db_get_field_assoc(qresult, "LocationY", string,128);		SetPVarFloat(playerid, "Mario", floatstr(string));
	db_get_field_assoc(qresult, "LocationZ", string,128);		SetPVarFloat(playerid, "SpiderPig", floatstr(string));
	db_get_field_assoc(qresult, "Name", string,128);			SetPVarString(playerid, "FAIL", string);

	GetPVarString(playerid, "FAIL", NameStore, 128);
	format(string2,sizeof(string2),"{B7B7B7}[GPS] {FFFFFF}Follow the arrow to reach {FFDC2E}%s", NameStore);

	SendClientMessage(playerid, 0xFFFFFFFF, string2);

 	GPSObject[playerid] = CreateObject(1318, 0, 0, 0, 0.0, 0.0, 0);
  	SetPVarInt(playerid, "YEAH", 1);
	db_free_result(qresult);

	return 1;
}

stock ReloadDatabase()
{
    new DBResult:qresult, count = 0, value[128];
	qresult = db_query(GPSDB, "SELECT * FROM `FGPSSystem`");
	count = db_num_rows(qresult);
	for(new a=0;a<count;a++)
	{
		if(count >= 1 && count <= MAX_LOCATIONS)
		{
 			db_get_field_assoc(qresult, "ID", value, 5);	 			GPSInfo[a][ID] = strval(value);
			db_get_field_assoc(qresult, "LocationX", value, 20);	 	GPSInfo[a][LocationX] = floatstr(value);
			db_get_field_assoc(qresult, "LocationY", value, 20);	 	GPSInfo[a][LocationY] = floatstr(value);
			db_get_field_assoc(qresult, "LocationZ", value, 20); 	 	GPSInfo[a][LocationZ] = floatstr(value);
			db_get_field(qresult,4,value,128);                          strmid(GPSInfo[a][PlaceName], value, 0, strlen(value), 128);
			db_next_row(qresult);
		}
	}
	db_free_result(qresult);
	return 1;
}

stock GetLastID()
{
    new DBResult:qresult, count = 0, Value[128];
	qresult = db_query(GPSDB, "SELECT * FROM `FGPSSystem` ORDER BY `ID` DESC LIMIT 1");
	count = db_num_rows(qresult);

	for(new a=0;a<count;a++)
	{
		if(count <= MAX_LOCATIONS)
		{
 			db_get_field_assoc(qresult, "ID", Value, 5);	gValue[a] = Value[a]+1;
			db_next_row(qresult);
		}
	}

	db_free_result(qresult);
	return 1;
}

public OnPlayerStateChange(playerid,newstate,oldstate)
{
    if(GetPVarInt(playerid,"YEAH") == 1)
	{
		if(newstate == PLAYER_STATE_ONFOOT && oldstate == PLAYER_STATE_DRIVER)
		{
	   		DestroyObject(GPSObject[playerid]);
	   		SetPVarInt(playerid, "YEAH",0);
	   		DeletePVar(playerid, "Spongebob");
	   		DeletePVar(playerid, "Mario");
	   		DeletePVar(playerid, "SpiderPig");
	   		DeletePVar(playerid, "FAIL");
		}
	}

    return 1;
}

stock split(const strsrc[], strdest[][], delimiter)
{
    new i, li;
    new aNum;
    new len;
    while(i <= strlen(strsrc))
    {
        if(strsrc[i] == delimiter || i == strlen(strsrc))
        {
            len = strmid(strdest[aNum], strsrc, li, i, 128);
            strdest[aNum][len] = 0;
            li = i+1;
            aNum++;
        }
        i++;
    }
    return 1;
}

public OnPlayerDisconnect(playerid)
{
    if(GetPVarInt(playerid,"YEAH") == 1)
	{
   		DestroyObject(GPSObject[playerid]);
   		SetPVarInt(playerid, "YEAH",0);
   		DeletePVar(playerid, "Spongebob");
   		DeletePVar(playerid, "Mario");
   		DeletePVar(playerid, "SpiderPig");
   		DeletePVar(playerid, "FAIL");
	}

	return 1;
}

public OnPlayerExitVehicle(playerid, vehicleid)
{
    if(GetPVarInt(playerid,"YEAH") == 1)
	{
   		DestroyObject(GPSObject[playerid]);
   		SetPVarInt(playerid, "YEAH",0);
   		DeletePVar(playerid, "Spongebob");
   		DeletePVar(playerid, "Mario");
   		DeletePVar(playerid, "SpiderPig");
   		DeletePVar(playerid, "FAIL");
	}

	return 1;
}
