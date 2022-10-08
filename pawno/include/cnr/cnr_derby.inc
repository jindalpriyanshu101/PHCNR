#define MAX_DERBY_POS 13
enum _derbyPos
{
	Float:derbyPos[3],
	DerbyCar
}

new Derby[MAX_DERBY_POS][_derbyPos] =
{
	{{467.421020, -3711.762939, 2.315244}},
	{{391.928283, -3691.387451, 2.317632}},
	{{358.083953, -3629.915527, 2.316626}},
	{{304.391204, -3661.461669, 2.316264}},
	{{402.880126, -3593.677001, 2.317783}},
	{{460.838012, -3605.954833, 2.339684}},
	{{503.423828, -3686.307617, 2.285591}},
	{{480.953369, -3625.396240, 2.315670}},
	{{501.349456, -3697.272949, 2.475157}},
	{{480.421020, -3709.662597, 2.325065}},
	{{397.188659, -3688.722412, 2.321398}},
	{{371.705230, -3705.748046, 2.262779}},
	{{356.873016, -3759.109863, 2.306581}}
},
Iterator:Derbys<MAX_DERBY_POS>;

COMMAND:derbyevent(playerid, params[])
{
	if(!DerbyOpen)
	{
		foreach(new i : Derbys)
		{
			if(IsValidVehicle(Derby[i][DerbyCar]))
				DestroyVehicle(Derby[i][DerbyCar]);
		}
		Iter_Clear(Derbys);
		foreach(new i : Player)
		{
			if(pData[i][InsideDerby])
			{
				pData[i][DerbyID] = -1;
				pData[i][InsideDerby] = false;
				pData[i][Event] = false;
			}

			ShowNotification(i, "Derby Event", "Type /joinderby to join derby event");
		}
		MessageAll(COLOR_CYAN, "[DERBY]{FFFFFF} Derby event has been started, type {FF00FF}/joinderby{FFFFFF} to join event");
		Message(playerid, -1, "{58D3F7}[EVENT HELP] {FFFFFF}To start the event, first type /derbyevent again to close entry, then type /startderby to unfreeze players");
		Message(playerid, -1, "{58D3F7}[EVENT HELP] {FFFFFF}When finished, please /destroyderby to free up vehicle space");
		DerbyOpen = true;
	}
	else
	{
		MessageAll(COLOR_CYAN, "{FF00FF}[DERBY]{FFFFFF} Derby event has been closed");
		DerbyOpen = false;
	}
	return 1;
}


COMMAND:joinderby(playerid, params[])
{
	if(IsPlayerRestricted(playerid))
		return COMMAND_NO_SPECIAL;

	if(IsPlayerInJail(playerid))
		return COMMAND_NO_JAIL;

	if(!!GetPlayerWantedLevel(playerid))
		return Message(playerid, COLOR_RED, "You cannot join events if you have a wanted level");

	if(DerbyOpen)
	{
		if(pData[playerid][InsideDerby])
			return ShowNotification(playerid, "Derby Event", "You already in derby event");

		new i = Iter_Free(Derbys);
		if(i == -1)
			return Message(playerid, COLOR_RED, "Derby event is full");

		if(IsValidVehicle(Derby[i][DerbyCar]))
			DestroyVehicle(Derby[i][DerbyCar]);
		Derby[i][DerbyCar] = CreateVehicle(556, Derby[i][derbyPos][0], Derby[i][derbyPos][1], Derby[i][derbyPos][2] + 3.0, 0.0, 0, 0, 120);

		SaveTemporaryStats(playerid);
		SetVehicleNumberPlate(Derby[i][DerbyCar], "EVENT");
		SetVehicleVirtualWorld(Derby[i][DerbyCar], 182);
		SetVehiclePos(Derby[i][DerbyCar], Derby[i][derbyPos][0], Derby[i][derbyPos][1], Derby[i][derbyPos][2] + 3.0);
		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 182);
		SetPlayerHealth(playerid, 100.0);
		ResetPlayerWeapons(playerid);
		SetPlayerTeam(playerid, 1);
		TogglePlayerControllable(playerid, true);
		PutPlayerInVehicle(playerid, Derby[i][DerbyCar], 0);
		SetVehicleSpeed(Derby[i][DerbyCar], 0);
		ToggleEngine(Derby[i][DerbyCar], false);
		GameTextForPlayer(playerid, "~r~THE EVENT WILL START SHORTLY!!!", 10000, 5);
		Message(playerid, COLOR_CYAN, "INFO: You joined derby event, push opponent cars into the water to won the event");
		pData[playerid][DerbyID] = i;
		pData[playerid][InsideDerby] = true;
		pData[playerid][Event] = true;
		Iter_Add(Derbys, i);
	}
	else
		Message(playerid, COLOR_RED, "There's no derby event right now");
	return 1;
}

ACMD:destroyderby[4](playerid, params[])
{
	foreach(new i : Derbys)
	{
		DestroyVehicle(Derby[i][DerbyCar]);
	}
	Iter_Clear(Derbys);
	foreach(new i : Player)
	{
		if(pData[i][InsideDerby])
		{
			pData[i][DerbyID] = -1;
			pData[i][InsideDerby] = false;
			pData[i][Event] = false;
		}
	}
	return 1;
}

