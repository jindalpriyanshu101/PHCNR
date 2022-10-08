#define	SQL_FILE				"pizza.db"
#define MAX_DELIVERY			30
#define MAX_PIZZA				5
#define DIALOG_PIZZALIST		9871
#define DIALOG_DELIVERYLOCS		9872
#define	ONLY_PIZZABOY			true
#define PIZZA_MONEY				Player[playerid][PizzaPrize]
#define SCORE_BONUS				1
#define MAP_INDEX				5

#define Flag_Get(%0,%1)		((%0) & (%1))
#define Flag_On(%0,%1)		((%0) |= (%1))
#define Flag_Off(%0,%1)		((%0) &= ~(%1))

#define LOOP(%1) foreach(new %1 : Player)
#define SendMessage(%0,%1)	SendClientMessage(%0, 0x00FFFFFF, %1)

enum _P_F:(<<= 1)
{
	ON_MISSION = 1
}

enum D_E
{
	DelID,
	Float:DelX,
	Float:DelY,
	Float:DelZ,
	DelName[56],
	bool:DelActive
}

enum P_E
{
	PizzaID,
	Float:PizzaX,
	Float:PizzaY,
	Float:PizzaZ,
	PizzaPickup,
	Text3D:PizzaLabel,
	PizzaIcon,
	bool:PizzaActive
}

enum _P_E
{
	PizzaTime,
	DeliveryID,
	WaitingTime,
	PlayerPizzaPickup,
	Text3D:PlayerPizzaLabel,
	PizzaPrize,
	PizzaTimer
}

new 
	_P_F:PFlag[MAX_PLAYERS],
	Player[MAX_PLAYERS][_P_E],
	Delivery[MAX_DELIVERY][D_E],
	Pizza[MAX_PIZZA][P_E],
	PlayerText:DistanceTD[MAX_PLAYERS],
	PlayerText:TimeleftTD[MAX_PLAYERS],
	PlayerText:DeliveryTD[MAX_PLAYERS]
;

static 
	DB:SQL
;

LoadPizza()
{
	print("\n--------------------------------------");
	print("  	Pizza Job Filterscript by Lczy");
	print("--------------------------------------\n");
	if((SQL = db_open(SQL_FILE)) == DB:0)
	{
		print("Failed to open database file "SQL_FILE"");
		SendRconCommand("exit");
	}
	else
	{
		new	
			DBResult:res,
			str[56],
			i = 0
		;
			
		db_query(SQL, "CREATE TABLE IF NOT EXISTS `delivery_cp` ( \
						`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, \
						`x`	FLOAT, \
						`y`	FLOAT, \
						`z`	FLOAT, \
						`name`	TEXT \
		)");
		db_query(SQL, "CREATE TABLE IF NOT EXISTS `pizza_cp` ( \
						`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, \
						`x`	FLOAT, \
						`y`	FLOAT, \
						`z`	FLOAT \
		)");
		res = db_query(SQL, "SELECT * FROM `delivery_cp`");
		for(new j = db_num_rows(res); i < j; i++)
		{
			if(i > MAX_DELIVERY)
				break;
				
			db_get_field_assoc(res, "id", str, 56);
			Delivery[i][DelID] = strval(str);
			
			db_get_field_assoc(res, "x", str, 56);
			Delivery[i][DelX] = floatstr(str);
			
			db_get_field_assoc(res, "y", str, 56);
			Delivery[i][DelY] = floatstr(str);
			
			db_get_field_assoc(res, "z", str, 56);
			Delivery[i][DelZ] = floatstr(str);
			
			db_get_field_assoc(res, "name", str, 56);
			format(Delivery[i][DelName], 56, "%s", str);
			Delivery[i][DelActive] = true;
			
			
		}
		printf("Total pizza delivery location : %d", i);
		
		res = db_query(SQL, "SELECT * FROM `pizza_cp`"), i = 0;
		for(new j = db_num_rows(res); i < j; i++)
		{
			if(i > MAX_PIZZA)
				break;
				
			db_get_field_assoc(res, "id", str, 56);
			Pizza[i][PizzaID] = strval(str);
			
			db_get_field_assoc(res, "x", str, 56);
			Pizza[i][PizzaX] = floatstr(str);
			
			db_get_field_assoc(res, "y", str, 56);
			Pizza[i][PizzaY] = floatstr(str);
			
			db_get_field_assoc(res, "z", str, 56);
			Pizza[i][PizzaZ] = floatstr(str);
			Pizza[i][PizzaActive] = true;
			
			Pizza[i][PizzaPickup] = CreateDynamicPickup(1239, 1, Pizza[i][PizzaX], Pizza[i][PizzaY], Pizza[i][PizzaZ]);
			Pizza[i][PizzaLabel] = CreateDynamic3DTextLabel("{CD5C5C}[PIZZA-JOB]\n{FFFFFF}Type /pizza to start delivery", 0xFFFFFFFF, Pizza[i][PizzaX], Pizza[i][PizzaY], Pizza[i][PizzaZ] + 0.1, 15.0);
			Pizza[i][PizzaIcon] = CreateDynamicMapIcon(Pizza[i][PizzaX], Pizza[i][PizzaY], Pizza[i][PizzaZ], 29, 0);
		}
		printf("Total pizza job checkpoint : %d", i);
		db_free_result(res);
	}
	return 1;
}

