forward enablearrest(playerid);
forward isPlayerInRangeOfPlayer(playerid, otherid, Float:cRadius);
forward updatePlayerRobbingProgress(playerid, robberyTime);
forward forceRobberyCancel(playerid);
forward givePlayerWanted(playerid, amount);
forward playerGiveMoney(playerid, amount);
forward playerTakeMoney(playerid, amount);
forward playerTakeBankMoney(playerid, amount);
forward playerGiveBankMoney(playerid, amount);
forward playerSetMoney(playerid, amount);
forward sendMessageAdmins(message);
forward cancelRobbery(playerid);
forward beginRobbery(playerid);
forward Unfreeze(playerid);
forward randomEx(min, max);
forward Retaze(playerid);
forward recuff(playerid);
forward checkDriveB(playerid);
forward untie(playerid);
forward uncuff(playerid);
forward reFix(playerid);
forward reFlip(playerid);
forward reNOS(playerid);
forward reEMP(playerid);
forward pHouseCP(playerid);
forward mechReEmp(playerid);
forward resetEMP(vehicleID);
forward arrest(playerid);
forward countRobTime();
forward countMuteTime();
forward GetClosestPlayer(playerid);
forward clearWorldObjects(playerid);
forward checkNameStatus(playerName[]);
forward updateExperienceCounter(playerid);
forward newPlayerColour(playerid);
forward addWorldObjects();
forward getVehicleModelFromName(vname[]);
forward checkSeatStatus(vehicleid, seatid);
forward GetClosestPlayerToPlayer(playerid);
forward reactivateRob(playerid);
forward reactivateRape(playerid);
forward sendWantedMessage(playerid, amountAdded);
forward playerGiveXP(playerid, amount);
forward hideAddedXP(playerid);
forward hideHitmarkerTD(playerid);
forward highPing();
forward Timer();
forward speedhack(playerid);
forward KickPublic(playerid);
forward kickWithDelay(playerid);
forward secretHideout(elevationState);
forward hideAnnouncement();
forward reKidnap(playerid);
forward playerHitmanTracker(playerid, otherPlayer);
forward raped(playerid);
forward taxplayer(playerid);
forward gameTip();
forward command(playerid);
forward saveStats();
forward randomWeather();
forward blowJail(playerid);
forward blowJail2(playerid);
forward resetJailTimer();
forward resetJailTimer2();
forward spawnPlayer(playerid);
forward rebreakcuffs(playerid);
forward AntiSpawnkill(playerid);
forward disableAchieve(playerid);
forward weedExpire(playerid);
forward StopSpam(playerid);
forward retruck(playerid);
forward canSaveStats(playerid);
forward reHeal(playerid);
forward reCure(playerid);
forward classCheck();
forward closeDialogs(playerid);
forward reBreakin(playerid);
forward loadObjects(playerid);
forward objectsLoaded(playerid);
forward dmStats(playerid);
forward disableStreak(playerid);
forward swapMOTD();
forward Countdown();
forward AttackingZones(zone);
forward UnlockZone(zoneid);
forward UnlockGang(gangid);
forward mustLogin(playerid);

new hidden[MAX_PLAYERS];
new at[MAX_PLAYERS];
new cl[MAX_PLAYERS];
new bo[MAX_PLAYERS];
new pFPS[MAX_PLAYERS];
new CountDownTimer;
new CountDownVar = 0;
public swapMOTD()
{
	if (serverInfo[enableMOTD])
	{
		new pick = random(3);
		new formatPick[128];

		switch (pick)
		{
			case 0:
			{
				format(formatPick, sizeof(formatPick), "~r~C~y~S~g~F-~w~BOT: ~g~%s", serverInfo[MOTD1]);
				TextDrawSetString(Text:MOTDTD, formatPick);
			}

			case 1:
			{
				format(formatPick, sizeof(formatPick), "~r~C~y~S~g~F-~w~BOT: ~g~%s", serverInfo[MOTD2]);
				TextDrawSetString(Text:MOTDTD, formatPick);
			}

			case 2:
			{
				format(formatPick, sizeof(formatPick), "~r~C~y~S~g~F-~w~BOT: ~g~%s", serverInfo[MOTD3]);
				TextDrawSetString(Text:MOTDTD, formatPick);
			}
		}
	}
	else
	{
		TextDrawSetString(Text:MOTDTD, " ");
	}
}

public enablearrest(playerid)
{
    playerData[playerid][playerCanArrest] = true;
}

public disableStreak(playerid)
{
	TextDrawHideForPlayer(playerid, streakBox[0]);
	TextDrawHideForPlayer(playerid, streakBox[1]);
	TextDrawHideForPlayer(playerid, streakBox[2]);

	PlayerTextDrawHide(playerid, playerData[playerid][killStreak]);
}

public dmStats(playerid)
{
	new
		kills[15],
		deaths[15],
		ratioString[100],
		myStreak[15]
	;

	new Float:ratio = float(playerData[playerid][dmKills]) / float(playerData[playerid][dmDeaths]);

	if (playerData[playerid][dmKills] == 0 && playerData[playerid][dmDeaths] == 0)
	{
		format(ratioString, sizeof(ratioString), "N/A");
	}
	else
	{
		format(ratioString, sizeof(ratioString), "%0.2f", ratio);
	}

	format(kills, sizeof(kills), "%i", playerData[playerid][dmKills]);
	format(deaths, sizeof(deaths), "%i", playerData[playerid][dmDeaths]);
	format(myStreak, sizeof(myStreak), "%i", playerData[playerid][dmStreak]);

	PlayerTextDrawSetString(playerid, playerData[playerid][dmArena][0], kills);
	PlayerTextDrawSetString(playerid, playerData[playerid][dmArena][1], deaths);
	PlayerTextDrawSetString(playerid, playerData[playerid][dmArena][2], ratioString);
	PlayerTextDrawSetString(playerid, playerData[playerid][dmArena][3], myStreak);

	switch(playerData[playerid][dmStreak])
	{
		case 3:
		{
			PlayerTextDrawSetString(playerid, playerData[playerid][killStreak], "~r~3 Kill Streak~w~~n~Desert Eagle Received");

			TextDrawShowForPlayer(playerid, streakBox[0]);
			TextDrawShowForPlayer(playerid, streakBox[1]);
			TextDrawShowForPlayer(playerid, streakBox[2]);

			PlayerTextDrawShow(playerid, playerData[playerid][killStreak]);

			GivePlayerWeaponEx(playerid, 24, 50000);
			playerData[playerid][streakTimer] = SetTimerEx("disableStreak", 3000, false, "i", playerid);

			for (new i=0; i<MAX_PLAYERS; i++)
			{
				if(playerData[i][isInDM])
				{
					new dmLeave[100];
					format(dmLeave, sizeof(dmLeave), "{58D3F7}[MINIGAME] {FFFFFF}%s(%i) is on a 3 kill streak!", playerData[playerid][playerNamee], playerid);
					SendClientMessage(i, COLOR_WHITE, dmLeave);
				}
			}
		}

		case 6:
		{
			PlayerTextDrawSetString(playerid, playerData[playerid][killStreak], "~r~6 Kill Streak~w~~n~Rockets Received");

			TextDrawShowForPlayer(playerid, streakBox[0]);
			TextDrawShowForPlayer(playerid, streakBox[1]);
			TextDrawShowForPlayer(playerid, streakBox[2]);

			PlayerTextDrawShow(playerid, playerData[playerid][killStreak]);

			GivePlayerWeaponEx(playerid, 35, 50000);
			playerData[playerid][streakTimer] = SetTimerEx("disableStreak", 3000, false, "i", playerid);

			for (new i=0; i<MAX_PLAYERS; i++)
			{
				if(playerData[i][isInDM])
				{
					new dmLeave[100];
					format(dmLeave, sizeof(dmLeave), "{58D3F7}[MINIGAME] {FFFFFF}%s(%i) {FFFFFF}is on a 6 kill streak!", playerData[playerid][playerNamee], playerid);
					SendClientMessage(i, COLOR_WHITE, dmLeave);
				}
			}
		}

		case 10:
		{
			PlayerTextDrawSetString(playerid, playerData[playerid][killStreak], "~r~10 Kill Streak~w~~n~Minigun Received");

			TextDrawShowForPlayer(playerid, streakBox[0]);
			TextDrawShowForPlayer(playerid, streakBox[1]);
			TextDrawShowForPlayer(playerid, streakBox[2]);

			PlayerTextDrawShow(playerid, playerData[playerid][killStreak]);

			GivePlayerWeaponEx(playerid, 38, 50000);
			playerData[playerid][streakTimer] = SetTimerEx("disableStreak", 3000, false, "i", playerid);

			for (new i=0; i<MAX_PLAYERS; i++)
			{
				if(playerData[i][isInDM])
				{
					new dmLeave[100];
					format(dmLeave, sizeof(dmLeave), "{58D3F7}[MINIGAME] {FFFFFF}%s(%i) {FFFFFF}is on a 10 kill streak!", playerData[playerid][playerNamee], playerid);
					SendClientMessage(i, COLOR_WHITE, dmLeave);
				}
			}
		}
	}
}

public loadObjects(playerid)
{
	new Float:resetHealth;

	if(!playerData[playerid][playerAdminDuty])
	{
		GetPlayerHealth(playerid, resetHealth);
		playerData[playerid][savedHealth] = resetHealth;
	}
	playerData[playerid][hasSpawned] = false;
	TogglePlayerControllable(playerid, 0);

	PlayerTextDrawShow(playerid, playerData[playerid][objects][0]);
	PlayerTextDrawShow(playerid, playerData[playerid][objects][1]);
	PlayerTextDrawShow(playerid, playerData[playerid][objects][2]);
	PlayerTextDrawShow(playerid, playerData[playerid][objects][3]);

	if(!playerData[playerid][playerAdminDuty])
	{
		SetPlayerHealth(playerid, 1000);
	}
	playerData[playerid][objectsTimer] = SetTimerEx("objectsLoaded", 1500, false, "i", playerid);
}

public objectsLoaded(playerid)
{
	PlayerTextDrawHide(playerid, playerData[playerid][objects][0]);
	PlayerTextDrawHide(playerid, playerData[playerid][objects][1]);
	PlayerTextDrawHide(playerid, playerData[playerid][objects][2]);
	PlayerTextDrawHide(playerid, playerData[playerid][objects][3]);
	if(!playerData[playerid][playerAdminDuty])
	{
		SetPlayerHealth(playerid, playerData[playerid][savedHealth]);
	}
	playerData[playerid][hasSpawned] = true;
	TogglePlayerControllable(playerid, 1);
}

public reBreakin(playerid)
{
	playerData[playerid][canBreakIn] = true;
}

public closeDialogs(playerid)
{
	// Welcome Box
	PlayerTextDrawHide(playerid, playerData[playerid][Welcome1]);
	PlayerTextDrawHide(playerid, playerData[playerid][Welcome2]);
	PlayerTextDrawHide(playerid, playerData[playerid][Welcome3]);
	PlayerTextDrawHide(playerid, playerData[playerid][Welcome4]);
	PlayerTextDrawHide(playerid, playerData[playerid][Welcome5]);
	PlayerTextDrawHide(playerid, playerData[playerid][Welcome6]);
	PlayerTextDrawHide(playerid, playerData[playerid][Welcome7]);
	PlayerTextDrawHide(playerid, playerData[playerid][Welcome8]);

	// Innocent Kill Box
	PlayerTextDrawHide(playerid, playerData[playerid][InnocentKill1]);
	PlayerTextDrawHide(playerid, playerData[playerid][InnocentKill2]);
	PlayerTextDrawHide(playerid, playerData[playerid][InnocentKill3]);
	PlayerTextDrawHide(playerid, playerData[playerid][InnocentKill4]);
	PlayerTextDrawHide(playerid, playerData[playerid][InnocentKill5]);
	PlayerTextDrawHide(playerid, playerData[playerid][InnocentKill6]);
	PlayerTextDrawHide(playerid, playerData[playerid][InnocentKill7]);
	PlayerTextDrawHide(playerid, playerData[playerid][InnocentKill8]);

	// Stats
	PlayerTextDrawHide(playerid, playerData[playerid][PlayerStats][0]);
	PlayerTextDrawHide(playerid, playerData[playerid][PlayerStats][1]);
	PlayerTextDrawHide(playerid, playerData[playerid][PlayerStats][2]);
	PlayerTextDrawHide(playerid, playerData[playerid][PlayerStats][3]);
	PlayerTextDrawHide(playerid, playerData[playerid][PlayerStats][4]);
	PlayerTextDrawHide(playerid, playerData[playerid][PlayerStats][5]);
	PlayerTextDrawHide(playerid, playerData[playerid][PlayerStats][6]);
	PlayerTextDrawHide(playerid, playerData[playerid][PlayerStats][7]);
	PlayerTextDrawHide(playerid, playerData[playerid][PlayerStats][8]);
	PlayerTextDrawHide(playerid, playerData[playerid][PlayerStats][9]);
	PlayerTextDrawHide(playerid, playerData[playerid][PlayerStats][10]);
	PlayerTextDrawHide(playerid, playerData[playerid][PlayerStats][11]);
	PlayerTextDrawHide(playerid, playerData[playerid][PlayerStats][12]);
	PlayerTextDrawHide(playerid, playerData[playerid][PlayerStats][13]);
	PlayerTextDrawHide(playerid, playerData[playerid][PlayerStats][14]);
	PlayerTextDrawHide(playerid, playerData[playerid][PlayerStats][15]);
	PlayerTextDrawHide(playerid, playerData[playerid][PlayerStats][16]);
	PlayerTextDrawHide(playerid, playerData[playerid][PlayerStats][17]);
	PlayerTextDrawHide(playerid, playerData[playerid][PlayerStats][18]);
	PlayerTextDrawHide(playerid, playerData[playerid][PlayerStats][19]);
	PlayerTextDrawHide(playerid, playerData[playerid][PlayerStats][20]);
	PlayerTextDrawHide(playerid, playerData[playerid][PlayerStats][21]);
	PlayerTextDrawHide(playerid, playerData[playerid][PlayerStats][22]);
	PlayerTextDrawHide(playerid, playerData[playerid][PlayerStats][23]);
	PlayerTextDrawHide(playerid, playerData[playerid][PlayerStats][24]);

	TextDrawHideForPlayer(playerid, TopTD[0]);
	TextDrawHideForPlayer(playerid, TopTD[1]);
	TextDrawHideForPlayer(playerid, TopTD[2]);
	TextDrawHideForPlayer(playerid, TopTD[3]);
	TextDrawHideForPlayer(playerid, TopTD[4]);
	TextDrawHideForPlayer(playerid, TopTD[5]);
	TextDrawHideForPlayer(playerid, TopTD[6]);
	TextDrawHideForPlayer(playerid, TopTD[7]);
	TextDrawHideForPlayer(playerid, TopTD[8]);
	TextDrawHideForPlayer(playerid, TopTD[9]);
	TextDrawHideForPlayer(playerid, TopTD[10]);
	TextDrawHideForPlayer(playerid, TopTD[11]);
	TextDrawHideForPlayer(playerid, TopTD[12]);
	TextDrawHideForPlayer(playerid, TopTD[13]);
	TextDrawHideForPlayer(playerid, TopTD[14]);
	TextDrawHideForPlayer(playerid, TopTD[15]);
	TextDrawHideForPlayer(playerid, TopTD[16]);
	TextDrawHideForPlayer(playerid, TopTD[17]);
	TextDrawHideForPlayer(playerid, TopTD[18]);
	TextDrawHideForPlayer(playerid, TopTD[19]);
	TextDrawHideForPlayer(playerid, TopTD[20]);
	TextDrawHideForPlayer(playerid, TopTD[21]);
	TextDrawHideForPlayer(playerid, TopTD[22]);
	TextDrawHideForPlayer(playerid, TopTD[23]);
	TextDrawHideForPlayer(playerid, TopTD[24]);
	TextDrawHideForPlayer(playerid, TopTD[25]);
	TextDrawHideForPlayer(playerid, TopTD[26]);
	TextDrawHideForPlayer(playerid, TopTD[27]);
	TextDrawHideForPlayer(playerid, TopTD[28]);
	TextDrawHideForPlayer(playerid, TopTD[29]);
	TextDrawHideForPlayer(playerid, TopTD[30]);
	TextDrawHideForPlayer(playerid, TopTD[31]);
	TextDrawHideForPlayer(playerid, TopTD[32]);
	TextDrawHideForPlayer(playerid, TopTD[33]);
	TextDrawHideForPlayer(playerid, TopTD[34]);
	TextDrawHideForPlayer(playerid, TopTD[35]);
	TextDrawHideForPlayer(playerid, TopTD[36]);
	TextDrawHideForPlayer(playerid, TopTD[37]);
	TextDrawHideForPlayer(playerid, TopTD[38]);
	TextDrawHideForPlayer(playerid, TopTD[39]);
	TextDrawHideForPlayer(playerid, TopTD[40]);
	TextDrawHideForPlayer(playerid, TopTD[41]);
	
	// Welcome Box
	PlayerTextDrawHide(playerid, playerData[playerid][Welcome1]);
	PlayerTextDrawHide(playerid, playerData[playerid][Welcome2]);
	PlayerTextDrawHide(playerid, playerData[playerid][Welcome3]);
	PlayerTextDrawHide(playerid, playerData[playerid][Welcome4]);
	PlayerTextDrawHide(playerid, playerData[playerid][Welcome5]);
	PlayerTextDrawHide(playerid, playerData[playerid][Welcome6]);
	PlayerTextDrawHide(playerid, playerData[playerid][Welcome7]);
	PlayerTextDrawHide(playerid, playerData[playerid][Welcome8]);

	// Innocent Kill Box
	PlayerTextDrawHide(playerid, playerData[playerid][InnocentKill1]);
	PlayerTextDrawHide(playerid, playerData[playerid][InnocentKill2]);
	PlayerTextDrawHide(playerid, playerData[playerid][InnocentKill3]);
	PlayerTextDrawHide(playerid, playerData[playerid][InnocentKill4]);
	PlayerTextDrawHide(playerid, playerData[playerid][InnocentKill5]);
	PlayerTextDrawHide(playerid, playerData[playerid][InnocentKill6]);
	PlayerTextDrawHide(playerid, playerData[playerid][InnocentKill7]);
	PlayerTextDrawHide(playerid, playerData[playerid][InnocentKill8]);

	// Stats
	PlayerTextDrawHide(playerid, playerData[playerid][PlayerStats][0]);
	PlayerTextDrawHide(playerid, playerData[playerid][PlayerStats][1]);
	PlayerTextDrawHide(playerid, playerData[playerid][PlayerStats][2]);
	PlayerTextDrawHide(playerid, playerData[playerid][PlayerStats][3]);
	PlayerTextDrawHide(playerid, playerData[playerid][PlayerStats][4]);
	PlayerTextDrawHide(playerid, playerData[playerid][PlayerStats][5]);
	PlayerTextDrawHide(playerid, playerData[playerid][PlayerStats][6]);
	PlayerTextDrawHide(playerid, playerData[playerid][PlayerStats][7]);
	PlayerTextDrawHide(playerid, playerData[playerid][PlayerStats][8]);
	PlayerTextDrawHide(playerid, playerData[playerid][PlayerStats][9]);
	PlayerTextDrawHide(playerid, playerData[playerid][PlayerStats][10]);
	PlayerTextDrawHide(playerid, playerData[playerid][PlayerStats][11]);
	PlayerTextDrawHide(playerid, playerData[playerid][PlayerStats][12]);
	PlayerTextDrawHide(playerid, playerData[playerid][PlayerStats][13]);
	PlayerTextDrawHide(playerid, playerData[playerid][PlayerStats][14]);
	PlayerTextDrawHide(playerid, playerData[playerid][PlayerStats][15]);
	PlayerTextDrawHide(playerid, playerData[playerid][PlayerStats][16]);
	PlayerTextDrawHide(playerid, playerData[playerid][PlayerStats][17]);
	PlayerTextDrawHide(playerid, playerData[playerid][PlayerStats][18]);
	PlayerTextDrawHide(playerid, playerData[playerid][PlayerStats][19]);
	PlayerTextDrawHide(playerid, playerData[playerid][PlayerStats][20]);
	PlayerTextDrawHide(playerid, playerData[playerid][PlayerStats][21]);
	PlayerTextDrawHide(playerid, playerData[playerid][PlayerStats][22]);
	PlayerTextDrawHide(playerid, playerData[playerid][PlayerStats][23]);
	PlayerTextDrawHide(playerid, playerData[playerid][PlayerStats][24]);
}

public classCheck()
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i) && playerData[i][playerLoggedIn])
		{
			if (playerData[i][hasSpawned])
			{
				switch(playerData[i][playerClass])
				{
					case CLASS_CIA:
					{
						// XP check
						if (playerData[i][playerXP] < 10000)
						{
							// Not allowed in this class
							ForceClassSelection(i);
							SetPlayerHealth(i, 0.0);
						}
					}

					case CLASS_FBI:
					{
						// XP check
						if (playerData[i][playerXP] < 5000)
						{
							// Not allowed in this class
							ForceClassSelection(i);
							SetPlayerHealth(i, 0.0);
						}
					}

					case CLASS_ARMY:
					{
						// XP check
						if (playerData[i][playerXP] < 20000)
						{
							// Not allowed in this class
							ForceClassSelection(i);
							SetPlayerHealth(i, 0.0);
						}
					}

					case CLASS_SECRETSERVICE:
					{
						// XP check
						if (playerData[i][playerVIPLevel] < 1)
						{
							// Not allowed in this class
							ForceClassSelection(i);
							SetPlayerHealth(i, 0.0);
						}
					}
				}
			}
		}
	}
}

public reCure(playerid)
{
	playerData[playerid][canCure] = true;
}

public reHeal(playerid)
{
	playerData[playerid][canHeal] = true;
}

public canSaveStats(playerid)
{
	playerData[playerid][playerCanSaveStats] = true;
}

public retruck(playerid)
{
	playerData[playerid][canTruck] = true;
}

public StopSpam(playerid)
{
	playerData[playerid][messageCount] = 0;
}

public weedExpire(playerid)
{
    playerData[playerid][canWeed] = true;
	Delete3DTextLabel(playerData[playerid][weedLabel]);
	return 1;
}

public disableAchieve(playerid)
{
	PlayerTextDrawHide(playerid, playerData[playerid][Achieve1]);
	PlayerTextDrawHide(playerid, playerData[playerid][Achieve2]);
	PlayerTextDrawHide(playerid, playerData[playerid][Achieve3]);
	PlayerTextDrawHide(playerid, playerData[playerid][Achieve4]);
	PlayerPlaySound(playerid,1184,0.0,0.0,0.0);
}

