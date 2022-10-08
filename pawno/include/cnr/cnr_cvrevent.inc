COMMAND:cvrevent(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(playerData[playerid][playerLevel] >= 4)
		{
			if (serverInfo[CVREvent])
			{
				// Close Event
				serverInfo[CVREvent] = 0;
				SendClientMessageToAll(COLOR_WHITE, "{58D3F7}[EVENT CLOSED] {FFFFFF}An administrator has closed the Cops vs Robbers TDM event.");
			}
			else
			{
				new
					weapID
				;

				if(sscanf(params, "i", weapID))
				{
					SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}Usage: \"cvrevent <weapon id>\"");
				}
				else
				{
					// Open Event
					serverInfo[CVREvent] = 1;
					serverInfo[DMWeapon] = weapID;

					SendClientMessageToAll(COLOR_WHITE, "{58D3F7}[EVENT OPENED] {FFFFFF}An administrator has started a Cops vs Robbers TDM event! Type {FFDC2E}/joincvr{FFFFFF} to participate.");
					SendClientMessage(playerid, COLOR_WHITE, "{58D3F7}[EVENT HELP] {FFFFFF}To start the event, first type /cvrevent again to close entry, then type /startcvr to unfreeze players.");

					GameTextForPlayer(playerid, "TEAM DEATH MATCH EVENT OPENED!", 5000, 5);
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

COMMAND:startcvr(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(playerData[playerid][playerLevel] >= 4)
		{
			for(new i = 0; i < MAX_PLAYERS; i++)
			{
				if(IsPlayerConnected(i) && playerData[i][playerLoggedIn])
				{
					if (playerData[i][isInCVR])
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

COMMAND:joincvr(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(playerData[playerid][playerClass] == CLASS_POLICE || playerData[playerid][playerClass] == CLASS_ARMY || playerData[playerid][playerClass] == CLASS_MEDIC || playerData[playerid][playerClass] == CLASS_FIREFIGHTER || playerData[playerid][playerClass] == CLASS_CIA || playerData[playerid][playerClass] == CLASS_FBI || playerData[playerid][playerClass] == CLASS_SECRETSERVICE || playerData[playerid][playerClass] == CLASS_CIVILIAN)
		{
			if (playerData[playerid][playerWantedLevel] == 0)
			{
				if (playerData[playerid][playerJailTime] < 1)
				{
					if (!playerData[playerid][isInCVR])
					{
						if (serverInfo[CVREvent])
						{
						    switch(playerData[playerid][playerClass])
							{
							    case CLASS_CIVILIAN:
							    {
									new randSpawn = random(2);
									switch(randSpawn)
									{
										case 0:
										{
											SetPlayerPos(playerid, 3496.7061,1194.9397,30.8687);
										}
										case 1:
										{
											SetPlayerPos(playerid, 3501.9734,1192.5763,30.8687);
										}

									}
								}
								case CLASS_POLICE:
								{
									new rand = random(2);

									switch (rand)
									{
									    case 0:
										{
											SetPlayerPos(playerid, 3585.6638,1276.7135,30.8687);
										}
										case 1:
										{
											SetPlayerPos(playerid, 3578.0193,1285.4124,30.8687);
										}
									}
								}
								case CLASS_ARMY:
								{
									new rand = random(2);

									switch (rand)
									{
									    case 0:
										{
											SetPlayerPos(playerid, 3585.6638,1276.7135,30.8687);
										}
										case 1:
										{
											SetPlayerPos(playerid, 3578.0193,1285.4124,30.8687);
										}
									}
								}
								case CLASS_CIA:
								{
									new rand = random(2);

									switch (rand)
									{
									    case 0:
										{
											SetPlayerPos(playerid, 3585.6638,1276.7135,30.8687);
										}
										case 1:
										{
											SetPlayerPos(playerid, 3578.0193,1285.4124,30.8687);
										}
									}
								}
								case CLASS_FBI:
								{
									new rand = random(2);

									switch (rand)
									{
									    case 0:
										{
											SetPlayerPos(playerid, 3585.6638,1276.7135,30.8687);
										}
										case 1:
										{
											SetPlayerPos(playerid, 3578.0193,1285.4124,30.8687);
										}
									}
								}
								case CLASS_SECRETSERVICE:
								{
									new rand = random(2);

									switch (rand)
									{
									   case 0:
										{
											SetPlayerPos(playerid, 3585.6638,1276.7135,30.8687);
										}
										case 1:
										{
											SetPlayerPos(playerid, 3578.0193,1285.4124,30.8687);
										}
									}
								}
								case CLASS_MEDIC:
								{
									new rand = random(2);

									switch (rand)
									{
									    case 0:
										{
											SetPlayerPos(playerid, 3585.6638,1276.7135,30.8687);
										}
										case 1:
										{
											SetPlayerPos(playerid, 3578.0193,1285.4124,30.8687);
										}
									}
								}
								case CLASS_FIREFIGHTER:
								{
									new rand = random(2);

									switch (rand)
									{
									    case 0:
										{
											SetPlayerPos(playerid, 3585.6638,1276.7135,30.8687);
										}
										case 1:
										{
											SetPlayerPos(playerid, 3578.0193,1285.4124,30.8687);
										}
									}
								}
							}


                            if(playerData[playerid][playerClass] == CLASS_POLICE || playerData[playerid][playerClass] == CLASS_MEDIC || playerData[playerid][playerClass] == CLASS_FIREFIGHTER || playerData[playerid][playerClass] == CLASS_ARMY || playerData[playerid][playerClass] == CLASS_CIA || playerData[playerid][playerClass] == CLASS_FBI || playerData[playerid][playerClass] == CLASS_SECRETSERVICE)
                            {
								SetPlayerTeam(playerid, 1);
								SetPlayerColor(playerid, 0x4000FFFF);
							}
							else if(playerData[playerid][playerClass] == CLASS_CIVILIAN)
							{
							    SetPlayerTeam(playerid, 2);
							    SetPlayerColor(playerid, 0xFF0000FF);
							}

							SetPlayerInterior(playerid, 15);
							SetPlayerVirtualWorld(playerid, 520);

							playerData[playerid][isInCVR] = true;
							TogglePlayerControllable(playerid, 0);

							// Remove armour
							SetPlayerArmour(playerid, 0);
							SetPlayerHealth(playerid, 100);

							ResetPlayerWeapons(playerid);
							playerData[playerid][adminWeapon] = true;
							GivePlayerWeaponEx(playerid, serverInfo[DMWeapon], 5000);
							GivePlayerWeaponEx(playerid, 17, 2);

							GameTextForPlayer(playerid, "THE EVENT WILL START SHORTLY!~n~~r~You are temporarily frozen", 10000, 5);
						}
						else
						{
							SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}There is no Cops Vs Robbers event open right now.");
						}
					}
					else
					{
						SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}Please leave the minigames arena before joining the CVR event.");
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
		    SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}You must be A Cop Class Or Civil Class To Join This Event.");
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}You must be logged in to use commands.");
	}

	return 1;
}