GeneratePlayerTextdraw(playerid)
{
	DistanceTD[playerid] = CreatePlayerTextDraw(playerid, 326.800170, 370.000000, "~b~Distance : ~w~100");
	PlayerTextDrawLetterSize(playerid, DistanceTD[playerid], 0.463999, 2.020000);
	PlayerTextDrawAlignment(playerid, DistanceTD[playerid], 2);
	PlayerTextDrawColor(playerid, DistanceTD[playerid], -1);
	PlayerTextDrawSetShadow(playerid, DistanceTD[playerid], 1);
	PlayerTextDrawSetOutline(playerid, DistanceTD[playerid], 0);
	PlayerTextDrawBackgroundColor(playerid, DistanceTD[playerid], 255);
	PlayerTextDrawFont(playerid, DistanceTD[playerid], 1);
	PlayerTextDrawSetProportional(playerid, DistanceTD[playerid], 1);
	PlayerTextDrawSetShadow(playerid, DistanceTD[playerid], 1);

	DeliveryTD[playerid] = CreatePlayerTextDraw(playerid, 328.000000, 389.000000, "(Los Santos Stadium)");
	PlayerTextDrawLetterSize(playerid, DeliveryTD[playerid], 0.300000, 1.273332);
	PlayerTextDrawAlignment(playerid, DeliveryTD[playerid], 2);
	PlayerTextDrawColor(playerid, DeliveryTD[playerid], -1);
	PlayerTextDrawSetShadow(playerid, DeliveryTD[playerid], 0);
	PlayerTextDrawSetOutline(playerid, DeliveryTD[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, DeliveryTD[playerid], 255);
	PlayerTextDrawFont(playerid, DeliveryTD[playerid], 1);
	PlayerTextDrawSetProportional(playerid, DeliveryTD[playerid], 1);
	PlayerTextDrawSetShadow(playerid, DeliveryTD[playerid], 0);

	TimeleftTD[playerid] = CreatePlayerTextDraw(playerid, 326.000000, 350.400024, "100");
	PlayerTextDrawLetterSize(playerid, TimeleftTD[playerid], 0.524999, 2.281333);
	PlayerTextDrawAlignment(playerid, TimeleftTD[playerid], 2);
	PlayerTextDrawColor(playerid, TimeleftTD[playerid], -16776961);
	PlayerTextDrawSetShadow(playerid, TimeleftTD[playerid], 1);
	PlayerTextDrawSetOutline(playerid, TimeleftTD[playerid], 0);
	PlayerTextDrawBackgroundColor(playerid, TimeleftTD[playerid], 255);
	PlayerTextDrawFont(playerid, TimeleftTD[playerid], 3);
	PlayerTextDrawSetProportional(playerid, TimeleftTD[playerid], 1);
	PlayerTextDrawSetShadow(playerid, TimeleftTD[playerid], 1);
}

COMMAND:pizzalist(playerid, params[])
{
	if(!IsPlayerAdmin(playerid))
		return SendMessage(playerid, "Unauthorized Command!"), 1;
		
	new str[256];
	strcat(str, "ID\tX\tY\tZ\n");
	for(new i = 0; i < MAX_PIZZA; i++)
	{
		if(!Pizza[i][PizzaActive])
			continue;
			
		format(str, 256, "%s%d\t%f\t%f\t%f\n", str, Pizza[i][PizzaID], Pizza[i][PizzaX], Pizza[i][PizzaY], Pizza[i][PizzaZ]);
	}
	ShowPlayerDialog(playerid, DIALOG_PIZZALIST, DIALOG_STYLE_TABLIST_HEADERS, "Pizza Job Location", str, "Teleport", "Close");
	return 1;
}

COMMAND:deliverylocs(playerid, params[])
{
	if(!IsPlayerAdmin(playerid))
		return SendMessage(playerid, "Unauthorized Command!"), 1;
		
	new str[512];
	strcat(str, "ID\tName\tX\tY\tZ\n");
	for(new i = 0; i < MAX_DELIVERY; i++)
	{
		if(!Delivery[i][DelActive])
			continue;
			
		format(str, 512, "%s%d\t%s\t%f\t%f\t%f\n", str, Delivery[i][DelID], Delivery[i][DelName], Delivery[i][DelX], Delivery[i][DelY], Delivery[i][DelZ]);
	}
	ShowPlayerDialog(playerid, DIALOG_DELIVERYLOCS, DIALOG_STYLE_TABLIST_HEADERS, "Delivery Location", str, "Teleport", "Close");
	return 1;
}

COMMAND:createpizzajob(playerid, params[])
{
	if(!IsPlayerAdmin(playerid))
		return SendMessage(playerid, "Unauthorized Command!"), 1;
	
	if(GetPlayerInterior(playerid) != 0)
		return SendMessage(playerid, "You must be in outside to use this command!"), 1;
	
	new
		Float:x,
		Float:y,
		Float:z
	;
	GetPlayerPos(playerid, x, y, z);
	CreatePizzaJob(x, y, z) && SendMessage(playerid, "Pizza job succesfully created!") || SendMessage(playerid, "Failed to create pizza job!");
	return 1;
}

COMMAND:createdelivery(playerid, params[])
{
	if(!IsPlayerAdmin(playerid))
		return SendMessage(playerid, "Unauthorized Command!"), 1;
	
	if(GetPlayerInterior(playerid) != 0)
		return SendMessage(playerid, "You must be in outside to use this command!"), 1;
	
	new
		Float:x,
		Float:y,
		Float:z,
		s[56]
	;
	if(sscanf(params, "s[56]", s))
		return SendMessage(playerid, "Usage : createdelivery <location name>"), 1;
		
	GetPlayerPos(playerid, x, y, z);
	CreateDeliveryLocation(x, y, z, s) && SendMessage(playerid, "Delivery location succesfully added!") || SendMessage(playerid, "Failed to add delivery location!");
	return 1;
}

COMMAND:pizza(playerid, params[])
{	
	#if ONLY_PIZZABOY == true
	if(GetVehicleModel(GetPlayerVehicleID(playerid)) != 448)
		return SendMessage(playerid, "You must be in a pizzaboy to start pizza mission!"), 1;
	#else
	if(!IsPlayerInAnyVehicle(playerid))
		return SendMessage(playerid, "You must be in a vehicle to use this command!"), 1;
	#endif
	
	if(!GetFreeDeliveryID())
		return SendMessage(playerid, "Sorry, there's no location to deliver the pizza!");
	for(new i = 0; i < MAX_PIZZA; i++)
	{
		if(IsPlayerInRangeOfPoint(playerid, 5.0, Pizza[i][PizzaX], Pizza[i][PizzaY], Pizza[i][PizzaZ]))
		{
			StartPizzaMission(playerid) || SendMessage(playerid, "Deliver the pizza to start another mission!");
		}
	}
	return 1;
}

COMMAND:pizzacmds(playerid, params[])
{
	SendMessage(playerid, "Dynamic Pizza Job by Lczy!");
	SendMessage(playerid, "Pizza Command : /pizza (To start pizza mission), /pizzacmds");
	if(IsPlayerAdmin(playerid))
		SendMessage(playerid, "Admin Command : /pizzaboy, /createpizzajob, /createdelivery, /pizzalist, /deliverylocs");
	return 1;
}

COMMAND:pizzaboy(playerid, params[])
{
	if(!IsPlayerAdmin(playerid))
		return SendMessage(playerid, "Unauthorized Command!"), 1;
	
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);
	CreateVehicle(448, x, y, z, 0.0, -1, -1, 0);
	return 1;
}