public AntiSpawnkill(playerid)
{
	if (!playerData[playerid][playerAdminDuty])
	{
		SetPlayerHealth(playerid, 100.0);
	}

	Delete3DTextLabel(playerData[playerid][spawnLabel]);
	playerData[playerid][ctpImmune] = false;
	playerData[playerid][abImmune] = false;
	return 1;
}

public spawnPlayer(playerid)
{
	if (!playerData[playerid][selectingClass])
	{
		SpawnPlayer(playerid);
	}
}

public resetJailTimer()
{
	serverInfo[jailblown] = 0;
}

public resetJailTimer2()
{
	serverInfo[jailblown2] = 0;
}

public blowJail(playerid)
{
	if (serverInfo[jailblown] == 0)
	{
		for(new p; p < MAX_PLAYERS; p++)
		{
			new pName[24];
			GetPlayerName(p, pName, sizeof(pName));

			if(!strcmp(pName, playerData[playerid][playerNamee]))
			{
				SendClientMessage(p, COLOR_WHITE, "{FFDC2E}[JAIL BLOWN] {FFFFFF}You blew up the San Fierro jail cells and freed everyone inside.");
			}
			else
			{
				new jailm[200];
				format(jailm, sizeof(jailm), "{FFDC2E}[JAIL BLOWN] {FFFFFF}%s(%i) has blown the San Fierro jail and freed the criminals!", playerData[playerid][playerNamee], playerid);
				SendClientMessage(p, COLOR_WHITE, jailm);
			}
		}

		for(new i = 0; i < MAX_PLAYERS; i++)
		{
			if(IsPlayerConnected(i) && playerData[i][playerJailTime] > 1)
			{
				if (playerData[i][playerAdminJailed] != 1)
				{
					

						SetPlayerInterior(i, 10);
						SetPlayerPos(i, 216.8014, 120.5791, 999.0156);
						SetPlayerFacingAngle(i, 183.3742);
						SetPlayerVirtualWorld(i, 25);
						SetPlayerHealth(i, 100);
						PlayerTextDrawSetString(i, playerData[i][playerJailTimerTD], " ");
						playerData[i][playerBailTo] = -1;
						playerData[i][playerBailPrice] = -1;
						playerData[i][playerJailTime] = 0;
						KillTimer(playerData[i][jailTimer]);

						SendClientMessage(i, COLOR_WHITE, "{FFDC2E}[JAIL BLOWN] {FFFFFF}You escaped from jail.");

				}
			}
		}

		serverInfo[jailblown] = GetTickCount();
		SetTimer("resetJailTimer", 300000, false);
		givePlayerWanted(playerid, 12);
		playerGiveXP(playerid, 40);
		sendWantedMessage(playerid, 12);
		playerData[playerid][playerScore] = playerData[playerid][playerScore] + 2;
		SetPlayerScore(playerid, playerData[playerid][playerScore]);
		newPlayerColour(playerid);
	}
}

public blowJail2(playerid)
{
	if (serverInfo[jailblown2] == 0)
	{
		for(new p; p < MAX_PLAYERS; p++)
		{
			new pName[24];
			GetPlayerName(p, pName, sizeof(pName));

			if(!strcmp(pName, playerData[playerid][playerNamee]))
			{
				SendClientMessage(p, COLOR_WHITE, "{FFDC2E}[JAIL BLOWN] {FFFFFF}You blew up the Las Venturas jail cells and freed everyone inside.");
			}
			else
			{
				new jailm[200];
				format(jailm, sizeof(jailm), "{FFDC2E}[JAIL BLOWN] {FFFFFF}%s(%i) has blown the Las Venturas jail and freed the criminals!", playerData[playerid][playerNamee], playerid);
				SendClientMessage(p, COLOR_WHITE, jailm);
			}
		}

		/*for(new i = 0; i < MAX_PLAYERS; i++)
		{
			if(IsPlayerConnected(i) && playerData[i][playerJailTime] > 1)
			{
				if (playerData[i][playerAdminJailed] != 1)
				{
					if(playerData[i][playerTown] == LV)
					{
						SetPlayerInterior(playerid, 3);
						SetPlayerPos(playerid, 200.6972, 168.2653, 1003.0234);
						SetPlayerFacingAngle(playerid, 89.0391);
						SetPlayerVirtualWorld(playerid, 142);
						SetPlayerHealth(i, 100);
						PlayerTextDrawSetString(i, playerData[i][playerJailTimerTD], " ");
						playerData[i][playerBailTo] = -1;
						playerData[i][playerBailPrice] = -1;
						playerData[i][playerJailTime] = 0;
						KillTimer(playerData[i][jailTimer]);
					}
					SendClientMessage(i, COLOR_WHITE, "{FFDC2E}[JAIL BLOWN] {FFFFFF}You escaped from jail.");
				}
			}
		}*/

		serverInfo[jailblown2] = GetTickCount();
		SetTimer("resetJailTimer2", 300000, false);
		givePlayerWanted(playerid, 12);
		playerGiveXP(playerid, 40);
		sendWantedMessage(playerid, 12);
		playerData[playerid][playerScore] = playerData[playerid][playerScore] + 2;
		SetPlayerScore(playerid, playerData[playerid][playerScore]);
		newPlayerColour(playerid);
	}
}

public randomWeather()
{
	new weather = random(6);

	switch(weather)
	{
		case 0: // Sunny
		{
			SetWeather(4);
		}
		case 1: // Sunny
		{
			SetWeather(4);
		}
		case 2: // Sunny
		{
			SetWeather(4);
		}
		case 3: // Cloudy
		{
			SetWeather(7);
		}
		case 4: // Sunny
		{
			SetWeather(4);
		}
		case 5: // Storm
		{
			SetWeather(4);
		}
	}
}

IsVehicleOccupied(vehiclesID)
{
    for(new i = 0; i < MAX_PLAYERS; i++)
	{
        if(IsPlayerConnected(i))
		{
            if(IsPlayerInVehicle(i, vehiclesID))
			{
				return 1;
			}
        }
    }
    return 0;
}

PreloadAnimLib(playerid, animlib[])
{
	ApplyAnimation(playerid,animlib,"null",0.0,0,0,0,0,0);
}

public saveStats()
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i) && playerData[i][playerLoggedIn])
		{
			savePlayerStats(i);
		}
	}
}

public command(playerid)
{
	playerData[playerid][canUseCommands] = true;
}

public gameTip()
{
	// Random tip
	new message = random(10);
	switch(message)
	{
		case 0:
		{
			SendClientMessageToAll(COLOR_WHITE, "{FFFF00}[~r~C~y~S~g~F-~w~BOT]>> {00D950}Type /cmds to view a list of server commands!");
		}
		case 1:
		{
			SendClientMessageToAll(COLOR_WHITE, "{FFFF00}[~r~C~y~S~g~F-~w~BOT]>> {00D950}Spotted a cheat? {00FF00}/report {FFFFFF}them!");
		}
		case 2:
		{
			SendClientMessageToAll(COLOR_WHITE, "{FFFF00}[~r~C~y~S~g~F-~w~BOT]>> {00D950}Found a bug or an exploit? Report it on Forums");
		}
		case 3:
		{
			SendClientMessageToAll(COLOR_WHITE, "{FFFF00}[~r~C~y~S~g~F-~w~BOT]>> {00D950}You can type {FF0000}/pc {00D950}to view a list of the player colours.");
		}
		case 4:
		{
			SendClientMessageToAll(COLOR_WHITE, "{FFFF00}[~r~C~y~S~g~F-~w~BOT]>> {00D950}Got a question? Use {00FF00}/ask {00D950}to ask our server helpers!");
		}
		case 5:
		{
			SendClientMessageToAll(COLOR_WHITE, "{FFFF00}[~r~C~y~S~g~F-~w~BOT]>> {00D950}Want to change your job? Head to the Job Centre {FF0000}(/gps)!");
		}
		case 6:
		{
			SendClientMessageToAll(COLOR_WHITE, "{FFFF00}[~r~C~y~S~g~F-~w~BOT]>> {00D950}Save your stats using {FFFFFF}/savestats {00D950}regularly to avoid stat loss!");
		}
		case 7:
		{
			SendClientMessageToAll(COLOR_WHITE, "{FFFF00}[~r~C~y~S~g~F-~w~BOT]>> {00D950}Wish to donate to the server? Visit: {00FF00}Soon");
		}
		case 8:
		{
			SendClientMessageToAll(COLOR_WHITE, "{FFFF00}[~r~C~y~S~g~F-~w~BOT]>> {00D950}Having trouble finding a location? Type {FF0000}/gps");
		}
                case 9:
                {
                        SendClientMessageToAll(COLOR_WHITE, "{FFFF00}[~r~C~y~S~g~F-~w~BOT] >> {00D950}<< Server Script by  [~r~C~y~S~g~F~w~-~r~CNR ~b~STAFFS] >> ");
                }
	}
	for(new i = 0; i < MAX_GANGS; i++)
	{
		if(gangData[i][gangScore] != -1)
		{
			saveGang(i);
		}
	}
}

public taxplayer(playerid)
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(playerData[playerid][playerVIPLevel] < 1)
		{
			if(playerData[playerid][playerMoney] >= 5000)
			{
				if(playerData[playerid][playerJailTime] < 10)
				{
					new takeValue = floatround(playerData[playerid][playerMoney] * 0.030, floatround_round);

					playerTakeMoney(playerid, takeValue);

					// Send tax info
					SendClientMessage(playerid, COLOR_WHITE, "{FFDC2E}[TAX] {FFFFFF}The server tax has been deducted from your account balance.");
				}
			}

			/*if(playerData[playerid][playerBank] >= 500000)
			{
				if(playerData[playerid][playerJailTime] < 10)
				{
					new takeValue = floatround(playerData[playerid][playerBank] * 0.001, floatround_round);

					playerTakeBankMoney(playerid, takeValue);
				}
			}*/
		}
	}
}

public raped(playerid)
{
	if(playerData[playerid][hasSTD])
	{
		playerData[playerid][suicide] = true;

		new Float:health;
		GetPlayerHealth(playerid, health);
		SetPlayerHealth(playerid, health - 3);
	}
	else
	{
		KillTimer(playerData[playerid][rapedTimer]);
	}
}

public playerHitmanTracker(playerid, otherPlayer)
{
	if(playerData[playerid][playerJailTime] > 1)
	{
		// Disable tracker
		playerData[playerid][playerIsTracking] = false;
		KillTimer(playerData[playerid][playerHitmanTrackerTimer]);
	}
	else
	{
		new Float:otherPlayerX, Float:otherPlayerY, Float:otherPlayerZ;
		GetPlayerPos(otherPlayer, otherPlayerX, otherPlayerY, otherPlayerZ);
		new Float:distance = GetPlayerDistanceFromPoint(playerid, otherPlayerX, otherPlayerY, otherPlayerZ);

		new trackString[100];
		format(trackString, sizeof(trackString), "%.0f Metres", distance);
		PlayerTextDrawSetString(playerid, playerData[playerid][playerTracker], trackString);
	}
}

public reKidnap(playerid)
{
	playerData[playerid][playerCanKidnap] = true;
	KillTimer(playerData[playerid][kidnapTimer]);
	return 1;
}

public hideAnnouncement()
{
	TextDrawHideForAll(AnnounceTD);
	return 1;
}

public KickPublic(playerid)
{
    Kick(playerid);
}

stock KickWithMessage(playerid, message[])
{
    SendClientMessage(playerid, COLOR_RED, message);
    SetTimerEx("KickPublic", 1000, 0, "d", playerid);
}

stock SoundForAll(sound)
{
	for (new i = 0; i != MAX_PLAYERS; ++i)
	{
		PlayerPlaySound(i,sound,0.0,0.0,0.0);
	}
}
public kickWithDelay(playerid)
{
	SetTimer("KickPublic", 500, false);
}

public Timer()
{
 	new timestring[256], daystring[256], gseconds = gtime % 60, gminutes = (gtime - gseconds) / 60;
	gtime ++;

	format(timestring, sizeof (timestring), "   %02d:%02d", gminutes, gseconds);
	TextDrawSetString(gTime, timestring);
	TextDrawShowForAll(gTime);
	format(daystring, sizeof (daystring), "%s", GetDayName());
	TextDrawSetString(gDay, daystring);
	TextDrawShowForAll(gDay);

	if(gday == 6 && gtime == 1440)
	{
		gday = 0;
		gtime = 0;
	}

	if(gtime == 1440)
	{
		gday++;
		gtime=0;
		format(daystring, sizeof (daystring), "   00:00");
		TextDrawSetString(gTime,daystring);
	}

	for(new i=0; i<MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
			SetPlayerTime(i, gminutes, gseconds);
			if(gtime == 0)
			{
				// Tax players
				taxplayer(i);

				// award LEO players $800
				if (playerData[i][playerClass] == CLASS_POLICE || playerData[i][playerClass] == CLASS_CIA || playerData[i][playerClass] == CLASS_FBI)
				{
					if (playerData[i][playerJailTime] == 0)
					{
						SendClientMessage(i, COLOR_WHITE, "{58D3F7}[PAYMENT] {FFFFFF}You have received {FFDC2E}$800 {FFFFFF}in wages from the city.");
						playerGiveMoney(i, 800);
					}
				}

				if (playerData[i][playerClass] == CLASS_MEDIC || playerData[i][playerClass] == CLASS_FIREFIGHTER)
				{
					if (playerData[i][playerJailTime] == 0)
					{
						SendClientMessage(i, COLOR_WHITE, "{58D3F7}[PAYMENT] {FFFFFF}You have received {FFDC2E}$500 {FFFFFF}in wages from the city.");
						playerGiveMoney(i, 500);
					}
				}

				if (playerData[i][hasSpawned])
				{
					if(playerData[i][houseCount] > 0)
					{
						new chousetax;
						chousetax = 1200 * playerData[i][houseCount];
						playerTakeMoney(i, chousetax);
					}
				}
			}
		}
	}

	if(gtime == 0)
	{
		for(new i = 0; i < MAX_ROB_CHECKPOINT; i++)
		{
			if(checkpointData[i][storeOwner] != -1 && checkpointData[i][storeOwner] != 0)
			{
				new mny[10], File:file, fmt[56];
				format(fmt, 256, "storeowner/%d.money", i);
				checkpointData[i][storeMoney] += checkpointData[i][highestCash];
				if(checkpointData[i][storeMoney] > 200000)
					checkpointData[i][storeMoney] = 200000;
				file = fopen(fmt, io_write);
				format(mny, 10, "%d", checkpointData[i][storeMoney]);
				fwrite(file, mny);
				fclose(file);
			}
		}
	}
	return 1;
}

SendAdminText(playerid, text[])
{
	if (playerData[playerid][playerLevel] < 7)
	{
		// Setup local variables
		new Name[24], Msg[250];

		// Get the player's name
		GetPlayerName(playerid, Name, sizeof(Name));
		// Send the given text to the admin
		format(Msg, sizeof(Msg), "%s", text);

		alog[5] = alog[4];
		alog[4] = alog[3];
		alog[3] = alog[2];
		alog[2] = alog[1];
		alog[1] = Msg;

		TextDrawSetString(alog1, Msg);
		TextDrawSetString(alog2, alog[2]);
		TextDrawSetString(alog3, alog[3]);
		TextDrawSetString(alog4, alog[4]);
		TextDrawSetString(alog5, alog[5]);

		// Also log all used commands in the server.log file
		format(Msg, 128, "%s used: %s", Name, text);
		print(Msg);
	}
}

public highPing()
{
    for(new i=0; i < MAX_PLAYERS; i++)
    {
		if(playerData[i][playerLoggedIn])
		{
			if (playerData[i][playerLevel] < 1)
			{
				if(!playerData[i][playerPingImmune])
				{
					if(GetPlayerPing(i) > serverInfo[maxPing] && GetPlayerPing(i) != 65535)
					{
						new messageContent[128];
						format(messageContent, sizeof(messageContent), "{FFDC2E}[ANTI-CHEAT] {FFFFFF}%s(%i) has been kicked for high ping [%i/%i]", playerData[i][playerNamee], i, GetPlayerPing(i), serverInfo[maxPing]);
						SendClientMessageToAll(COLOR_WHITE, messageContent);
						KickWithMessage(i, "You have been kicked due to your ping being over the limit.");
					}
				}
			}
		}
	}

    return 1;
}

public reactivateRob(playerid)
{
	if(IsPlayerConnected(playerid))
	{
		if(playerData[playerid][playerLoggedIn])
		{
			playerData[playerid][playerCanRob] = true;
			KillTimer(playerData[playerid][reactivateRobStatus]);
		}
	}
}

public reactivateRape(playerid)
{
	if(IsPlayerConnected(playerid))
	{
		if(playerData[playerid][playerLoggedIn])
		{
			playerData[playerid][playerCanRape] = true;
			KillTimer(playerData[playerid][reactivateRapeStatus]);
		}
	}
}

public GetClosestPlayerToPlayer(playerid)
{
    new Float:dist = 1000.0;
    new targetid = INVALID_PLAYER_ID;
    new Float:x1,Float:y1,Float:z1;
    new Float:x2,Float:y2,Float:z2;
    new Float:tmpdis;
    GetPlayerPos(playerid,x1,y1,z1);
    for(new i=0;i<MAX_PLAYERS;i++)
    {
		if (playerData[i][playerLoggedIn])
		{
			if(i == playerid)
				continue;

			if (playerData[i][playerIsSpectating])
				continue;

			GetPlayerPos(i,x2,y2,z2);
			tmpdis = floatsqroot(floatpower(floatabs(floatsub(x2,x1)),2)+floatpower(floatabs(floatsub(y2,y1)),2)+floatpower(floatabs(floatsub(z2,z1)),2));

			if(tmpdis < dist)
			{
				dist = tmpdis;
				targetid = i;
			}
		}
    }
    return targetid;
}

public playerGiveXP(playerid, amount)
{
	if(IsPlayerConnected(playerid))
	{
		if(playerData[playerid][playerLoggedIn])
		{
			new tdMessage[50], finalAmount;

			if (serverInfo[doubleXP] == 1 || playerData[playerid][playerVIPLevel] >= 2)
			{
			    finalAmount = amount * 2;
			}
			else
			{
				finalAmount = amount;
			}

			new oldXP = playerData[playerid][playerXP];

			format(tdMessage, sizeof(tdMessage), "+ %i XP", finalAmount);

			playerData[playerid][playerXP] = playerData[playerid][playerXP] + finalAmount;
			updateExperienceCounter(playerid);
			PlayerTextDrawSetString(playerid, playerData[playerid][playerAddedXPTD], tdMessage);
			SetTimerEx("hideAddedXP", 2000, false, "i", playerid);

			if (playerData[playerid][playerXP] >= 1000 && oldXP < 1000)
			{
				disableAchieve(playerid);
				PlayerTextDrawShow(playerid, playerData[playerid][Achieve1]);
				PlayerTextDrawShow(playerid, playerData[playerid][Achieve2]);
				PlayerTextDrawShow(playerid, playerData[playerid][Achieve3]);
				PlayerTextDrawShow(playerid, playerData[playerid][Achieve4]);

				PlayerTextDrawSetString(playerid, playerData[playerid][Achieve3], "XP Prostitute");
				PlayerTextDrawSetString(playerid, playerData[playerid][Achieve4], "You earnt 1,000 XP! Well done!");
				PlayerPlaySound(playerid, 1185 ,0.0, 0.0, 0.0);

				playerData[playerid][achieveTimer] = SetTimerEx("disableAchieve", 6000, false, "i", playerid);

				playerGiveXP(playerid, 25);
				playerData[playerid][playerScore] = playerData[playerid][playerScore] + 2;
				SetPlayerScore(playerid, playerData[playerid][playerScore]);
			}
			else if (playerData[playerid][playerXP] >= 5000 && oldXP < 5000)
			{
				disableAchieve(playerid);
				PlayerTextDrawShow(playerid, playerData[playerid][Achieve1]);
				PlayerTextDrawShow(playerid, playerData[playerid][Achieve2]);
				PlayerTextDrawShow(playerid, playerData[playerid][Achieve3]);
				PlayerTextDrawShow(playerid, playerData[playerid][Achieve4]);

				PlayerTextDrawSetString(playerid, playerData[playerid][Achieve3], "XP Hoarder");
				PlayerTextDrawSetString(playerid, playerData[playerid][Achieve4], "You earnt 5,000 XP! FBI class unlocked!");
				PlayerPlaySound(playerid, 1185 ,0.0, 0.0, 0.0);
				savePlayerStats(playerid);

				playerData[playerid][achieveTimer] = SetTimerEx("disableAchieve", 6000, false, "i", playerid);

				playerGiveXP(playerid, 25);
				playerData[playerid][playerScore] = playerData[playerid][playerScore] + 2;
				SetPlayerScore(playerid, playerData[playerid][playerScore]);
			}
			else if (playerData[playerid][playerXP] >= 10000 && oldXP < 10000)
			{
				disableAchieve(playerid);
				PlayerTextDrawShow(playerid, playerData[playerid][Achieve1]);
				PlayerTextDrawShow(playerid, playerData[playerid][Achieve2]);
				PlayerTextDrawShow(playerid, playerData[playerid][Achieve3]);
				PlayerTextDrawShow(playerid, playerData[playerid][Achieve4]);

				PlayerTextDrawSetString(playerid, playerData[playerid][Achieve3], "XP Boss");
				PlayerTextDrawSetString(playerid, playerData[playerid][Achieve4], "You earnt 10,000 XP! CIA class unlocked!");
				PlayerPlaySound(playerid, 1185 ,0.0, 0.0, 0.0);

				playerData[playerid][achieveTimer] = SetTimerEx("disableAchieve", 6000, false, "i", playerid);

				playerGiveXP(playerid, 25);
				playerData[playerid][playerScore] = playerData[playerid][playerScore] + 2;
				SetPlayerScore(playerid, playerData[playerid][playerScore]);
			}
			else if (playerData[playerid][playerXP] >= 20000 && oldXP < 20000)
			{
				disableAchieve(playerid);
				PlayerTextDrawShow(playerid, playerData[playerid][Achieve1]);
				PlayerTextDrawShow(playerid, playerData[playerid][Achieve2]);
				PlayerTextDrawShow(playerid, playerData[playerid][Achieve3]);
				PlayerTextDrawShow(playerid, playerData[playerid][Achieve4]);

				PlayerTextDrawSetString(playerid, playerData[playerid][Achieve3], "XP God");
				PlayerTextDrawSetString(playerid, playerData[playerid][Achieve4], "You earnt 20,000 XP! Army class unlocked!");
				PlayerPlaySound(playerid, 1185 ,0.0, 0.0, 0.0);

				playerData[playerid][achieveTimer] = SetTimerEx("disableAchieve", 6000, false, "i", playerid);

				playerGiveXP(playerid, 25);
				playerData[playerid][playerScore] = playerData[playerid][playerScore] + 2;
				SetPlayerScore(playerid, playerData[playerid][playerScore]);
			}
		}
	}
}

