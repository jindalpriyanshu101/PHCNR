COMMAND:raceevent(playerid, params[])
{
	new msg[512];
	if(playerData[playerid][playerLoggedIn])
	{
		if(playerData[playerid][playerLevel] >= 4)
		{
			if(!serverInfo[race1open])
			{
				foreach(new i : Player)
				{
					if(IsValidVehicle(playerData[i][RaceCar]))
						DestroyVehicle(playerData[i][RaceCar]);
					if(playerData[i][onRace1])
						playerData[i][onRace1] = false;
				}
				if (!serverInfo[race1open])
				{
					if(IsValidDynamicRaceCP(FINISH))
						DestroyDynamicRaceCP(FINISH);

					format(msg, sizeof(msg), "{8AF56C}[RACE]{FFFFFF} Race event has been started, type {FF00FF}/joinrace{FFFFFF} to join event.");
					SendClientMessageToAll(COLOR_WHITE, msg);
					serverInfo[race1open] = true;
					FINISH = CreateDynamicRaceCP(1, 1551.4574,3956.7942,56.6390, 1551.4574,3956.7942,56.6390, 5, 184, -1, -1, 100.0);
					RaceCurrent = 0;

					for(new i=0; i<MAX_PLAYERS; i++)
					{
						GameTextForPlayer(i, "RACE EVENT OPENED!", 5000, 5);
					}
				}
			}
			else
			{
				format(msg, sizeof(msg), "{8AF56C}[RACE]{FFFFFF} Race event has been closed.");
				SendClientMessageToAll(0xffffff, msg);
				serverInfo[race1open] = false;
			}
		}
	}
	return 1;
}


COMMAND:joinrace(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if (playerData[playerid][playerWantedLevel] == 0)
		{
			if (playerData[playerid][playerJailTime] < 1)
			{
				new msg[512];
				if(serverInfo[race1open])
				{
					if(playerData[playerid][onRace1])
					{
						SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}You already in race event.");
						return 1;
					}
					if(IsValidVehicle(playerData[playerid][RaceCar]))
						DestroyVehicle(playerData[playerid][RaceCar]);

					new row = floatround(RaceCurrent / 4), cell = RaceCurrent % 4, Float:devx = 1560.4835, Float:devy = 3984.4919;
					for(new i = 0; i < row; i++)
						devy += 8.0;
					for(new i = 0; i < cell; i++)
						devx -= 7.0;
					RaceCurrent++;

					playerData[playerid][RaceCar] = CreateVehicle(411, devx, devy, 56.3691 + 3.0, 0.0, 0, 0, 120);
					for (new i = 0; i < 11; i++)
					{
						GetPlayerWeaponData(playerid, i, playerData[playerid][previousWeapons][i], playerData[playerid][previousAmmoLots][i]);
					}
					playerData[playerid][previousVirtualWorld] = GetPlayerVirtualWorld(playerid);
					playerData[playerid][previousInteriorWorld] = GetPlayerInterior(playerid);

					SetVehicleNumberPlate(playerData[playerid][RaceCar], "CZCNR");
					SetVehicleVirtualWorld(playerData[playerid][RaceCar], 184);
					GetPlayerHealth(playerid, playerData[playerid][previousHealth]);
					GetPlayerArmour(playerid, playerData[playerid][previousArmour]);
					GetPlayerPos(playerid, playerData[playerid][previousX], playerData[playerid][previousY], playerData[playerid][previousZ]);
					SetPlayerInterior(playerid, 0);
					new engine, lights, alarm, doors, bonnet, boot, objective;
					GetVehicleParamsEx(playerData[playerid][RaceCar], engine, lights, alarm, doors, bonnet, boot, objective);
					SetVehicleParamsEx(playerData[playerid][RaceCar], 0, lights, alarm, doors, bonnet, boot, objective);
					SetPlayerVirtualWorld(playerid, 184);
					ac_PutPlayerInVehicle(playerid, playerData[playerid][RaceCar], 0);
					ResetPlayerWeapons(playerid);
					SetPlayerTeam(playerid, 1);
					GameTextForPlayer(playerid, "~r~THE EVENT WILL START SHORTLY!!!", 10000, 5);
					format(msg, sizeof(msg), "{8AF56C}[RACE]{FFFFFF} You joined Race event, finish first to won the event.");
					SendClientMessage(playerid, COLOR_WHITE, msg);
					playerData[playerid][onRace1] = true;
					playerData[playerid][isInEvent] = true;
				}
				else
				{
					SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}There's no Race event right now.");
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}You cannot join events whilst jailed.");
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}You cannot join events if you have a wanted level.");
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}You must be logged in to use commands.");
	}
	return 1;
}

/*forward OnPlayerEnterDynamicRaceCP(playerid, checkpointid);
public OnPlayerEnterDynamicRaceCP(playerid, checkpointid)
{
    if(checkpointid == FINISH)
	{
 		if(playerData[playerid][onRace1])
   		{
     		if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 411)
     		{
       			SendClientMessageToAll(-1, "Hello!");
	            DestroyDynamicRaceCP(FINISH);
	        }
	    }
	}
	return 1;
}*/       


COMMAND:destroyrace(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(playerData[playerid][playerLevel] >= 4)
		{
			foreach(new i : Player)
			{
				if(IsValidVehicle(playerData[i][RaceCar]))
					DestroyVehicle(playerData[i][RaceCar]);
				if(playerData[i][onRace1])
					playerData[i][onRace1] = false;
			}
			if(IsValidDynamicRaceCP(FINISH))
				DestroyDynamicRaceCP(FINISH);
		}
	}
	return 1;
}

COMMAND:startrace(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(playerData[playerid][playerLevel] >= 4)
		{
			foreach(new i : Player)
			{
				if(playerData[i][onRace1])
				{
					GameTextForPlayer(i, "Event Started!!!", 1000, 5);
					new engine, lights, alarm, doors, bonnet, boot, objective;
					GetVehicleParamsEx(playerData[i][RaceCar], engine, lights, alarm, doors, bonnet, boot, objective);
					SetVehicleParamsEx(playerData[i][RaceCar], 1, lights, alarm, doors, bonnet, boot, objective);
				}
			}
		}
	}
	return 1;
}

COMMAND:gotorace(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(playerData[playerid][playerLevel] >= 4)
		{
			if(serverInfo[race1open])
			{
				SetPlayerPos(playerid, 1542.2869,4058.5042,56.3661);
				SetPlayerVirtualWorld(playerid, 184);
			}
			else
			{
			    SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}There's no Race event right now.");
			}
		}
	}
	return 1;
}