ACMD:startderby[4](playerid, params[])
{
	foreach(new i : Derbys)
	{
		ToggleEngine(Derby[i][DerbyCar], true);
	}
	foreach(new i : Player)
	{
		if(pData[i][InsideDerby])
		{
			GameTextForPlayer(i, "Event Started!!!", 1000, 5);
		}
	}
	return 1;
}

ACMD:watchderby[4](playerid, params[])
{
	if(pData[playerid][Event])
		return COMMAND_NO_EVENT;

	if(!PFlag(Spectating))
	{
		SaveTemporaryStats(playerid);
	}
	// TogglePlayerSpectating(playerid, true);
	PFlag_On(Spectating);
	pData[playerid][SpectatingDerby] = true;
	pData[playerid][CurrentCam] = 1;
	SetPlayerCameraPos(playerid, 553.2625, -3686.8384, 44.1893);
	SetPlayerCameraLookAt(playerid, 552.2645, -3686.8342, 43.7443);
	SetPlayerVirtualWorld(playerid, 182);
	SetPlayerInterior(playerid, 0);
	Message(playerid, COLOR_YELLOW, "Press left click to change camera position, use /specoff to stop spectating event");
	return 1;
}

public OnPlayerUpdate(playerid)
{
	if(pData[playerid][InsideDerby] || pData[playerid][InsideFallout])
	{
		new Float:x, Float:y, Float:z;
		GetPlayerPos(playerid, x, y, z);
		if(z < 0.0 && pData[playerid][InsideDerby])
		{
			pData[playerid][InsideDerby] = false;
			pData[playerid][Event] = false;
			new i = pData[playerid][DerbyID];
			Iter_Remove(Derbys, i);
			DestroyVehicle(Derby[i][DerbyCar]);
			pData[playerid][DerbyID] = -1;
			FallenDerbyMessage(playerid);
			LoadTemporaryStats(playerid);
		}
		else if(z < 50.0 && pData[playerid][InsideFallout])
		{
			pData[playerid][InsideFallout] = false;
			pData[playerid][Event] = false;
			Iter_Remove(FallPlayers, playerid);
			FallenFalloutMessage(playerid);
			LoadTemporaryStats(playerid);
		}
		else if(z < 50.0 && pData[playerid][InsideGlass])
		{
			pData[playerid][InsideGlass] = false;
			pData[playerid][Event] = false;
			pData[playerid][AdminWeapon] = false;
			Iter_Remove(Glasses, playerid);
			FallenGlassMessage(playerid);
			LoadTemporaryStats(playerid);
		}
	}
	#if defined Dr_OnPlayerUpdate
		return Dr_OnPlayerUpdate(playerid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerUpdate
	#undef OnPlayerUpdate
#else
	#define _ALS_OnPlayerUpdate
#endif
 
#define OnPlayerUpdate Dr_OnPlayerUpdate
#if defined Dr_OnPlayerUpdate
	forward Dr_OnPlayerUpdate(playerid);
#endif

public OnPlayerDisconnect(playerid, reason)
{
	if(pData[playerid][InsideDerby])
	{
		pData[playerid][InsideDerby] = false;
		pData[playerid][Event] = false;
		new i = pData[playerid][DerbyID];
		Iter_Remove(Derbys, i);
		DestroyVehicle(Derby[i][DerbyCar]);
		FallenDerbyMessage(playerid);
	}
	else if(pData[playerid][InsideFallout])
	{
		pData[playerid][InsideFallout] = false;
		pData[playerid][Event] = false;
		Iter_Remove(FallPlayers, playerid);
		FallenFalloutMessage(playerid);
	}
	else if(pData[playerid][InsideCVR])
	{
		pData[playerid][InsideCVR] = false;
		pData[playerid][Event] = false;
		new t = GetPlayerTeam(playerid);
		if(t == 1)
			Iter_Remove(CopTeam, playerid);
		else
			Iter_Remove(TerroristTeam, playerid);
		FallenCVRMessage(playerid, t);
	}
	else if(pData[playerid][InsideDM])
	{
		pData[playerid][InsideDM] = false;
		pData[playerid][Event] = false;
		Iter_Remove(DMs, playerid);
		FallenDMMessage(playerid);
	}
	else if(pData[playerid][InsideFFA])
	{
		pData[playerid][InsideFFA] = false;
		pData[playerid][Event] = false;
		Iter_Remove(DMs, playerid);
		FallenDMMessage(playerid);
	}
	else if(pData[playerid][InsideGlass])
	{
		pData[playerid][InsideGlass] = false;
		pData[playerid][Event] = false;
		Iter_Remove(Glasses, playerid);
		FallenGlassMessage(playerid);
	}
	else if(pData[playerid][InsideRace])
	{
		pData[playerid][InsideRace] = false;
		pData[playerid][Event] = false;
		DestroyVehicle(pData[playerid][RaceCar]);
		Iter_Remove(Racers, playerid);
		FallenRaceMessage(playerid);
	}
	else if(pData[playerid][InsideDuel])
	{
		pData[playerid][Event] = false;
	}
	#if defined Dr_OnPlayerDisconnect
		return Dr_OnPlayerDisconnect(playerid, reason);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
 
#define OnPlayerDisconnect Dr_OnPlayerDisconnect
#if defined Dr_OnPlayerDisconnect
	forward Dr_OnPlayerDisconnect(playerid, reason);
#endif

public OnPlayerDeath(playerid, killerid, reason)
{
	if(pData[playerid][InsideDerby])
	{
		pData[playerid][Event] = false;
		new i = pData[playerid][DerbyID];
		Iter_Remove(Derbys, i);
		pData[playerid][DerbyID] = -1;
		DestroyVehicle(Derby[i][DerbyCar]);
		FallenDerbyMessage(playerid);
		return 1;
	}
	else if(pData[playerid][InsideFallout])
	{
		pData[playerid][Event] = false;
		Iter_Remove(FallPlayers, playerid);
		FallenFalloutMessage(playerid);
		return 1;
	}
	else if(pData[playerid][InsideCVR])
	{
		pData[playerid][Event] = false;
		pData[playerid][AdminWeapon] = false;
		new t = GetPlayerTeam(playerid);
		if(t == 1)
			Iter_Remove(CopTeam, playerid);
		else
			Iter_Remove(TerroristTeam, playerid);
		FallenCVRMessage(playerid, t);
		return 1;
	}
	else if(pData[playerid][InsideDM])
	{
		pData[playerid][Event] = false;
		pData[playerid][AdminWeapon] = false;
		Iter_Remove(DMs, playerid);
		FallenDMMessage(playerid);
		return 1;
	}
	else if(pData[playerid][InsideFFA])
	{
		pData[playerid][Event] = false;
		pData[playerid][AdminWeapon] = false;
		Iter_Remove(FFAs, playerid);
		FallenFFAMessage(playerid);
		return 1;
	}

	else if(pData[playerid][InsideGlass])
	{
		pData[playerid][Event] = false;
		pData[playerid][AdminWeapon] = false;
		Iter_Remove(Glasses, playerid);
		FallenGlassMessage(playerid);
		return 1;
	}
	else if(pData[playerid][InsideRace])
	{
		pData[playerid][Event] = false;
		DestroyVehicle(pData[playerid][RaceCar]);
		Iter_Remove(Racers, playerid);
		FallenRaceMessage(playerid);
		return 1;
	}
	else if(pData[playerid][InsideDuel])
	{
		FallenDuelMessage(playerid, killerid);
		return 1;
	}
	#if defined Dr_OnPlayerDeath
		return Dr_OnPlayerDeath(playerid, killerid, reason);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerDeath
	#undef OnPlayerDeath
#else
	#define _ALS_OnPlayerDeath
#endif
 
#define OnPlayerDeath Dr_OnPlayerDeath
#if defined Dr_OnPlayerDeath
	forward Dr_OnPlayerDeath(playerid, killerid, reason);
#endif

public OnPlayerSpawn(playerid)
{
	if(pData[playerid][InsideDerby] || pData[playerid][InsideFallout] || pData[playerid][InsideCVR] || pData[playerid][InsideDM] || pData[playerid][InsideFFA] || pData[playerid][InsideGlass] || pData[playerid][InsideRace] || pData[playerid][InsideDuel])
	{
		pData[playerid][InsideDerby] = false;
		pData[playerid][InsideCVR] = false;
		pData[playerid][InsideDM] = false;
		pData[playerid][InsideFallout] = false;
		pData[playerid][InsideFFA] = false;
		pData[playerid][InsideGlass] = false;
		pData[playerid][InsideRace] = false;
		pData[playerid][InsideDuel] = false;
		pData[playerid][Event] = false;
		LoadTemporaryStats(playerid);
		return 1;
	}
	#if defined Dr_OnPlayerSpawn
		return Dr_OnPlayerSpawn(playerid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerSpawn
	#undef OnPlayerSpawn
#else
	#define _ALS_OnPlayerSpawn
#endif
 
#define OnPlayerSpawn Dr_OnPlayerSpawn
#if defined Dr_OnPlayerSpawn
	forward Dr_OnPlayerSpawn(playerid);
#endif

FallenDerbyMessage(playerid)
{
	new total = Iter_Count(Derbys);
	if(total)
		MessageAll(COLOR_RED, "%p has fallen from the event! Players left: %d", playerid, total);
	if(total == 1)
	{
		foreach(new i : Derbys)
		{
			foreach(new p : Player)
			{
				if(pData[p][DerbyID] == i)
				{
					MessageAll(COLOR_CYAN, "%p has won the derby event!", p);
					LoadTemporaryStats(p);
				}
				pData[p][DerbyID] = -1;
				pData[p][InsideDerby] = false;
				pData[p][Event] = false;
			}
			DestroyVehicle(Derby[i][DerbyCar]);
		}
		Iter_Clear(Derbys);
	}
	return 1;
}
