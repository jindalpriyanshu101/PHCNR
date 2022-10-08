COMMAND:ffaevent(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(playerData[playerid][playerLevel] >= 4)
		{
			if (serverInfo[FREEFORALLEVENT])
			{
				serverInfo[FREEFORALLEVENT] = 0;
				SendClientMessageToAll(COLOR_WHITE, "{58D3F7}[EVENT CLOSED] {FFFFFF}An administrator has closed the Free For All event.");
			}
			else
			{
					
				serverInfo[FREEFORALLEVENT] = 1;
				M4 = CreateDynamicPickup(356, 23, -2828.4741,-1546.2417,139.8911, 520);
				SNIPER = CreateDynamicPickup(358, 23, -2788.2520,-1546.2860,139.9938, 520);
				AK47 = CreateDynamicPickup(355, 23, -2785.5083,-1526.9115,139.2559, 520);
				SHOTGUN = CreateDynamicPickup(351, 23, -2787.8499,-1492.8828,138.1109, 520);
				GRENADE = CreateDynamicPickup(342, 23, -2814.6245,-1511.8822,139.2891, 520);
				ROCKET = CreateDynamicPickup(359, 23, -2816.4509,-1510.2363,147.5845, 520);
				CHAINSAW = CreateDynamicPickup(341, 23, -2816.7231,-1511.2341,143.0851, 520);
				MOLOTOV = CreateDynamicPickup(344, 23, -2845.9431,-1525.5729,138.5389, 520);
				TEC9 = CreateDynamicPickup(372, 23, -2821.6233,-1570.8617,141.3203, 520);
				DEAGLE = CreateDynamicPickup(348, 23, -2817.6008,-1486.9915,140.9137, 520);
				JETPACK = CreateDynamicPickup(370, 23, -2816.1714,-1536.2777,146.5813, 520);

				SendClientMessageToAll(COLOR_WHITE, "{58D3F7}[EVENT OPENED] {FFFFFF}An administrator has started a Free For All event! Type {FFDC2E}/joinffa{FFFFFF} to participate.");
				SendClientMessage(playerid, COLOR_WHITE, "{58D3F7}[EVENT HELP] {FFFFFF}To start the event, first type /ffaevent again to close entry, then type /startffa to unfreeze players.");

				GameTextForPlayer(playerid, "FREE FOR ALL EVENT OPENED!", 5000, 5);
			}
		}
		else
		{
			return 0;
		}
 	}
	else
	{
		SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}You must be logged in to use commands.");
	}

	return 1;
}

COMMAND:startffa(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(playerData[playerid][playerLevel] >= 4)
		{
			for(new i = 0; i < MAX_PLAYERS; i++)
			{
				if(IsPlayerConnected(i) && playerData[i][playerLoggedIn])
				{
					if (playerData[i][isinFREEFORALL])
					{
						TogglePlayerControllable(i, 1);
						GameTextForPlayer(i, "EVENT STARTED!", 5000, 5);
					}
				}
			}
		}
		else
		{
			return 0;
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}You must be logged in to use commands.");
	}

	return 1;
}

COMMAND:joinffa(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if (playerData[playerid][playerWantedLevel] == 0)
		{
			if (playerData[playerid][playerJailTime] < 1)
			{
				if (!playerData[playerid][isinFREEFORALL])
				{
					if (serverInfo[FREEFORALLEVENT])
					{
						new randSpawn = random(4);
						switch(randSpawn)
						{
							case 0:
							{
								SetPlayerPos(playerid, -2815.5349,-1529.0854,140.8438);
							}
							case 1:
							{
								SetPlayerPos(playerid, -2815.9175,-1526.4918,140.8438);
							}
							case 2:
							{
								SetPlayerPos(playerid, -2815.7437,-1522.8492,140.8438);
							}
							case 3:
							{
								SetPlayerPos(playerid, -2815.8953,-1518.7479,140.8438);
							}
						}

						SetPlayerTeam(playerid, NO_TEAM);

						SetPlayerInterior(playerid, 0);
						SetPlayerVirtualWorld(playerid, 520);

						playerData[playerid][isinFREEFORALL] = true;
						TogglePlayerControllable(playerid, 0);

						SetPlayerArmour(playerid, 0);
						SetPlayerHealth(playerid, 100);

						ResetPlayerWeapons(playerid);

						GameTextForPlayer(playerid, "THE EVENT WILL START SHORTLY!~n~~r~You are temporarily frozen", 10000, 5);
					}
					else
					{
						SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}There is no Free For All event open right now.");
					}
				}
				else
				{
					SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}Please leave the minigames arena before joining the Free For All event.");
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

COMMAND:destroyffa(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(playerData[playerid][playerLevel] >= 4)
		{
		    if (!serverInfo[FREEFORALLEVENT])
			{
			    DestroyDynamicPickup(M4);
			    DestroyDynamicPickup(SNIPER);
			    DestroyDynamicPickup(AK47);
			    DestroyDynamicPickup(SHOTGUN);
			    DestroyDynamicPickup(GRENADE);
			    DestroyDynamicPickup(ROCKET);
			    DestroyDynamicPickup(CHAINSAW);
			    DestroyDynamicPickup(MOLOTOV);
			    DestroyDynamicPickup(JETPACK);
			    DestroyDynamicPickup(TEC9);
			    DestroyDynamicPickup(DEAGLE);
			    DestroyDynamicPickup(JETPACK);
			}
			else
			{
				SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}Close this event first.");
			}
		}
	}
	return 1;
}
			
		