public hideAddedXP(playerid)
{
	if(IsPlayerConnected(playerid))
	{
		if(playerData[playerid][playerLoggedIn])
		{
			PlayerTextDrawSetString(playerid, playerData[playerid][playerAddedXPTD], " ");
		}
	}
}

public hideHitmarkerTD(playerid)
{
	if(IsPlayerConnected(playerid))
	{
		if(playerData[playerid][playerLoggedIn])
		{
			PlayerTextDrawSetString(playerid, playerData[playerid][playerHitmarkerTD], " ");
		}
	}
}

public Countdown()
{
	new msg[56];
	if(serverInfo[VIPcount] > 0)
	{
		foreach(new i : Player)
		{
			PlayerPlaySound(i, 1057, 0.0, 0.0, 0.0);
		}
		format(msg, sizeof(msg), "~r~%d", serverInfo[VIPcount]);
		GameTextForAll(msg, 1000, 3);
		serverInfo[VIPcount]--;
	}
	else
	{
		KillTimer(serverInfo[countTimer]);
		foreach(new i : Player)
		{
			PlayerPlaySound(i, 1058, 0.0, 0.0, 0.0);
		}
		GameTextForAll("~r~GO!!! ~g~GO!!! ~b~GO!!!", 1000, 3);
	}
	return 1;
}

public updateExperienceCounter(playerid)
{
	if(IsPlayerConnected(playerid))
	{
		if(playerData[playerid][playerLoggedIn])
		{
			new finalExperience[250];
			format(finalExperience, sizeof(finalExperience), "%08d", playerData[playerid][playerXP]);

			PlayerTextDrawSetString(playerid, playerData[playerid][playerExperience], finalExperience);
			// SetProgressBarValue(playerData[playerid][xpBar], xpProgress);
			// ShowProgressBarForPlayer(playerid, playerData[playerid][xpBar]);
		}
	}
}

public countMuteTime()
{
    for(new i = 0; i < MAX_PLAYERS; i++)
    {
        if(IsPlayerConnected(i))
        {
			if(playerData[i][playerMuteTime] >= 1)
			{
				playerData[i][playerMuteTime] = playerData[i][playerMuteTime] - 1;

				if(playerData[i][playerMuteTime] == 0)
				{
					SendClientMessage(i, COLOR_WHITE, "{FFDC2E}[UNMUTED] {FFFFFF}You have been unmuted!");
				}
			}
        }
    }
}

public checkNameStatus(playerName[])
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
			new playerName2[24];
			GetPlayerName(i, playerName2, sizeof(playerName2));
			if(strcmp(playerName2, playerName, true, strlen(playerName)) == 0)
			{
				return i;
			}
		}
	}

	return INVALID_PLAYER_ID;
}

public givePlayerWanted(playerid, amount)
{
	new newWantedLevel;

	if (playerData[playerid][mask])
	{
		newWantedLevel = playerData[playerid][playerWantedLevel] + amount / 2;
	}
	else
	{
		newWantedLevel = playerData[playerid][playerWantedLevel] + amount;
	}

	playerData[playerid][playerWantedLevel] = newWantedLevel;
	SetPlayerWantedLevel(playerid, newWantedLevel);
	newPlayerColour(playerid);
}

public sendMessageAdmins(message)
{
    new messageContent[128];
    format(messageContent, sizeof(messageContent), "%s", message);
    for(new i=0; i < MAX_PLAYERS; i++)
    {
        if(IsPlayerConnected(i))
        {
            if(playerData[i][playerLoggedIn])
            {
                if(playerData[i][playerLevel] > 0)
                {
                    format(messageContent, sizeof(messageContent), "{FF00FF}[CHEAT ALERT] {FFFFFF}%s", messageContent);
                    SendClientMessage(i, COLOR_WHITE, messageContent);
                }
            }
        }
    }
}

public randomEx(min, max)
{
    new rand = random (max - min) + min;
    return rand;
}

public playerGiveMoney(playerid, amount)
{
	playerData[playerid][playerMoney] = playerData[playerid][playerMoney] + amount;
	GivePlayerMoney(playerid, amount);

	savePlayerStats(playerid);
}

public playerTakeMoney(playerid, amount)
{
	playerData[playerid][playerMoney] = playerData[playerid][playerMoney] - amount;
	GivePlayerMoney(playerid, - amount);

	savePlayerStats(playerid);
}

public playerGiveBankMoney(playerid, amount)
{
	playerData[playerid][playerBank] = playerData[playerid][playerBank] + amount;

	savePlayerStats(playerid);
}

public playerTakeBankMoney(playerid, amount)
{
	playerData[playerid][playerBank] = playerData[playerid][playerBank] - amount;

	savePlayerStats(playerid);
}

public playerSetMoney(playerid, amount)
{
	ResetPlayerMoney(playerid);
	GivePlayerMoney(playerid, amount);
	playerData[playerid][playerMoney] = amount;
	savePlayerStats(playerid);
}

public beginRobbery(playerid)
{
	new message[128];
	for(new i; i < MAX_ROB_CHECKPOINT; i++)
	{
		if(IsPlayerInDynamicCP(playerid, checkpointIndex[i][2]))
		{
			new lastRobbedTime;

			lastRobbedTime = GetTickCount() - checkpointData[i][lastRobbed];

			if(lastRobbedTime > 120000 || checkpointData[i][lastRobbed] == 0)
			{
				if(checkpointData[i][storeStatus] == 1)
				{
					if (playerData[playerid][playerClass] == 0)
					{
						new Float:pX, Float:pY, Float:pZ, Float:vA, intWorld, virWorld;

						playerData[playerid][playerStoreID] = checkpointData[i][storeID];
						playerData[playerid][playerCheckID] = checkpointIndex[i][2];
						playerData[playerid][playerRobTime] = 15;
						checkpointData[i][storeStatus] = 0;

						ClearAnimations(playerid);
           				ApplyAnimation(playerid,"ROB_BANK","CAT_Safe_Rob", 1, 1, 0, 0, 0, 0, 1);
						SetPlayerAttachedObject(playerid, 0, 1550, 1, 0.158482, -0.203833, 0.000000, 167.302505, 79.854949, 342.084838, 1.000000, 1.000000, 1.000000);

						new tdStoreName[100];
						format(tdStoreName, sizeof(tdStoreName), "Robbing: ~w~%s", checkpointData[i][storeName]);
						PlayerTextDrawSetString(playerid, playerData[playerid][robTD][0], tdStoreName);

						PlayerTextDrawShow(playerid, playerData[playerid][robTD][0]);
						PlayerTextDrawShow(playerid, playerData[playerid][robTD][1]);
						PlayerTextDrawShow(playerid, playerData[playerid][robTD][2]);
						PlayerTextDrawShow(playerid, playerData[playerid][robTD][3]);
						

						GetPlayerPos(playerid, pX, pY, pZ);
						GetPlayerFacingAngle(playerid, vA);

						virWorld = GetPlayerVirtualWorld(playerid);
						intWorld = GetPlayerInterior(playerid);

						playerData[playerid][playerSafeObj] = CreateDynamicObject(1829, pX + (0.55 * floatsin(-vA, degrees)), pY + (0.55 * floatcos(-vA, degrees)), pZ - 0.5, 0, 0, vA, virWorld, intWorld, playerid, 100.0);
						playerData[playerid][robberyFriend] = INVALID_PLAYER_ID;
						foreach(new pl : Player)
						{
							if(GetPlayerTargetActor(pl) == checkpointData[i][storeActor])
							{
								playerData[playerid][robberyFriend] = pl;
								playerData[pl][targetActor] = checkpointData[i][storeActor];
								PlayerTextDrawSetString(pl, playerData[pl][robTD][0], tdStoreName);
								PlayerTextDrawShow(pl, playerData[pl][robTD][0]);
								PlayerTextDrawShow(pl, playerData[pl][robTD][1]);
								PlayerTextDrawShow(pl, playerData[pl][robTD][2]);
								PlayerTextDrawShow(pl, playerData[pl][robTD][3]);
								ApplyActorAnimation(checkpointData[i][storeActor], "SHOP", "SHP_HandsUp_Scr", 4.1, 0, 0, 0, 1, 0);
								break;
							}
						}
					}
					else
					{
						SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}Only civilians can rob this store");
					}
				}
				else
				{
					format(message, sizeof(message), "{B7B7B7}[SERVER] {FFFFFF}%s is currently being robbed", checkpointData[i][storeName]);
					SendClientMessage(playerid, COLOR_WHITE, message);
				}
			}
			else
			{
				format(message, sizeof(message), "{B7B7B7}[SERVER] {FFFFFF}%s has already been robbed, please wait!", checkpointData[i][storeName]);
				SendClientMessage(playerid, COLOR_WHITE, message);
			}
		}
	}
}

public updatePlayerRobbingProgress(playerid, robberyTime)
{
	new timeRemaining = robberyTime;

	if(timeRemaining == 1) PlayerTextDrawSetString(playerid, playerData[playerid][robTD][2], "l");
	else if(timeRemaining == 2) PlayerTextDrawSetString(playerid, playerData[playerid][robTD][2], "ll");
	else if(timeRemaining == 3) PlayerTextDrawSetString(playerid, playerData[playerid][robTD][2], "lll");
	else if(timeRemaining == 4) PlayerTextDrawSetString(playerid, playerData[playerid][robTD][2], "llll");
	else if(timeRemaining == 5) PlayerTextDrawSetString(playerid, playerData[playerid][robTD][2], "lllll");
	else if(timeRemaining == 6) PlayerTextDrawSetString(playerid, playerData[playerid][robTD][2], "llllll");
	else if(timeRemaining == 7) PlayerTextDrawSetString(playerid, playerData[playerid][robTD][2], "lllllll");
	else if(timeRemaining == 8) PlayerTextDrawSetString(playerid, playerData[playerid][robTD][2], "llllllll");
	else if(timeRemaining == 9) PlayerTextDrawSetString(playerid, playerData[playerid][robTD][2], "lllllllll");
	else if(timeRemaining == 10) PlayerTextDrawSetString(playerid, playerData[playerid][robTD][2], "llllllllll");
	else if(timeRemaining == 11) PlayerTextDrawSetString(playerid, playerData[playerid][robTD][2], "lllllllllll");
	else if(timeRemaining == 12) PlayerTextDrawSetString(playerid, playerData[playerid][robTD][2], "llllllllllll");
	else if(timeRemaining == 13) PlayerTextDrawSetString(playerid, playerData[playerid][robTD][2], "lllllllllllll");
	else if(timeRemaining == 14) PlayerTextDrawSetString(playerid, playerData[playerid][robTD][2], "llllllllllllll");
	if(timeRemaining == 0)
	{
		PlayerTextDrawHide(playerid, playerData[playerid][robTD][0]);
		PlayerTextDrawHide(playerid, playerData[playerid][robTD][1]);
		PlayerTextDrawHide(playerid, playerData[playerid][robTD][2]);
		PlayerTextDrawHide(playerid, playerData[playerid][robTD][3]);
	}

	if(IsPlayerConnected(playerData[playerid][robberyFriend]))
	{
		new pl = playerData[playerid][robberyFriend];
		if(playerData[pl][playerLoggedIn])
		{
			updatePlayerRobbingProgress(pl, timeRemaining);
		}
	}
}

public cancelRobbery(playerid)
{
	for(new i; i < MAX_ROB_CHECKPOINT; i++)
	{
		if(IsPlayerInDynamicCP(playerid, checkpointIndex[i][2]))
		{
			if(playerData[playerid][playerStoreID] > 0)
			{
				if(playerData[playerid][playerRobTime] > 0)
				{
					playerData[playerid][playerRobTime] = -1;
					checkpointData[i][storeStatus] = 1;
					playerData[playerid][playerStoreID] = -1;
					ClearAnimations(playerid);
					RemovePlayerAttachedObject(playerid, 0);
					DestroyDynamicObject(playerData[playerid][playerSafeObj]);
					updatePlayerRobbingProgress(playerid, 0);
					TextDrawHideForPlayer(playerid, newRob);
					HideProgressBarForPlayer(playerid, playerData[playerid][robbery]);
					if(IsPlayerConnected(playerData[playerid][robberyFriend]))
					{
						new pl = playerData[playerid][robberyFriend];
						if(playerData[pl][playerLoggedIn])
						{
							TextDrawHideForPlayer(pl, newRob);
							HideProgressBarForPlayer(pl, playerData[pl][robbery]);
							SendClientMessage(pl, -1, "{B7B7B7}[SERVER] {FFFFFF}Robbery failed, your team has canceled the robbery.");
							ClearActorAnimations(playerData[pl][targetActor]);
						}
					}
					playerData[playerid][robberyFriend] = INVALID_PLAYER_ID;
				}
			}
		}
	}
}

public forceRobberyCancel(playerid)
{
	if(playerData[playerid][playerStoreID] > 0)
	{
		if(playerData[playerid][playerRobTime] > 0)
		{
			if(playerData[playerid][playerCheckID] > 0)
			{
				new msg[128], pStoreID = playerData[playerid][playerStoreID] - 1;

				SendClientMessage(playerid, COLOR_WHITE, msg);
				checkpointData[pStoreID][storeStatus] = 1;
				playerData[playerid][playerRobTime] = -1;
				playerData[playerid][playerCheckID] = -1;
				playerData[playerid][playerStoreID] = -1;
				ClearAnimations(playerid);
				RemovePlayerAttachedObject(playerid, 0);
				DestroyDynamicObject(playerData[playerid][playerSafeObj]);
				updatePlayerRobbingProgress(playerid, 0);
				TextDrawHideForPlayer(playerid, newRob);
				if(IsPlayerConnected(playerData[playerid][robberyFriend]))
				{
					new pl = playerData[playerid][robberyFriend];
					if(playerData[pl][playerLoggedIn])
					{
						updatePlayerRobbingProgress(pl, 0);
						TextDrawHideForPlayer(pl, newRob);
						HideProgressBarForPlayer(pl, playerData[pl][robbery]);
						SendClientMessage(pl, -1, "{B7B7B7}[SERVER] {FFFFFF}Robbery failed, your team has canceled the robbery.");
						ClearActorAnimations(playerData[pl][targetActor]);
					}
				}
				playerData[playerid][robberyFriend] = INVALID_PLAYER_ID;
			}
		}
	}
}

public newPlayerColour(playerid)
{
	if(playerData[playerid][playerAdminDuty] == false)
	{
		if (playerData[playerid][isInDM])
		{
			SetPlayerColor(playerid, 0xFAAC58FF);
		}
		else
		{
			switch(playerData[playerid][playerClass])
			{
				case 0, 6:
				{
					if(playerData[playerid][playerWantedLevel] == 0)
					{
						if (playerData[playerid][vipColour])
						{
							SetPlayerColor(playerid, 0x58D3F7FF);
						}
						else
						{
							if(playerData[playerid][playerClass] == CLASS_MEDIC)
							{
								// Medic Colour
								SetPlayerColor(playerid, CLASS_MEDIC_COLOUR);
							}
							else if(playerData[playerid][playerClass] == CLASS_FIREFIGHTER)
							{
								// Medic Colour
								SetPlayerColor(playerid, CLASS_FIREFIGHTER_COLOUR);
							}
							else
							{
								// White Wanted Level
								SetPlayerColor(playerid, CLASS_CIVILIAN_COLOUR);
							}
						}
					}

					if (playerData[playerid][playerWantedLevel] >= 1)
					{
						// Yellow Wanted Level
						SetPlayerColor(playerid, CLASS_CIVILIAN_YELLOW);
					}

					if(playerData[playerid][playerWantedLevel] >= 6)
					{
						// Orange Wanted Level
						SetPlayerColor(playerid, CLASS_CIVILIAN_ORANGE);
					}

					if(playerData[playerid][playerWantedLevel] >= 25)
					{
						// Red Wanted Level
						SetPlayerColor(playerid, CLASS_CIVILIAN_RED);
					}

					if(playerData[playerid][playerWantedLevel] > 0)
					{
						if (playerData[playerid][playerClass] == CLASS_CIVILIAN)
						{
							new wantedText[200];
							format(wantedText, sizeof(wantedText), "%i Stars", playerData[playerid][playerWantedLevel]);
							PlayerTextDrawSetString(playerid, playerData[playerid][wantedStars], wantedText);
						}
						else
						{
							PlayerTextDrawSetString(playerid, playerData[playerid][wantedStars], " ");
						}
					}
					else
					{
						PlayerTextDrawSetString(playerid, playerData[playerid][wantedStars], " ");
					}
				}
				case 1:
				{
					if (playerData[playerid][vipColour])
					{
						SetPlayerColor(playerid, COLOR_PURPLE);
					}
					else
					{
						SetPlayerColor(playerid, CLASS_POLICE_COLOUR);
					}
				}
				case 2:
				{
					if (playerData[playerid][vipColour])
					{
						SetPlayerColor(playerid, COLOR_PURPLE);
					}
					else
					{
						SetPlayerColor(playerid, CLASS_ARMY_COLOUR);
					}
				}
				case 3:
				{
					if (playerData[playerid][vipColour])
					{
						SetPlayerColor(playerid, COLOR_PURPLE);
					}
					else
					{
						SetPlayerColor(playerid, CLASS_CIA_COLOUR);
					}
				}
				case 4:
				{
					if (playerData[playerid][vipColour])
					{
						SetPlayerColor(playerid, COLOR_PURPLE);
					}
					else
					{
						SetPlayerColor(playerid, CLASS_FBI_COLOUR);
					}
				}
				case 7:
				{
					if (playerData[playerid][vipColour])
					{
						SetPlayerColor(playerid, COLOR_PURPLE);
					}
					else
					{
						SetPlayerColor(playerid, CLASS_SECRETSERVICE_COLOUR);
					}
				}
			}
		}
	}
	else
	{
		SetPlayerColor(playerid, 0x6AEE39FF);
	}
}

