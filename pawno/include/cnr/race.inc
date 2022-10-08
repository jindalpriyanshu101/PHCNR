new Iterator:Racers<MAX_PLAYERS>;
ACMD:raceevent[4](playerid, params[])
{
	if(!RaceOpen)
	{
		new vmodel[64];
		if(sscanf(params, "s[64]", vmodel))
			return Usage(playerid, "raceevent [vehiclename]");

		new vid = GetVIDByName(vmodel);
		if(vid == -1)
			return Message(playerid, COLOR_RED, "Unknown vehicle name provided");

		DestroyDynamicRaceCP(FinishRace);
		foreach(new i : Player)
		{
			DestroyVehicle(pData[i][RaceCar]);
			pData[i][InsideRace] = false;
			pData[i][Event] = false;
			ShowNotification(i, "Race Event", "Type /joinrace to join race event");
		}
		Iter_Clear(Racers);
		MessageAll(-1, "{8AF56C}[RACE]{FFFFFF} Race event has been started, type {FF00FF}/joinrace{FFFFFF} to join event");
		Message(playerid, -1, "{58D3F7}[EVENT HELP] {FFFFFF}To start the event, first type /raceevent again to close entry, then type /startrace to unfreeze players");
		Message(playerid, -1, "{58D3F7}[EVENT HELP] {FFFFFF}When finished, please /destroyrace to free up vehicle space");
		RaceOpen = true;
		RaceVehicle = vid;
		RaceCurrent = 0;
		FinishRace = CreateDynamicRaceCP(1, 1551.4574,3956.7942,56.6390, 1551.4574,3956.7942,56.6390, 5, 184, -1, -1, 100.0);
	}
	else
	{
		MessageAll(-1, "{8AF56C}[RACE]{FFFFFF} Race event has been closed");
		RaceOpen = false;
	}
	return 1;
}

COMMAND:joinrace(playerid, params[])
{
	if(IsPlayerRestricted(playerid))
		return COMMAND_NO_SPECIAL;

	if(IsPlayerInJail(playerid))
		return COMMAND_NO_JAIL;

	if(!!GetPlayerWantedLevel(playerid))
		return Message(playerid, COLOR_RED, "You cannot join events if you have a wanted level");

	if(pData[playerid][InsideRace])
		return ShowNotification(playerid, "Race Event", "You already inside race event");

	if(RaceOpen)
	{
		SaveTemporaryStats(playerid);
		new row = floatround(RaceCurrent / 4), cell = RaceCurrent % 4, Float:devx = 1560.4835, Float:devy = 3984.4919;
		for(new i = 0; i < row; i++)
			devy += 8.0;
		for(new i = 0; i < cell; i++)
			devx -= 7.0;
		RaceCurrent++;
		DestroyVehicle(pData[playerid][RaceCar]);
		pData[playerid][RaceCar] = CreateVehicle(RaceVehicle, devx, devy, 56.3691 + 3.0, 0.1777, 0, 0, -1);
		SetVehicleNumberPlate(pData[playerid][RaceCar], "{FF0000}RACE");
		SetVehicleVirtualWorld(pData[playerid][RaceCar], 184);
		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 184);
		ResetPlayerWeapons(playerid);
		SetPlayerTeam(playerid, 1);
		ToggleEngine(pData[playerid][RaceCar], false);
		SetVehicleSpeed(pData[playerid][RaceCar], 0);
		PutPlayerInVehicle(playerid, pData[playerid][RaceCar], 0);
		GameTextForPlayer(playerid, "~r~THE EVENT WILL START SHORTLY!!!", 10000, 5);
		Message(playerid, -1, "{8AF56C}[RACE]{FFFFFF} You joined Race event, finish first to win the event");
		pData[playerid][InsideRace] = true;
		pData[playerid][Event] = true;
		Iter_Add(Racers, playerid);
	}
	else
		Message(playerid, COLOR_RED, "There's no Race event right now");
	return 1;
}

ACMD:destroyrace[4](playerid, params[])
{
	foreach(new i : Racers)
	{
		DestroyVehicle(pData[i][RaceCar]);
		pData[i][InsideRace] = false;
		pData[i][Event] = false;
		LoadTemporaryStats(playerid);
	}
	Iter_Clear(Racers);
	return 1;
}

ACMD:startrace[4](playerid, params[])
{
	foreach(new i : Racers)
	{
		TogglePlayerControllable(i, true);
		GameTextForPlayer(i, "Event Started!!!", 1000, 5);
		ToggleEngine(pData[i][RaceCar], true);
	}
	return 1;
}

ACMD:gotorace[4](playerid, params[])
{
	if(RaceOpen)
	{
		SetPlayerPos(playerid, 1542.2869,4058.5042,56.3661);
		SetPlayerVirtualWorld(playerid, 184);
		SetPlayerInterior(playerid, 0);
	}
	else
	    return Message(playerid, COLOR_RED, "There's no Race event right now");
	return 1;
}

FallenRaceMessage(playerid)
{
	new total = Iter_Count(Racers);
	MessageAll(COLOR_RED, "%p has fallen from the event! Players left: %d", playerid, total);
	if(!total)
	{
		MessageAll(COLOR_RED, "Race event finished, no one won on the event");
		Iter_Clear(Racers);
	}
	return 1;
}

public OnPlayerEnterDynamicRaceCP(playerid, checkpointid)
{
	if(checkpointid == FinishRace)
	{
		if(GetPlayerVehicleID(playerid) == pData[playerid][RaceCar])
		{
			DestroyDynamicRaceCP(FinishRace);
			foreach(new i : Racers)
			{
				DestroyVehicle(pData[i][RaceCar]);
				pData[i][InsideRace] = false;
				pData[i][Event] = false;
				LoadTemporaryStats(i);
			}
			Iter_Clear(Racers);
			MessageAll(COLOR_CYAN, "%p finished first, and won the race event!", playerid);
		}
	}
	#if defined Rc_OnPlayerEnterDynamicRaceCP
		return Rc_OnPlayerEnterDynamicRaceCP(playerid, checkpointid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerEnterDynamicRaceCP
	#undef OnPlayerEnterDynamicRaceCP
#else
	#define _ALS_OnPlayerEnterDynamicRaceCP
#endif
 
#define OnPlayerEnterDynamicRaceCP Rc_OnPlayerEnterDynamicRaceCP
#if defined Rc_OnPlayerEnterDynamicRaceCP
	forward Rc_OnPlayerEnterDynamicRaceCP(playerid, checkpointid);
#endif

public OnPlayerExitVehicle(playerid, vehicleid)
{
	if(pData[playerid][InsideRace])
	{
		pData[playerid][InsideRace] = false;
		pData[playerid][Event] = false;
		DestroyVehicle(pData[playerid][RaceCar]);
		Iter_Remove(Racers, playerid);
		FallenRaceMessage(playerid);
		LoadTemporaryStats(playerid);
	}
	#if defined Rc_OnPlayerExitVehicle
		return Rc_OnPlayerExitVehicle(playerid, vehicleid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerExitVehicle
	#undef OnPlayerExitVehicle
#else
	#define _ALS_OnPlayerExitVehicle
#endif
 
#define OnPlayerExitVehicle Rc_OnPlayerExitVehicle
#if defined Rc_OnPlayerExitVehicle
	forward Rc_OnPlayerExitVehicle(playerid, vehicleid);
#endif