GetFreePizzaID()
{
	for(new i = 0; i < MAX_PIZZA; i++)
	{
		if(Pizza[i][PizzaActive])
			continue;
			
		return i;
	}
	return -1;
}

GetFreeDeliveryID()
{
	for(new i = 0; i < MAX_DELIVERY; i++)
	{
		if(Delivery[i][DelActive])
			continue;
			
		return i;
	}
	return -1;
}

StopPizzaMission(playerid)
{
	Flag_Off(PFlag[playerid], ON_MISSION);
	
	KillTimer(Player[playerid][PizzaTimer]);
	
	if(IsValidDynamicPickup(Player[playerid][PlayerPizzaPickup]))
		DestroyDynamicPickup(Player[playerid][PlayerPizzaPickup]);
		
	if(IsValidDynamic3DTextLabel(Player[playerid][PlayerPizzaLabel]))
		DestroyDynamic3DTextLabel(Player[playerid][PlayerPizzaLabel]);
		
	PlayerTextDrawHide(playerid, DeliveryTD[playerid]);
	PlayerTextDrawHide(playerid, DistanceTD[playerid]);
	PlayerTextDrawHide(playerid, TimeleftTD[playerid]);
	RemovePlayerMapIcon(playerid, MAP_INDEX);
}

StartPizzaMission(playerid)
{
	if(!!Flag_Get(PFlag[playerid], ON_MISSION))
		return 0;
		
	if(IsValidDynamicPickup(Player[playerid][PlayerPizzaPickup]))
		DestroyDynamicPickup(Player[playerid][PlayerPizzaPickup]);
		
	if(IsValidDynamic3DTextLabel(Player[playerid][PlayerPizzaLabel]))
		DestroyDynamic3DTextLabel(Player[playerid][PlayerPizzaLabel]);
		
	new 
		i = random(GetFreeDeliveryID()),
		Float:dist = GetPlayerDistanceFromPoint(playerid, Delivery[i][DelX], Delivery[i][DelY], Delivery[i][DelZ])
	;
	Player[playerid][PlayerPizzaLabel] = CreateDynamic3DTextLabel("{CD5C5C}[LOCATION]", 0xFFFFFFFF, Delivery[i][DelX], Delivery[i][DelY], Delivery[i][DelZ], 15.0, .playerid = playerid);
	Player[playerid][PlayerPizzaPickup] = CreateDynamicPickup(1582, 14, Delivery[i][DelX], Delivery[i][DelY], Delivery[i][DelZ], .playerid = playerid);
	Player[playerid][DeliveryID] = i;
	Player[playerid][PizzaTime] = floatround((dist / 10) + 30);
	Player[playerid][PizzaPrize] = floatround(dist * 5);
	Player[playerid][WaitingTime] = 10;
	Player[playerid][PizzaTimer] = SetTimerEx("OnPizzaUpdate", 1000, true, "d", playerid);
	SetPlayerMapIcon(playerid, MAP_INDEX, Delivery[i][DelX], Delivery[i][DelY], Delivery[i][DelZ], 41, 0);
	
	new s[128];
	format(s, 128, "Deliver hot pizza to %s", Delivery[i][DelName]);
	SendMessage(playerid, s);
	PlayerTextDrawSetString(playerid, DeliveryTD[playerid], Delivery[i][DelName]);
	format(s, 128, "%0.2f", dist);
	PlayerTextDrawSetString(playerid, DistanceTD[playerid], s);
	format(s, 128, "%d", Player[playerid][PizzaTime]);
	PlayerTextDrawSetString(playerid, TimeleftTD[playerid], s);
	
	PlayerTextDrawShow(playerid, DeliveryTD[playerid]);
	PlayerTextDrawShow(playerid, DistanceTD[playerid]);
	PlayerTextDrawShow(playerid, TimeleftTD[playerid]);
	
	Flag_On(PFlag[playerid], ON_MISSION);
	return 1;
}