public countRobTime()
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
			if(playerData[i][playerLoggedIn])
			{
				if(playerData[i][playerRobTime] > 0)
				{
					if(playerData[i][playerStoreID] > 0)
					{
						if(IsPlayerInDynamicCP(i, playerData[i][playerCheckID]))
						{
							new pl = playerData[i][robberyFriend];
							playerData[i][playerRobTime]--;
							updatePlayerRobbingProgress(i, playerData[i][playerRobTime]);
							if(IsPlayerConnected(pl))
							{
								if(playerData[pl][playerLoggedIn])
								{
									if(GetPlayerTargetActor(pl) != playerData[pl][targetActor])
									{
										updatePlayerRobbingProgress(pl, 0);
										TextDrawHideForPlayer(pl, newRob);
										HideProgressBarForPlayer(pl, playerData[pl][robbery]);
										ClearActorAnimations(playerData[pl][targetActor]);
										SendClientMessage(i, -1, "{B7B7B7}[SERVER] {FFFFFF}Robbery failed, your team is no longer aiming store actor.");
										playerData[i][robberyFriend] = INVALID_PLAYER_ID;
										forceRobberyCancel(i);
									}
								}
							}

							if(playerData[i][playerRobTime] == 0)
							{
							    new moneyToGive, message2[328], playerName[24], currentStoreID, robberyBonus;
							    new randomNum = random(4);
							    if (randomNum != 0 || playerData[i][luckyCharm] || playerData[i][playerRobberies] < 5)
							    {
    								currentStoreID = playerData[i][playerStoreID] - 1;

									if (playerData[i][playerBiggerPockets])
									{
										// $500 bonus
										moneyToGive = randomEx(checkpointData[currentStoreID][lowestCash], checkpointData[currentStoreID][highestCash]);
										robberyBonus = (moneyToGive / 2);
									}
									else
									{
										// No bonuses
										moneyToGive = randomEx(checkpointData[currentStoreID][lowestCash], checkpointData[currentStoreID][highestCash]);
									}

    								checkpointData[currentStoreID][lastRobbed] = GetTickCount();
    								checkpointData[currentStoreID][storeStatus] = 1;

    								playerData[i][playerRobTime] = -1;
    								playerData[i][playerRobberies]++;
    								playerGiveMoney(i, moneyToGive);
									playerGiveMoney(i, robberyBonus);
    								GetPlayerName(i, playerName, sizeof(playerName));
    								ClearAnimations(i);
    								RemovePlayerAttachedObject(i, 0);
    								DestroyDynamicObject(playerData[i][playerSafeObj]);

    								if(IsPlayerConnected(pl))
									{
										if(playerData[pl][playerLoggedIn])
										{
		    								playerGiveMoney(pl, moneyToGive);
											playerGiveMoney(pl, robberyBonus);
											ClearActorAnimations(playerData[pl][targetActor]);
										}
									}

									if (playerData[i][playerBiggerPockets])
									{
										// Has a bonus
										format(message2, sizeof(message2), "{FF0000}[ROBBERY] {FFFFFF}%s(%i) robbed %s and received {FFDC2E}$%s {FFFFFF}({58D3F7}+$%s{FFFFFF})", playerName, i, checkpointData[currentStoreID][storeName], FormatNumber(moneyToGive), FormatNumber(robberyBonus));
										if(IsPlayerConnected(pl))
										{
											if(playerData[pl][playerLoggedIn])
											{
												new plname[MAX_PLAYER_NAME];
												GetPlayerName(pl, plname, MAX_PLAYER_NAME);
												format(message2, sizeof(message2), "{FF0000}[ROBBERY] {FFFFFF}%s(%i) and %s(%i) robbed %s and received {FFDC2E}$%s {FFFFFF}({58D3F7}+$%s{FFFFFF})", playerName, i, plname, pl, checkpointData[currentStoreID][storeName], FormatNumber(moneyToGive * 2), FormatNumber(robberyBonus * 2));
											}
										}
									}
									else
									{
										// No bonus
										format(message2, sizeof(message2), "{FF0000}[ROBBERY] {FFFFFF}%s(%i) robbed %s and received {FFDC2E}$%s {FFFFFF}", playerName, i, checkpointData[currentStoreID][storeName], FormatNumber(moneyToGive));
										if(IsPlayerConnected(pl))
										{
											if(playerData[pl][playerLoggedIn])
											{
												new plname[MAX_PLAYER_NAME];
												GetPlayerName(pl, plname, MAX_PLAYER_NAME);
												format(message2, sizeof(message2), "{FF0000}[ROBBERY] {FFFFFF}%s(%i) and %s(%i) robbed %s and received {FFDC2E}$%s", playerName, i, plname, pl, checkpointData[currentStoreID][storeName], FormatNumber(moneyToGive * 2));
											}
										}
									}

									if (playerData[i][mask])
									{
										SendClientMessage(i, COLOR_WHITE, message2);
										if(IsPlayerConnected(pl))
										{
											if(playerData[pl][playerLoggedIn])
											{
												SendClientMessage(pl, COLOR_WHITE, message2);
											}
										}
									}
									else
									{
										SendClientMessageToAll(COLOR_WHITE, message2);
									}

    								givePlayerWanted(i, 6);
									playerGiveXP(i, 20);
    								sendWantedMessage(i, 6);
									playerData[i][playerScore] = playerData[i][playerScore] + 1;
									SetPlayerScore(i, playerData[i][playerScore]);
									TextDrawHideForPlayer(i, newRob);
									newPlayerColour(i);

									if(IsPlayerConnected(pl))
									{
										if(playerData[pl][playerLoggedIn])
										{
											givePlayerWanted(pl, 6);
											playerGiveXP(pl, 20);
		    								sendWantedMessage(pl, 6);
											playerData[pl][playerScore] = playerData[pl][playerScore] + 1;
											SetPlayerScore(pl, playerData[pl][playerScore]);
											TextDrawHideForPlayer(pl, newRob);
											newPlayerColour(pl);
										}
									}									
									if (playerData[i][playerRobberies] == 1)
									{
										disableAchieve(i);
										PlayerTextDrawShow(i, playerData[i][Achieve1]);
										PlayerTextDrawShow(i, playerData[i][Achieve2]);
										PlayerTextDrawShow(i, playerData[i][Achieve3]);
										PlayerTextDrawShow(i, playerData[i][Achieve4]);

										PlayerTextDrawSetString(i, playerData[i][Achieve3], "Cat Burgler");
										PlayerTextDrawSetString(i, playerData[i][Achieve4], "You robbed your first store!");
										PlayerPlaySound(i, 1185 ,0.0, 0.0, 0.0);

										playerData[i][achieveTimer] = SetTimerEx("disableAchieve", 6000, false, "i", i);

										playerGiveXP(i, 50);
										playerData[i][playerScore] = playerData[i][playerScore] + 2;
										SetPlayerScore(i, playerData[i][playerScore]);
										savePlayerStats(i);
									}
									else if (playerData[i][playerRobberies] == 50)
									{
										disableAchieve(i);
										PlayerTextDrawShow(i, playerData[i][Achieve1]);
										PlayerTextDrawShow(i, playerData[i][Achieve2]);
										PlayerTextDrawShow(i, playerData[i][Achieve3]);
										PlayerTextDrawShow(i, playerData[i][Achieve4]);

										PlayerTextDrawSetString(i, playerData[i][Achieve3], "Established Thief");
										PlayerTextDrawSetString(i, playerData[i][Achieve4], "You robbed 50 stores!");
										PlayerPlaySound(i, 1183 ,0.0, 0.0, 0.0);

										playerData[i][achieveTimer] = SetTimerEx("disableAchieve", 6000, false, "i", i);

										playerGiveXP(i, 50);
										playerData[i][playerScore] = playerData[i][playerScore] + 2;
										SetPlayerScore(i, playerData[i][playerScore]);
										savePlayerStats(i);
									}
									else if (playerData[i][playerRobberies] == 100)
									{
										disableAchieve(i);
										PlayerTextDrawShow(i, playerData[i][Achieve1]);
										PlayerTextDrawShow(i, playerData[i][Achieve2]);
										PlayerTextDrawShow(i, playerData[i][Achieve3]);
										PlayerTextDrawShow(i, playerData[i][Achieve4]);

										PlayerTextDrawSetString(i, playerData[i][Achieve3], "Master Thief");
										PlayerTextDrawSetString(i, playerData[i][Achieve4], "You robbed 100 stores!");
										PlayerPlaySound(i, 1183 ,0.0, 0.0, 0.0);

										playerData[i][achieveTimer] = SetTimerEx("disableAchieve", 6000, false, "i", i);

										playerGiveXP(i, 50);
										playerData[i][playerScore] = playerData[i][playerScore] + 2;
										SetPlayerScore(i, playerData[i][playerScore]);
										savePlayerStats(i);
									}
									else if (playerData[i][playerRobberies] == 200)
									{
										disableAchieve(i);
										PlayerTextDrawShow(i, playerData[i][Achieve1]);
										PlayerTextDrawShow(i, playerData[i][Achieve2]);
										PlayerTextDrawShow(i, playerData[i][Achieve3]);
										PlayerTextDrawShow(i, playerData[i][Achieve4]);

										PlayerTextDrawSetString(i, playerData[i][Achieve3], "The Heist");
										PlayerTextDrawSetString(i, playerData[i][Achieve4], "Lucky Charm unlocked!");
										PlayerPlaySound(i, 1183 ,0.0, 0.0, 0.0);

										playerData[i][achieveTimer] = SetTimerEx("disableAchieve", 6000, false, "i", i);

										playerGiveXP(i, 50);
										playerData[i][playerScore] = playerData[i][playerScore] + 2;
										SetPlayerScore(i, playerData[i][playerScore]);
										savePlayerStats(i);
									}
									playerData[i][robberyFriend] = INVALID_PLAYER_ID;
                                }
                                else
                                {
    								currentStoreID = playerData[i][playerStoreID] - 1;
    								moneyToGive = randomEx(checkpointData[currentStoreID][lowestCash], checkpointData[currentStoreID][highestCash]);

    								checkpointData[currentStoreID][lastRobbed] = GetTickCount();
    								checkpointData[currentStoreID][storeStatus] = 1;

    								playerData[i][playerRobTime] = -1;
    								playerData[i][playerRobberies]++;
    								GetPlayerName(i, playerName, sizeof(playerName));
    								ClearAnimations(i);
    								RemovePlayerAttachedObject(i, 0);
    								DestroyDynamicObject(playerData[i][playerSafeObj]);

    								format(message2, sizeof(message2), "{FF0000}[ROBBERY] {FFFFFF}%s(%i) attempted to rob %s and failed", playerName, i, checkpointData[currentStoreID][storeName]);
    								if(IsPlayerConnected(pl))
									{
										if(playerData[pl][playerLoggedIn])
										{
											new plname[MAX_PLAYER_NAME];
											GetPlayerName(pl, plname, MAX_PLAYER_NAME);
											format(message2, sizeof(message2), "{FF0000}[ROBBERY] {FFFFFF}%s(%i) and %s(%i) attempted to rob %s and failed", playerName, i, plname, pl, checkpointData[currentStoreID][storeName]);
											givePlayerWanted(pl, 6);
		    								sendWantedMessage(pl, 6);
											TextDrawHideForPlayer(pl, newRob);
											newPlayerColour(pl);
										}
									}

    								SendClientMessageToAll(COLOR_WHITE, message2);

    								// Add to player's wanted level
    								givePlayerWanted(i, 6);
    								sendWantedMessage(i, 6);
									TextDrawHideForPlayer(i, newRob);
									newPlayerColour(i);
									playerData[i][robberyFriend] = INVALID_PLAYER_ID;
                                }
							}
						}
						else
						{
							forceRobberyCancel(i);
						}
					}
				}
			}
		}
	}
}

public arrest(playerid)
{
	playerData[playerid][playerCanArrest] = true;
	KillTimer(playerData[playerid][arrestTimer]);
    return 1;
}

public reFix(playerid)
{
	playerData[playerid][playerCanRepair] = true;
	KillTimer(playerData[playerid][fixTimer]);
    return 1;
}

public reFlip(playerid)
{
	playerData[playerid][playerCanFlip] = true;
	KillTimer(playerData[playerid][flipTimer]);
    return 1;
}

public reNOS(playerid)
{
	playerData[playerid][playerCanNOS] = true;
	KillTimer(playerData[playerid][nosTimer]);
    return 1;
}

public reEMP(playerid)
{
	playerData[playerid][playerCanEMP] = true;
	KillTimer(playerData[playerid][reEMPTimer]);
    return 1;
}

public mechReEmp(playerid)
{
	playerData[playerid][playerCanREMP] = true;
	KillTimer(playerData[playerid][mechREMPTimer]);
    return 1;
}

public resetEMP(vehicleID)
{
    new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(vehicleID, engine, lights, alarm, doors, bonnet, boot, objective);
	SetVehicleParamsEx(vehicleID, 1, lights, alarm, doors, bonnet, boot, objective);
	KillTimer(resetEMPTimer[vehicleID]);
    return 1;
}

public untie(playerid)
{
	ClearAnimations(playerid);
	playerData[playerid][playerIsTied] = false;

    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
	KillTimer(playerData[playerid][untieTimer]);
	TogglePlayerControllable(playerid, true);

	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		new message[128], playerName[24];
		if(IsPlayerConnected(i))
		{
			if(playerData[i][playerLoggedIn])
			{
				if(i == playerid)
				{
					SendClientMessage(playerid, COLOR_WHITE, "{FFDC2E}[ANTI-ABUSE] {FFFFFF}You have been un-tied by the anti-abuse system.");
					Delete3DTextLabel(playerData[playerid][kidnappedLabel]);
				}
				else
				{
					GetPlayerName(playerid, playerName, sizeof(playerName));
					format(message, sizeof(message), "{FFDC2E}[ANTI-ABUSE] {FFFFFF}%s(%i) has been un-tied by the anti-abuse system.", playerName, playerid);
					SendClientMessage(i, COLOR_WHITE, message);
				}
			}
		}
	}

    return 1;
}

public uncuff(playerid)
{
	ClearAnimations(playerid);
	playerData[playerid][playerIsCuffed] = false;
	TogglePlayerControllable(playerid, 1);

    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

	KillTimer(playerData[playerid][uncuffTimer]);

	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		new message[128], playerName[24];
		if(IsPlayerConnected(i))
		{
			if(playerData[i][playerLoggedIn])
			{
				if(i == playerid)
				{
					SendClientMessage(playerid, COLOR_WHITE, "{FFDC2E}[ANTI-ABUSE] {FFFFFF}You have been uncuffed by the anti-abuse system.");
				}
				else
				{
					GetPlayerName(playerid, playerName, sizeof(playerName));
					format(message, sizeof(message), "{FFDC2E}[ANTI-ABUSE] {FFFFFF}%s(%i) has been uncuffed by the anti-abuse system.", playerName, playerid);
					SendClientMessage(i, COLOR_WHITE, message);
				}
			}
		}
	}

    return 1;
}

public rebreakcuffs(playerid)
{
	playerData[playerid][canBreakCuffs] = true;
	KillTimer(playerData[playerid][breakCuffsTimer]);
    return 1;
}

public recuff(playerid)
{
	playerData[playerid][playerCanCuff] = true;
	KillTimer(playerData[playerid][recuffTimer]);
    return 1;
}

public Unfreeze(playerid)
{
	ClearAnimations(playerid);
    TogglePlayerControllable(playerid, 1);
	playerData[playerid][playerIsTazed] = false;
	KillTimer(playerData[playerid][unfreezeTimer]);
    return 1;
}

public Retaze(playerid)
{
	playerData[playerid][playerCanTaze] = true;
	KillTimer(playerData[playerid][retazeTimer]);
    return 1;
}

public pHouseCP(playerid)
{
	playerData[playerid][pEnterHouse] = true;
	KillTimer(playerData[playerid][hcpTimer]);
    return 1;
}

public isPlayerInRangeOfPlayer(playerid, otherid, Float:cRadius)
{
    new Float:cX, Float:cY, Float:cZ;

    GetPlayerPos(otherid, cX, cY, cZ);

    if(IsPlayerInRangeOfPoint(playerid, cRadius, cX, cY, cZ))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

public clearWorldObjects(playerid)
{
	RemoveBuildingForPlayer(playerid, 1411, -1656.14331, -10.63583, 5.05489, 5.38907289505);
	RemoveBuildingForPlayer(playerid, 1411, -1662.51416, -4.41222, 5.21241, 5.38907289505);
	RemoveBuildingForPlayer(playerid, 1411, -1668.75586, 1.87025, 5.1631, 5.38907289505);
	RemoveBuildingForPlayer(playerid, 967, -1674.96094, 5.55469, 2.51563, 4.1212320327759);
	RemoveBuildingForPlayer(playerid, 966, -1676.25781, 4.65625, 2.51563, 6.0111284255981);
	RemoveBuildingForPlayer(playerid, 968, -1676.22656, 4.625, 3.24219, 5.5763330459595);
	RemoveBuildingForPlayer(playerid, 1411, -1676.03296, 9.0714, 5.25612, 5.38907289505);
	RemoveBuildingForPlayer(playerid, 1278, -1706.11719, 33.16406, 16.61719, 16.251438140869);
	RemoveBuildingForPlayer(playerid, 10831, -1706.47656, 13.01563, 7.40625, 30.153728485107);
	RemoveBuildingForPlayer(playerid, 10840, -1666.1250, -62.0781, 10.9453, 0.25);
	RemoveBuildingForPlayer(playerid, 10912, -1666.1250, -62.0781, 10.9453, 0.25);
	RemoveBuildingForPlayer(playerid, 10914, -1706.4766, 13.0156, 7.4063, 0.25);
	RemoveBuildingForPlayer(playerid, 10831, -1706.4766, 13.0156, 7.4063, 0.25);
	
	//viphouse near jazzy
	RemoveBuildingForPlayer(playerid, 1468, -2406.2734, 1400.8750, 8.1250, 0.25);
	RemoveBuildingForPlayer(playerid, 1468, -2395.7266, 1400.8750, 8.1250, 0.25);
	RemoveBuildingForPlayer(playerid, 1468, -2401.0000, 1400.8750, 8.1250, 0.25);
	RemoveBuildingForPlayer(playerid, 1468, -2390.4453, 1400.8750, 8.1250, 0.25);

	// 1.2.1
	RemoveBuildingForPlayer(playerid, 9900, -1753.7109, 884.3906, 159.9766, 0.25);
	RemoveBuildingForPlayer(playerid, 9933, -1753.6250, 884.4531, 179.2656, 0.25);
	RemoveBuildingForPlayer(playerid, 9936, -1753.7109, 884.3906, 159.9766, 0.25);
	RemoveBuildingForPlayer(playerid, 10165, -1753.7813, 884.3906, 35.1172, 0.25);
	RemoveBuildingForPlayer(playerid, 10235, -1753.7813, 884.3906, 35.1172, 0.25);
	RemoveBuildingForPlayer(playerid, 10260, -1753.7422, 884.3984, 25.3438, 0.25);
	RemoveBuildingForPlayer(playerid, 1496, -1618.6016, 680.9141, 6.1719, 0.25);

	RemoveBuildingForPlayer(playerid, 3924, -1086.0938, 1061.1875, 1360.5703, 0.25);
	RemoveBuildingForPlayer(playerid, 3932, -1131.9453, 1029.1406, 1346.4063, 0.25);
	RemoveBuildingForPlayer(playerid, 3936, -974.5547, 1059.4609, 1344.7734, 0.25);
	RemoveBuildingForPlayer(playerid, 3937, -1130.9219, 1059.4609, 1345.4688, 0.25);
	RemoveBuildingForPlayer(playerid, 3939, -975.0469, 1089.6563, 1345.6563, 0.25);
	RemoveBuildingForPlayer(playerid, 3958, -1142.0078, 1001.9141, 1348.4219, 0.25);
	RemoveBuildingForPlayer(playerid, 3959, -1061.8906, 1057.3125, 1369.3359, 0.25);
	RemoveBuildingForPlayer(playerid, 1596, -1132.6953, 1073.9922, 1354.7500, 0.25);
	RemoveBuildingForPlayer(playerid, 1596, -973.5625, 1046.0703, 1353.9688, 0.25);


	//Custom Mappings
    RemoveBuildingForPlayer(playerid, 3339, 1297.2813, 173.5781, 19.4609, 0.25);
	RemoveBuildingForPlayer(playerid, 3340, 1308.3984, 168.1406, 19.4063, 0.25);
	RemoveBuildingForPlayer(playerid, 3341, 1281.2266, 158.0938, 19.3438, 0.25);
	RemoveBuildingForPlayer(playerid, 3343, 1295.9844, 158.7422, 19.3828, 0.25);
	RemoveBuildingForPlayer(playerid, 3343, 1305.0391, 184.9141, 19.3438, 0.25);
	RemoveBuildingForPlayer(playerid, 3345, 1298.6094, 194.2656, 19.3281, 0.25);
	RemoveBuildingForPlayer(playerid, 3345, 1305.2656, 152.7734, 19.2969, 0.25);
	RemoveBuildingForPlayer(playerid, 3344, 1299.7109, 138.7344, 19.3438, 0.25);
	RemoveBuildingForPlayer(playerid, 3344, 1313.9688, 179.8438, 19.3594, 0.25);
	RemoveBuildingForPlayer(playerid, 3594, 1265.5703, 153.3828, 19.4609, 0.25);
	RemoveBuildingForPlayer(playerid, 769, 1267.9141, 146.8203, 19.1953, 0.25);
	RemoveBuildingForPlayer(playerid, 3170, 1281.2266, 158.0938, 19.3438, 0.25);
	RemoveBuildingForPlayer(playerid, 3594, 1280.9297, 147.3125, 20.0078, 0.25);
	RemoveBuildingForPlayer(playerid, 3168, 1295.9844, 158.7422, 19.3828, 0.25);
	RemoveBuildingForPlayer(playerid, 3171, 1299.7109, 138.7344, 19.3438, 0.25);
	RemoveBuildingForPlayer(playerid, 3172, 1305.2656, 152.7734, 19.2969, 0.25);
	RemoveBuildingForPlayer(playerid, 1308, 1301.2578, 147.3828, 18.8203, 0.25);
	RemoveBuildingForPlayer(playerid, 780, 1301.5938, 154.5078, 19.3281, 0.25);
	RemoveBuildingForPlayer(playerid, 3594, 1271.3125, 163.3906, 19.4375, 0.25);
	RemoveBuildingForPlayer(playerid, 1294, 1264.5469, 172.2188, 23.0078, 0.25);
	RemoveBuildingForPlayer(playerid, 1308, 1281.5156, 165.5313, 18.8203, 0.25);
	RemoveBuildingForPlayer(playerid, 1440, 1297.0703, 179.2266, 19.9453, 0.25);
	RemoveBuildingForPlayer(playerid, 1440, 1293.5547, 163.8828, 19.9453, 0.25);
	RemoveBuildingForPlayer(playerid, 3168, 1305.0391, 184.9141, 19.3438, 0.25);
	RemoveBuildingForPlayer(playerid, 3169, 1297.2813, 173.5781, 19.4609, 0.25);
	RemoveBuildingForPlayer(playerid, 775, 1301.2734, 164.2656, 19.3516, 0.25);
	RemoveBuildingForPlayer(playerid, 764, 1303.6328, 173.3984, 18.9375, 0.25);
	RemoveBuildingForPlayer(playerid, 3171, 1313.9688, 179.8438, 19.3594, 0.25);
	RemoveBuildingForPlayer(playerid, 3167, 1308.3984, 168.1406, 19.4063, 0.25);
	RemoveBuildingForPlayer(playerid, 1308, 1308.2656, 174.2891, 18.8203, 0.25);
	RemoveBuildingForPlayer(playerid, 1440, 1313.3203, 167.0313, 19.9453, 0.25);
	RemoveBuildingForPlayer(playerid, 3172, 1298.6094, 194.2656, 19.3281, 0.25);
	RemoveBuildingForPlayer(playerid, 1308, 1274.1875, 191.4609, 18.8203, 0.25);
	RemoveBuildingForPlayer(playerid, 1438, 1276.1172, 190.2266, 18.6094, 0.25);
	RemoveBuildingForPlayer(playerid, 617, 1324.7266, 187.3516, 17.7813, 0.25);
	RemoveBuildingForPlayer(playerid, 1440, 1318.3828, 196.0547, 19.6094, 0.25);
	RemoveBuildingForPlayer(playerid, 705, 1290.4766, 198.6797, 18.7656, 0.25);
	RemoveBuildingForPlayer(playerid, 13441, 1338.0625, 198.7344, 30.0234, 0.25);

	// Sweeper
	RemoveBuildingForPlayer(playerid, 1283, -2007.8828, 945.3906, 47.5234, 0.25);
	RemoveBuildingForPlayer(playerid, 1283, -2000.7578, 903.7891, 47.5234, 0.25);
	RemoveBuildingForPlayer(playerid, 1284, -1990.9922, 931.7031, 47.6094, 0.25);
	RemoveBuildingForPlayer(playerid, 1232, -1552.7578, 1231.6094, 8.8047, 0.25);

	// Jail
	RemoveBuildingForPlayer(playerid, 1771, 216.6484, 108.4219, 998.6719, 0.25);
	RemoveBuildingForPlayer(playerid, 1771, 220.5703, 108.4219, 998.6719, 0.25);
	RemoveBuildingForPlayer(playerid, 1771, 224.5625, 108.4219, 998.6719, 0.25);
	RemoveBuildingForPlayer(playerid, 2165, 223.0703, 120.0625, 998.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 2165, 223.0703, 122.0469, 998.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 1806, 223.3984, 120.4219, 998.0000, 0.25);
	RemoveBuildingForPlayer(playerid, 2356, 224.2031, 121.7266, 997.9922, 0.25);
	RemoveBuildingForPlayer(playerid, 1771, 228.7031, 108.4219, 998.6719, 0.25);
	RemoveBuildingForPlayer(playerid, 1806, 226.7500, 119.2578, 998.0000, 0.25);
	RemoveBuildingForPlayer(playerid, 2165, 227.1094, 118.9297, 998.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 14895, 234.7031, 122.0625, 1004.3203, 0.25);
}

public addWorldObjects()
{
	// Car Spawn Points
	/*
	CreateObject(1216, -1754.24011, 957.25983, 24.54695,   0.00000, 0.00000, -0.48000); // d
	CreateObject(1216, -1493.71191, 907.27802, 6.75172,   0.00000, 0.00000, -90.59999); // d
	CreateObject(1216, -1998.18066, 119.40524, 27.31461,   0.00000, 0.00000, 0.00000); // d
	CreateObject(1216, -1551.81201, 1183.52417, 6.83623,   0.00000, 0.00000, -88.14010); // d
	CreateObject(1216, -1772.55579, 1083.62207, 45.07680,   0.00000, 0.00000, 178.31992); // d
	CreateObject(1216, -2515.02759, -16.88707, 25.19635,   0.00000, 0.00000, 30.60000); // d
	CreateObject(1216, -2016.23254, 901.00342, 45.13615,   0.00000, 0.00000, 90.06001); // d
	CreateObject(1216, -1600.57239, 729.24384, -5.29116,   0.00000, 0.00000, 177.90007); // d
	CreateObject(1216, -1977.40125, 239.38686, 34.82018,   0.00000, 0.00000, 180.65994); // d*/
	
	//new bank
	/*CreateObject(7419, -1472.54419, 885.54639, -0.50126,   0.00000, 0.00000, 0.23998);
	CreateObject(4002, -1483.05457, 957.29620, 28.06814,   0.00000, 0.00000, 270.05994);
	CreateObject(4002, -1459.27429, 957.31073, 28.14024,   0.00000, 0.00000, 270.05994);
	CreateDynamicObject(2631, -1502.49316, 955.69470, 6.18066,   0.00000, 0.00000, 0.18000);
	CreateDynamicObject(2631, -1502.50403, 957.59314, 6.18066,   0.00000, 0.00000, 0.18000);
	CreateDynamicObject(2631, -1506.44312, 953.72559, 6.18066,   0.00000, 0.00000, 0.18000);
	CreateDynamicObject(2631, -1506.42493, 957.58557, 6.18066,   0.00000, 0.00000, 0.18000);
	CreateDynamicObject(2631, -1510.35437, 957.55048, 6.18066,   0.00000, 0.00000, 0.18000);
	CreateDynamicObject(2631, -1510.38989, 953.68384, 6.18066,   0.00000, 0.00000, 0.18000);
	CreateDynamicObject(2773, -1501.67310, 953.03485, 6.73982,   0.00000, 0.00000, -90.90003);
	CreateDynamicObject(2773, -1503.99170, 953.06592, 6.73982,   0.00000, 0.00000, -90.90003);
	CreateDynamicObject(2773, -1506.29980, 953.09808, 6.73982,   0.00000, 0.00000, -90.90003);
	CreateDynamicObject(2773, -1508.61267, 953.08704, 6.73982,   0.00000, 0.00000, -90.90003);
	CreateDynamicObject(2773, -1510.93091, 953.10406, 6.73982,   0.00000, 0.00000, -90.90003);
	CreateDynamicObject(2773, -1501.70105, 958.28931, 6.73982,   0.00000, 0.00000, -90.90003);
	CreateDynamicObject(2773, -1504.06238, 958.31903, 6.73982,   0.00000, 0.00000, -90.90003);
	CreateDynamicObject(2773, -1506.40540, 958.34485, 6.73982,   0.00000, 0.00000, -90.90003);
	CreateDynamicObject(2773, -1508.72864, 958.35272, 6.73982,   0.00000, 0.00000, -90.90003);
	CreateDynamicObject(2773, -1511.07544, 958.41693, 6.73982,   0.00000, 0.00000, -90.90003);
	CreateDynamicObject(19978, -1517.92236, 848.34686, 6.17663,   0.00000, 0.00000, -129.78001);
	CreateDynamicObject(19978, -1516.97595, 859.35718, 6.17663,   0.00000, 0.00000, -57.78002);
	CreateDynamicObject(1257, -1536.27356, 981.64691, 7.37975,   0.00000, 0.00000, 32.69999);
	CreateDynamicObject(1257, -1522.56628, 870.67206, 7.37470,   0.00000, 0.00000, -4.98000);
	CreateDynamicObject(1568, -1511.90686, 950.77637, 6.16775,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1568, -1512.04517, 960.49341, 6.16775,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1557, -1500.46375, 954.18561, 6.22238,   0.00000, 0.00000, 90.29996);
	CreateDynamicObject(1557, -1500.47034, 957.14789, 6.22239,   0.00000, 0.00000, 270.59973);
	CreateDynamicObject(2631, -1502.52466, 953.77264, 6.18066,   0.00000, 0.00000, 0.18000);
	CreateDynamicObject(2631, -1506.44812, 955.64001, 6.18066,   0.00000, 0.00000, 0.18000);
	CreateDynamicObject(2631, -1510.37463, 955.62012, 6.18066,   0.00000, 0.00000, 0.18000);
	CreateDynamicObject(7092, -1493.17236, 939.64020, 19.27785,   0.00000, 33.00000, 0.00000);
	CreateDynamicObject(1622, -1500.86963, 953.61346, 10.67560,   0.00000, -11.00000, -48.19997);
	CreateDynamicObject(1622, -1501.05933, 957.41064, 10.67560,   0.00000, -11.00000, -27.79998);
	CreateDynamicObject(1550, -1500.79163, 953.26910, 6.56530,   0.00000, -33.00000, 207.60001);
	CreateDynamicObject(1550, -1500.72815, 953.74512, 6.56530,   0.00000, -33.00000, 139.80002);
	CreateDynamicObject(1550, -1500.92749, 953.53662, 6.30930,   0.00000, 55.00000, 140.00000);
	CreateDynamicObject(1550, -1500.68652, 957.90552, 6.56530,   0.00000, -33.00000, 139.80002);
	CreateDynamicObject(1550, -1500.70789, 957.48865, 6.56530,   0.00000, -33.00000, 207.60001);
	CreateDynamicObject(1550, -1500.90662, 957.63678, 6.30930,   0.00000, 55.00000, 140.00000);
	CreateDynamicObject(2452, -1500.77344, 948.85309, 6.15149,   0.00000, 0.00000, -91.19999);
	CreateDynamicObject(19126, -1499.59985, 941.16272, 6.61044,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19126, -1499.81677, 970.30438, 6.61044,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19126, -1503.00244, 968.36475, 6.61044,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19126, -1506.26331, 966.18365, 6.61044,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19126, -1509.30371, 963.98627, 6.61044,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19126, -1502.45654, 943.11005, 6.61044,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19126, -1505.29614, 945.19739, 6.61044,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(19126, -1508.25940, 947.48199, 6.61044,   0.00000, 0.00000, 0.00000);*/



	// Extras for Hotel
	CreateDynamicObject(3509, -1754.21436, 940.27539, 23.81790,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3509, -1743.55432, 940.27539, 23.81790,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3509, -1764.95435, 940.27539, 23.81790,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3472, -1764.67444, 940.27789, 26.95100,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3472, -1753.77441, 940.43793, 26.95100,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3472, -1753.77441, 93.99790, 26.95100,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3472, -1743.23438, 940.43793, 26.95100,   0.00000, 0.00000, 0.00000);
	
	//bank front
	CreateObject(970,-1498.5000000,919.9000200,6.7000000,0.0000000,0.0000000,270.0000000); //object(fencesmallb) (1)
	CreateObject(970,-1495.5999800,923.2000100,6.7000000,0.0000000,0.0000000,180.0000000); //object(fencesmallb) (2)
	CreateObject(970,-1495.5999800,917.0000000,6.7000000,0.0000000,0.0000000,179.9950000); //object(fencesmallb) (3)
	
	//fbi base
	CreateObject(987, -2537.29004, 605.03003, 23.00000,   0.00000, -20.00000, 90.00000);
	CreateObject(987, -2548.94995, 579.63000, 11.94000,   0.00000, 0.00000, 0.00000);
	CreateObject(987, -2599.89990, 579.40002, 13.42000,   0.00000, 0.00000, 0.00000);
	CreateObject(987, -2599.86011, 603.25000, 13.42000,   0.00000, 0.00000, 270.00000);
	CreateObject(987, -2599.86011, 615.25000, 13.42000,   0.00000, 0.00000, 270.00000);
	CreateObject(1215, -2585.31006, 582.03003, 13.99000,   0.00000, 0.00000, 0.00000);
	CreateObject(9623, -2566.19995, 578.79999, 15.37000,   0.00000, 0.00000, 0.00000);
	CreateObject(3934, -2560.48999, 578.66998, 18.17000,   0.00000, 0.00000, 90.00000);
	CreateObject(3934, -2573.46997, 578.82001, 18.17000,   0.00000, 0.00000, 90.00000);
	CreateObject(970, -2549.96997, 574.46997, 18.72000,   0.00000, 0.00000, 0.00000);
	CreateObject(987, -2557.92993, 579.65997, 11.94000,   0.00000, 0.00000, 0.00000);
	CreateObject(987, -2587.95996, 579.51001, 11.94000,   0.00000, 0.00000, 0.00000);
	CreateObject(5816, -2551.80005, 584.77002, 14.66000,   0.00000, 0.00000, 0.00000);
	CreateObject(987, -2537.23999, 593.76001, 18.90000,   0.00000, -20.00000, 90.00000);
	CreateObject(987, -2537.25000, 582.51001, 14.78000,   0.00000, -20.00000, 90.00000);
	CreateObject(987, -2537.41992, 579.72998, 13.78000,   0.00000, -20.00000, 90.00000);
	CreateObject(970, -2547.63989, 581.17999, 18.64000,   0.00000, 0.00000, 90.00000);
	CreateObject(987, -2599.86011, 591.28003, 13.42000,   0.00000, 0.00000, 270.00000);
	CreateObject(987, -2599.87012, 627.20001, 13.42000,   0.00000, 0.00000, 270.00000);
	CreateObject(970, -2547.64990, 577.01001, 18.64000,   0.00000, 0.00000, 90.00000);
	CreateObject(970, -2554.11011, 574.46997, 18.72000,   0.00000, 0.00000, 0.00000);
	CreateObject(970, -2558.30005, 574.46997, 18.72000,   0.00000, 0.00000, 0.00000);
	CreateObject(970, -2562.50000, 574.46997, 18.72000,   0.00000, 0.00000, 0.00000);
	CreateObject(970, -2566.68994, 574.46997, 18.72000,   0.00000, 0.00000, 0.00000);
	CreateObject(970, -2570.87012, 574.46997, 18.72000,   0.00000, 0.00000, 0.00000);
	CreateObject(970, -2575.04004, 574.46997, 18.72000,   0.00000, 0.00000, 0.00000);
	CreateObject(970, -2579.25000, 574.46997, 18.72000,   0.00000, 0.00000, 0.00000);
	CreateObject(970, -2582.87988, 574.46997, 18.72000,   0.00000, 0.00000, 0.00000);
	CreateObject(970, -2584.90991, 576.53998, 18.72000,   0.00000, 0.00000, 90.00000);
	CreateObject(970, -2584.90991, 580.53003, 18.72000,   0.00000, 0.00000, 90.00000);
	CreateObject(970, -2582.78003, 583.23999, 18.72000,   0.00000, 0.00000, 0.00000);
	CreateObject(970, -2578.61011, 583.23999, 18.72000,   0.00000, 0.00000, 0.00000);
	CreateObject(970, -2574.41992, 583.23999, 18.72000,   0.00000, 0.00000, 0.00000);
	CreateObject(970, -2570.23999, 583.23999, 18.72000,   0.00000, 0.00000, 0.00000);
	CreateObject(970, -2566.05005, 583.23999, 18.72000,   0.00000, 0.00000, 0.00000);
	CreateObject(970, -2561.88989, 583.23999, 18.72000,   0.00000, 0.00000, 0.00000);
	CreateObject(970, -2557.71997, 583.23999, 18.72000,   0.00000, 0.00000, 0.00000);
	CreateObject(970, -2549.71997, 583.23999, 18.64000,   0.00000, 0.00000, 0.00000);
	CreateObject(970, -2551.44995, 583.23999, 18.64000,   0.00000, 0.00000, 0.00000);
	CreateObject(987, -2537.78101, 617.29999, 27.93660,   0.00000, 0.00000, 180.00000);
	CreateObject(987, -2537.46997, 608.01001, 23.72000,   0.00000, -20.00000, 90.00000);
	CreateObject(987, -2549.78101, 617.29999, 27.93660,   0.00000, 0.00000, 180.00000);
	CreateObject(987, -2561.68091, 617.29999, 27.93660,   0.00000, 0.00000, 180.00000);
	CreateObject(987, -2573.56104, 617.29999, 27.93660,   0.00000, 0.00000, 180.00000);
	CreateObject(987, -2585.56104, 617.29999, 27.93660,   0.00000, 0.00000, 180.00000);
	CreateObject(987, -2601.52100, 617.29999, 27.93660,   0.00000, 0.00000, 0.00000);
	CreateObject(987, -2567.40454, 580.02917, 11.87980,   0.00000, 0.00000, 0.00000);
	CreateObject(16773, -2548.62646, 619.69379, 17.37700,   0.00000, 0.00000, 0.00000);
	CreateObject(16773, -2562.82642, 619.69379, 17.37700,   0.00000, 0.00000, 0.00000);
	CreateObject(16773, -2576.82642, 619.69379, 17.37700,   0.00000, 0.00000, 0.00000);
	CreateObject(16773, -2588.82642, 619.69379, 17.37700,   0.00000, 0.00000, 0.00000);


	// DM Event Gate Closed
	// DM Event Gate Closed
	CreateObject(9625, 1414.99683, 7.60580, 1007.13251,   0.00000, 0.00000, 90.00000);
	CreateObject(9625, 1420.16650, 3.79320, 1004.30371,   0.00000, 0.00000, 0.00000);

	// Jail
	CreateObject(2930, 224.56384, 116.61489, 1000.74719,   0.00000, 0.00000, 90.71999);
	CreateObject(2930, 223.01932, 116.59758, 1000.74719,   0.00000, 0.00000, 90.71999);
	CreateObject(2930, 221.39159, 116.61296, 1000.74719,   0.00000, 0.00000, 90.71999);
	CreateObject(2930, 219.96480, 116.59406, 1000.74719,   0.00000, 0.00000, 90.71999);
	CreateObject(19870, 219.97960, 117.60460, 998.97449,   0.00000, 0.00000, 90.00000);
	CreateObject(19302, 216.39316, 117.38087, 999.25421,   0.00000, 0.00000, 123.48003);
	CreateObject(2588, 213.69853, 109.09761, 999.71503,   0.00000, 0.00000, 87.23993);
	CreateObject(2587, 213.68849, 110.34654, 1000.10175,   0.00000, 0.00000, 91.37996);
	CreateObject(2816, 224.58386, 107.61146, 998.01508,   0.00000, 0.00000, 0.00000);
	CreateObject(2716, 219.50577, 107.06760, 1000.24072,   0.00000, 0.00000, 0.00000);
	CreateObject(2587, 229.35185, 110.03686, 999.92389,   0.00000, 0.00000, -89.51999);
	CreateObject(2855, 228.86404, 107.58269, 998.01495,   0.00000, 0.00000, 0.00000);
	CreateObject(1647, 220.82088, 108.46875, 998.17493,   0.00000, 0.00000, 0.00000);
	CreateObject(1647, 222.21758, 108.25808, 998.17493,   0.00000, 0.00000, 0.00000);
	CreateObject(1647, 216.97357, 108.39111, 998.17493,   0.00000, 0.00000, 0.00000);
	CreateObject(1647, 226.12830, 108.32042, 998.17493,   0.00000, 0.00000, 0.00000);
	CreateObject(1647, 226.39137, 124.30331, 998.18237,   0.00000, 0.00000, 91.38004);
	CreateObject(1647, 226.40892, 121.88379, 998.18237,   0.00000, 0.00000, 91.38004);
	CreateObject(1647, 226.39352, 119.47002, 998.18237,   0.00000, 0.00000, 91.38004);
	CreateObject(14604, 220.81860, 124.10445, 998.98724,   0.00000, 0.00000, -123.90001);
	CreateObject(2582, 220.37807, 118.33850, 998.88843,   0.00000, 0.00000, 91.91994);
	CreateObject(321, 226.55919, 108.76790, 997.96417,   28.80000, -66.18002, -364.14005);
	CreateObject(1569, 233.10779, 119.22845, 1002.21490,   0.00000, 0.00000, 0.00000);
	CreateObject(1569, 236.81975, 119.26270, 1002.21490,   0.00000, 0.00000, 0.00000);

	// New Spawn
	CreateObject(14400, -1583.55872, 1232.11169, 6.85934,   0.00000, 0.00000, 0.00000);
	CreateObject(14400, -1578.57056, 1231.79761, 6.85934,   0.00000, 0.00000, 0.00000);
	CreateObject(14400, -1574.22864, 1231.68896, 6.85934,   0.00000, 0.00000, 0.00000);
	CreateObject(14400, -1569.19751, 1232.01758, 6.85934,   0.00000, 0.00000, 0.00000);
	CreateObject(14400, -1563.83325, 1231.60095, 6.85934,   0.00000, 0.00000, 0.00000);
	CreateObject(14400, -1559.42847, 1231.82874, 6.85934,   0.00000, 0.00000, 0.00000);
	CreateObject(14400, -1553.48071, 1232.35693, 6.85934,   0.00000, 0.00000, 0.00000);


	// Sweeper
	CreateObject(983, -1991.66077, 955.08270, 45.11189,   0.00000, 0.00000, 0.00000);
	CreateObject(983, -1991.67676, 948.67700, 45.11189,   0.00000, 0.00000, 0.00000);
	CreateObject(1331, -1977.88867, 953.69049, 45.30152,   0.00000, 0.00000, -91.79997);
	CreateObject(1331, -1978.00684, 950.31219, 45.30152,   0.00000, 0.00000, -91.79997);


	// 1.2.1
	CreateObject(8210, -1560.59998, 287.89999, 9.30000,   0.00000, 0.00000, 269.50000);
	CreateObject(7522, -1635.30005, 334.50000, 10.70000,   0.00000, 0.00000, 0.00000);
	CreateObject(987, -1660.19995, 328.29999, 6.20000,   0.00000, 0.00000, 136.00000);
	CreateObject(987, -1622.30005, 327.70001, 6.20000,   0.00000, 0.00000, 0.00000);
	CreateObject(987, -1648.30005, 328.10001, 6.20000,   0.00000, 0.00000, 179.49500);
	CreateObject(987, -1598.40002, 328.10001, 6.20000,   0.00000, 0.00000, 182.75000);
	CreateObject(968, -1632.50000, 327.79999, 6.20000,   0.00000, 0.00000, 0.00000);
	CreateObject(968, -1646.00000, 327.90039, 6.20000,   0.00000, 0.00000, 0.00000);
	CreateObject(3109, -1607.09998, 317.00000, 7.40000,   0.00000, 0.00000, 271.00000);
	CreateObject(3109, -1562.19995, 328.60001, 22.80000,   0.00000, 0.00000, 0.00000);
	CreateObject(3263, -1869.50000, 1424.19995, 6.30000,   0.00000, 0.00000, 44.00000);
	CreateObject(1280, -1979.80005, 1041.80005, 55.10000,   0.00000, 0.00000, 270.00000);
	CreateObject(1280, -1983.59998, 1041.80005, 55.10000,   0.00000, 0.00000, 270.00000);
	CreateObject(7037, -1755.09998, 1075.50000, 49.70000,   0.00000, 0.00000, 270.00000);
	CreateObject(1594, -1745.90002, 1087.09998, 44.90000,   0.00000, 0.00000, 0.00000);
	CreateObject(1594, -1750.30005, 1087.09998, 44.90000,   0.00000, 0.00000, 0.00000);
	CreateObject(1594, -1755.00000, 1087.09998, 44.90000,   0.00000, 0.00000, 0.00000);
	CreateObject(2735, -1735.90002, 1083.30005, 47.10000,   0.00000, 0.00000, 180.00000);
	CreateObject(2733, -1735.90002, 1083.30005, 48.90000,   0.00000, 0.00000, 180.00000);
	CreateObject(3578, -1623.09998, 334.50000, 7.00000,   0.00000, 0.00000, 270.00000);
	CreateObject(3578, -1647.40002, 334.50000, 7.00000,   0.00000, 0.00000, 270.00000);
	CreateObject(1569, -1667.90002, 1202.09998, 6.30000,   0.00000, 0.00000, 0.00000);
	CreateObject(2001, -1666.09998, 1202.59998, 6.30000,   0.00000, 0.00000, 0.00000);
	CreateObject(987, -1636.73999, 328.10001, 5.86000,   0.00000, 0.00000, 179.49500);
	CreateObject(987, -1633.83997, 328.10001, 5.86000,   0.00000, 0.00000, 179.49500);

	//new sfpd bound
	CreateDynamicObject(987, -1572.15845, 676.68591, 8.55400,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(987, -1572.15845, 666.10590, 8.55400,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(987, -1572.15845, 656.58588, 8.55400,   0.00000, 0.00000, -90.00000);
	CreateDynamicObject(987, -1572.67834, 646.32593, 8.55400,   0.00000, 0.00000, -180.00000);
	CreateDynamicObject(987, -1583.95825, 646.32593, 8.55400,   0.00000, 0.00000, -180.00000);
	CreateDynamicObject(987, -1595.95825, 646.32593, 8.55400,   0.00000, 0.00000, -180.00000);
	CreateDynamicObject(987, -1607.95825, 646.32593, 8.55400,   0.00000, 0.00000, -180.00000);
	CreateDynamicObject(987, -1619.95825, 646.32593, 8.55400,   0.00000, 0.00000, -180.00000);
	CreateDynamicObject(987, -1629.95825, 646.32593, 8.55400,   0.00000, 0.00000, -180.00000);
	CreateDynamicObject(987, -1641.43835, 646.32593, 8.55400,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(987, -1641.43835, 657.50592, 8.55400,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(987, -1641.43835, 664.34589, 8.55400,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(987, -1641.83838, 676.06592, 8.55400,   0.00000, -18.00000, 180.00000);
	CreateDynamicObject(987, -1652.93835, 676.22589, 12.75400,   0.00000, -18.00000, 180.00000);
	CreateDynamicObject(987, -1664.35852, 676.46588, 16.49400,   0.00000, -18.00000, 168.34000);
	CreateDynamicObject(987, -1675.29846, 678.74591, 20.15400,   0.00000, -18.00000, 174.38000);
	CreateDynamicObject(987, -1686.77844, 679.66589, 23.15400,   0.00000, -18.00000, 178.84000);
	CreateDynamicObject(987, -1695.71838, 679.66589, 22.41400,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(987, -1695.71838, 679.66589, 27.27400,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(987, -1695.71838, 688.90588, 22.41400,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(987, -1695.71838, 688.98590, 27.27400,   0.00000, 0.00000, 90.00000);
	CreateDynamicObject(987, -1695.67834, 699.36591, 23.17400,   0.00000, 0.00000, 0.00000);



	// Ammunation
	CreateObject(10631, -1920.59827, 883.40680, 38.52720,   0.00000, 0.00000, -90.00000);


	// Sex Shop
	CreateObject(1498, -1671.42822, 902.62646, 23.82669,   0.00000, 0.00000, 0.00000);
	CreateObject(2580, -1672.32434, 902.79974, 25.58323,   0.00000, 0.00000, 179.87997);
	CreateObject(14672, 1157.20154, -3919.53809, 18.18112,   0.00000, 0.00000, 0.00000);
	CreateObject(1498, 1164.01587, -3928.70801, 16.17027,   0.00000, 0.00000, 0.00000);
	CreateObject(2599, -1669.39307, 903.42358, 24.31651,   0.00000, 0.00000, 0.00000);
	CreateObject(2714, -1670.63806, 902.76349, 26.73600,   0.00000, 0.00000, -178.13998);
	CreateObject(7305, -1726.65271, 675.91815, 37.20449,   0.00000, 0.00000, 136.02007);
	CreateObject(971, -1642.60535, 688.45624, 9.46652,   0.00000, 0.00000, -179.40005);
	CreateObject(971, -1618.48511, 688.36389, 9.46652,   0.00000, 0.00000, 1.25997);
	CreateObject(2604, -1593.43958, 708.27991, -5.42587,   0.00000, 0.00000, 92.52001);
	CreateObject(2611, -1594.01782, 707.65314, -3.97016,   0.00000, 0.00000, 90.00003);
	CreateObject(1569, -1618.64221, 680.93909, 6.12940,   0.00000, 0.00000, 89.63999);

	// Bus Stops
	CreateObject(1257, -1723.54846, 765.10748, 25.19175,   0.00000, 0.00000, -180.72009);
	CreateObject(1229, -1722.74658, 768.33453, 25.46908,   0.00000, 0.00000, 83.27997);
	CreateObject(1257, -1704.93713, 815.55725, 25.19313,   0.00000, 0.00000, 0.00000);
	CreateObject(1229, -1705.50049, 812.56970, 25.29590,   0.00000, 0.00000, -97.44000);
	CreateObject(1257, -1974.17163, 740.63861, 45.68918,   0.00000, 0.00000, 89.87997);
	CreateObject(1229, -1971.11328, 739.78052, 45.89279,   0.00000, 0.00000, 0.00000);
	CreateObject(1257, -1929.37366, 721.80133, 45.68676,   0.00000, 0.00000, -90.18005);
	CreateObject(1229, -1932.32813, 722.56000, 45.91112,   0.00000, 0.00000, 179.40018);
	CreateObject(1257, -2132.32275, 843.50446, 69.71516,   0.00000, 0.00000, 0.00000);
	CreateObject(1229, -2132.88354, 840.67554, 69.92036,   0.00000, 0.00000, -91.31995);
	CreateObject(1257, -2153.60718, 959.90515, 80.29284,   0.00000, 0.00000, -178.55991);
	CreateObject(1229, -2153.49536, 963.02911, 80.30704,   0.00000, 0.00000, 91.38001);
	CreateObject(1257, -2230.02124, 1099.92761, 80.22085,   0.00000, 0.00000, 90.11996);
	CreateObject(1229, -2226.94360, 1099.38904, 80.32484,   0.00000, 0.00000, 0.00000);
	CreateObject(1257, -2197.26758, 1086.60071, 80.18259,   0.00000, 0.00000, -88.07997);
	CreateObject(1229, -2200.19604, 1087.27783, 80.30644,   0.00000, 0.00000, 185.15994);
	CreateObject(1257, -2018.34424, 1166.45056, 45.69162,   0.00000, 0.00000, -89.57999);
	CreateObject(1229, -2021.40125, 1166.82751, 45.88551,   0.00000, 0.00000, 192.95990);
	CreateObject(1257, -2042.80652, 1187.84863, 45.66860,   0.00000, 0.00000, 89.76000);
	CreateObject(1229, -2039.63525, 1187.23486, 45.75120,   0.00000, 0.00000, 0.00000);
	CreateObject(1257, -1902.86768, 977.39917, 35.42737,   0.00000, 0.00000, 170.99998);
	CreateObject(1229, -1902.97998, 980.42627, 35.49848,   0.00000, 0.00000, 89.57996);
	CreateObject(1257, -1886.80017, 964.69214, 35.33593,   0.00000, 0.00000, -7.74000);
	CreateObject(1229, -1887.42871, 961.66235, 35.49875,   0.00000, 0.00000, -101.69998);

	//bankinter
	CreateDynamicObject(14789, 2926.69922, -1780.19922, 1194.30005,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1723, 2935.59961, -1794.09961, 1190.02490,   0.00000, 0.00000, 88.99475);
	CreateDynamicObject(2208, 2929.30005, -1774.09998, 1190.09998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(9131, 2928.60010, -1774.09998, 1190.90002,   0.00000, 0.00000, 1.25000);
	CreateDynamicObject(9131, 2928.60010, -1774.09998, 1193.09998,   0.00000, 0.00000, 1.24695);
	CreateDynamicObject(9131, 2928.60010, -1774.09998, 1195.30005,   0.00000, 0.00000, 1.24695);
	CreateDynamicObject(9131, 2928.60010, -1774.09998, 1197.40002,   0.00000, 0.00000, 1.24695);
	CreateDynamicObject(2208, 2932.80005, -1774.09998, 1190.09998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2208, 2936.30005, -1774.09998, 1190.09998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(9131, 2939.69995, -1774.09998, 1191.09998,   0.00000, 0.00000, 1.24695);
	CreateDynamicObject(9131, 2939.69995, -1774.09998, 1193.30005,   0.00000, 0.00000, 1.24695);
	CreateDynamicObject(2208, 2940.50000, -1774.09961, 1190.09998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2208, 2944.89990, -1774.09998, 1190.09998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(9131, 2944.00000, -1774.00000, 1191.19995,   0.00000, 0.00000, 1.24695);
	CreateDynamicObject(9131, 2944.00000, -1774.00000, 1193.40002,   0.00000, 0.00000, 1.24695);
	CreateDynamicObject(2208, 2947.50000, -1774.09998, 1190.09998,   0.00000, 0.00000, 269.75000);
	CreateDynamicObject(2208, 2947.50000, -1777.59998, 1190.09998,   0.00000, 0.00000, 269.74731);
	CreateDynamicObject(2208, 2947.50000, -1781.09998, 1190.09998,   0.00000, 0.00000, 269.74731);
	CreateDynamicObject(2208, 2947.50000, -1784.59998, 1190.09998,   0.00000, 0.00000, 269.74731);
	CreateDynamicObject(9131, 2947.50000, -1788.00000, 1191.19995,   0.00000, 0.00000, 1.24695);
	CreateDynamicObject(9131, 2947.50000, -1788.00000, 1193.40002,   0.00000, 0.00000, 1.24695);
	CreateDynamicObject(2208, 2947.39941, -1788.89941, 1190.09998,   0.00000, 0.00000, 269.74182);
	CreateDynamicObject(9131, 2947.39941, -1792.39941, 1191.19995,   0.00000, 0.00000, 1.24146);
	CreateDynamicObject(9131, 2947.39990, -1792.40002, 1193.40002,   0.00000, 0.00000, 1.24695);
	CreateDynamicObject(2208, 2947.39990, -1793.19995, 1190.09998,   0.00000, 0.00000, 269.74731);
	CreateDynamicObject(2208, 2947.39990, -1796.69995, 1190.09998,   0.00000, 0.00000, 269.74731);
	CreateDynamicObject(2208, 2947.39990, -1800.19995, 1190.09998,   0.00000, 0.00000, 269.74731);
	CreateDynamicObject(9131, 2947.50000, -1803.00000, 1191.09998,   0.00000, 0.00000, 1.24695);
	CreateDynamicObject(9131, 2947.50000, -1803.00000, 1193.30005,   0.00000, 0.00000, 1.24695);
	CreateDynamicObject(9131, 2947.50000, -1803.00000, 1195.50000,   0.00000, 0.00000, 1.24695);
	CreateDynamicObject(9131, 2947.50000, -1803.00000, 1197.69995,   0.00000, 0.00000, 1.24695);
	CreateDynamicObject(9131, 2939.69995, -1774.09998, 1195.50000,   0.00000, 0.00000, 1.24695);
	CreateDynamicObject(9131, 2939.69995, -1774.09998, 1197.59998,   0.00000, 0.00000, 1.24695);
	CreateDynamicObject(9131, 2944.00000, -1774.00000, 1195.50000,   0.00000, 0.00000, 1.24695);
	CreateDynamicObject(9131, 2944.00000, -1774.00000, 1197.59998,   0.00000, 0.00000, 1.24695);
	CreateDynamicObject(9131, 2947.39990, -1792.40002, 1195.59998,   0.00000, 0.00000, 1.24695);
	CreateDynamicObject(9131, 2947.39990, -1792.40002, 1197.80005,   0.00000, 0.00000, 1.24695);
	CreateDynamicObject(9131, 2947.50000, -1788.00000, 1195.59998,   0.00000, 0.00000, 1.24695);
	CreateDynamicObject(9131, 2947.50000, -1788.00000, 1197.69995,   0.00000, 0.00000, 1.24695);
	CreateDynamicObject(9131, 2934.10010, -1784.30005, 1191.19995,   0.00000, 0.00000, 1.24695);
	CreateDynamicObject(9131, 2934.10010, -1784.30005, 1193.40002,   0.00000, 0.00000, 1.24695);
	CreateDynamicObject(9131, 2934.10010, -1784.30005, 1195.59998,   0.00000, 0.00000, 1.24695);
	CreateDynamicObject(9131, 2934.10010, -1784.30005, 1197.80005,   0.00000, 0.00000, 1.24695);
	CreateDynamicObject(9131, 2934.10010, -1797.00000, 1191.19995,   0.00000, 0.00000, 1.24695);
	CreateDynamicObject(9131, 2934.10010, -1797.00000, 1193.40002,   0.00000, 0.00000, 1.24695);
	CreateDynamicObject(9131, 2934.10010, -1797.00000, 1195.59998,   0.00000, 0.00000, 1.24695);
	CreateDynamicObject(9131, 2934.10010, -1797.00000, 1197.80005,   0.00000, 0.00000, 1.24695);
	CreateDynamicObject(9131, 2941.89990, -1784.30005, 1191.19995,   0.00000, 0.00000, 1.24695);
	CreateDynamicObject(9131, 2941.89990, -1784.30005, 1193.40002,   0.00000, 0.00000, 1.24695);
	CreateDynamicObject(9131, 2941.89990, -1784.30005, 1195.59998,   0.00000, 0.00000, 1.24695);
	CreateDynamicObject(9131, 2941.89990, -1784.30005, 1197.80005,   0.00000, 0.00000, 1.24695);
	CreateDynamicObject(9131, 2941.80005, -1797.00000, 1191.19995,   0.00000, 0.00000, 1.24695);
	CreateDynamicObject(9131, 2941.80005, -1797.00000, 1193.40002,   0.00000, 0.00000, 1.24695);
	CreateDynamicObject(9131, 2941.80005, -1797.00000, 1195.59998,   0.00000, 0.00000, 1.24695);
	CreateDynamicObject(9131, 2941.80005, -1797.00000, 1197.80005,   0.00000, 0.00000, 1.24695);
	CreateDynamicObject(1808, 2927.50000, -1804.30005, 1190.09998,   0.00000, 0.00000, 183.25003);
	CreateDynamicObject(2162, 2932.50000, -1769.90002, 1190.09998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2164, 2934.30005, -1769.90002, 1190.09998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2162, 2936.10010, -1769.90002, 1190.09998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2164, 2937.89990, -1769.90002, 1190.09998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2007, 2939.69995, -1770.30005, 1190.09998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2007, 2940.69922, -1770.29980, 1190.09998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2162, 2943.50000, -1769.90002, 1190.09998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2164, 2945.30005, -1769.90002, 1190.09998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2162, 2947.10010, -1769.90002, 1190.09998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2164, 2948.89990, -1769.90002, 1190.09998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2164, 2950.60010, -1770.80005, 1190.09998,   0.00000, 0.00000, 270.25000);
	CreateDynamicObject(2162, 2950.60010, -1772.59998, 1190.09998,   0.00000, 0.00000, 269.75000);
	CreateDynamicObject(2164, 2950.60010, -1774.40002, 1190.09998,   0.00000, 0.00000, 270.24951);
	CreateDynamicObject(2162, 2950.60010, -1776.19995, 1190.09998,   0.00000, 0.00000, 269.74731);
	CreateDynamicObject(2164, 2950.60010, -1778.00000, 1190.09998,   0.00000, 0.00000, 270.24719);
	CreateDynamicObject(2162, 2950.60010, -1779.80005, 1190.09998,   0.00000, 0.00000, 269.74731);
	CreateDynamicObject(2164, 2950.60010, -1781.59998, 1190.00000,   0.00000, 0.00000, 270.24719);
	CreateDynamicObject(2162, 2950.60010, -1783.40002, 1190.09998,   0.00000, 0.00000, 269.74731);
	CreateDynamicObject(2164, 2950.60010, -1785.19995, 1190.09998,   0.00000, 0.00000, 270.24719);
	CreateDynamicObject(2162, 2950.60010, -1787.00000, 1190.09998,   0.00000, 0.00000, 269.74731);
	CreateDynamicObject(2007, 2950.10010, -1788.80005, 1190.09998,   0.00000, 0.00000, 269.25000);
	CreateDynamicObject(2007, 2950.09961, -1789.79980, 1190.09998,   0.00000, 0.00000, 269.24744);
	CreateDynamicObject(2164, 2950.60010, -1792.59998, 1190.09998,   0.00000, 0.00000, 270.24719);
	CreateDynamicObject(2162, 2950.60010, -1794.40002, 1190.09998,   0.00000, 0.00000, 269.74731);
	CreateDynamicObject(2164, 2950.60010, -1796.19995, 1190.09998,   0.00000, 0.00000, 270.24719);
	CreateDynamicObject(2162, 2950.60010, -1798.00000, 1190.09998,   0.00000, 0.00000, 269.74731);
	CreateDynamicObject(2164, 2950.60010, -1799.80005, 1190.09998,   0.00000, 0.00000, 270.24719);
	CreateDynamicObject(1808, 2949.60010, -1804.30005, 1190.00000,   0.00000, 0.00000, 185.25003);
	CreateDynamicObject(1723, 2935.59961, -1789.69922, 1190.02490,   0.00000, 0.00000, 88.98926);
	CreateDynamicObject(1723, 2940.39941, -1792.09961, 1190.04993,   0.00000, 0.00000, 270.24170);
	CreateDynamicObject(1723, 2940.39941, -1787.59961, 1189.99988,   0.00000, 0.00000, 270.23621);
	CreateDynamicObject(1723, 2937.00000, -1784.79980, 1190.02490,   0.00000, 0.00000, 359.24194);
	CreateDynamicObject(2357, 2938.00000, -1793.40002, 1190.00000,   0.00000, 0.00000, 90.25000);
	CreateDynamicObject(2357, 2938.00000, -1789.19995, 1190.00000,   0.00000, 0.00000, 90.24719);
	CreateDynamicObject(2852, 2937.89990, -1788.30005, 1190.40002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2852, 2938.00000, -1790.90002, 1190.40002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2852, 2937.89990, -1794.40002, 1190.40002,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(16780, 2938.80005, -1788.69995, 1198.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2106, 2947.30005, -1791.50000, 1191.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2106, 2947.39990, -1788.80005, 1191.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2106, 2940.60010, -1774.19995, 1191.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2106, 2943.10010, -1774.19995, 1191.00000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2190, 2941.66309, -1774.36743, 1191.00000,   0.00000, 0.00000, 183.99902);
	CreateDynamicObject(2190, 2947.16821, -1790.55603, 1191.00000,   0.00000, 0.00000, 85.99548);
	CreateDynamicObject(2614, 2950.60010, -1790.59998, 1195.50000,   0.00000, 0.00000, 270.00000);
	CreateDynamicObject(2614, 2941.89990, -1769.90002, 1195.80005,   0.00000, 0.00000, 359.99451);
	CreateDynamicObject(3964, 2926.80005, -1788.59998, 1195.09998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(3964, 2926.80005, -1788.59998, 1193.50000,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2286, 2926.71729, -1781.81079, 1195.47595,   0.00000, 0.00000, 89.99976);
	CreateDynamicObject(2942, 2938.10010, -1804.09998, 1190.69995,   0.00000, 0.00000, 179.99994);
	CreateDynamicObject(2942, 2927.19995, -1785.69995, 1190.69995,   0.00000, 0.00000, 89.99451);
	CreateDynamicObject(1723, 2925.91382, -1781.02039, 1190.02490,   0.00000, 0.00000, 88.98926);
	CreateDynamicObject(1723, 2925.89990, -1795.00000, 1190.00000,   0.00000, 0.00000, 88.99475);
	CreateDynamicObject(1723, 2927.19922, -1801.32617, 1190.04993,   0.00000, 0.00000, 87.98926);
	CreateDynamicObject(1723, 2932.00000, -1803.89941, 1189.99988,   0.00000, 0.00000, 180.74158);
	CreateDynamicObject(630, 2926.00000, -1796.19995, 1191.09998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(630, 2926.00000, -1792.00000, 1191.09998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(630, 2935.00000, -1796.69995, 1191.09998,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(630, 2941.10010, -1797.00000, 1191.09998,   0.00000, 0.00000, 62.00000);
	CreateDynamicObject(630, 2941.89990, -1785.09998, 1191.09998,   0.00000, 0.00000, 61.99585);
	CreateDynamicObject(630, 2934.30005, -1785.00000, 1191.09998,   0.00000, 0.00000, 61.99585);
	CreateDynamicObject(630, 2926.19995, -1777.90002, 1191.09998,   0.00000, 0.00000, 61.99585);
	CreateDynamicObject(630, 2926.19995, -1782.40002, 1191.09998,   0.00000, 0.00000, 61.99585);
	CreateDynamicObject(1723, 2927.24146, -1789.27393, 1190.02490,   0.00000, 0.00000, 88.98926);
	CreateDynamicObject(630, 2927.10010, -1770.09998, 1191.09998,   0.00000, 0.00000, 61.99585);
	CreateDynamicObject(630, 2950.30005, -1804.00000, 1191.09998,   0.00000, 0.00000, 61.99585);
	CreateDynamicObject(2245, 2929.60010, -1774.30005, 1191.30005,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2245, 2947.30005, -1801.90002, 1191.30005,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2245, 2947.39990, -1793.40002, 1191.30005,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2245, 2947.50000, -1774.40002, 1191.30005,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2245, 2938.89990, -1774.19995, 1191.30005,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1494, 2945.58008, -1804.59998, 1190.04004,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(9131, 2984.60010, -1891.40002, 1192.09998,   0.00000, 0.00000, 1.24695);
	CreateDynamicObject(1663, 2948.61133, -1790.31726, 1190.52588,   0.00000, 0.00000, 274.00000);
	CreateDynamicObject(1663, 2941.27759, -1772.99500, 1190.52588,   0.00000, 0.00000, 3.99902);
	CreateDynamicObject(1719, 2947.48291, -1789.33167, 1190.99463,   0.00000, 0.00000, 94.00000);
	CreateDynamicObject(1719, 2942.48926, -1774.05762, 1191.01965,   0.00000, 0.00000, 181.99402);
	CreateDynamicObject(2894, 2941.19043, -1773.94141, 1190.96521,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2894, 2947.53735, -1790.02112, 1190.96521,   0.00000, 0.00000, 269.25000);
	CreateDynamicObject(2163, 2941.72656, -1769.79956, 1190.06567,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2163, 2950.58203, -1790.79395, 1190.11279,   0.00000, 0.00000, 270.25000);
	CreateDynamicObject(2332, 2950.43555, -1791.64172, 1191.50439,   0.00000, 0.00000, 269.99997);
	CreateDynamicObject(2332, 2950.44482, -1790.80896, 1191.50439,   0.00000, 0.00000, 269.99451);
	CreateDynamicObject(2332, 2941.72363, -1769.95398, 1191.45410,   0.00000, 0.00000, 359.24451);
	CreateDynamicObject(2332, 2942.54395, -1769.94629, 1191.45410,   0.00000, 0.00000, 359.24194);
	CreateDynamicObject(2005, 2941.62329, -1769.93311, 1191.36084,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2005, 2942.57568, -1770.07422, 1191.36084,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2005, 2950.33521, -1791.62805, 1191.64404,   0.00000, 0.00000, 268.50000);
	CreateDynamicObject(2005, 2950.31519, -1790.78076, 1191.64404,   0.00000, 0.00000, 268.49487);
	CreateDynamicObject(2921, 2950.22949, -1769.63989, 1196.22119,   0.00000, 354.00000, 100.00000);
	CreateDynamicObject(2921, 2941.76147, -1797.10046, 1196.62451,   0.00000, 353.99597, 69.49756);
	CreateDynamicObject(2921, 2950.69727, -1804.27649, 1196.59424,   0.00000, 353.99597, 333.49402);
	CreateDynamicObject(2921, 2934.17603, -1784.11646, 1195.75586,   0.00000, 353.99597, 267.48999);
	CreateDynamicObject(2921, 2926.48047, -1770.00000, 61035156.00000,   1196.85010, 0.00000, 353.99597);
	CreateDynamicObject(2773, 2940.56152, -1775.70886, 1190.58289,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2773, 2942.35498, -1775.65039, 1190.58289,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(2773, 2945.90430, -1789.47571, 1190.58289,   0.00000, 0.00000, 271.25000);
	CreateDynamicObject(2773, 2945.83643, -1791.33789, 1190.58289,   0.00000, 0.00000, 269.99695);
	CreateObject(14576, 2942.71899, -1789.97180, 1185.76636,   0.00000, 0.00000, 0.00000);
	CreateDynamicObject(1967, 2948.46069, -1805.78406, 1187.21289,   0.00000, 0.00000, 0.00000);

	// Forklift
	/*CreateObject(18257,-1713.6999500,101.4000000,2.6000000,0.0000000,0.0000000,224.0000000); //object(crates) (1)
	CreateObject(2935,-1703.0000000,107.8000000,4.0000000,0.0000000,0.0000000,0.0000000); //object(kmb_container_yel) (1)
	CreateObject(1271,-1710.5000000,98.8000000,2.9000000,0.0000000,0.0000000,0.0000000); //object(gunbox) (1)
	CreateObject(1271,-1709.9000200,101.7000000,2.9000000,0.0000000,0.0000000,280.0000000); //object(gunbox) (2)
	CreateObject(1271,-1709.8000500,100.2000000,2.9000000,0.0000000,0.0000000,26.0000000); //object(gunbox) (3)
	CreateObject(2932,-1714.1999500,65.1000000,4.0000000,0.0000000,0.0000000,300.0000000); //object(kmb_container_blue) (1)
	CreateObject(2478,-1706.4000200,105.0000000,2.8000000,0.0000000,0.0000000,0.0000000); //object(model_box6) (1)
	CreateObject(3576,-1690.9000200,100.7000000,4.0000000,0.0000000,0.0000000,348.0000000); //object(dockcrates2_la) (1)
	CreateObject(2935,-1685.0000000,97.5000000,4.0000000,0.0000000,0.0000000,50.0000000); //object(kmb_container_yel) (2)
	CreateObject(8886,-1723.0999800,70.7000000,6.0000000,0.0000000,0.0000000,44.0000000); //object(vgsefrght04) (1)
	CreateObject(3633,-1731.0999800,81.6000000,3.0000000,0.0000000,0.0000000,270.0000000); //object(imoildrum4_las) (1)
	CreateObject(3633,-1729.0996100,71.0996100,3.0000000,0.0000000,0.0000000,0.0000000); //object(imoildrum4_las) (2)
	CreateObject(3633,-1727.5000000,73.0000000,3.0000000,0.0000000,0.0000000,309.9960000); //object(imoildrum4_las) (3)
	CreateObject(7025,-1685.4000200,-94.6000000,6.0000000,0.0000000,0.0000000,316.0000000); //object(plantbox1) (1)
	CreateObject(3575,-1692.5999800,-74.6000000,5.3000000,0.0000000,0.0000000,226.0000000); //object(lasdkrt05) (1)
	CreateObject(3571,-1676.0000000,-79.4000000,3.9000000,0.0000000,0.0000000,0.0000000); //object(lasdkrt3) (1)
	CreateObject(3566,-1682.1999500,-70.4000000,5.2000000,0.0000000,0.0000000,240.0000000); //object(lasntrk1) (1)
	CreateObject(3576,-1672.8000500,-91.7000000,4.1000000,0.0000000,0.0000000,0.0000000); //object(dockcrates2_la) (2)
	CreateObject(5269,-1675.5999800,-94.3000000,4.9000000,0.0000000,0.0000000,16.0000000); //object(las2dkwar05) (1)
	CreateObject(3573,-1665.0000000,-29.9000000,5.3000000,0.0000000,0.0000000,226.0000000); //object(lasdkrtgrp1) (1)
	CreateObject(3569,-1644.5999800,-34.6000000,5.2000000,0.0000000,0.0000000,44.0000000); //object(lasntrk3) (1)
	CreateObject(3565,-1656.0999800,-33.6000000,3.9000000,0.0000000,0.0000000,316.0000000); //object(lasdkrt1_la01) (1)
	CreateObject(2934,-1651.4000200,-41.1000000,4.0000000,0.0000000,0.0000000,260.0000000); //object(kmb_container_red) (1)
	CreateObject(2935,-1651.8000500,-45.2000000,4.0000000,0.0000000,0.0000000,270.0000000); //object(kmb_container_yel) (3)
	CreateObject(922,-1660.6999500,-37.5000000,3.4000000,0.0000000,0.0000000,0.0000000); //object(packing_carates1) (1)
	CreateObject(942,-1672.5000000,-39.1000000,5.0000000,0.0000000,0.0000000,0.0000000); //object(cj_df_unit_2) (1)
	CreateObject(12934,-1635.6999500,-54.0000000,5.9000000,0.0000000,0.0000000,100.0000000); //object(sw_trailer03) (1)
	CreateObject(3565,-1660.0999800,-46.2000000,3.9000000,0.0000000,0.0000000,0.0000000); //object(lasdkrt1_la01) (2)
	CreateObject(3630,-1668.5000000,-72.0000000,4.1000000,0.0000000,0.0000000,226.0000000); //object(crdboxes2_las) (1)*/

	// ATM Machines
	CreateDynamicObject(2754, -1867.30200, 943.27991, 35.08000,   0.00000, 0.00000, 89.31868);
        CreateDynamicObject(2754, -1622.09375, 716.87970, 14.50500,   0.00000, 0.00000, 270.53171);
        CreateDynamicObject(2754, -2471.71802, 759.21143, 35.08000,   0.00000, 0.00000, 86.85550);
        CreateDynamicObject(2754, -2727.60181, 390.09631, 4.21590,   0.00000, 0.00000, 90.35210);
        CreateDynamicObject(2754, -2637.03613, 635.37592, 14.31310,   0.00000, 0.00000, 0.00000);
        CreateDynamicObject(2754, -1763.38660, 1083.69629, 45.34620,   0.00000, 0.00000, 270.97391);
        CreateDynamicObject(2754, -1493.13049, 930.49518, 7.08170,   0.00000, 0.00000, 0.00000);
        CreateDynamicObject(2754, -1939.45850, 265.33191, 40.94300,   0.00000, 0.00000, 179.90140);





	// Supa Save
	CreateObject(10966, 2849.3515625, 2454.2802734375, 1796.7916259766, 270, 180, 180);
	CreateObject(19460, 2842.083984375, 2444.373046875, 1783.9499511719, 0, 0, 0);
	CreateObject(19460, 2837.3024902344, 2453.7451171875, 1783.9499511719, 0, 0, 0);
	CreateObject(19460, 2837.2951660156, 2463.3776855469, 1783.9499511719, 0, 0, 0);
	CreateObject(19460, 2842.1691894531, 2449.0207519531, 1783.9499511719, 0, 0, 90);
	CreateObject(19460, 2831.2434082031, 2459.2973632813, 1783.9499511719, 0, 0, 90);
	CreateObject(19460, 2840.8200683594, 2459.2973632813, 1783.9499511719, 0, 0, 90);
	CreateObject(19460, 2826.5087890625, 2464.0244140625, 1783.9499511719, 0, 0, 0);
	CreateObject(19460, 2821.6533203125, 2467.4045410156, 1783.9499511719, 0, 0, 90);
	CreateObject(19460, 2812.0319824219, 2467.4113769531, 1783.9499511719, 0, 0, 90);
	CreateObject(19460, 2837.2092285156, 2440.6469726563, 1783.9499511719, 0, 0, 90);
	CreateObject(19460, 2827.6118164063, 2440.6457519531, 1783.9499511719, 0, 0, 90);
	CreateObject(19176, 2842.0478515625, 2444.720703125, 1786.9649658203, 0.3955078125, 0, 90);
	CreateObject(19460, 2843.73046875, 2446.5092773438, 1783.7572021484, 90, 270, 0);
	CreateObject(19460, 2843.73046875, 2442.9130859375, 1783.7572021484, 90, 269.99450683594, 0);
	CreateObject(19368, 2843.7316894531, 2444.8884277344, 1788.4859619141, 0, 270, 0);
	CreateObject(19368, 2843.7316894531, 2444.5910644531, 1788.4859619141, 0, 269.99450683594, 0);
	CreateObject(997, 2828.9438476563, 2448.9797363281, 1785.4809570313, 0, 0, 270);
	CreateObject(997, 2832.2048339844, 2448.9409179688, 1785.4809570313, 0, 0, 180);
	CreateObject(1349, 2830.6010742188, 2441.3681640625, 1786.0516357422, 0, 0, 179.99572753906);
	CreateObject(1349, 2830.0285644531, 2441.3447265625, 1786.0516357422, 0, 0, 179.99450683594);
	CreateObject(1349, 2830.1420898438, 2442.3579101563, 1786.0516357422, 0, 0, 157.99450683594);
	CreateObject(1885, 2829.7084960938, 2443.3666992188, 1785.4809570313, 0, 0, 42.247924804688);
	CreateObject(1885, 2829.6135253906, 2447.4978027344, 1785.4809570313, 0, 0, 348.24792480469);
	CreateObject(2754, 2839.6223144531, 2448.6276855469, 1786.3831787109, 0, 0, 90);
	CreateObject(2754, 2838.7680664063, 2448.640625, 1786.3831787109, 0, 0, 90);
	CreateObject(1330, 2840.5222167969, 2448.4565429688, 1785.9072265625, 0, 0, 342);
	CreateObject(949, 2841.6860351563, 2442.587890625, 1786.1174316406, 0, 0, 0);
	CreateObject(949, 2841.658203125, 2446.8225097656, 1786.1174316406, 0, 0, 0);
	CreateObject(2197, 2839.0922851563, 2441.8000488281, 1785.4809570313, 0, 0, 180);
	CreateObject(2197, 2838.4187011719, 2441.8000488281, 1785.4809570313, 0, 0, 179.99450683594);
	CreateObject(2197, 2837.7448730469, 2441.8000488281, 1785.4809570313, 0, 0, 179.99450683594);
	CreateObject(2197, 2837.0661621094, 2441.8000488281, 1785.4809570313, 0, 0, 179.99450683594);
	CreateObject(2197, 2839.091796875, 2441.7998046875, 1787.1400146484, 0, 0, 179.99450683594);
	CreateObject(2197, 2838.41796875, 2441.7998046875, 1787.1400146484, 0, 0, 179.99450683594);
	CreateObject(2197, 2837.744140625, 2441.7998046875, 1787.1400146484, 0, 0, 179.99450683594);
	CreateObject(19329, 2834.3852539063, 2440.7329101563, 1788.390625, 0, 0, 0);
	CreateObject(997, 2828.8999023438, 2443.9348144531, 1785.4809570313, 0, 0, 270);
	CreateObject(1349, 2829.9526367188, 2448.208984375, 1786.0516357422, 0, 0, 165.74572753906);
	CreateObject(997, 2837.2060546875, 2448.9636230469, 1785.4809570313, 0, 0, 179.99450683594);
	CreateObject(1885, 2829.7080078125, 2443.3662109375, 1785.9063720703, 0, 0, 42.247924804688);
	CreateObject(1885, 2829.3771972656, 2446.4743652344, 1785.4809570313, 0, 0, 268.24462890625);
	CreateObject(19460, 2817.986328125, 2440.6455078125, 1783.9499511719, 0, 0, 90);
	CreateObject(1984, 2829.5764160156, 2451.7495117188, 1785.4809570313, 0, 0, 0);
	CreateObject(1984, 2829.5764160156, 2456.8178710938, 1785.4809570313, 0, 0, 0);
	CreateObject(997, 2832.1381835938, 2452.23046875, 1785.4809570313, 0, 0, 270);
	CreateObject(997, 2832.1184082031, 2457.3193359375, 1785.4809570313, 0, 0, 270);
	CreateObject(997, 2832.2087402344, 2454.0554199219, 1785.4809570313, 0, 0, 179.99450683594);
	CreateObject(1806, 2831.3071289063, 2455.453125, 1785.4809570313, 0, 0, 320);
	CreateObject(1806, 2831.3913574219, 2450.4020996094, 1785.4809570313, 0, 0, 19.998779296875);
	CreateObject(1885, 2830.037109375, 2456.0383300781, 1785.4809570313, 0, 0, 348.24462890625);
	CreateObject(1349, 2830.3630371094, 2448.0969238281, 1786.0516357422, 0, 0, 165.74523925781);
	CreateObject(1349, 2830.8759765625, 2447.1928710938, 1786.0516357422, 0, 0, 195.74523925781);
	CreateObject(2197, 2836.3916015625, 2441.7998046875, 1785.4809570313, 0, 0, 179.99450683594);
	CreateObject(1702, 2836.6613769531, 2456.7463378906, 1785.4809570313, 0, 0, 270);
	CreateObject(15038, 2836.6896972656, 2457.5700683594, 1786.0981445313, 0, 0, 0);
	CreateObject(15038, 2836.6896972656, 2450.3999023438, 1786.0981445313, 0, 0, 0);
	CreateObject(2370, 2836.64453125, 2451.462890625, 1785.4809570313, 0, 0, 0);
	CreateObject(2370, 2836.6457519531, 2453.1557617188, 1785.4809570313, 0, 0, 0);
	CreateObject(1716, 2835.5134277344, 2449.7143554688, 1785.4809570313, 0, 0, 0);
	CreateObject(1886, 2836.4526367188, 2458.5627441406, 1795.2008056641, 20, 0, 313);
	CreateObject(2362, 2829.2434082031, 2456.2048339844, 1786.4272460938, 0, 0, 180);
	CreateObject(2490, 2830.0541992188, 2456.6203613281, 1786.5592041016, 0, 0, 180);
	CreateObject(2489, 2829.5217285156, 2451.5290527344, 1786.5594482422, 0, 0, 180);
	CreateObject(2495, 2830.1791992188, 2451.513671875, 1786.5563964844, 0, 0, 180);
	CreateObject(19460, 2808.4165039063, 2440.6442871094, 1783.9499511719, 0, 0, 90);
	CreateObject(19460, 2809.8193359375, 2464.0690917969, 1783.9499511719, 0, 0, 0);
	CreateObject(19460, 2809.8193359375, 2444.9020996094, 1783.9499511719, 0, 0, 0);
	CreateObject(19460, 2809.8193359375, 2454.4775390625, 1783.9499511719, 0, 0, 0);
	CreateObject(9527, 2832.052734375, 2459.9187011719, 1789.9001464844, 0, 0, 0);
	CreateObject(19326, 2837.2116699219, 2451.8759765625, 1788.1075439453, 0, 0, 90);
	CreateObject(18100, 2836.4140625, 2447.400390625, 1785.5, 0, 0, 20);
	CreateObject(2690, 2839.8725585938, 2440.7944335938, 1786.29296875, 0, 0, 180);
	CreateObject(1891, 2821.8000488281, 2447.4833984375, 1785.4809570313, 0, 0, 0);
	CreateObject(1890, 2815.4440917969, 2447.8359375, 1785.4809570313, 0, 0, 90);
	CreateObject(1889, 2815.4445800781, 2444.7844238281, 1785.4809570313, 0, 0, 90);
	CreateObject(1887, 2821.1188964844, 2455.599609375, 1785.4809570313, 0, 0, 90);
	CreateObject(1884, 2824.9118652344, 2447.4833984375, 1785.4809570313, 0, 0, 0);
	CreateObject(1883, 2821.4450683594, 2462.0690917969, 1785.4809570313, 0, 0, 0);
	CreateObject(1850, 2820.0832519531, 2466.919921875, 1785.4809570313, 0, 0, 0);
	CreateObject(1849, 2810.2727050781, 2460.6638183594, 1785.4809570313, 0, 0, 90);
	CreateObject(1848, 2816.537109375, 2454.6013183594, 1785.4809570313, 0, 0, 90);
	CreateObject(1847, 2823.8596191406, 2466.7534179688, 1785.4809570313, 0, 0, 0);
	CreateObject(1845, 2824.9375, 2453.654296875, 1785.4809570313, 0, 0, 0);
	CreateObject(1844, 2816.7849121094, 2466.7900390625, 1785.4809570313, 0, 0, 0);
	CreateObject(1843, 2810.3747558594, 2464.6760253906, 1785.4809570313, 0, 0, 90);
	CreateObject(1842, 2818.4384765625, 2462.0615234375, 1785.9483642578, 0, 0, 0);
	CreateObject(1983, 2813, 2466.8459472656, 1787.0999755859, 0, 0, 0);
	CreateObject(1983, 2812, 2466.845703125, 1787.0999755859, 0, 0, 0);
	CreateObject(1848, 2820.0458984375, 2454.6081542969, 1785.4809570313, 0, 0, 270);
	CreateObject(1847, 2815.4440917969, 2454.6103515625, 1785.4809570313, 0, 0, 270);
	CreateObject(1981, 2810.3908691406, 2450.669921875, 1785.4809570313, 0, 0, 90);
	CreateObject(1981, 2810.390625, 2452.6630859375, 1785.4809570313, 0, 0, 90);
	CreateObject(1981, 2810.390625, 2451.669921875, 1785.4809570313, 0, 0, 90);
	CreateObject(2871, 2823.3229980469, 2441.2177734375, 1786.6528320313, 0, 0, 180);
	CreateObject(2871, 2824.322265625, 2441.2177734375, 1786.6528320313, 0, 0, 179.99450683594);
	CreateObject(2583, 2827.34765625, 2458.9497070313, 1786.3486328125, 0, 0, 0);
	CreateObject(2542, 2822.2858886719, 2441.2177734375, 1786.6528320313, 0, 0, 180);
	CreateObject(2541, 2825.6999511719, 2441.2177734375, 1786.6528320313, 0, 0, 180);
	CreateObject(2536, 2810.34765625, 2443.2309570313, 1785.4809570313, 0, 0, 90);
	CreateObject(2535, 2810.3486328125, 2444.220703125, 1785.4809570313, 0, 0, 90);
	CreateObject(2539, 2810.3408203125, 2445.2106933594, 1785.4809570313, 0, 0, 90);
	CreateObject(2538, 2810.3386230469, 2446.1892089844, 1785.4809570313, 0, 0, 90);
	CreateObject(2537, 2810.3801269531, 2449.7255859375, 1785.4809570313, 0, 0, 90);
	CreateObject(2536, 2810.3852539063, 2448.7373046875, 1785.4809570313, 0, 0, 90);
	CreateObject(1996, 2818.9992675781, 2441.2260742188, 1785.4809570313, 0, 0, 180);
	CreateObject(1996, 2810.38671875, 2453.66015625, 1785.4809570313, 0, 0, 90);
	CreateObject(1991, 2819.9909667969, 2441.2287597656, 1785.4809570313, 0, 0, 180);
	CreateObject(1993, 2810.3317871094, 2456.1987304688, 1785.4809570313, 0, 0, 90);
	CreateObject(1994, 2810.30078125, 2457.2084960938, 1785.4809570313, 0, 0, 270);
	CreateObject(1995, 2810.2990722656, 2455.2067871094, 1785.4809570313, 0, 0, 270);
	CreateObject(2541, 2825.962890625, 2463.0961914063, 1786.8907470703, 0, 0, 270);
	CreateObject(2541, 2825.962890625, 2464.0827636719, 1786.8907470703, 0, 0, 269.98901367188);
	CreateObject(1988, 2814, 2466.8459472656, 1787.0999755859, 0, 0, 0);
	CreateObject(1983, 2813.3979492188, 2441.2177734375, 1787.7856445313, 0, 0, 180);
	CreateObject(1987, 2814.3979492188, 2441.2177734375, 1787.7856445313, 0, 0, 180);
	CreateObject(1987, 2810.3923339844, 2455.75, 1787.5124511719, 0, 0, 90);
	CreateObject(1988, 2810.3923339844, 2456.75, 1787.5124511719, 0, 0, 90);
	CreateObject(1988, 2812.3984375, 2441.2177734375, 1787.7856445313, 0, 0, 179.99450683594);
	CreateObject(2804, 2810.2768554688, 2455.3195800781, 1786.3756103516, 0, 0, 0);
	CreateObject(2804, 2810.4467773438, 2455.4560546875, 1786.3756103516, 0, 0, 198);
	CreateObject(2806, 2810.310546875, 2456.2607421875, 1786.3668212891, 0, 0, 3);
	CreateObject(2804, 2810.4826660156, 2457.3017578125, 1786.3756103516, 0, 0, 197.99560546875);
	CreateObject(1209, 2820.888671875, 2453.4406738281, 1785.4809570313, 0, 0, 90);
	CreateObject(1776, 2826.0593261719, 2460.7253417969, 1786.5804443359, 0, 0, 270);
	CreateObject(1775, 2810.3010253906, 2447.5808105469, 1786.5782470703, 0, 0, 90);
	CreateObject(2663, 2836.8146972656, 2453.9580078125, 1786.5826416016, 0, 0, 40);
	CreateObject(1776, 2817.8935546875, 2441.17578125, 1786.5804443359, 0, 0, 179.99450683594);
	CreateObject(1886, 2810.5607910156, 2466.5046386719, 1795.2264404297, 19.9951171875, 0, 43.744995117188);
	CreateObject(1886, 2810.4194335938, 2441.3022460938, 1795.2531738281, 19.989624023438, 0, 137.74203491211);
	CreateObject(1845, 2824.9521484375, 2456.6181640625, 1785.4809570313, 0, 0, 180);
	CreateObject(8710, 2803.6101074219, 2491.5998535156, 1766.9392089844, 0, 0, 0);
	CreateObject(8710, 2785.669921875, 2438.8532714844, 1766.9392089844, 0, 0, 90);
	CreateObject(8710, 2850.6010742188, 2488.9499511719, 1766.9392089844, 0, 0, 270);
	CreateObject(8710, 2861.3962402344, 2478.6650390625, 1766.9392089844, 0, 0, 270);
	CreateObject(8710, 2866.1787109375, 2467.2573242188, 1766.9392089844, 0, 0, 270);
	CreateObject(8710, 2830.6586914063, 2410.9499511719, 1766.9392089844, 0, 0, 90);
	CreateObject(6989, 2886.0209960938, 2447.4331054688, 1873.279296875, 0, 270, 0);
	CreateObject(1892, 2832.5703125, 2448.6364746094, 1785.4809570313, 0, 0, 0);
	CreateObject(14439, 2834.4116210938, 2448.1572265625, 1795.5, 0, 0, 270);
	CreateObject(14439, 2818.33984375, 2448.13671875, 1795.5, 0, 0, 270);
	CreateObject(9186, 2817.2431640625, 2466.6611328125, 1797.0516357422, 0, 0, 7.75);
	CreateObject(8326, 2809.8044433594, 2451.6799316406, 1792.4576416016, 0, 0, 180);
	CreateObject(4729, 2821.2099609375, 2440.7229003906, 1791.3382568359, 0, 0, 110);
	
	//office
	CreateObject(19378, -648.44, 1595.52, 1027.20,   0.00, 90.00, 0.00);
	CreateObject(19454, -653.58, 1595.52, 1029.02,   0.00, 0.00, 0.00);
	CreateObject(19454, -648.78, 1590.80, 1026.92,   0.00, 0.00, 90.00);
	CreateObject(19439, -651.81, 1591.60, 1028.00,   0.00, 90.00, 0.00);
	CreateObject(19439, -648.33, 1591.60, 1028.00,   0.00, 90.00, 0.00);
	CreateObject(19439, -644.85, 1591.60, 1028.00,   0.00, 90.00, 0.00);
	CreateObject(19435, -646.65, 1592.32, 1027.28,   90.00, 0.00, 90.00);
	CreateObject(19435, -650.14, 1592.32, 1027.28,   90.00, 0.00, 90.00);
	CreateObject(19435, -644.10, 1592.32, 1029.02,   0.00, 0.00, 90.00);
	CreateObject(19435, -644.82, 1591.52, 1029.02,   0.00, 0.00, 0.00);
	CreateObject(19435, -653.72, 1600.42, 1029.02,   0.00, 0.00, 90.00);
	CreateObject(19435, -651.97, 1591.52, 1029.02,   0.00, 0.00, 0.00);
	CreateObject(19325, -648.39, 1590.88, 1028.93,   0.00, 0.00, 90.00);
	CreateObject(19439, -652.51, 1590.80, 1030.42,   0.00, 0.00, 90.00);
	CreateObject(19439, -644.27, 1590.80, 1028.82,   0.00, 0.00, 90.00);
	CreateObject(19325, -648.39, 1590.78, 1028.93,   0.00, 0.00, 90.00);
	CreateObject(19325, -648.39, 1590.71, 1028.93,   0.00, 0.00, 90.00);
	CreateObject(19439, -650.91, 1590.80, 1032.30,   0.00, 0.00, 90.00);
	CreateObject(19439, -649.31, 1590.80, 1032.30,   0.00, 0.00, 90.00);
	CreateObject(19439, -647.71, 1590.80, 1032.30,   0.00, 0.00, 90.00);
	CreateObject(19439, -646.12, 1590.80, 1032.30,   0.00, 0.00, 90.00);
	CreateObject(19439, -644.52, 1590.80, 1032.30,   0.00, 0.00, 90.00);
	CreateObject(19377, -648.44, 1595.52, 1030.85,   0.00, 90.00, 0.00);
	CreateObject(19439, -643.22, 1593.12, 1029.02,   0.00, 0.00, 0.00);
	CreateObject(19366, -643.22, 1598.73, 1029.02,   0.00, 0.00, 0.00);
	CreateObject(19391, -643.22, 1595.52, 1029.02,   0.00, 0.00, 0.00);
	CreateObject(2270, -643.81, 1593.10, 1028.93,   0.00, 0.00, 270.00);
	CreateObject(2267, -647.15, 1600.31, 1029.19,   0.00, 0.00, 0.00);
	CreateObject(948, -651.60, 1591.71, 1028.08,   0.00, 0.00, 0.00);
	CreateObject(2119, -653.36, 1595.20, 1027.28,   0.00, 0.00, 90.00);
	CreateObject(2251, -653.43, 1595.75, 1028.91,   0.00, 0.00, 0.00);
	CreateObject(948, -643.79, 1593.08, 1027.29,   0.00, 0.00, 0.00);
	CreateObject(19454, -648.10, 1600.42, 1029.02,   0.00, 0.00, 90.00);
	CreateObject(19435, -652.70, 1592.32, 1029.02,   0.00, 0.00, 90.00);
	CreateObject(19366, -645.05, 1598.74, 1030.84,   0.00, 90.00, 180.00);
	CreateObject(19366, -648.55, 1598.74, 1030.84,   0.00, 90.00, 180.00);
	CreateObject(19366, -652.04, 1598.74, 1030.84,   0.00, 90.00, 180.00);
	CreateObject(19439, -645.04, 1593.11, 1030.84,   0.00, 90.00, 0.00);
	CreateObject(19439, -648.54, 1593.11, 1030.84,   0.00, 90.00, 0.00);
	CreateObject(19439, -652.04, 1593.11, 1030.84,   0.00, 90.00, 0.00);
	CreateObject(957, -645.47, 1591.45, 1030.73,   0.00, 0.00, 0.00);
	CreateObject(957, -648.36, 1591.45, 1030.73,   0.00, 0.00, 0.00);
	CreateObject(957, -651.30, 1591.45, 1030.73,   0.00, 0.00, 0.00);
	CreateObject(957, -646.59, 1595.57, 1030.72,   0.00, 0.00, 0.00);
	CreateObject(957, -652.64, 1595.57, 1030.73,   0.00, 0.00, 0.00);
	CreateObject(957, -643.88, 1595.57, 1030.73,   0.00, 0.00, 0.00);
	CreateObject(957, -649.65, 1595.57, 1030.73,   0.00, 0.00, 0.00);
	CreateObject(2205, -650.25, 1596.27, 1027.28,   0.00, 0.00, 270.00);
	CreateObject(1714, -651.37, 1596.26, 1027.28,   0.00, 0.00, 45.00);
	CreateObject(2204, -653.41, 1597.87, 1027.28,   0.00, 0.00, 90.00);
	CreateObject(1727, -645.78, 1599.63, 1027.29,   0.00, 0.00, 320.00);
	CreateObject(1727, -648.47, 1597.06, 1027.25,   0.00, 0.00, 300.00);
	CreateObject(1727, -649.31, 1598.98, 1027.29,   0.00, 0.00, 40.00);
	CreateObject(2271, -652.99, 1595.70, 1029.09,   0.00, 0.00, 90.00);
	CreateObject(2110, -647.62, 1600.12, 1027.04,   0.00, 0.00, 0.00);
	CreateObject(1670, -647.06, 1599.94, 1027.85,   0.00, 0.00, 0.00);
	CreateObject(1665, -650.54, 1594.64, 1028.23,   0.00, 0.00, 0.00);
	CreateObject(19466, -653.02, 1599.21, 1028.07,   0.00, 0.00, 0.00);
	CreateObject(1666, -653.21, 1599.93, 1028.41,   0.00, 0.00, 0.00);
	CreateObject(1667, -653.26, 1600.02, 1028.41,   0.00, 0.00, 0.00);
	CreateObject(1664, -653.26, 1599.75, 1028.49,   0.00, 0.00, 0.00);
	CreateObject(1665, -650.03, 1596.48, 1028.23,   0.00, 0.00, 0.00);
	CreateObject(2190, -650.12, 1594.90, 1028.21,   0.00, 0.00, 230.00);
	CreateObject(2257, -643.33, 1598.60, 1029.09,   0.00, 0.00, 270.00);
	CreateObject(2119, -643.28, 1598.07, 1027.28,   0.00, 0.00, 90.00);
	CreateObject(2251, -643.61, 1598.58, 1028.91,   0.00, 0.00, 0.00);
	CreateObject(1569, -643.25, 1594.79, 1027.27,   0.00, 0.00, 90.00);




}


forward SkydiveInteriorChanger(playerid);
public SkydiveInteriorChanger(playerid)
{
	if(!IsPlayerConnected(playerid))
	{
		KillTimer(playerData[playerid][skydiveTimer]);
	}
	else
	{
		if(GetPlayerInterior(playerid) == 9)
		{
			if(!IsPlayerInRangeOfPoint(playerid, 100.0, 1673.670043, 1447.932861, 1200.784775))
			{
				SetPlayerInterior(playerid, 0);
				KillTimer(playerData[playerid][skydiveTimer]);
			}
		}
		else
		{
			KillTimer(playerData[playerid][skydiveTimer]);
		}
	}
	return 1;
}

public getVehicleModelFromName(vname[])
{
	for(new i = 0; i < 213; i++)
	{
		if(strfind(vehicleNames[i], vname, true) != -1)
		{
			return i + 400;
		}
	}

	return -1;
}

public checkSeatStatus(vehicleid, seatid)
{
    for(new i = 0; i < MAX_PLAYERS; i++)
    {
        if(GetPlayerVehicleID(i) == vehicleid && GetPlayerVehicleSeat(i) == seatid)
		{
			return 0;
		}
    }

    return 1;
}
forward CountDown();
public CountDown()
{
     CountDownVar--;
     new str[128];

     format(str, sizeof(str), "%d", CountDownVar);
     GameTextForAll(str, 1500, 3);
     SoundForAll(1056);

	 if(CountDownVar == 0)
	 {
        KillTimer(CountDownTimer);
        SoundForAll(1057);
        GameTextForAll("~y~~h~~h~GO!", 2000, 3);
        CountDownVar = 0;
        for (new i = 0; i<MAX_PLAYERS; i++)
    	{
        	if(IsPlayerConnected(i))
        	{
        		TogglePlayerControllable(i, true);
			}
		}
	 }

     return 1;
}
public sendWantedMessage(playerid, amountAdded)
{
	new message[128];
	format(message, sizeof(message), "{FFDC2E}[WANTED] {FFFFFF}Your wanted level has increased by %i! Your wanted level is now %i!", amountAdded, playerData[playerid][playerWantedLevel]);
	SendClientMessage(playerid, COLOR_WHITE, message);
}

writeInLog(const destinationFile[], stringToWrite[])
{

	new
		logFile[32] = "logs/";

	strcat(logFile, destinationFile);

    if(!fexist(logFile))
    {
        new
			File:fileToCreate = fopen(logFile, io_write);

        fclose(fileToCreate);
    }

    new
        logYear,
        logMonth,
		logDay,

		logHour,
		logMinute,
		logSecond,

		stringForLogging[256];

    getdate(logYear, logMonth, logDay);
    gettime(logHour, logMinute, logSecond);

    format(stringForLogging, 300, "<div id=\"sex\">[%d/%d/%d - %02d:%02d:%d] %s</div>\r\n", logDay, logMonth, logYear, logHour, logMinute, logSecond, stringToWrite);

    new
		File:fileToAppend = fopen(logFile, io_append);

    fwrite(fileToAppend, stringForLogging);
    fclose(fileToAppend);

    return 1;
}

stock FormatNumber(iNum, const szChar[] = ",")
{
    new
        szStr[16]
    ;
    format(szStr, sizeof(szStr), "%d", iNum);

    for(new iLen = strlen(szStr) - 3; iLen > 0; iLen -= 3)
    {
        strins(szStr, szChar, iLen);
    }
    return szStr;
}

stock strtolower(text[])
{
    for(new i; i< 32; i++)
    {
        text[i] = tolower(text[i]);
    }
    return text;
}

stock ClearStats(playerid)
{
	if (playerData[playerid][playerLoggedIn])
	{
		forceRobberyCancel(playerid);

		// Reset main stats
		playerData[playerid][playerLevel] 			= 0;
		playerData[playerid][playerMoney]			= 0;
		playerData[playerid][playerBank]			= 0;
		playerData[playerid][playerScore]			= 0;
		playerData[playerid][playerXP]				= 0;
		playerData[playerid][playerIP]				= 0;
		playerData[playerid][playerInterior]		= 0;
		playerData[playerid][playerVWorld]			= 0;
		playerData[playerid][playerJailTime] 		= 0;
		playerData[playerid][playerMuteTime] 		= 0;
		playerData[playerid][playerCheckpointTime]	= 0;
		playerData[playerid][playerRobTime]			= 0;
		playerData[playerid][playerSafeObj]			= 0;
		playerData[playerid][playerClass]			= 0;
		playerData[playerid][playerWantedLevel]     = 0;
		playerData[playerid][playerVIPLevel]		= 0;
		playerData[playerid][playerRope]			= 0;
		playerData[playerid][playerJailKit]			= 0;
		playerData[playerid][playerScissors]		= 0;
		playerData[playerid][playerButtPlug]		= 0;
		playerData[playerid][playerBiggerPockets]	= 0;
		playerData[playerid][playerSecureWallet]	= 0;
		playerData[playerid][playerCourierLevel]    = 0;
		playerData[playerid][playerBanned]          = 0;
		playerData[playerid][playerLastVehicleID]   = 0;
		playerData[playerid][playerWarnings]        = 0;
		playerData[playerid][playerHelper]			= 0;
		playerData[playerid][playerWeed]			= 0;
		playerData[playerid][playerExplosives]		= 0;
		playerData[playerid][vipWeapon]             = 0;
		playerData[playerid][innocentKills]			= 0;
		playerData[playerid][aInnocentKills]		= 0;
		playerData[playerid][healthInsurance]		= 0;

		// Reset stats
		playerData[playerid][playerKills]			= 0;
		playerData[playerid][playerDeaths]			= 0;
		playerData[playerid][playerRobberies]		= 0;
		playerData[playerid][playerTimesJailed]		= 0;
		playerData[playerid][copArrests]			= 0;
		playerData[playerid][rulesRead]				= 0;
		playerData[playerid][streetRobberies] 		= 0;
		playerData[playerid][streetRapes] 			= 0;
		playerData[playerid][playersTied] 			= 0;
		playerData[playerid][playersKidnapped] 		= 0;
		playerData[playerid][copDetains]			= 0;
		playerData[playerid][copKills]				= 0;
		playerData[playerid][forkliftCompleted]		= 0;
		playerData[playerid][bankRobs]				= 0;
		playerData[playerid][bombsDefused]			= 0;

		// Reset Jobs
		playerData[playerid][lastCarDrop]			= -1;
		playerData[playerid][playerJob]				= -1;

		// Reset ID systems
		playerData[playerid][playerLastTicket] 		= -1;
		playerData[playerid][playerBailTo] 			= -1;
		playerData[playerid][playerBailPrice] 		= -1;
		playerData[playerid][playerAdminJailed] 	= -1;
		playerData[playerid][playerGunOffer] 		= -1;
		playerData[playerid][playerGunDealer] 		= -1;
		playerData[playerid][playerHousePass]       = -1;
		playerData[playerid][lastRecipient]         = -1;
		playerData[playerid][playerCustomSkin]		= -1;
		playerData[playerid][vehicleMenu]			= -1;
		playerData[playerid][playerStoreID]			= 0;
		playerData[playerid][playerCheckID]         = 0;
		playerData[playerid][playerInsideHouse]     = 0;
		playerData[playerid][playerInsideBusiness]  = 0;
		playerData[playerid][adDetected]			= 0;
		playerData[playerid][shotWarnings]			= 0;
		playerData[playerid][cbugWarnings]			= 0;
		playerData[playerid][carSwing]				= 0;

		// Reset Trucking
		if (playerData[playerid][truckingStatus] > 0)
		{
			DestroyDynamicRaceCP(playerData[playerid][truckingCheckpoint]);
		}

		playerData[playerid][truckingStatus]        = -1;
		playerData[playerid][truckingMission]       = -1;

		playerData[playerid][playerMissionCPTime] 	= 0;

		// Reset Forklift
		if (playerData[playerid][forkliftStatus] > 0)
		{
			DestroyObject(playerData[playerid][forkliftObject]);
		}

		playerData[playerid][forkliftStatus]		= -1;
		playerData[playerid][forkliftDamage]		= -1;

		// Reset Bus

		if (playerData[playerid][busStatus] > 0)
		{
			DestroyDynamicRaceCP(playerData[playerid][busCP]);
		}

		playerData[playerid][busStatus] 			= -1;

		// Reset Sweeper

		if (playerData[playerid][sweepStatus] > 0)
		{
			DestroyDynamicRaceCP(playerData[playerid][sweepCP]);
		}

		// Reset medic
		if (playerData[playerid][medicStatus] > 0)
		{
			playerData[playerid][medicStatus] = -1;
			playerData[playerid][medicMission] = -1;

			RemovePlayerMapIcon(playerid, 69);
			DestroyDynamicRaceCP(playerData[playerid][medicCheckpoint]);
		}

		playerData[playerid][sweepStatus] 			= -1;

		// Reset DM
		playerData[playerid][dmStreak] 			= 0;

		// Reset booleans
		playerData[playerid][playerGangID]			= INVALID_GANG_ID;
		playerData[playerid][hasSTD] 				= false;
		playerData[playerid][isInEvent]             = false;
		playerData[playerid][playerPingImmune]      = false;
		playerData[playerid][hasSpawned]            = false;
		playerData[playerid][playerLoggedIn] 		= false;
		playerData[playerid][playerAdminDuty]		= false;
		playerData[playerid][playerCanTaze]			= false;
		playerData[playerid][playerCanCuff]			= false;
		playerData[playerid][playerCanArrest]		= false;
		playerData[playerid][playerCanEMP]			= false;
		playerData[playerid][playerIsTazed]			= false;
		playerData[playerid][playerIsCuffed]		= false;
		playerData[playerid][playerIsInHouse]		= false;
		playerData[playerid][playerHitmarker]		= false;
		playerData[playerid][playerCanRape]			= false;
		playerData[playerid][playerCanRob]			= false;
		playerData[playerid][playerCanRepair]		= false;
		playerData[playerid][adminWeapon]			= false;
		playerData[playerid][pEnterHouse]			= false;
		playerData[playerid][showALog]              = false;
		playerData[playerid][iscourier]             = false;
		playerData[playerid][pmSpy]           		= false;
		playerData[playerid][gangspy]               = false;
		playerData[playerid][cwspy]               	= false;
		playerData[playerid][isBanned]              = false;
		playerData[playerid][playerBeenBanned]      = false;
		playerData[playerid][playerDied]	        = false;
		playerData[playerid][suicide] 				= false;
		playerData[playerid][vipColour]				= false;
		playerData[playerid][isInDM]				= false;
		playerData[playerid][hasBackpack] 			= false;
		playerData[playerid][hasParrot] 			= false;
		playerData[playerid][luckyCharm] 			= false;
		playerData[playerid][weaponSkill]			= true;
		playerData[playerid][playerDefuseKit]		= false;
		playerData[playerid][allowSpec]				= true;
		playerData[playerid][canEscape]				= true;

		playerData[playerid][canAsk] 				= true;
		playerData[playerid][canReport] 			= true;
		playerData[playerid][useAdminName]			= false;

		playerData[playerid][robberyFriend] 		= INVALID_PLAYER_ID;
		if (playerData[playerid][vSellTo] != -1)
		{
			// Remove the sale
			new sellto = playerData[playerid][vSellTo];
			playerData[sellto][vBuyFrom] = -1;
			SendClientMessage(sellto, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}The vehicle offer has expired, the seller has quit.");
		}

		if (playerData[playerid][vBuyFrom] != -1)
		{
			// Remove the sale
			new buyfrom = playerData[playerid][vBuyFrom];
			playerData[buyfrom][vSellTo] = -1;
			SendClientMessage(buyfrom, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}The vehicle offer has expired, the buyer has quit.");
		}

		// Progress Bars
		if (GetProgressBarValue(playerData[playerid][breakin]) != INVALID_BAR_VALUE)
		{
			DestroyProgressBar(playerData[playerid][breakin]);
		}

		DestroyProgressBar(playerData[playerid][robbery]);
	}
}

stock randomString(strDest[], strLen = 10)
{
    while(strLen--)
        strDest[strLen] = random(2) ? (random(26) + (random(2) ? 'a' : 'A')) : (random(10) + '0');
}

stock GetVehicleSpeed(vehicleid)
{
    new Float:xPos[3];
    GetVehicleVelocity(vehicleid, xPos[0], xPos[1], xPos[2]);
    return floatround(floatsqroot(xPos[0] * xPos[0] + xPos[1] * xPos[1] + xPos[2] * xPos[2]) * 170.00);
}

stock FindIP(text[])
{
	new strR[255];
	new is1=0;
 	new r=0;
 	while(strlen(text[is1]))
 	{
  	if('0'<=text[is1]<='9')
  	{
 	new is2=is1+1;
  	new p=0;
   	while(p==0)
  	{
   	if('0'<=text[is2]<='9'&&strlen(text[is2])) is2++;
 	else
  	{
   	strmid(strR[r],text,is1,is2,255);
   	if(strval(strR[r])<255) r++;
    is1=is2;
    p=1;
    }
    }
    }
    is1++;
 	}
 	if(r>=4)
 	{
		return true;
 	}
	else
	{
		return false;
	}
}
function GetINIString(file[], result[])
{
    new File:inifile, line[512];
    inifile = fopen(file, io_read);
    if(!inifile)
    {
        printf("Fatal Error: Couldn't open \"%s\"!", file);
        return 0;
    }
    while(fread(inifile, line)) format(result, sizeof(line), "%s", line);
    fclose(inifile);
    return 0;
}

function WriteNIString(file[], string[])
{
    new File:inifile;
    inifile = fopen(file, io_write);
    if(!inifile)
    {
        printf("Fatal Error: Couldn't open \"%s\"!", file);
        return 0;
    }
    fwrite(inifile, string);
    fclose(inifile);
    return 0;
}
stock isNumber(const string[])
{
	for (new i = 0, z = strlen(string); i < z; i++)
	{
		if (string[i] > '9' || string[i] < '0') return 0;
	}
	return 1;
}
stock IsNum(textchar) // Short function to find if a char is a num or not.
{
    if(textchar == '0') return 1;
    if(textchar == '1') return 1;
    if(textchar == '2') return 1;
    if(textchar == '3') return 1;
    if(textchar == '4') return 1;
    if(textchar == '5') return 1;
    if(textchar == '6') return 1;
    if(textchar == '7') return 1;
    if(textchar == '8') return 1;
    if(textchar == '9') return 1;
    return 0;
}

public checkDriveB(playerid)//wait
{
	if(IsPlayerInAnyVehicle(playerid))
	{
		SetPlayerArmedWeapon(playerid, 0);
	}
	return 1;
}


public AttackingZones(zone)
{
	new gang = zoneData[zone][zoneAttacker], found = false;
	zoneData[zone][zoneTime]--;
	new msg[128], time[10];
	format(msg, 56, "Capturing ~r~%s", zoneData[zone][zoneName]);
	format(time, 10, "%02d:%02d", (zoneData[zone][zoneTime] / 60), (zoneData[zone][zoneTime] % 60));
	foreach(new i : Player)
	{
		if(playerData[i][playerLoggedIn])
		{
			if(playerData[i][playerGang] == gang)
			{
				PlayerTextDrawSetString(i, playerData[i][CaptureZoneTD][0], msg);
				PlayerTextDrawSetString(i, playerData[i][CaptureZoneTD][1], time);
				PlayerTextDrawShow(i, playerData[i][CaptureZoneTD][0]);
				PlayerTextDrawShow(i, playerData[i][CaptureZoneTD][1]);
				if(IsPlayerInDynamicArea(i, zoneData[zone][zoneArea]))
				{
					found = true;
				}
			}
		}
	}
	if(!found || zoneData[zone][zoneTime] <= 0)
	{
		GangZoneStopFlashForAll(zoneData[zone][zoneGangZone]);
		foreach(new i : Player)
		{
			if(playerData[i][playerLoggedIn])
			{
				if(playerData[i][playerGang] == gang)
				{
					PlayerTextDrawSetString(i, playerData[i][CaptureZoneTD][0], " ");
					PlayerTextDrawSetString(i, playerData[i][CaptureZoneTD][1], " ");
					PlayerTextDrawHide(i, playerData[i][CaptureZoneTD][0]);
					PlayerTextDrawHide(i, playerData[i][CaptureZoneTD][1]);
				}
			}
		}	
		if(zoneData[zone][zoneTime] <= 0)
		{
			format(msg, 128, "{58D3F7}[GANG] {FFFFFF}%s succesfully captured %s zone, gang zone will be locked for 12 hours", gangData[gang][gangName], zoneData[zone][zoneName]);
			SendClientMessageToAll(-1, msg);
			zoneData[zone][zoneGang] = gang;
			new colour[10];
			format(colour, 10, "%s50", gangData[gang][gangColor]);
			GangZoneHideForAll(zoneData[zone][zoneGangZone]);
			GangZoneShowForAll(zoneData[zone][zoneGangZone], HexToInt(colour));
			SetTimerEx("UnlockZone", 12 * 60 * 60 * 1000, false, "d", zone);
			gangData[gang][gangScore] += 5;
			saveGang(gang);
		}
		else if(!found)
		{
			format(msg, 128, "{58D3F7}[GANG] {FFFFFF}%s failed to capture %s zone, gang zone will be locked for 30 minutes", gangData[gang][gangName], zoneData[zone][zoneName]);
			SendClientMessageToAll(-1, msg);	
			SetTimerEx("UnlockZone", 30 * 60 * 1000, false, "d", zone);
		}
		SetTimerEx("UnlockGang", 5 * 60 * 1000, false, "d", gang);
		zoneData[zone][zoneAttacker] = -1;
		KillTimer(zoneData[zone][zoneTimer]);
	}
	return 1;
}

HexToInt(string[])
{
   if (string[0] == 0) return 0;
   new i, cur=1, res = 0;
   for (i=strlen(string);i>0;i--) {
     if (string[i-1]<58) res=res+cur*(string[i-1]-48); else res=res+cur*(string[i-1]-65+10);
     cur=cur*16;
   }
   return res;
}

public UnlockZone(zoneid)
{
	zoneData[zoneid][zoneLocked] = false;
	return 1;
}

public UnlockGang(gangid)
{
	gangData[gangid][gangLocked] = false;
	return 1;
}

public mustLogin(playerid)
{
	KickWithMessage(playerid, "You must login or register to play here.");
	return 1;	
}