forward OnPizzaUpdate(playerid);
public OnPizzaUpdate(playerid)
{
	#if ONLY_PIZZABOY == true
	if(GetVehicleModel(GetPlayerVehicleID(playerid)) != 448)
	{
		new s[56];
		Player[playerid][WaitingTime]--;
		format(s, 128, "~b~Enter pizzaboy to complete pizza mission!\n~r~%d", Player[playerid][WaitingTime]);
		GameTextForPlayer(playerid, s, 1000, 4);
		if(Player[playerid][WaitingTime] <= 0)
		{
			GameTextForPlayer(playerid, "Pizza Mission Failed!", 5000, 0);
			StopPizzaMission(playerid);
		}
	}
	#else
	if(!IsPlayerInAnyVehicle(playerid))
	{
		new s[56];
		Player[playerid][WaitingTime]--;
		format(s, 128, "~b~Enter vehicle to complete pizza mission!\n~r~%d", Player[playerid][WaitingTime]);
		GameTextForPlayer(playerid, s, 1000, 4);
		if(Player[playerid][WaitingTime] <= 0)
		{
			GameTextForPlayer(playerid, "Pizza Mission Failed!", 5000, 0);
			StopPizzaMission(playerid);
		}
	}
	#endif
	Player[playerid][PizzaTime]--;
	if(Player[playerid][PizzaTime] <= 0)
	{
		GameTextForPlayer(playerid, "Pizza Mission Failed!", 5000, 0);
		StopPizzaMission(playerid);
	}
	new s[6];
	format(s, 6, "%d", Player[playerid][PizzaTime]);
	PlayerTextDrawSetString(playerid, TimeleftTD[playerid], s);
	return;
}

CreatePizzaJob(Float:x, Float:y, Float:z)
{
	new i = GetFreePizzaID();
	if(i == -1)
		return 0;

	new query[76];
	Pizza[i][PizzaX] = x;
	Pizza[i][PizzaY] = y;
	Pizza[i][PizzaZ] = z;
	Pizza[i][PizzaPickup] = CreateDynamicPickup(1239, 1, x, y, z);
	Pizza[i][PizzaLabel] = CreateDynamic3DTextLabel("{CD5C5C}[PIZZA-JOB]\n{FFFFFF}Type /pizza to start delivery", 0xFFFFFFFF, x, y, z + 0.1, 15.0);
	Pizza[i][PizzaIcon] = CreateDynamicMapIcon(x, y, z, 29, 0);
	Pizza[i][PizzaActive] = true;
	format(query, 76, "INSERT INTO `pizza_cp` VALUES(NULL, %f, %f, %f)", x, y, z);
	db_query(SQL, query);
	Pizza[i][PizzaID] = GetLastInsertID(SQL);
	return 1;
}

CreateDeliveryLocation(Float:x, Float:y, Float:z, name[])
{
	new i = GetFreeDeliveryID();
	if(i == -1)
		return 0;

	new query[156];
	Delivery[i][DelX] = x;
	Delivery[i][DelY] = y;
	Delivery[i][DelZ] = z;
	Delivery[i][DelActive] = true;
	format(Delivery[i][DelName], 56, "%s", name);
	format(query, 156, "INSERT INTO `delivery_cp` VALUES(NULL, %f, %f, %f, '%s')", x, y, z, name);
	db_query(SQL, query);
	Delivery[i][DelID] = GetLastInsertID(SQL);
	return 1;
}

public OnPlayerPickUpDynamicPickup(playerid, pickupid)
{
	if(pickupid == Player[playerid][PlayerPizzaPickup])
	{
		#if ONLY_PIZZABOY == true
		if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 448)
		#else
		if(IsPlayerInAnyVehicle(playerid))
		#endif
		{
			new 
				s[128],
				i = Player[playerid][DeliveryID]
			;
			GetPlayerName(playerid, s, MAX_PLAYER_NAME);
			format(s, 128, "Pizza Job : %s has delivered hot pizza to %s and earnt some money!", s, Delivery[i][DelName]);
			SendClientMessageToAll(0x00FFFFFF, s);
			GivePlayerMoney(playerid, PIZZA_MONEY);
			SetPlayerScore(playerid, GetPlayerScore(playerid) + SCORE_BONUS);
			StopPizzaMission(playerid);
		}
		else
		{
			SendMessage(playerid, "You must be in a vehicle to complete this mission!");
		}
	}
	return 1;
}