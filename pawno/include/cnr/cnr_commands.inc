#define DIALOG_TELEPORTS 38

COMMAND:vipguns(playerid, params[])
{
    if(playerData[playerid][playerLoggedIn])
    {
		if (playerData[playerid][playerVIPLevel] >= 3)
		{
			if (!playerData[playerid][isInEvent])
			{
			    ShowPlayerDialog(playerid, DIALOG_FREESHOP, DIALOG_STYLE_LIST, "Weapons","Chainsaw\nDesert Eagle\nSawnoff Shotgun\nAK-47\nSniper Rifle\nParachute","Select","Close");
			}
			else
			{
				SendClientMessage(playerid,red,"You can't use this command in event");
			}
		}
		else
		{
			SendClientMessage(playerid,red,"You have to be a Gold Vip to use this command");
		}
	}
	return 1;
}
//---------------------------Credits--made--by--priyanshu-----------------------------
forward ShowCredits(playerid);
public ShowCredits(playerid)
{
    new BigString20[2000];
    strcat(BigString20, "{FFFFFF}1.-{33CCFF}Community Founder: {FF0000}Change me\n\n");
    strcat(BigString20, "{FFFFFF}3.-{FF0000}Owner: {00FF00}change me \n\n");
    strcat(BigString20, "{FFFFFF}4.-{FF0000}Co-Owner: {FFFFFF}Adding soon\n\n");
    strcat(BigString20, "{FFFFFF}5.-{FF0000}Server Manager: {00FF00}Adding Soon\n\n");
    strcat(BigString20, "{FFFFFF}6.-{FF0000}Script Developed by: {00FF00}Priyanshu\n\n");
    strcat(BigString20, "{FFFFFF}7.-{00FF00} Feel free to use this script but you must give credits!! - priyanshu\n\n");
   //================== [  You can keep addding more!  ] ====================== //
    ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "~b~CZ ~r~Cops ~w~N ~g~Robbers ~y~Credits", BigString20, "|Great|","|Nice|");
    return 1;
}
COMMAND:credits(playerid,params[]) {
	#pragma unused params
	ShowCredits(playerid);
	return 1;
}
//-------------------------------------------------------------------------------------------------------

COMMAND:wl(playerid, params[])
{
	new msg[1000], count = 1;
	foreach(new i : Player)
	{
		if(playerData[i][playerWantedLevel] > 3)
		{
			format(msg, sizeof(msg), "%s%d. %s( %d Star(s) )\n", msg, count, playerData[i][playerNamee], playerData[i][playerWantedLevel]);
			count++;
		}
	}
	if(count != 1)
	{
		ShowPlayerDialog(playerid, 200, DIALOG_STYLE_MSGBOX, "Wanted List", msg, "Close", "");
	}
	else
	{
		ShowPlayerDialog(playerid, 200, DIALOG_STYLE_MSGBOX, "Wanted List", "There are no wanted players present.", "Close", "");
	}
	return 1;
}


new iLastfixed[MAX_PLAYERS];


COMMAND:vfix(playerid, params[])
{
    if(playerData[playerid][playerLoggedIn])
    {
		if (playerData[playerid][playerVIPLevel] >= 2)
		{
			if(IsPlayerInAnyVehicle(playerid))
			{
	   			new iCount = GetTickCount(); // Get the current tick count
	    		if((iCount - iLastfixed[playerid]) > 30000)
	    		{
					new VehicleID;
					VehicleID = GetPlayerVehicleID(playerid);
					RepairVehicle(VehicleID);
					iLastfixed[playerid] = iCount;
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					return SendClientMessage(playerid, COLOR_WHITE, "{51FF00}[Fixed] {FFFF00}Sucessfully Fixed The Vehicle.");
				}
				else return SendClientMessage(playerid, COLOR_WHITE, "{FF0000}[Error] {FFFF00}Wait 30 seconds to use this command again!.");
			}
			else return SendClientMessage(playerid, COLOR_WHITE, "{FF0000}[Error] {FFFF00}you are not in a Vehicle!.");
		}
		else return SendClientMessage(playerid, COLOR_WHITE, "{FF0000}[Error] {FFFF00}only vips can use this command.");
	}
	return 1;
}

/*COMMAND:selecttown(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		playerData[playerid][playerTown] = SF;
	}
	return 1;
}*/

COMMAND:changepass(playerid, params[])
{
    if(isnull(params)) return SendClientMessage(playerid, COLOR_WHITE, "USAGE: /changepass (New Password)");

    new query[205], name[24];
    GetPlayerName(playerid, name,24);
    format(query, sizeof query, "UPDATE playerdata SET playerPass = SHA1('%s') WHERE playerName = '%s'", params, name);
    mysql_query(query);
    SendClientMessage(playerid, COLOR_GREEN, "Password Changed!");
    return 1;
}

COMMAND:viewtop(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		ShowPlayerDialog(playerid, DIALOG_TOP, DIALOG_STYLE_LIST, "Select Option", "Top Killer \nBest Robbers \nTop Players \nTop Truckers \nTop Briefcase Hunters \nBest Cop \nRichest Player", "Select", "Back");
    }
	else
	{
		SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFF00}You must be logged in to use commands.");
	}
	return 1;
}

COMMAND:breakout(playerid, params[])//lol
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(playerData[playerid][playerJailTime] >= 20)
		{
			if (!playerData[playerid][playerAdminJailed])
			{
				if(playerData[playerid][playerJailKit] > 0)
				{
					if (playerData[playerid][canEscape])
					{
						SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFF00}You're now attempting to escape from jail.");
						ApplyAnimation(playerid, "BOMBER", "BOM_PLANT_LOOP", 4.0, 1, 0, 0, 0, -1);
						SetTimerEx("EscapeJail", 5000, false, "ii", playerid);
						playerData[playerid][playerUsingAnim] = true;
					}
					else
					{
						SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFF00}You screwed up the escape attempt and can no longer escape from jail.");
					}
				}
				else
				{
					SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFF00}Your escape methods are outdated, purchase another Escapist Guide when you get out.");
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFF00}You are admin jailed.");
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{E81919}[ERROR}{FFFF00}You are not cuffed.");
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You must be logged in to use commands.");
	}
	return 1;
}

/*COMMAND:updates(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
	    new string[20264];
		format(string, sizeof(string), "%s{FD7DDB}\n1)Admin On Duty Changed -{0004FF} \n2)IRC Added -{00FF0D} \n3)new cmds for admins=={00FCFF} \n4)Gang Fixed ! ---{6F00FF} \n5)/psay For Members Added!--{FF0000}\n6 /credits To See Server Credits{F48383}\n7)AFK System Added - afk - back{ECF483}\n8HeadSHot System Added{CB83F4}\n9New Commands Soon!", string);
		
		ShowPlayerDialog(playerid, DIALOG_RULES, DIALOG_STYLE_MSGBOX, "Server Updates", string, "OK", "");
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFFFF}You must be logged in to use commands.");
		}

	return 1;
}*/

/*COMMAND:moviemode(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(hidden[playerid] == 0)
		{
			hidden[playerid] =1;
			PlayerTextDrawHide(playerid, playerData[playerid][wantedStars]);
			PlayerTextDrawHide(playerid, playerData[playerid][playerTracker]);
			PlayerTextDrawHide(playerid, playerData[playerid][playerExperience]);
			PlayerTextDrawHide(playerid, playerData[playerid][cnrLogo]);
			TextDrawHideForPlayer(playerid, URLTD);
			TextDrawHideForPlayer(playerid, MOTDTD);
			TextDrawHideForPlayer(playerid, gDay);
			TextDrawHideForPlayer(playerid, gTime);
			SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}You have enabled your moviemode.");

		}
		else
		{
			hidden[playerid] =0;
			PlayerTextDrawShow(playerid, playerData[playerid][wantedStars]);
			PlayerTextDrawShow(playerid, playerData[playerid][playerTracker]);
			PlayerTextDrawShow(playerid, playerData[playerid][playerExperience]);
			PlayerTextDrawShow(playerid, playerData[playerid][cnrLogo]);
			TextDrawShowForPlayer(playerid, URLTD);
			TextDrawShowForPlayer(playerid, MOTDTD);
			TextDrawShowForPlayer(playerid, gDay);
			TextDrawShowForPlayer(playerid, gTime);

			SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}You have disabled your moviemode");
		}

	}
	else
	{
		SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFFFF}You must be logged in to use commands.");
	}
	return 1;
}*/

/*COMMAND:music(playerid, params[])
{
    if (playerData[playerid][playerLoggedIn])
    {
        ShowPlayerDialog(playerid, DIALOG_MUSIC, DIALOG_STYLE_LIST, "Music Selection", "Green Day - American Idiot \nGreen Day - Jesus of Suburbia \nGreen Day - Homecoming \nGreen Day - 21st Century Breakdown \nA7X - So Far Away \nA7X - Missing in Action \nA7X - Dear God \nA7X - Burn it Down", "Go", "Cancel");
    }
    else
    {
        SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFF00}You must be logged in to use commands.");
    }
    return 1;
}*/

COMMAND:controlsettings(playerid,params[])
{
	new string[300];
	new s_2[60];
	new s_3[60];
	new s_4[60];
	new s_5[60];
	new s_6[60];
	//Connection Log
	if(cl[playerid] == 0) { format(s_2,sizeof(s_2),"{FF0000}"); }
	if(cl[playerid] == 1) { format(s_2,sizeof(s_2),"{00FF00}"); }
	//Event Teleports
	if(at[playerid] == 0) { format(s_3,sizeof(s_3),"{FF0000}"); }
	if(at[playerid] == 1) { format(s_3,sizeof(s_3),"{00FF00}"); }
	//recieving Messages
	if(!playerData[playerid][playerBlockPMs]) { format(s_4,sizeof(s_4),"{FF0000}"); }
	if(playerData[playerid][playerBlockPMs]) { format(s_4,sizeof(s_4),"{00FF00}"); }
	//Bail Offers
	if(bo[playerid] == 0) { format(s_5,sizeof(s_5),"{FF0000}"); }
	if(bo[playerid] == 1) { format(s_5,sizeof(s_5),"{00FF00}"); }
	//Hitmarker
	if(!playerData[playerid][playerHitmarker]) { format(s_6,sizeof(s_6),"{FF0000}"); }
	if(playerData[playerid][playerHitmarker]) { format(s_6,sizeof(s_6),"{00FF00}"); }

	format(string,sizeof(string),"Connection Log %s\nEvent Teleports %s\nRecieving Private Messages %s\nBail Offers %s\nHitmarker %s", s_2, s_3, s_4, s_5, s_6);
	ShowPlayerDialog(playerid, DIALOG_CS, DIALOG_STYLE_LIST, "Control Settings", string, "Select", "Cancel");
	return 1;
}
/*COMMAND:cs(playerid,params[])
{
	return cmd_controlsettings(playerid,params);
}*/
COMMAND:pl(playerid, params[])
{
	new string[128];
	if(playerData[playerid][playerLoggedIn])
	{
		format(string,sizeof(string),"{B7B7B7}[PACKETLOSS] {FFFF00}Your packets loss: %.2f percent.",NetStats_PacketLossPercent(playerid));
		SendClientMessage(playerid,-1,string);
	}
	else
	{
		SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You must be logged in to use commands.");
	}
	return 1;
}
COMMAND:escape(playerid, params[])
{
	return cmd_breakout(playerid, params);
}

COMMAND:tokens(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		new tokens[200];
		format(tokens, sizeof(tokens), "{FFDC2E}[TOKENS] {FFFF00}You have {FFDC2E}%i {FFFFFF}tokens to spend.", playerData[playerid][rTokens]);
		SendClientMessage(playerid, COLOR_WHITE, tokens);
	}
	else
	{
		SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You must be logged in to use commands.");
	}
	return 1;
}
COMMAND:parrot(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if (playerData[playerid][playerVIPLevel] >= 1)
		{
			if (playerData[playerid][hasParrot])
			{
				if(IsPlayerAttachedObjectSlotUsed(playerid, 8)) RemovePlayerAttachedObject(playerid, 8);
				playerData[playerid][hasParrot] = false;

				SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFF00}You removed the parrot from your shoulder.");
			}
			else
			{
				SetPlayerAttachedObject( playerid, 8, 19078, 3, -0.025633, 0.071474, -0.042353, 152.483703, 170.041259, 353.874603, 1.000000, 1.000000, 1.000000 ); // TheParrot1 - aest 5
				playerData[playerid][hasParrot] = true;

				SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFF00}You have placed a parrot onto your shoulder.");
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You must be a Premium player to use this command.");
		}
	}


	return 1;
}

COMMAND:backpack(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if (playerData[playerid][playerBackpack] == 1)
		{
			if (playerData[playerid][hasBackpack])
			{
				if(IsPlayerAttachedObjectSlotUsed(playerid, 9)) RemovePlayerAttachedObject(playerid, 9);
				playerData[playerid][hasBackpack] = false;

				SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFF00}You removed your backpack.");
			}
			else
			{
				SetPlayerAttachedObject( playerid, 9, 371, 1, 0.048503, -0.112052, -0.021527, 356.659484, 85.123565, 0.000000, 0.919283, 1.000000, 1.000000 ); // gun_para - aest 44
				playerData[playerid][hasBackpack] = true;

				SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFF00}You put your backpack on.");
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You don't have a backpack! Buy one from EGCNR.");
		}
	}


	return 1;
}

COMMAND:leavedm(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if (playerData[playerid][isInDM])
		{
			TextDrawHideForPlayer(playerid, dmBox[0]);
			TextDrawHideForPlayer(playerid, dmBox[1]);
			TextDrawHideForPlayer(playerid, dmBox[2]);
			TextDrawHideForPlayer(playerid, dmBox[3]);
			TextDrawHideForPlayer(playerid, dmBox[4]);
			TextDrawHideForPlayer(playerid, dmBox[5]);
			TextDrawHideForPlayer(playerid, dmBox[6]);

			PlayerTextDrawHide(playerid, playerData[playerid][dmArena][0]);
			PlayerTextDrawHide(playerid, playerData[playerid][dmArena][1]);
			PlayerTextDrawHide(playerid, playerData[playerid][dmArena][2]);
			PlayerTextDrawHide(playerid, playerData[playerid][dmArena][3]);

			ResetPlayerWeapons(playerid);
			playerData[playerid][isInDM] = false;
			playerData[playerid][isInEvent] = false;

			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerInterior(playerid, 0);

			playerData[playerid][hasSpawned] = false;
			SpawnPlayer(playerid);

			for (new i=0; i<MAX_PLAYERS; i++)
			{
				if(playerData[i][isInDM])
				{
					new dmLeave[100];
					format(dmLeave, sizeof(dmLeave), "{FAAC58}%s(%i) {FFFF00}left the arena.", playerData[playerid][playerNamee], playerid);
					SendClientMessage(i, COLOR_WHITE, dmLeave);

				}
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You're not in a DM event.");
		}
	}

	return 1;
}

COMMAND:breakin(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if (playerData[playerid][playerClass] == CLASS_CIVILIAN || playerData[playerid][playerClass] == CLASS_MEDIC || playerData[playerid][playerClass] == CLASS_FIREFIGHTER)
		{
			closeDialogs(playerid);

			if (playerData[playerid][canBreakIn])
			{
				houseBreakin(playerid);
			}
			else
			{
				SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}Please wait before breaking into another property.");
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}This command can only be used by civilians.");
		}
	}

	return 1;
}

COMMAND:openrobbery(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		closeDialogs(playerid);

		PlayerTextDrawShow(playerid, playerData[playerid][robTD][0]);
		PlayerTextDrawShow(playerid, playerData[playerid][robTD][1]);
		PlayerTextDrawShow(playerid, playerData[playerid][robTD][2]);
		PlayerTextDrawShow(playerid, playerData[playerid][robTD][3]);
	}

	return 1;
}

/*COMMAND:openwelcome(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		closeDialogs(playerid);

		PlayerTextDrawShow(playerid, playerData[playerid][Welcome1]);
		PlayerTextDrawShow(playerid, playerData[playerid][Welcome2]);
		PlayerTextDrawShow(playerid, playerData[playerid][Welcome3]);
		PlayerTextDrawShow(playerid, playerData[playerid][Welcome4]);
		PlayerTextDrawShow(playerid, playerData[playerid][Welcome5]);
		PlayerTextDrawShow(playerid, playerData[playerid][Welcome6]);
		PlayerTextDrawShow(playerid, playerData[playerid][Welcome7]);
		PlayerTextDrawShow(playerid, playerData[playerid][Welcome8]);
	}

	return 1;
}*/

COMMAND:openik(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		closeDialogs(playerid);

		PlayerTextDrawShow(playerid, playerData[playerid][InnocentKill1]);
		PlayerTextDrawShow(playerid, playerData[playerid][InnocentKill2]);
		PlayerTextDrawShow(playerid, playerData[playerid][InnocentKill3]);
		PlayerTextDrawShow(playerid, playerData[playerid][InnocentKill4]);
		PlayerTextDrawShow(playerid, playerData[playerid][InnocentKill5]);
		PlayerTextDrawShow(playerid, playerData[playerid][InnocentKill6]);
		PlayerTextDrawShow(playerid, playerData[playerid][InnocentKill7]);
		PlayerTextDrawShow(playerid, playerData[playerid][InnocentKill8]);
	}

	return 1;
}

COMMAND:stats(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		closeDialogs(playerid);

		// Set stat strings
		new
			kills[15],
			deaths[15],
			sRobberies[15],
			pRobberies[15],
			pRapes[15],
			scopArrests[15],
			scopKills[15],
			scopDetains[15],
			ratioString[100]
		;

		new Float:ratio = float(playerData[playerid][playerKills]) / float(playerData[playerid][playerDeaths]);

		format(ratioString, sizeof(ratioString), "~y~%0.2f", ratio);
		format(kills, sizeof(kills), "~y~%i", playerData[playerid][playerKills]);
		format(deaths, sizeof(deaths), "~y~%i", playerData[playerid][playerDeaths]);
		format(sRobberies, sizeof(sRobberies), "~y~%i", playerData[playerid][playerRobberies]);
		format(pRobberies, sizeof(pRobberies), "~y~%i", playerData[playerid][streetRobberies]);
		format(pRapes, sizeof(pRapes), "~y~%i", playerData[playerid][streetRapes]);
		format(scopArrests, sizeof(scopArrests), "~y~%i", playerData[playerid][copArrests]);
		format(scopKills, sizeof(scopKills), "~y~%i", playerData[playerid][copKills]);
		format(scopDetains, sizeof(scopDetains), "~y~%i", playerData[playerid][copDetains]);

		PlayerTextDrawSetString(playerid, playerData[playerid][PlayerStats][15], kills);
		PlayerTextDrawSetString(playerid, playerData[playerid][PlayerStats][16], deaths);
		PlayerTextDrawSetString(playerid, playerData[playerid][PlayerStats][17], sRobberies);
		PlayerTextDrawSetString(playerid, playerData[playerid][PlayerStats][18], pRobberies);
		PlayerTextDrawSetString(playerid, playerData[playerid][PlayerStats][19], pRapes);
		PlayerTextDrawSetString(playerid, playerData[playerid][PlayerStats][20], ratioString);
		PlayerTextDrawSetString(playerid, playerData[playerid][PlayerStats][22], scopArrests);
		PlayerTextDrawSetString(playerid, playerData[playerid][PlayerStats][23], scopKills);
		PlayerTextDrawSetString(playerid, playerData[playerid][PlayerStats][24], scopDetains);

		PlayerTextDrawShow(playerid, playerData[playerid][PlayerStats][0]);
		PlayerTextDrawShow(playerid, playerData[playerid][PlayerStats][1]);
		PlayerTextDrawShow(playerid, playerData[playerid][PlayerStats][2]);
		PlayerTextDrawShow(playerid, playerData[playerid][PlayerStats][3]);
		PlayerTextDrawShow(playerid, playerData[playerid][PlayerStats][4]);
		PlayerTextDrawShow(playerid, playerData[playerid][PlayerStats][5]);
		PlayerTextDrawShow(playerid, playerData[playerid][PlayerStats][6]);
		PlayerTextDrawShow(playerid, playerData[playerid][PlayerStats][7]);
		PlayerTextDrawShow(playerid, playerData[playerid][PlayerStats][8]);
		PlayerTextDrawShow(playerid, playerData[playerid][PlayerStats][9]);
		PlayerTextDrawShow(playerid, playerData[playerid][PlayerStats][10]);
		PlayerTextDrawShow(playerid, playerData[playerid][PlayerStats][11]);
		PlayerTextDrawShow(playerid, playerData[playerid][PlayerStats][12]);
		PlayerTextDrawShow(playerid, playerData[playerid][PlayerStats][13]);
		PlayerTextDrawShow(playerid, playerData[playerid][PlayerStats][14]);
		PlayerTextDrawShow(playerid, playerData[playerid][PlayerStats][15]);
		PlayerTextDrawShow(playerid, playerData[playerid][PlayerStats][16]);
		PlayerTextDrawShow(playerid, playerData[playerid][PlayerStats][17]);
		PlayerTextDrawShow(playerid, playerData[playerid][PlayerStats][18]);
		PlayerTextDrawShow(playerid, playerData[playerid][PlayerStats][19]);
		PlayerTextDrawShow(playerid, playerData[playerid][PlayerStats][20]);
		PlayerTextDrawShow(playerid, playerData[playerid][PlayerStats][22]);
		PlayerTextDrawShow(playerid, playerData[playerid][PlayerStats][23]);
		PlayerTextDrawShow(playerid, playerData[playerid][PlayerStats][24]);
	}

	return 1;
}

COMMAND:closehelp(playerid, params[])
{
	closeDialogs(playerid);

	return 1;
}

COMMAND:richlist(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		new
			richList[256],
			richPlayers[5] = {INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID},
			highestValue = -1,
			timesRan = 0,
			playerCount = 0,
			loopAmount = 0;

		for(new j = 0; j < MAX_PLAYERS; j++)
		{
			if(IsPlayerConnected(j))
			{
				playerCount++;
			}
		}

		if(playerCount >= 5)
		{
			loopAmount = 5;
		}
		else
		{
			loopAmount = playerCount;
		}

		while(timesRan < loopAmount)
		{
			highestValue = 0;

			for(new i = 0; i < MAX_PLAYERS; i++)
			{
				if(IsPlayerConnected(i))
				{
					if(playerData[i][playerLoggedIn])
					{
						if(playerData[i][playerMoney] > highestValue)
						{
							if(i != richPlayers[0] && i != richPlayers[1] && i != richPlayers[2] && i != richPlayers[3] && i != richPlayers[4])
							{
								highestValue = playerData[i][playerMoney];
								richPlayers[i] = i;
							}
						}
					}
				}
			}

			timesRan++;
		}

		for(new k = 0; k < sizeof(richPlayers); k++)
		{
			if(richPlayers[k] != INVALID_PLAYER_ID)
			{
				if(IsPlayerConnected(richPlayers[k]))
				{
					if(playerData[richPlayers[k]][playerLoggedIn])
					{
						format(richList, sizeof(richList), "#%i - %s: $%s", richPlayers[k], playerData[richPlayers[k]][playerNamee], FormatNumber(playerData[richPlayers[k]][playerMoney]));
						SendClientMessage(playerid, COLOR_WHITE, richList);
					}
				}
			}
		}

	}

	return 1;
}

COMMAND:resetskin(playerid, params[])
{
	new otherID;
	if(!sscanf(params, "d", otherID))
	{
	    if(playerData[playerid][playerLevel] >= 4)
	    {
	        if(!playerData[otherID][playerLoggedIn])
			{
				SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFF00}That player is not logged in.");
			}
			else
			{
			    SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFF00}Command succesfully executed.");
            	SendClientMessage(otherID, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFF00}Your custom skin has removed by administrator.");
				playerData[otherID][playerCustomSkin] = -1;
			}
	    }
	    else
	    {
	        cmd_resetskin(playerid, "");
	    }
	}
	else
	{
		if(playerData[playerid][playerLoggedIn])
		{
			if (playerData[playerid][playerCustomSkin] != -1)
			{
				SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFF00}Your custom skin will be reset when you next spawn.");
				playerData[playerid][playerCustomSkin] = -1;
			}
			else
			{
				SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You don't have a custom skin.");
			}
		}
 	}

	return 1;
}

/*COMMAND:me(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		new message[100];

		if(sscanf(params, "s[100]", message))
		{
			SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}Usage: \"me <message>\"");
		}
		else
		{
			if (playerData[playerid][messageCount] != 3)
			{
				if (playerData[playerid][playerMuteTime] != 0)
				{
					return 0;
				}
				else
				{
					format(message, sizeof(message), "{FE9A2E}* %s %s", playerData[playerid][playerNamee], message);
					SendClientMessageToAll(COLOR_WHITE, message);

					playerData[playerid][messageCount]++;
					KillTimer(playerData[playerid][spamTimer]);
					playerData[playerid][spamTimer] = SetTimerEx("StopSpam", 3000, false, "i", playerid);
				}
			}
		}
	}

	return 1;
}*/

COMMAND:idof(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		new message[250], otherPlayer;

		if(sscanf(params, "u", otherPlayer))
		{
			SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFF00}Usage: \"id <id/name>\"");
		}
		else
		{
			// Check if player is connected
			if(IsPlayerConnected(otherPlayer))
			{
				if (playerData[otherPlayer][useAdminName])
				{
					format(message, sizeof(message), "{B7B7B7}[SERVER] {FFFF00}%s(%i)", playerData[otherPlayer][tempAdminName], otherPlayer);
				}
				else
				{
					format(message, sizeof(message), "{B7B7B7}[SERVER] {FFFF00}%s(%i)", playerData[otherPlayer][playerNamee], otherPlayer);
				}

				SendClientMessage(playerid, COLOR_WHITE, message);
			}
			else
			{
				SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}That ID is not connected.");
			}
		}
	}

	return 1;
}

COMMAND:myjob(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(playerData[playerid][playerJob] == JOB_KIDNAPPER)
		{
			SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[KIDNAPPER] {FFFF00}Use {FFDC2E}/kidnap {FFFFFF}to kidnap players.");
		}
		else if(playerData[playerid][playerJob] == JOB_MECHANIC)
		{
			SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[MECHANIC] {FFFF00}Use {FFDC2E}/mech {FFFFFF}to view available job commands.");
		}
		else if(playerData[playerid][playerJob] == JOB_WEAPONDEALER)
		{
			SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[WEAPON DEALER] {FFFF00}Use {FFDC2E}/sellgun {FFFFFF}to offer weapons to players.");
		}
		else if(playerData[playerid][playerJob] == JOB_HITMAN)
		{
			SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[HITMAN] {FFFF00}Use {FFDC2E}/track {FFFFFF}to locate players. Use {FFDC2E}/hitlist {FFFFFF}to view players with a bounty on them.");
		}
		else if(playerData[playerid][playerJob] == JOB_RAPIST)
		{
			SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[RAPIST] {FFFF00}Use {FFDC2E}/rape {FFFFFF}to infect players with an STD.");
		}
		else if(playerData[playerid][playerJob] == JOB_DRUGDEALER)
		{
			SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[DRUG DEALER] {FFFF00}Use {FFDC2E}/sellweed {FFFFFF}whilst in an ice cream truck to sell drugs to players.");
		}
		else if(playerData[playerid][playerJob] == JOB_TERRORIST)
		{
			SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[TERRORIST] {FFFF00}Use {FFDC2E}/plantc4 {FFFFFF}whilst in possession of explosives to blow up objectives such as the bank vault, or the jail.");
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{E81919}[JOB] {FFFF00}You don't have a job yet.");
		}
	}

	return 1;
}

COMMAND:achievements(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		new
			count, sRules[60], fiftyKills[60], firstKill[60], kills2[60], thousandXP[60], thousandXP2[60], thousandXP3[60], thousandXP4[60],
			firstRobbery[60], robberies[60], robberies2[60], robberies3[60], arrests1[60], arrests2[60], arrests3[60], arrests4[60], amoneyBag[60],
			contracts1[60], contracts2[60], sRobberies1[60], sRobberies2[60], sRobberies3[60], sRape1[60], sRape2[60], sRape3[60], sKidnap1[60], sKidnap2[60], sKidnap3[60],
			dock1[60], dock2[60], dock3[60], defuse1[60], defuse2[60]
		;

		count = 0;

		// read the server rules
		if (playerData[playerid][rulesRead]) { format(sRules, sizeof(sRules), "{58D3F7}(Y)"); count++; } else { format(sRules, sizeof(sRules), "{FE9A2E}(N)"); }

		// find and claim a money bag
		if (playerData[playerid][moneyBags] >= 1) { format(amoneyBag, sizeof(amoneyBag), "{58D3F7}(Y)"); count++; } else { format(amoneyBag, sizeof(amoneyBag), "{FE9A2E}(N)"); }

		// first kill achievement
		if (playerData[playerid][playerKills] >= 1) { format(firstKill, sizeof(firstKill), "{58D3F7}(Y)"); count++; } else { format(firstKill, sizeof(firstKill), "{FE9A2E}(N)"); }

		// 50 kills achievement
		if (playerData[playerid][playerKills] >= 50) { format(fiftyKills, sizeof(fiftyKills), "{58D3F7}(Y)"); count++; } else { format(fiftyKills, sizeof(fiftyKills), "{FE9A2E}(N)"); }

		// 100 kills achievement
		if (playerData[playerid][playerKills] >= 500) { format(kills2, sizeof(kills2), "{58D3F7}(Y)"); count++; } else { format(kills2, sizeof(kills2), "{FE9A2E}(N)"); }

		// 1000 xp achievement
		if (playerData[playerid][playerXP] >= 1000) { format(thousandXP, sizeof(thousandXP), "{58D3F7}(Y)"); count++; } else { format(thousandXP, sizeof(thousandXP), "{FE9A2E}(N)"); }

		// 5000 xp achievement
		if (playerData[playerid][playerXP] >= 5000) { format(thousandXP2, sizeof(thousandXP2), "{58D3F7}(Y)"); count++; } else { format(thousandXP2, sizeof(thousandXP2), "{FE9A2E}(N)"); }

		// 10000 xp achievement
		if (playerData[playerid][playerXP] >= 10000) { format(thousandXP3, sizeof(thousandXP3), "{58D3F7}(Y)"); count++; } else { format(thousandXP3, sizeof(thousandXP3), "{FE9A2E}(N)"); }

		// 20000 xp achievement
		if (playerData[playerid][playerXP] >= 20000) { format(thousandXP4, sizeof(thousandXP4), "{58D3F7}(Y)"); count++; } else { format(thousandXP4, sizeof(thousandXP4), "{FE9A2E}(N)"); }

		// first robbery
		if (playerData[playerid][playerRobberies] >= 1) { format(firstRobbery, sizeof(firstRobbery), "{58D3F7}(Y)"); count++; } else { format(firstRobbery, sizeof(firstRobbery), "{FE9A2E}(N)"); }

		// 20 robberies
		if (playerData[playerid][playerRobberies] >= 20) { format(robberies, sizeof(robberies), "{58D3F7}(Y)"); count++; } else { format(robberies, sizeof(robberies), "{FE9A2E}(N)"); }

		// 50 robberies
		if (playerData[playerid][playerRobberies] >= 50) { format(robberies2, sizeof(robberies2), "{58D3F7}(Y)"); count++; } else { format(robberies2, sizeof(robberies2), "{FE9A2E}(N)"); }

		// 100 robberies
		if (playerData[playerid][playerRobberies] >= 100) { format(robberies3, sizeof(robberies3), "{58D3F7}(Y)"); count++; } else { format(robberies3, sizeof(robberies3), "{FE9A2E}(N)"); }

		// 1 arrest
		if (playerData[playerid][copArrests] >= 1) { format(arrests1, sizeof(arrests1), "{58D3F7}(Y)"); count++; } else { format(arrests1, sizeof(arrests1), "{FE9A2E}(N)"); }

		// 20 arrests
		if (playerData[playerid][copArrests] >= 20) { format(arrests2, sizeof(arrests2), "{58D3F7}(Y)"); count++; } else { format(arrests2, sizeof(arrests2), "{FE9A2E}(N)"); }

		// 50 arrests
		if (playerData[playerid][copArrests] >= 50) { format(arrests3, sizeof(arrests3), "{58D3F7}(Y)"); count++; } else { format(arrests3, sizeof(arrests3), "{FE9A2E}(N)"); }

		// 100 arrests
		if (playerData[playerid][copArrests] >= 100) { format(arrests4, sizeof(arrests4), "{58D3F7}(Y)"); count++; } else { format(arrests4, sizeof(arrests4), "{FE9A2E}(N)"); }

		// 1 contract kill
		if (playerData[playerid][hitsCompleted] == 1) { format(contracts1, sizeof(contracts1), "{58D3F7}(Y)"); count++; } else { format(contracts1, sizeof(contracts1), "{FE9A2E}(N)"); }

		// 20 contract kills
		if (playerData[playerid][hitsCompleted] >= 20) { format(contracts2, sizeof(contracts2), "{58D3F7}(Y)"); count++; } else { format(contracts2, sizeof(contracts2), "{FE9A2E}(N)"); }

		// 1 Street Robbery
		if (playerData[playerid][streetRobberies] >= 1) { format(sRobberies1, sizeof(sRobberies1), "{58D3F7}(Y)"); count++; } else { format(sRobberies1, sizeof(sRobberies1), "{FE9A2E}(N)"); }

		// 10 Street Robberies
		if (playerData[playerid][streetRobberies] >= 10) { format(sRobberies2, sizeof(sRobberies2), "{58D3F7}(Y)"); count++; } else { format(sRobberies2, sizeof(sRobberies2), "{FE9A2E}(N)"); }

		// 50 Street Robberies
		if (playerData[playerid][streetRobberies] >= 50) { format(sRobberies3, sizeof(sRobberies3), "{58D3F7}(Y)"); count++; } else { format(sRobberies3, sizeof(sRobberies3), "{FE9A2E}(N)"); }

		// 1 Street Rape
		if (playerData[playerid][streetRapes] >= 1) { format(sRape1, sizeof(sRape1), "{58D3F7}(Y)"); count++; } else { format(sRape1, sizeof(sRape1), "{FE9A2E}(N)"); }

		// 10 Street Rapes
		if (playerData[playerid][streetRapes] >= 10) { format(sRape2, sizeof(sRape2), "{58D3F7}(Y)"); count++; } else { format(sRape2, sizeof(sRape2), "{FE9A2E}(N)"); }

		// 50 Street Rapes
		if (playerData[playerid][streetRapes] >= 50) { format(sRape3, sizeof(sRape3), "{58D3F7}(Y)"); count++; } else { format(sRape3, sizeof(sRape3), "{FE9A2E}(N)"); }

		// 1 Street Kidnaps
		if (playerData[playerid][playersKidnapped] >= 1) { format(sKidnap1, sizeof(sKidnap1), "{58D3F7}(Y)"); count++; } else { format(sKidnap1, sizeof(sKidnap1), "{FE9A2E}(N)"); }

		// 10 Street Kidnaps
		if (playerData[playerid][playersKidnapped] >= 10) { format(sKidnap2, sizeof(sKidnap2), "{58D3F7}(Y)"); count++; } else { format(sKidnap2, sizeof(sKidnap2), "{FE9A2E}(N)"); }

		// 50 Street Kidnaps
		if (playerData[playerid][playersKidnapped] >= 50) { format(sKidnap3, sizeof(sKidnap3), "{58D3F7}(Y)"); count++; } else { format(sKidnap3, sizeof(sKidnap3), "{FE9A2E}(N)"); }

		// 1 forklift mission
		if (playerData[playerid][forkliftCompleted] >= 1) { format(dock1, sizeof(dock1), "{58D3F7}(Y)"); count++; } else { format(dock1, sizeof(dock1), "{FE9A2E}(N)"); }

		// 10 forklift missions
		if (playerData[playerid][forkliftCompleted] >= 10) { format(dock2, sizeof(dock2), "{58D3F7}(Y)"); count++; } else { format(dock2, sizeof(dock2), "{FE9A2E}(N)"); }

		// 50 forklift missions
		if (playerData[playerid][forkliftCompleted] >= 50) { format(dock3, sizeof(dock3), "{58D3F7}(Y)"); count++; } else { format(dock3, sizeof(dock3), "{FE9A2E}(N)"); }

		// 1 bomb defusal
		if (playerData[playerid][bombsDefused] >= 1) { format(defuse1, sizeof(defuse1), "{58D3F7}(Y)"); count++; } else { format(defuse1, sizeof(defuse1), "{FE9A2E}(N)"); }

		// 10 bomb defusal
		if (playerData[playerid][bombsDefused] >= 10) { format(defuse2, sizeof(defuse2), "{58D3F7}(Y)"); count++; } else { format(defuse2, sizeof(defuse2), "{FE9A2E}(N)"); }

		new aList[1600];

		// General
		format(aList, sizeof(aList), "%s\n%s {FFFF00}Read the /rules", aList, sRules);
		format(aList, sizeof(aList), "%s\n%s {FFFF00}Find and claim a Briefcase", aList, amoneyBag);

		// Kills
		format(aList, sizeof(aList), "%s\n%s {FFFF00}Kill 1 Player", aList, firstKill);
		format(aList, sizeof(aList), "%s\n%s {FFFF00}Kill 50 Players", aList, fiftyKills);
		format(aList, sizeof(aList), "%s\n%s {FFFF00}Kill 500 Players", aList, kills2);

		// XP
		format(aList, sizeof(aList), "%s\n%s {FFFF00}Earn 1,000 XP", aList, thousandXP);
		format(aList, sizeof(aList), "%s\n%s {FFFF00}Earn 5,000 XP", aList, thousandXP2);
		format(aList, sizeof(aList), "%s\n%s {FFFF00}Earn 10,000 XP", aList, thousandXP3);
		format(aList, sizeof(aList), "%s\n%s {FFFF00}Earn 20,000 XP", aList, thousandXP4);

		// Robberies
		format(aList, sizeof(aList), "%s\n%s {FFFF00}Rob 1 Store", aList, firstRobbery);
		format(aList, sizeof(aList), "%s\n%s {FFFF00}Rob 20 Stores", aList, robberies);
		format(aList, sizeof(aList), "%s\n%s {FFFF00}Rob 50 Stores", aList, robberies2);
		format(aList, sizeof(aList), "%s\n%s {FFFF00}Rob 100 Stores", aList, robberies3);

		// Arrests
		format(aList, sizeof(aList), "%s\n%s {FFFF00}Arrest 1 Criminal", aList, arrests1);
		format(aList, sizeof(aList), "%s\n%s {FFFF00}Arrest 20 Criminals", aList, arrests2);
		format(aList, sizeof(aList), "%s\n%s {FFFF00}Arrest 50 Criminals", aList, arrests3);
		format(aList, sizeof(aList), "%s\n%s {FFFF00}Arrest 100 Criminals", aList, arrests4);

		// Hit Contracts
		format(aList, sizeof(aList), "%s\n%s {FFFF00}Complete 1 Hit Contract", aList, contracts1);
		format(aList, sizeof(aList), "%s\n%s {FFFF00}Complete 20 Hit Contracts", aList, contracts2);

		// Street Robberies
		format(aList, sizeof(aList), "%s\n%s {FFFF00}Complete 1 Street Robbery", aList, sRobberies1);
		format(aList, sizeof(aList), "%s\n%s {FFFF00}Complete 10 Street Robberies", aList, sRobberies2);
		format(aList, sizeof(aList), "%s\n%s {FFFF00}Complete 50 Street Robberies", aList, sRobberies3);

		// Street Rapes
		format(aList, sizeof(aList), "%s\n%s {FFFF00}Rape 1 Player", aList, sRape1);
		format(aList, sizeof(aList), "%s\n%s {FFFF00}Rape 10 Players", aList, sRape2);
		format(aList, sizeof(aList), "%s\n%s {FFFF00}Rape 20 Players", aList, sRape3);

		// Street Kidnaps
		format(aList, sizeof(aList), "%s\n%s {FFFF00}Kidnap 1 Player", aList, sKidnap1);
		format(aList, sizeof(aList), "%s\n%s {FFFF00}Kidnap 10 Players", aList, sKidnap2);
		format(aList, sizeof(aList), "%s\n%s {FFFF00}Kidnap 20 Players", aList, sKidnap3);

		// Forklift Missions
		format(aList, sizeof(aList), "%s\n%s {FFFF00}Complete 1 Forklift Mission", aList, dock1);
		format(aList, sizeof(aList), "%s\n%s {FFFF00}Complete 10 Forklift Missions", aList, dock2);
		format(aList, sizeof(aList), "%s\n%s {FFFF00}Complete 20 Forklift Missions", aList, dock3);

		// Bomb Defusal
		format(aList, sizeof(aList), "%s\n%s {FFFF00}Defuse 1 Bomb", aList, defuse1);
		format(aList, sizeof(aList), "%s\n%s {FFFF00}Defuse 10 Bombs", aList, defuse2);

		new aTitle[100];
		format(aTitle, sizeof(aTitle), "Achievements %i/32", count);

		ShowPlayerDialog(playerid, DIALOG_ACHIEVEMENTS, DIALOG_STYLE_LIST, aTitle, aList, "OK", "Close");
	}

	return 1;
}

/*COMMAND:redeemvip(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		ShowPlayerDialog(playerid, DIALOG_REDEMPTION, DIALOG_STYLE_LIST, "CNRSF Shop", "Redeem VIP \nRedeem Other", "Next", "Cancel");
	}
	else
	{
	    SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFFFF}You must be logged in to use commands.");
	}

	return 1;
}*/

COMMAND:cardrop(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(playerData[playerid][playerClass] == CLASS_CIVILIAN)
		{
			new time = GetTickCount() - playerData[playerid][lastCarDrop];
			if(time > 300000 || playerData[playerid][lastCarDrop] == -1)
			{
				if(IsPlayerInRangeOfPoint(playerid, -1734.0756, 190.9162, 3.5547, 2.0) || IsPlayerInDynamicCP(playerid, CardropCP))
				{
					if(IsPlayerInAnyVehicle(playerid))
					{
						SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}This vehicle cannot be dropped off.");
					}
					else
					{
						SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You are not in a vehicle.");
					}
				}
				else
				{
					SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You're not near the car drop checkpoint.");
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You've already dropped off a vehicle recently, come back later.");
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}Only civilians may drop-off vehicles.");
		}
	}
	else
	{
	    SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You must be logged in to use commands.");
	}

	return 1;
}

COMMAND:pc(playerid, params[])
{
	if (playerData[playerid][playerLoggedIn])
	{
		new string[600];

		format(string, sizeof(string), "%s{98B0CD}Player Colours \n", string);
		format(string, sizeof(string), "%s{FFFFFF}The following colour list shows all in-game colours for players. \n", string);
		format(string, sizeof(string), "%s{FFFFFF}LEOs should take note of the wanted level colours. \n\n", string);

		format(string, sizeof(string), "%s{FFFFFF}Civilian\n", string);
		format(string, sizeof(string), "%s{FFEC41}Low Level Wanted\n", string);
		format(string, sizeof(string), "%s{DF802D}Wanted\n", string);
		format(string, sizeof(string), "%s{D92C3C}Most Wanted\n", string);
		format(string, sizeof(string), "%s{3E7EFF}Police\n", string);
		format(string, sizeof(string), "%s{8F48F5}Army\n", string);
		format(string, sizeof(string), "%s{2F205B}CIA\n", string);
		format(string, sizeof(string), "%s{1C3EFF}FBI\n", string);
		format(string, sizeof(string), "%s{F78181}Medic\n", string);
		format(string, sizeof(string), "%s{9C3D36}Firefighter\n", string);
		format(string, sizeof(string), "%s{00FF0D}Admin on Duty\n", string);
		format(string, sizeof(string), "%s{58D3F7}Premium Player\n", string);

		ShowPlayerDialog(playerid, DIALOG_PLAYER_COLOURS, DIALOG_STYLE_MSGBOX, "Player Colours", string, "OK", "");
	}
	else
	{
	    SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You must be logged in to use commands.");
	}

	return 1;
}

COMMAND:blockpms(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(playerData[playerid][playerBlockPMs])
		{
			SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFF00}You will now receive private messages.");
			playerData[playerid][playerBlockPMs] = false;
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFF00}You will no longer receive private messages.");
			playerData[playerid][playerBlockPMs] = true;
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFF00}You must be logged in to use commands.");
	}
	return 1;
}

COMMAND:getmytax(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(playerData[playerid][playerVIPLevel] < 1)
		{
			if(playerData[playerid][playerMoney] >= 5000)
			{
				new takeValue = floatround(playerData[playerid][playerMoney] * 0.030, floatround_round);

				// Send tax info
				new taxInfo[200];
				format(taxInfo, sizeof(taxInfo), "{FFDC2E}[TAX] {FFFF00}Your tax is {FFDC2E}$%s {FFFF00}per game day.", FormatNumber(takeValue));
				SendClientMessage(playerid, COLOR_WHITE, taxInfo);

				if(playerData[playerid][houseCount] > 0)
				{
					new houseTax[200], chousetax;

					chousetax = 1200 * playerData[playerid][houseCount];

					format(houseTax, sizeof(houseTax), "{FFDC2E}[HOUSE TAX] {FFFF00}Your house tax is {FFDC2E}$%s {FFFF00}per game day.", FormatNumber(chousetax));
					SendClientMessage(playerid, COLOR_WHITE, houseTax);
				}

			}
			else
			{
				SendClientMessage(playerid, COLOR_WHITE, "{FFDC2E}[TAX] {FFFF00}You have less than $5,000 therefore you're exempt from tax.");
			}
		}
		else
		{
			// No tax
			SendClientMessage(playerid, COLOR_WHITE, "{FFDC2E}[TAX] {FFFF00}You're exempt from tax.");
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You must be logged in to use commands.");
	}
	return 1;
}

COMMAND:cuttie(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(playerData[playerid][playerIsTied])
		{
			if(playerData[playerid][playerScissors] > 0)
			{
				new rand = random(3);
				if(rand == 1 || rand == 2)
				{
					SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[CUT TIE] {FFFF00}You successfully cut the tie and escaped.");
					Delete3DTextLabel(playerData[playerid][kidnappedLabel]);
					playerData[playerid][playerScissors] = playerData[playerid][playerScissors] - 1;

					playerData[playerid][playerIsTied] = false;

					SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
					KillTimer(playerData[playerid][untieTimer]);

					TogglePlayerControllable(playerid, 1);
				}
				else
				{
					SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[CUT TIE] {FFFF00}You failed to cut the tie.");
					playerData[playerid][playerScissors] = playerData[playerid][playerScissors] - 1;
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You don't have any scissors.");
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You are not tied.");
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You must be logged in to use commands.");
	}
	return 1;
}

COMMAND:breakcuffs(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(playerData[playerid][playerIsCuffed])
		{
			if(playerData[playerid][playerBobbyPins] > 0)
			{
				if (playerData[playerid][canBreakCuffs])
				{
					new rand = random(3);
					if(rand == 1 || rand == 2)
					{
						SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[BREAK CUFFS] {FFFF00}You have successfully broken your cuffs and escaped.");
						playerData[playerid][playerBobbyPins]--;

						playerData[playerid][playerIsCuffed] = false;

						SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
						KillTimer(playerData[playerid][uncuffTimer]);

						TogglePlayerControllable(playerid, 1);
					}
					else
					{
						SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[BREAK CUFFS] {FFFF00}You failed to break your cuffs.");
						playerData[playerid][playerBobbyPins]--;

						playerData[playerid][breakCuffsTimer] = SetTimerEx("rebreakcuffs", 30000, false, "i", playerid);

						// Cannot cuff for 30 seconds
						playerData[playerid][canBreakCuffs] = false;
					}
				}
				else
				{
					SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}Please wait before attempting to break free again.");
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You don't have any bobby pins.");
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{E81919}[ERROR} {FFFF00}You are not cuffed.");
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You must be logged in to use commands.");
	}
	return 1;
}

COMMAND:bc(playerid, params[])
{
	return cmd_breakcuffs(playerid, params);
}

CMD:admins(playerid)
{
     new count=0, PlayerName[MAX_PLAYER_NAME], rankname[32],color[100];
     new list1[512];
     strcat(list1, "{FFFFFF}NO\t{FFFFFF}Name(ID)\t{FFFFFF}Level\n");
     foreach(Player, i)
     {
        if(!playerData[i][playerLevel])
            continue;
        count++;
        GetPlayerName(i, PlayerName, sizeof(PlayerName));
        color = ((playerData[i][playerAdminDuty])?("{FF0770}"):("{C0C0C0}"));
        format(list1, sizeof(list1), "%s\n%d\t%s%s(%d)\t{FFFFFF}LEVEL %i\n", list1, count + 1,color, PlayerName, i, playerData[i][playerLevel]);
     }
    if(!count)
    {
        SendClientMessage(playerid, -1, "There are no administrators online.");
    }
    else
    {
        ShowPlayerDialog(playerid, 555, DIALOG_STYLE_TABLIST_HEADERS, "Online Admins",list1, "Close", "");
    }
       return 1;
}

COMMAND:jaillist(playerid, params[])
{
    new count = 1, name[24], string[828];
    for(new i = 0; i < MAX_PLAYERS; i++)
    {
        if(IsPlayerConnected(i) && playerData[i][playerJailTime] >= 1)
        {
			// If jail time is higher than 1
            GetPlayerName(i, name, sizeof(name));
            format(string, sizeof(string), "%s%s(%i)\n", string, name, i);
            count ++;
        }
    }

    if(count != 1)
    {
        ShowPlayerDialog(playerid, 200, DIALOG_STYLE_MSGBOX, "Jailed Players", string, "OK", "");
    }
	else
	{
	    ShowPlayerDialog(playerid, 200, DIALOG_STYLE_MSGBOX, "Jailed Players", "No players are jailed.", "OK", "");
	}

	return 1;

}

COMMAND:hitlist(playerid, params[])
{
    new count = 1, name[24], string[828];
    for(new i = 0; i < MAX_PLAYERS; i++)
    {
        if(IsPlayerConnected(i) && playerData[i][playerHitValue] >= 1000)
        {
            GetPlayerName(i, name, sizeof(name));
            format(string, sizeof(string), "%s%s(%i) - Hit Value: $%s\n", string, name, i, FormatNumber(playerData[i][playerHitValue]));
            count ++;
        }
    }

    if(count != 1)
    {
        ShowPlayerDialog(playerid, 200, DIALOG_STYLE_MSGBOX, "Hit List", string, "OK", "");
    }
	else
	{
	    ShowPlayerDialog(playerid, 200, DIALOG_STYLE_MSGBOX, "Hit List", "No players have a bounty on their head.", "OK", "");
	}

	return 1;
}

COMMAND:helpers(playerid, params[])
{
    new count = 1, name[24], string[528];
    for(new i = 0; i < MAX_PLAYERS; i++)
    {
        if(IsPlayerConnected(i) && playerData[i][playerHelper] >= 1)
        {
			if (playerData[i][playerHelper] > 2)
			{
				playerData[i][playerHelper] = 0;
			}

            GetPlayerName(i, name, sizeof(name));
            format(string, sizeof(string), "%s%s(%i) - Level: %i\n", string, name, i, playerData[i][playerHelper]);
            count ++;
        }
    }

    if(count != 1)
    {
        ShowPlayerDialog(playerid, 200, DIALOG_STYLE_MSGBOX, "Helpers", string, "OK", "");
    }
	else
	{
	    ShowPlayerDialog(playerid, 200, DIALOG_STYLE_MSGBOX, "Helpers", "There are no helpers online.", "OK", "");
	}

	return 1;
}

COMMAND:viplist(playerid, params[])
{
     new vcount=0, vPlayerName[MAX_PLAYER_NAME], viprankname[32],color[100];
     new vlist1[900];
     strcat(vlist1, "{FFFFFF}Name(ID)\t{FFFFFF}Level\n");
     foreach(Player, i)
     {
           if(playerData[i][playerVIPLevel] > 0)
           {
              GetPlayerName(i, vPlayerName, sizeof(vPlayerName));
              switch(playerData[i][playerVIPLevel])
              {
                 case 1: { viprankname = "{C1CDC1}Regular V.I.P"; }
                 case 2: { viprankname = "{DCCC08}Bronze V.I.P"; }
                 case 3: { viprankname = "{C1CDC1}Silver V.I.P"; }
                 case 4: { viprankname = "{F4FB09}Gold V.I.P"; }
                 case 5: { viprankname = "{C1CDC1}Platinum V.I.P"; }
                 case 6: { viprankname = "{09DEFB}Diamond V.I.P"; }
              }
              format(vlist1, sizeof(vlist1), "%s\n%s(%d)\t%s\n", vlist1,vPlayerName, i, viprankname);
              vcount++;
           }
           if(vcount == 0)
           {
             SendClientMessage(playerid, -1, "There are no VIPs online.");
             return true;
           }
           ShowPlayerDialog(playerid, 123, DIALOG_STYLE_TABLIST_HEADERS, "Online VIPs",vlist1, "Close", "");
     }
     return 1;
}

COMMAND:r(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		new input[120], message[250], message2[250];

		if(sscanf(params, "s[100]", input))
		{
			SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFF00}Usage: \"r <message>\"");
		}
		else
		{
			if (playerData[playerid][lastRecipient] == -1)
			{
				// No recipient
				SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}There is no one to quickly respond to. Use /pm!");
			}
			else
			{
				new replyto = playerData[playerid][lastRecipient];
				// Check if player is connected
				if(IsPlayerConnected(replyto))
				{
					if(playerData[replyto][playerLoggedIn])
					{
						if(!playerData[replyto][playerBlockPMs])
						{
							new from[24], otherName[24];
							GetPlayerName(replyto, otherName, sizeof(otherName));
							format(message, sizeof(message), "{FFBF00}[PM] {FFFFFF}To %s(%i): %s", otherName, replyto, input);
							SendClientMessage(playerid, COLOR_WHITE, message);

							GetPlayerName(playerid, from, sizeof(from));
							format(message2, sizeof(message2), "{FFBF00}[PM] {FFFFFF}From %s(%i): %s", from, playerid, input);
							SendClientMessage(replyto, COLOR_WHITE, message2);
							PlayerPlaySound(replyto, 1085,0.0,0.0,0.0);

							for(new i = 0; i <= MAX_PLAYERS; i++)
							{
								if(IsPlayerConnected(i))
								{
									if(playerData[i][playerLoggedIn])
									{
										if (playerData[i][playerLevel] > 4)
										{
											if (playerData[i][pmSpy])
											{
												new spyText[200];
												format(spyText, sizeof(spyText), "{FFBF00}[PM SPY] {FFFFFF}From %s(%i) to %s(%i): %s", playerData[playerid][playerNamee], playerid, playerData[replyto][playerNamee], replyto, input);
												SendClientMessage(i, COLOR_WHITE, spyText);
											}
										}
									}
								}
							}

							new loggingString[256];
							format(loggingString, sizeof(loggingString), "%s PM'd %s: %s", playerData[playerid][playerNamee], playerData[replyto][playerNamee], input);
							writeInLog("privateMessages.html", loggingString);
						}
						else
						{
							SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}The player your trying to PM has disabled private messages.");
						}
					}
					else
					{
						SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}The player your trying to PM is not logged in.");
					}
				}
				else
				{
					SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}The player your trying to PM isn't connected.");
				}
			}
		}
	}
	return 1;
}

COMMAND:pm(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		new input[120], message[250], message2[250], otherPlayer;

		if(sscanf(params, "us[100]", otherPlayer, input))
		{
			SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFF00}Usage: \"pm <player> <message>\"");
		}
		else
		{
			if (playerid == otherPlayer)
			{
				// Cannot send yourself a PM
				SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot send yourself a PM.");
			}
			else
			{
				// Check if player is connected
				if(IsPlayerConnected(otherPlayer))
				{
					if(playerData[otherPlayer][playerLoggedIn])
					{
						if(!playerData[otherPlayer][playerBlockPMs] || playerData[otherPlayer][playerBlockPMs] && playerData[playerid][playerLevel] >= 1)
						{
							new from[24], otherName[24];
							GetPlayerName(otherPlayer, otherName, sizeof(otherName));
							format(message, sizeof(message), "{FFFC00}[PM] {84FABD}To %s(%i): %s", otherName, otherPlayer, input);
							SendClientMessage(playerid, COLOR_WHITE, message);

							GetPlayerName(playerid, from, sizeof(from));
							format(message2, sizeof(message2), "{FFFC00}[PM] {84FABD}From %s(%i): %s", from, playerid, input);
							SendClientMessage(otherPlayer, COLOR_WHITE, message2);
       						PlayerPlaySound(otherPlayer, 1139,0.0,0.0,0.0);

							playerData[playerid][lastRecipient] = otherPlayer;

							for(new i = 0; i <= MAX_PLAYERS; i++)
							{
								if(IsPlayerConnected(i))
								{
									if(playerData[i][playerLoggedIn])
									{
										if (playerData[i][playerLevel] >= 4)
										{
											if (playerData[i][pmSpy])
											{
												new spyText[200];
												format(spyText, sizeof(spyText), "{FFBF00}[PM SPY] {FFFFFF}From %s(%i) to %s(%i): %s", playerData[playerid][playerNamee], playerid, playerData[otherPlayer][playerNamee], otherPlayer, input);
												SendClientMessage(i, COLOR_WHITE, spyText);
											}
										}
									}
								}
							}

							new loggingString[256];
							format(loggingString, sizeof(loggingString), "%s PM'd %s: %s", playerData[playerid][playerNamee], playerData[otherPlayer][playerNamee], input);
							writeInLog("privateMessages.html", loggingString);
						}
						else
						{
							SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}The player your trying to PM has disabled private messages.");
						}
					}
					else
					{
						SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}The player your trying to PM is not logged in.");
					}
				}
				else
				{
					SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}The player your trying to PM isn't connected.");
				}
			}
		}
	}
	return 1;
}

COMMAND:whisper(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		new string[250];

		if (sscanf(params, "s[250]", string))
		{
			SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}Usage: \"/(w)hisper <message>\"");
		}
		else
		{
			new Float:x,Float:y,Float:z;
			GetPlayerPos(playerid,x,y,z);

			new string2[250];
			format(string2, sizeof(string2), "{B76767}[WHISPER] {FFFFFF}%s(%i): %s", playerData[playerid][playerNamee], playerid, string);

			for(new i = 0; i <= MAX_PLAYERS; i++)
			{
				if(IsPlayerInRangeOfPoint(i, 15.0, x, y, z))
				{
					SendClientMessage(i, COLOR_WHITE, string2);
					PlayerPlaySound(i, 1085,0.0,0.0,0.0);
				}
			}
		}
	}
	return 1;
}

COMMAND:cw(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		new string[250], input[120];

		if (sscanf(params, "s[250]", string))
		{
			SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}Usage: \"/cw <message>\"");
		}
		else
		{
			if(IsPlayerInAnyVehicle(playerid))
			{
				new vehicleID = GetPlayerVehicleID(playerid);

				new string2[250];
				format(string2, sizeof(string2), "{FE9A2E}[CAR WHISPER] {FFFFFF}%s(%i): %s", playerData[playerid][playerNamee], playerid, string);

				for(new i = 0; i <= MAX_PLAYERS; i++)
				{
					if(IsPlayerInVehicle(i, vehicleID))
					{
						SendClientMessage(i, COLOR_WHITE, string2);
					}
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFFFF}You are not in a vehicle.");
			}
			for(new i = 0; i <= MAX_PLAYERS; i++)
			{
				if(IsPlayerConnected(i))
				{
				    if(IsPlayerInAnyVehicle(playerid))
				    {
						if(playerData[i][playerLoggedIn])
						{
							if (playerData[i][playerLevel] >= 5)
							{
								if (playerData[i][cwspy])
								{
									new cwtext[200];
									format(cwtext, sizeof(cwtext), "{FFBF00}[CAR WHISPER SPY]> %s: %s",playerData[playerid][playerNamee], string, input);
									SendClientMessage(i, COLOR_WHITE, cwtext);

								}
							}
						}
					}
				}
			}
		}
	}
	return 1;
}

COMMAND:eject(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		new otherID;

		if (sscanf(params, "u", otherID))
		{
			SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}Usage: \"/eject <player>\"");
		}
		else
		{
			if(playerid != otherID)
			{
			    if(GetPlayerInterior(playerid) == 0)
			    {
					if(IsPlayerInAnyVehicle(playerid))
					{
						if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
						{
							new vehicleID = GetPlayerVehicleID(playerid);
							if(IsPlayerConnected(otherID))
							{
								if(IsPlayerInAnyVehicle(otherID))
								{
									if(GetPlayerVehicleID(otherID) == vehicleID)
									{
										RemovePlayerFromVehicle(otherID);

										SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[EJECTED] {FFFF00}The player has been ejected from your vehicle.");
										SendClientMessage(otherID, COLOR_WHITE, "{B7B7B7}[EJECTED] {FFFF00}You have been ejected from the vehicle.");
									}
									else
									{
										SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}The player is not in your vehicle.");
									}
								}
								else
								{
									SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}The player is not in your vehicle.");
								}
							}
							else
							{
								SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}The player your trying to eject isn't connected.");
							}
						}
						else
						{
							SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You must be the driver to eject players.");
						}
					}
					else
					{
						SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You are not in a vehicle.");
					}
				}
				else
				{
				    SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot eject player in this place.");
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot eject yourself.");
			}
		}
	}
	return 1;
}

COMMAND:w(playerid, params[])
{
	return cmd_whisper(playerid, params);
}

/*COMMAND:payticket(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if (playerData[playerid][playerLastTicket] == -1)
		{
			SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}There are no tickets to pay.");
		}
		else
		{
			new message[250];
			new status = checkNameStatus(playerData[playerid][playerLastTicket]);
			if(status == -1)
			{
				// Pay cash to state
				SendClientMessage(playerid, COLOR_WHITE, "{FFDC2E}[TICKET] {FFFF00}You have paid your ticket.");
				playerTakeMoney(playerid, 2500);

				SetPlayerWantedLevel(playerid, playerData[playerid][playerWantedLevel] - 3);
				playerData[playerid][playerWantedLevel] = playerData[playerid][playerWantedLevel] - 3;
				newPlayerColour(playerid);
				playerData[playerid][playerLastTicket] = -1;
			}
			else
			{
				// Pay cash to ID
				playerGiveMoney(status, 2500);
				playerTakeMoney(playerid, 2500);

				SetPlayerWantedLevel(playerid, playerData[playerid][playerWantedLevel] - 3);
				playerData[playerid][playerWantedLevel] = playerData[playerid][playerWantedLevel] - 3;
				playerData[playerid][playerLastTicket] = -1;
				newPlayerColour(playerid);

				// Send message to player
				SendClientMessage(playerid, COLOR_WHITE, "{FFDC2E}[TICKET] {FFFF00}You have paid your ticket.");

				// Send message to cop
				format(message, sizeof(message), "{FFDC2E}[TICKET PAID] {FFFF00}You received {FFDC2E}$2,500 {FFFFFF}from %s(%i)", playerData[playerid][playerNamee], playerid);
				SendClientMessage(status, COLOR_WHITE, message);
			}
		}
	}
	return 1;
}*/

COMMAND:acceptbail(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if (playerData[playerid][playerJailTime] > 1)
		{
			if (playerData[playerid][playerBailTo] == -1)
			{
				SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}There are no bail offers.");
			}
			else
			{
				if (playerData[playerid][playerMoney] >= playerData[playerid][playerBailPrice])
				{
					new message[250];
					new bailID = playerData[playerid][playerBailTo];
					if (playerid != bailID)
					{
						if(IsPlayerConnected(bailID))
						{
							if(playerData[bailID][playerClass] == CLASS_POLICE || playerData[bailID][playerClass] == CLASS_ARMY || playerData[bailID][playerClass] == CLASS_CIA || playerData[bailID][playerClass] == CLASS_FBI) // offer gone
							{
								// Pay cash to ID
								playerGiveMoney(bailID, playerData[playerid][playerBailPrice]);
								playerTakeMoney(playerid, playerData[playerid][playerBailPrice]);

								// Send message to cop
								format(message, sizeof(message), "{58D3F7}[BAIL PAID] {FFFFFF}You received {FFDC2E}$%s {FFFFFF}from %s(%i)", FormatNumber(playerData[playerid][playerBailPrice]), playerData[playerid][playerNamee], playerid);
								SendClientMessage(bailID, COLOR_WHITE, message);
								playerGiveXP(bailID, 5);

								new loggingString[256];
								format(loggingString, sizeof(loggingString), "%s bailed %s for $%s.", playerData[bailID][playerNamee], playerData[playerid][playerNamee], FormatNumber(playerData[playerid][playerBailPrice]));
								writeInLog("bailTransactions.html", loggingString);

								playerData[playerid][playerBailTo] = 0;
								playerData[playerid][playerBailPrice] = 0;

								// Release from jail
								SetPlayerInterior(playerid, 10);
								SetPlayerPos(playerid, 249.4593, 115.0391, 1003.2188);
								SetPlayerFacingAngle(playerid, 183.3742);
								SetPlayerVirtualWorld(playerid, 25);
								SetPlayerHealth(playerid, 100);
								PlayerTextDrawSetString(playerid, playerData[playerid][playerJailTimerTD], " ");
								playerData[playerid][playerJailTime] = 0;
								KillTimer(playerData[playerid][jailTimer]);

								new Name[24], MsgAll[200];
								GetPlayerName(playerid, Name, sizeof(Name));

								for(new p; p < MAX_PLAYERS; p++)
								{
									new pName[24];
									GetPlayerName(p, pName, sizeof(pName));

									if(!strcmp(pName, Name))
									{
										SendClientMessage(p, COLOR_WHITE, "{58D3F7}[BAIL] {FFFF00}You have been released on bail.");
									}
									else
									{
										format(MsgAll, sizeof(MsgAll), "{FFDC2E}[JAIL] {FFFF00}%s(%i) has been released from jail {58D3F7}[Paid Bail]{FFFFFF}", Name, playerid);
										SendClientMessage(p, COLOR_WHITE, MsgAll);
									}
								}
							}
							else
							{
								// Cop offline
								SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}The bail offer is no longer available.");
							}
						}
						else
						{
							SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}The bail offer is no longer available. (2)");
						}
					}
				}
				else
				{
					SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cant afford this offer.");
				}
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You aren't jailed.");
		}
	}

	return 1;
}

COMMAND:report(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if (playerData[playerid][canReport])
		{
			new input[120], message[250];

			if(sscanf(params, "s[100]", input))
			{
				SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}Usage: \"report <message>\"");
			}
			else
			{
				for(new i = 0; i < MAX_PLAYERS; i++)
				{
					if(IsPlayerConnected(i) && playerData[i][playerLevel] >= 1)
					{
						format(message, sizeof(message), "{DF0101}[REPORT] {FFFFFF}From %s(%i): %s", playerData[playerid][playerNamee], playerid, input);
						SendClientMessage(i, COLOR_WHITE, message);
					}
				}

				SendClientMessage(playerid, COLOR_WHITE, "{DF0101}[REPORT] {FFFF00}Your report has been sent to the online administrators.");
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You have been blocked from using report by an administrator.");
		}
	}
	return 1;
}
COMMAND:ask(playerid, params[])
{
    if(playerData[playerid][playerLoggedIn])
    {
        if (playerData[playerid][canAsk])
        {
            new input[120], message[250];

            if(sscanf(params, "s[100]", input))
            {
                SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}Usage: \"ask <message>\"");
            }
            else
            {
                for(new i = 0; i < MAX_PLAYERS; i++)
                {
                    if(IsPlayerConnected(i) && playerData[i][playerLevel] >= 1 || playerData[i][playerHelper] == 1)
                    {
                        format(message, sizeof(message), "{FF1493}[QUESTION] {FFFFFF}From %s(%i): %s", playerData[playerid][playerNamee], playerid, input);
                        SendClientMessage(i, COLOR_WHITE, message);
                    }
                }

                format( message, sizeof( message ), "{FE5700}[QUESTION] {FFFFFF}You've asked \"%s\".", input );
                SendClientMessage( playerid, COLOR_WHITE, message);
            }
        }
        else
        {
            SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFF00}You have been blocked from using ask by an administrator.");
        }
    }
    return 1;
}
                
COMMAND:answer(playerid, params[])
{
	return cmd_ans(playerid, params);
}

COMMAND:radio(playerid, params[])
{
    if (playerData[playerid][playerLoggedIn])
    {
 	    new string[3000];

    	strcat(string,"{FCFCFF}Country\n");
 		strcat(string,"{FCFCFF}Drum n' Bass\n");
 		strcat(string,"{FCFCFF}Electronic\n");
 		strcat(string,"{FCFCFF}Metal\n");
 		strcat(string,"{FCFCFF}Hip - Hop\n");
		strcat(string,"{FCFCFF}Pop\n");
		strcat(string,"{FCFCFF}Rap\n");
		strcat(string,"{FCFCFF}Raggae\n");
		strcat(string,"{FCFCFF}Rock\n");
		strcat(string,"{FCFCFF}Trance\n");
		strcat(string,"{FCFCFF}Techno\n");
		strcat(string,"{FCFCFF}House\n");
		strcat(string,"{FCFCFF}SKY.FM Hits\n");
		strcat(string,"{FCFCFF}Party 181.FM\n");
		strcat(string,"{FCFCFF}Top 40 181.FM\n");
		strcat(string,"{FCFCFF}977 Hits.\n");

		ShowPlayerDialog(playerid, DIALOG_RADIO, DIALOG_STYLE_LIST,"Radio",string,"Select","Cancel");

		return 1;
    }
    else
    {
        SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You must be logged in to use commands.");
    }
    return 1;
}

COMMAND:stopradio(playerid, params[])
{
    if (playerData[playerid][playerLoggedIn])
    {
        StopAudioStreamForPlayer(playerid); // Stop the audio stream
	}
    else
    {
        SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You must be logged in to use commands.");
    }
    return 1;
}

COMMAND:help(playerid, params[])
{
    if (playerData[playerid][playerLoggedIn])
    {
		ShowPlayerDialog(playerid, DIALOG_HELP, DIALOG_STYLE_LIST, "CFS-CNR Help", "Player Commands\nServer Admins\nHosted Events\nPlayer Houses\nStore Robberies\nTokens", "Go", "Cancel");
    }
    else
    {
        SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You must be logged in to use commands.");
    }
    return 1;
}

COMMAND:vipcmds(playerid, params[])
{
    if (playerData[playerid][playerLoggedIn])
    {
		if(playerData[playerid][playerVIPLevel] > 0)
		{
		new string[1200];
		format(string, sizeof(string), "%s{98B0CD}1. {FFFF00}/viphat (ALL)\n", string);
		format(string, sizeof(string), "%s{98B0CD}2. {FFFF00}/vipskin (silvervip)\n", string);
		format(string, sizeof(string), "%s{98B0CD}3. {FFFF00}/vmod (silvervip)\n", string);
		format(string, sizeof(string), "%s{98B0CD}4. {FFFF00}/toys (goldvip)\n", string);
		format(string, sizeof(string), "%s{98B0CD}5. {FFFF00}/vipweapon (silvervip)\n", string);
		format(string, sizeof(string), "%s{98B0CD}6. {FFFF00}/vsay (ALL)\n", string);
		format(string, sizeof(string), "%s{98B0CD}6. {FFFF00}/parrot (ALL)\n", string);
		format(string, sizeof(string), "%s{98B0CD}7. {FFFF00}/countdown (ALL)\n", string);
		format(string, sizeof(string), "%s{98B0CD}7. {FFFF00}/neon (ALL}\n", string);
		format(string, sizeof(string), "%s{98B0CD}7. {FFFF00}/vfix (silvervip)\n", string);
		format(string, sizeof(string), "%s{98B0CD}7. {FFFF00}/flip (silvervip)\n", string);
		format(string, sizeof(string), "%s{98B0CD}7. {FFFF00}/vipguns (goldvip)\n", string);
		format(string, sizeof(string), "%s{98B0CD}8. {FFFF00}/vipcolor (ALL)\n", string);
		ShowPlayerDialog(playerid, 188, DIALOG_STYLE_MSGBOX, "VIP Commands", string, "OK", "Leave");
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You must be a VIP member to use this command.");
		}
    }
    else
    {
        SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You must be logged in to use commands.");
    }
    return 1;
}

COMMAND:vmod(playerid, params[])
{
    if (playerData[playerid][playerLoggedIn])
    {
		if(playerData[playerid][playerVIPLevel] >= 2)
		{
			if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
			{
				SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You must be the driver of a vehicle to use this command.");
			}
			else
			{
				new vehiclemodel = GetVehicleModel(GetPlayerVehicleID(playerid));
				if(vehiclemodel < 400 || vehiclemodel > 611)
				{
					SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}This vehicle can't be modified.");
				}
				else
				{
					new string[2048], component, title[80];
					ccount[playerid] = 1;

					while(GetVehicleCompatibleUpgrades(vehiclemodel, ccount[playerid], component))
					{
						if(ccount[playerid] <= MAX_COMP)
						{
							if(ccount[playerid] == 1) format(string, sizeof(string), "%s", GetComponentName(component));
							else format(string, sizeof(string), "%s\n%s", string, GetComponentName(component));
							componentsid[playerid][ccount[playerid]-1] = component;
							ccount[playerid]++;
						}
						else
						{
							break;
						}
					}

					format(title, sizeof(title), "VIP Mod Menu", vehiclemodel);
					ShowPlayerDialog(playerid, DIALOG_MODMENU, DIALOG_STYLE_LIST, title, string, "Apply", "Cancel");
				}
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You must be at-least Silver VIP to use this command.");
		}
    }
    else
    {
        SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You must be logged in to use commands.");
    }

    return 1;
}

COMMAND:viphat(playerid, params[])
{
    if (playerData[playerid][playerLoggedIn])
    {
		if(playerData[playerid][playerVIPLevel] >= 1)
		{
			ShowPlayerDialog(playerid, DIALOG_VIPHAT, DIALOG_STYLE_LIST, "VIP HATS", "Hat 1\nHat 2\nHat 3\nHat 4\nHat 5\nHat 6 \nHat 7\nHat 8\n{D87C3E}Remove Hat", "Wear", "Close");
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You must be a VIP to use this command.");
		}
    }
    else
    {
        SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You must be logged in to use commands.");
    }

    return 1;
}

COMMAND:commands(playerid, params[])
{
    if (playerData[playerid][playerLoggedIn])
    {
		ShowPlayerDialog(playerid, DIALOG_COMMANDS, DIALOG_STYLE_LIST, "Commands", "General Commands\nTrucker Commands\nAnimation Commands\nPolice Commands\nJob Commands\nHouse Commands\nVehicle Commands", "Go", "Cancel");
    }
    else
    {
        SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You must be logged in to use commands.");
    }
    return 1;
}

COMMAND:cmds(playerid, params[])
{
	return cmd_commands(playerid, params);
}

COMMAND:rules(playerid, params[])
{
    if (playerData[playerid][playerLoggedIn])
    {
		new string[1200];
		format(string, sizeof(string), "%s{98B0CD}1. {02FEE7}Respect players and admins. \n", string);
		format(string, sizeof(string), "%s{98B0CD}2. {02FEE7}Do not flood the chat, or advertise other servers. \n", string);
		format(string, sizeof(string), "%s{98B0CD}3. {02FEE7}Hacking/Cheating will get you banned. \n", string);
		format(string, sizeof(string), "%s{98B0CD}4. {02FEE7}LEO players must not kill innocent civilians. \n", string);
		format(string, sizeof(string), "%s{98B0CD}5. {02FEE7}Team killing is not allowed. \n", string);
		format(string, sizeof(string), "%s{98B0CD}6. {02FEE7}Do not tie abuse (leaving a player once tied) \n", string);
		format(string, sizeof(string), "%s{98B0CD}7. {02FEE7}If you are a LEO, do not assist criminals. \n", string);
		format(string, sizeof(string), "%s{98B0CD}8. {02FEE7}Do not EMP vehicles if there are no wanted players inside. \n", string);
		format(string, sizeof(string), "%s{98B0CD}9. {02FEE7}Do not quit or pause to avoid anything. You will be jailed for this.\n", string);
		format(string, sizeof(string), "%s{98B0CD}10. {02FEE7}Park your owned vehicle in a sensible spot, preferably at your home. \n", string);
		format(string, sizeof(string), "%s{98B0CD}11. {02FEE7}Farming score/xp/money is unacceptable, you will be banned for this. \n", string);
		format(string, sizeof(string), "%s{98B0CD}12. {02FEE7}Do not drive-by without a driver. \n", string);
		format(string, sizeof(string), "%s{98B0CD}13. {02FEE7}Do not question administrative actions. \n", string);
		format(string, sizeof(string), "%s{98B0CD}14. {02FEE7}Bugs should be reported, not exploited. \n", string);
		format(string, sizeof(string), "%s{98B0CD}15. {02FEE7}Keybinds are not allowed. \n", string);
		format(string, sizeof(string), "%s{98B0CD}16. {02FEE7}Roadblock and Spike Strip abuse are not allowed. \n", string);
		format(string, sizeof(string), "%s{98B0CD}16. {02FEE7}Asking For Adminship ban 3 days. \n", string);
		format(string, sizeof(string), "%s{98B0CD}16. {02FEE7}English In Main-Chat or u will be Kicked!. \n", string);

		if (!playerData[playerid][rulesRead])

		{
			disableAchieve(playerid);
			PlayerTextDrawShow(playerid, playerData[playerid][Achieve1]);
			PlayerTextDrawShow(playerid, playerData[playerid][Achieve2]);
			PlayerTextDrawShow(playerid, playerData[playerid][Achieve3]);
			PlayerTextDrawShow(playerid, playerData[playerid][Achieve4]);

			PlayerTextDrawSetString(playerid, playerData[playerid][Achieve3], "Book Worm");
			PlayerTextDrawSetString(playerid, playerData[playerid][Achieve4], "You read the server rules, great!");
			PlayerPlaySound(playerid, 1185 ,0.0, 0.0, 0.0);

			playerData[playerid][achieveTimer] = SetTimerEx("disableAchieve", 6000, false, "i", playerid);

			playerGiveXP(playerid, 25);
			playerData[playerid][playerScore] = playerData[playerid][playerScore] + 2;
			playerData[playerid][rulesRead] = 1;
			SetPlayerScore(playerid, playerData[playerid][playerScore]);
			savePlayerStats(playerid);
		}

		ShowPlayerDialog(playerid, DIALOG_RULES, DIALOG_STYLE_MSGBOX, "Rules", string, "OK", "");
    }
    else
    {
        SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You must be logged in to use commands.");
    }
    return 1;
}

COMMAND:vip(playerid, params[])
{
    if (playerData[playerid][playerLoggedIn])
    {
		new string[2200];
		format(string, sizeof(string), "{FFDC2E}Standard VIP [$3.00 USD]\n\n", string);
		format(string, sizeof(string), "%s{FF271B}- Receive 500,000 in-game cash.\n", string);
		format(string, sizeof(string), "%s{FF271B}- Receive 1,050 in-game XP.\n", string);
		format(string, sizeof(string), "%s{FF271B}- Gets access to VIP louge for health refills.\n", string);
		format(string, sizeof(string), "%s{FF271B}- Get access to: /vsay, /viphelp, /parrot, /vipcolour, /viphat, /vcolour\n", string);
		format(string, sizeof(string), "%s{FF271B}- Get a 30.5% success rate, on asking an admin for an event and them saying yes.\n", string);
		format(string, sizeof(string), "%s{FF271B}- Get 1 FREE VIP House, of any location!\n", string);

		format(string, sizeof(string), "%s{1BFFEB}-------------------------------------------------------------------\n\n", string);

		format(string, sizeof(string), "%s{1BFFEB}Silver VIP [$8.00 USD]{FFFFFF}\n\n", string);
		format(string, sizeof(string), "%s{1BFFEB}- Receive 2 million in-game cash.\n", string);
		format(string, sizeof(string), "%s{1BFFEB}- Receive 16,000 in-game XP.\n", string);
		format(string, sizeof(string), "%s{1BFFEB}- Gets access to VIP louge for 50 percent armour refills.\n", string);
		format(string, sizeof(string), "%s{1BFFEB}- Get access to: /vmod, /vipweapon\n", string);
		format(string, sizeof(string), "%s{1BFFEB}- Connect/Spawn with 50 percent armour.\n", string);
		format(string, sizeof(string), "%s{1BFFEB}- Get 3 Tokens, each token is valid for a vehicle.\n", string);
		format(string, sizeof(string), "%s{1BFFEB}- Get a 70.5% success rate, on asking an admin for an event and them saying yes.\n", string);
		format(string, sizeof(string), "%s{1BFFEB}- Get 1 FREE VIP House, of any location!\n", string);
		format(string, sizeof(string), "%s{1BFFEB}- Get all of the things from Standard VIP.\n", string);

		format(string, sizeof(string), "%s{FFFFFF}-------------------------------------------------------------------\n\n", string);

		format(string, sizeof(string), "%s{FFDC2E}Gold VIP [$12.00 USD]{FFFFFF}\n\n", string);
		format(string, sizeof(string), "%s{1BFFEB}- Receive 5 million in-game cash.\n", string);
		format(string, sizeof(string), "%s{1BFFEB}- Receive 30,000 in-game XP.\n", string);
		format(string, sizeof(string), "%s{1BFFEB}- Gets access to VIP louge for 100 percent armour refills.\n", string);
		format(string, sizeof(string), "%s{1BFFEB}- Get access to: /toys, /vipskin\n", string);
		format(string, sizeof(string), "%s{1BFFEB}- Connect/Spawn with 100 percent armour.\n", string);
		format(string, sizeof(string), "%s{1BFFEB}- Get 7 Tokens, each token is valid for a vehicle.\n", string);
		format(string, sizeof(string), "%s{1BFFEB}- Get a 99.5% success rate, on asking an admin for an event and them saying yes.\n", string);
		format(string, sizeof(string), "%s{1BFFEB}- Get 2 FREE VIP Houses, of any location!\n", string);
		format(string, sizeof(string), "%s{1BFFEB}- Get all of the things from Silver VIP & Standard VIP.\n", string);

		ShowPlayerDialog(playerid, DIALOG_RULES, DIALOG_STYLE_MSGBOX, "V.I.P Packages", string, "OK", "");
    }
    else
    {
        SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFFFF}You must be logged in to use commands.");
    }
    return 1;
}

COMMAND:shop(playerid, params[])
{
    if (playerData[playerid][playerLoggedIn])
    {
        new curint = GetPlayerInterior(playerid);
        if (curint == 90 || curint == 207)
        {
			if (!playerData[playerid][playerIsTied] && !playerData[playerid][playerIsCuffed])
			{
				new supaSave[1000];
				format(supaSave, sizeof(supaSave), "%s\n{D87C3E}$1,000      {FFFFFF}1x Rope {FFF700}(Saves)", supaSave);
				format(supaSave, sizeof(supaSave), "%s\n{D87C3E}$4,000      {FFFFFF}4x Rope {FFF700}(Saves)", supaSave);
				format(supaSave, sizeof(supaSave), "%s\n{D87C3E}$2,500      {FFFFFF}1x Scissors {FFF700}(Saves)", supaSave);
				format(supaSave, sizeof(supaSave), "%s\n{D87C3E}$2,000      {FFFFFF}1x Bobby Pins {FFF700}(Saves)", supaSave);
				format(supaSave, sizeof(supaSave), "%s\n{D87C3E}$2,000      {FFFFFF}4x Bobby Pins {FFF700}(Saves)", supaSave);
				format(supaSave, sizeof(supaSave), "%s\n{D87C3E}$15,000    {FFFFFF}Backpack {FFF700}(Saves)", supaSave);
				format(supaSave, sizeof(supaSave), "%s\n{D87C3E}$5,000      {FFFFFF}Bigger Pockets", supaSave);
				format(supaSave, sizeof(supaSave), "%s\n{D87C3E}$5,000      {FFFFFF}Secure Wallet", supaSave);
				format(supaSave, sizeof(supaSave), "%s\n{D87C3E}$5,000      {FFFFFF}1x Butt Plug", supaSave);
				format(supaSave, sizeof(supaSave), "%s\n{D87C3E}$25,000    {FFFFFF}Lucky Charm", supaSave);
				format(supaSave, sizeof(supaSave), "%s\n{D87C3E}$20,000    {FFFFFF}Mask {FFF700}(Removed on death)", supaSave);
				format(supaSave, sizeof(supaSave), "%s\n{D87C3E}$10,000    {FFFFFF}Bomb Defusal Kit", supaSave);
   				format(supaSave, sizeof(supaSave), "%s\n{D87C3E}$5,000      {FFFFFF}1x Escapists Guide", supaSave);
   				//format(supaSave, sizeof(supaSave), "%s\n{D87C3E}$20,000     {FFFFFF}Toy System", supaSave);

				ShowPlayerDialog(playerid, DIALOG_SUPASAVE, DIALOG_STYLE_LIST, "Shop", supaSave, "Buy", "Close");
			}
			else
			{
				SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {1BFFEB}You cannot do this whilst tied/cuffed.");
			}
		}
        else
        {
            SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You're not inside CSF-CNR.");
        }
    }
    else
    {
        SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You must be logged in to use commands.");
    }
    return 1;
}

COMMAND:xpmarket(playerid, params[])
{
    if (playerData[playerid][playerLoggedIn])
    {
		if (!playerData[playerid][playerIsTied] && !playerData[playerid][playerIsCuffed])
		{
			new xpSHOP[500];
			format(xpSHOP, sizeof(xpSHOP), "%s\n{D87C3E}100 XP       {FFFF00}Gives you $1000 in cash.", xpSHOP);

			ShowPlayerDialog(playerid, DIALOG_XPSHOP, DIALOG_STYLE_LIST, "XP Shop", xpSHOP, "Buy", "Close");
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFFFF}You cannot do this whilst tied/cuffed.");
		}
    }
    else
    {
        SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFFFF}You must be logged in to use commands.");
    }
    return 1;
}

COMMAND:kill(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
	    if (playerData[playerid][playerWantedLevel] == 0)
	    {
		    if(playerData[playerid][playerJailTime] <= 0)
			{
				if(!playerData[playerid][playerIsTied])
				{
					playerData[playerid][suicide] = true;
					SetPlayerHealth(playerid, 0.0);
				}
				else
				{
					SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot use this command whilst you are tied!");
				}
			}
			else
			{
			    SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot use this command whilst you are jailed!");
			}
	    }
	    else
	    {
            SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot use this command whilst you have a wanted level!");
        }
	}
	return 1;
}

COMMAND:selectcity(playerid, params[])
{
    if(playerData[playerid][playerLoggedIn])
	{
	    if (playerData[playerid][playerWantedLevel] == 0)
	    {
		    if(playerData[playerid][playerJailTime] <= 0)
			{
				if(!playerData[playerid][playerIsTied])
				{
 	            new teleports[2500];

                strcat(teleports,"Area 51\n");
	            strcat(teleports,"LS Grove Street\n");
	            strcat(teleports,"SF Garage\n");
	            strcat(teleports,"LV Casino");

	            ShowPlayerDialog(playerid,DIALOG_TELEPORTS,DIALOG_STYLE_LIST,"San Andreas City",teleports,"OK","Cancel");
	            }
				else
				{
					SendClientMessage(playerid, COLOR_WHITE, "{FF0404}.: You cannot teleport while you are tied :.");
				}
			}
			else
			{
			    SendClientMessage(playerid, COLOR_WHITE, "{FF0404}.: You cannot teleport while you are in jail :.");
			}
	    }
	    else
	    {
            SendClientMessage(playerid, COLOR_WHITE, "{FF0404}.: You cannot teleport while you have wanted level! :.");
        }
	}
	return 1;
}


COMMAND:newclass(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
	    if (playerData[playerid][playerWantedLevel] == 0)
	    {
		    if(playerData[playerid][playerJailTime] <= 0)
			{
				if(!playerData[playerid][playerIsTied])
				{
					ForceClassSelection(playerid);
					SetPlayerHealth(playerid, 0.0);
				}
				else
				{
					SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot use this command whilst you are tied!");
				}
			}
			else
			{
			    SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot use this command whilst you are jailed!");
			}
	    }
	    else
	    {
            SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot use this command whilst you have a wanted level!");
        }
	}
	return 1;
}

COMMAND:robstore(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		beginRobbery(playerid);
	}
	return 1;
}

COMMAND:cancelrob(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(playerData[playerid][playerStoreID] > 0)
		{
			cancelRobbery(playerid);
		}
	}
	return 1;
}

COMMAND:cancel(playerid, params[])
{
	return cmd_cancelrob(playerid, params);
}


COMMAND:arenas(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(playerData[playerid][playerLevel] >= 2)
		{
            ShowPlayerDialog(playerid, DIALOG_ARENAS, DIALOG_STYLE_LIST, "Arenas", "Dirt Track \n8 Track Arena \nBloodbowl \nVice Stadium \nWarehouse \nDerby arena", "Go", "Cancel");
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You do not have the correct permissions to use this command.");
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You must be logged in to use commands.");
	}

	return 1;
}

COMMAND:inventory(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		new inventory[500];

		format(inventory, sizeof(inventory), "%s\n{58D3F7}%i {FFFF00}Weed", inventory, playerData[playerid][playerWeed]);
		format(inventory, sizeof(inventory), "%s\n{58D3F7}%i {FFFF00}Ropes", inventory, playerData[playerid][playerRope]);
		format(inventory, sizeof(inventory), "%s\n{58D3F7}%i {FFFF00}Scissors", inventory, playerData[playerid][playerScissors]);
		format(inventory, sizeof(inventory), "%s\n{58D3F7}%i {FFFF00}Bobby Pins", inventory, playerData[playerid][playerBobbyPins]);
		format(inventory, sizeof(inventory), "%s\n{58D3F7}%i {FFFF00}Explosives", inventory, playerData[playerid][playerExplosives]);
		format(inventory, sizeof(inventory), "%s\n{58D3F7}%i {FFFF00}Bigger Pockets", inventory, playerData[playerid][playerBiggerPockets]);
		format(inventory, sizeof(inventory), "%s\n{58D3F7}%i {FFFF00}Secure Wallet", inventory, playerData[playerid][playerSecureWallet]);
		format(inventory, sizeof(inventory), "%s\n{58D3F7}%i {FFFF00}Mask", inventory, playerData[playerid][mask]);
		format(inventory, sizeof(inventory), "%s\n{58D3F7}%i {FFFF00}Bomb Defusal Kit", inventory, playerData[playerid][playerDefuseKit]);

		ShowPlayerDialog(playerid, DIALOG_ACHIEVEMENTS, DIALOG_STYLE_LIST, "Inventory", inventory, "OK", "Close");
	}

	return 1;
}

COMMAND:allstats(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
        ShowPlayerDialog(playerid, DIALOG_STATS, DIALOG_STYLE_LIST, "Game Statistics", "Player Statistics \nPolice Statistics \nCrime Statistics \nMission Statistics \nMy Inventory", "View", "Cancel");

	}
	else
	{
		SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You must be logged in to use commands.");
	}

	return 1;
}

COMMAND:jailtime(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		new timeMessage[150];
		format(timeMessage, sizeof(timeMessage), "Time Remaining: %i seconds", playerData[playerid][playerJailTime]);
		SendClientMessage(playerid, COLOR_ORANGE, timeMessage);
	}
	else
	{
		SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You must be logged in to use commands.");
	}

	return 1;
}

COMMAND:savestats(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if (playerData[playerid][playerCanSaveStats])
		{
			savePlayerStats(playerid);

			SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFF00}Your stats have been saved.");

			playerData[playerid][playerCanSaveStats] = false;
			playerData[playerid][saveStatsTimer] = SetTimerEx("canSaveStats", 120000, false, "i", playerid);
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}Please wait before attempting to save your stats again.");
		}
    }
    else
    {
       SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You must be logged in to use commands.");
    }

    return 1;
}


COMMAND:sendmoney(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		new otherID, amount, message[128], message2[128], loggingString[256];

		if(sscanf(params, "ui", otherID, amount))
		{
			SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFF00}Usage: \"sendmoney <otherID> <amount>\"");
		}
		else
		{
			if(IsPlayerConnected(otherID))
			{
				if(playerData[otherID][playerLoggedIn])
				{
					if (otherID != playerid)
					{
						if (playerData[playerid][playerMoney] >= amount && amount > 0)
						{
							playerGiveMoney(otherID, amount);
							playerTakeMoney(playerid, amount);
							format(message, sizeof(message), "{B7B7B7}[CASH] {FFFFFF}You have given {FFDC2E}$%s {FFFFFF}to %s(%i)", FormatNumber(amount), playerData[otherID][playerNamee], otherID);
							SendClientMessage(playerid, COLOR_WHITE, message);

							format(message2, sizeof(message2), "{B7B7B7}[CASH] {FFFFFF}You have received {FFDC2E}$%s {FFFFFF}from %s(%i)", FormatNumber(amount), playerData[playerid][playerNamee], playerid);
							SendClientMessage(otherID, COLOR_WHITE, message2);
							PlayerPlaySound(otherID, 1149, 0.0, 0.0, 10.0);

							format(loggingString, sizeof(loggingString), "%s sent %s $%s.", playerData[playerid][playerNamee], playerData[otherID][playerNamee], FormatNumber(amount));
							writeInLog("moneyTransactions.html", loggingString);
						}
						else
						{
							SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You don't have enough money to complete this transaction.");
						}
					}
					else
					{
						SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot send money to yourself.");
					}
				}
				else
				{
					SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}That player is not logged in!");
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}That player is not online!");
			}
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You must be logged in to use commands.");
	}

	return 1;
}

COMMAND:countdown(playerid, params[])
{
	if(!playerData[playerid][playerLoggedIn])
	{
		return 0;
	}
	new msg[256];
	if(playerData[playerid][playerVIPLevel] >= 1)
	{
		if(serverInfo[VIPcount] == 0)
		{
		    KillTimer(serverInfo[countTimer]);
			format(msg, sizeof(msg), "{58D3F7}[VIP] %s{FFFF00} started countdown!", playerData[playerid][playerNamee]);
			SendClientMessageToAll(0xFFFFFF, msg);
			serverInfo[VIPcount] = 5;
			serverInfo[countTimer] = SetTimer("Countdown", 1000, true);			
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}Another countdown on progress.");
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}This command only for VIP.");
	}
	return 1;
}

COMMAND:sm(playerid, params[])
{
	return cmd_sendmoney(playerid, params);
}


COMMAND:rob(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
	    if(!playerData[playerid][playerAdminDuty])
		{
			if(!playerData[playerid][isInEvent] && !playerData[playerid][isInlms] && !playerData[playerid][isInCVR])
			{
				if(playerData[playerid][playerClass] == CLASS_CIVILIAN)
				{
					if(playerData[playerid][playerCanRob])
					{
						new otherPlayer = GetClosestPlayerToPlayer(playerid);

						new message[128];
						if(IsPlayerConnected(otherPlayer))
						{
							if(playerData[otherPlayer][playerLoggedIn])
							{
								new Float:lX, Float:lY, Float:lZ;
								GetPlayerPos(otherPlayer, lX, lY, lZ);
								if(IsPlayerInRangeOfPoint(playerid, 4.0, lX, lY, lZ))
								{
									if(playerData[playerid][playerJailTime] <= 0)
									{
										if(playerData[otherPlayer][playerJailTime] <= 0)
										{
											if(!IsPlayerInAnyVehicle(otherPlayer))
											{
												if(!IsPlayerInAnyVehicle(playerid))
												{
													if(!playerData[otherPlayer][playerAdminDuty])
													{
														if(!playerData[playerid][playerIsCuffed])
														{
															if(!playerData[playerid][playerIsTazed])
															{
																if(!playerData[playerid][playerIsTied])
																{
																	if(playerData[otherPlayer][playerMoney] >= 5000)
																	{
																		if(playerData[otherPlayer][playerSecureWallet] == 0)
																		{
																			new determinator = random(4);
																			switch(determinator)
																			{
																				case 0, 1, 2:
																				{
																					new robberyAmount = randomEx(250, 3000);
																					playerGiveMoney(playerid, robberyAmount);
																					playerGiveMoney(otherPlayer, -robberyAmount);

																					format(message, sizeof(message), "{E6BD1A}[CRIME] {FFFF00}You successfully robbed %s(%i) and received {FFDC2E}$%s ", playerData[otherPlayer][playerNamee], otherPlayer, FormatNumber(robberyAmount));
																					SendClientMessage(playerid, COLOR_WHITE, message);

																					format(message, sizeof(message), "{E6BD1A}[CRIME] {FFFF00}You were robbed by %s(%i) they stole {FFDC2E}$%s ", playerData[playerid][playerNamee], playerid, FormatNumber(robberyAmount));
																					SendClientMessage(otherPlayer, COLOR_WHITE, message);

																					playerGiveXP(playerid, 10);
																					playerData[playerid][playerScore] = playerData[playerid][playerScore] + 1;
																					SetPlayerScore(playerid, playerData[playerid][playerScore]);

																					playerData[playerid][streetRobberies] = playerData[playerid][streetRobberies] + 1;

																					if (playerData[playerid][streetRobberies] == 1)
																					{
																						disableAchieve(playerid);
																						PlayerTextDrawShow(playerid, playerData[playerid][Achieve1]);
																						PlayerTextDrawShow(playerid, playerData[playerid][Achieve2]);
																						PlayerTextDrawShow(playerid, playerData[playerid][Achieve3]);
																						PlayerTextDrawShow(playerid, playerData[playerid][Achieve4]);

																						PlayerTextDrawSetString(playerid, playerData[playerid][Achieve3], "Pocket Chaser");
																						PlayerTextDrawSetString(playerid, playerData[playerid][Achieve4], "You robbed a player for the first time!");
																						PlayerPlaySound(playerid, 1185 ,0.0, 0.0, 0.0);

																						playerData[playerid][achieveTimer] = SetTimerEx("disableAchieve", 6000, false, "i", playerid);

																						playerGiveXP(playerid, 25);
																						playerData[playerid][playerScore] = playerData[playerid][playerScore] + 2;
																						SetPlayerScore(playerid, playerData[playerid][playerScore]);
																					}

																					if (playerData[playerid][streetRobberies] == 10)
																					{
																						disableAchieve(playerid);
																						PlayerTextDrawShow(playerid, playerData[playerid][Achieve1]);
																						PlayerTextDrawShow(playerid, playerData[playerid][Achieve2]);
																						PlayerTextDrawShow(playerid, playerData[playerid][Achieve3]);
																						PlayerTextDrawShow(playerid, playerData[playerid][Achieve4]);

																						PlayerTextDrawSetString(playerid, playerData[playerid][Achieve3], "Oliver Twist");
																						PlayerTextDrawSetString(playerid, playerData[playerid][Achieve4], "You stole from 10 players!");
																						PlayerPlaySound(playerid, 1185 ,0.0, 0.0, 0.0);

																						playerData[playerid][achieveTimer] = SetTimerEx("disableAchieve", 6000, false, "i", playerid);

																						playerGiveXP(playerid, 25);
																						playerData[playerid][playerScore] = playerData[playerid][playerScore] + 2;
																						SetPlayerScore(playerid, playerData[playerid][playerScore]);
																					}

																					if (playerData[playerid][streetRobberies] == 50)
																					{
																						disableAchieve(playerid);
																						PlayerTextDrawShow(playerid, playerData[playerid][Achieve1]);
																						PlayerTextDrawShow(playerid, playerData[playerid][Achieve2]);
																						PlayerTextDrawShow(playerid, playerData[playerid][Achieve3]);
																						PlayerTextDrawShow(playerid, playerData[playerid][Achieve4]);

																						PlayerTextDrawSetString(playerid, playerData[playerid][Achieve3], "Invisible");
																						PlayerTextDrawSetString(playerid, playerData[playerid][Achieve4], "You stole from 50 players, nice!");
																						PlayerPlaySound(playerid, 1185 ,0.0, 0.0, 0.0);

																						playerData[playerid][achieveTimer] = SetTimerEx("disableAchieve", 6000, false, "i", playerid);

																						playerGiveXP(playerid, 25);
																						playerData[playerid][playerScore] = playerData[playerid][playerScore] + 2;
																						SetPlayerScore(playerid, playerData[playerid][playerScore]);
																					}
																				}
																				case 3:
																				{
																					format(message, sizeof(message), "{E6BD1A}[CRIME] {FFFF00}You attempted to rob %s(%i) and failed!", playerData[otherPlayer][playerNamee], otherPlayer);
																					SendClientMessage(playerid, COLOR_WHITE, message);
																					format(message, sizeof(message), "{B7B7B7}[SERVER] {FFFF00}%s(%i) tried to rob you but failed!", playerData[playerid][playerNamee], playerid);
																					SendClientMessage(otherPlayer, COLOR_WHITE, message);
																				}
																			}
																		}
																		else
																		{
																			format(message, sizeof(message), "{E6BD1A}[CRIME] {FFFF00}You attempted to rob %s(%i) and failed!", playerData[otherPlayer][playerNamee], otherPlayer);
																			SendClientMessage(playerid, COLOR_WHITE, message);
																			format(message, sizeof(message), "{B7B7B7}[SERVER] {FFFF00}%s(%i) tried to rob you but failed due to your secure wallet!", playerData[playerid][playerNamee], playerid);
																			SendClientMessage(otherPlayer, COLOR_WHITE, message);
																		}

																		playerData[playerid][playerCanRob] = false;
																		playerData[playerid][reactivateRobStatus] = SetTimerEx("reactivateRob", 120000, false, "i", playerid);
																		givePlayerWanted(playerid, 6);
																		sendWantedMessage(playerid, 6);

																	}
																	else
																	{
																		SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFFFF}This player cannot afford to be robbed.");
																	}
																}
																else
																{
																	SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFFFF}You cannot do this whilst tied.");
																}
															}
															else
															{
																SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFFFF}You cannot do this whilst tazed.");
															}
														}
														else
														{
															SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFFFF}You cannot do this whilst cuffed.");
														}
													}
													else
													{
														SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFFFF}You cannot rob administrators who are on duty.");
													}
												}
												else
												{
													SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFFFF}You cannot rob people while you are in a vehicle.");
												}
											}
											else
											{
												SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFFFF}The player you're trying to rob is in a vehicle.");
											}
										}
										else
										{
											SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFFFF}You cannot rob players who are in jail.");
										}
									}
									else
									{
										SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFFFF}You cannot rob players while you are in jail.");
									}
								}
								else
								{
									SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFFFF}You are not close enough to that player.");
								}
							}
							else
							{
								SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFFFF}The player your trying to rob is not logged in.");
							}
						}
						else
						{
							SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFFFF}The player your trying to rob isn't connected.");
						}
					}
					else
					{
						SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFFFF}You need to wait before robbing another player.");
					}
				}
				else
				{
					SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFFFF}This command can only be used by civilians.");
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFFFF}You cannot rob players whilst in an event.");
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFFFF}AOD off please.");
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFFFF}You must be logged in to use commands.");
	}

	return 1;
}

COMMAND:rape(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
	    if(!playerData[playerid][playerAdminDuty])
		{
			if(!playerData[playerid][isInEvent] && !playerData[playerid][isInlms] && !playerData[playerid][isInCVR])
			{
				if(playerData[playerid][playerClass] == CLASS_CIVILIAN)
				{
					if(playerData[playerid][playerCanRape])
					{
						if(!playerData[playerid][playerIsCuffed])
						{
							if(!playerData[playerid][playerIsTazed])
							{
								if(!playerData[playerid][playerIsTied])
								{
									new otherPlayer = GetClosestPlayerToPlayer(playerid);

									new message[128];
									if(IsPlayerConnected(otherPlayer))
									{
										if(playerData[otherPlayer][playerLoggedIn])
										{
											new Float:lX, Float:lY, Float:lZ;
											GetPlayerPos(otherPlayer, lX, lY, lZ);
											if(IsPlayerInRangeOfPoint(playerid, 4.0, lX, lY, lZ))
											{
												if(playerData[playerid][playerJailTime] <= 0)
												{
													if(playerData[otherPlayer][playerJailTime] <= 0)
													{
														if(!IsPlayerInAnyVehicle(otherPlayer))
														{
															if(!IsPlayerInAnyVehicle(playerid))
															{
																if(!playerData[otherPlayer][playerAdminDuty])
																{
																	if(playerData[otherPlayer][playerButtPlug] == 0)
																	{
																		new determinator = random(4);
																		switch(determinator)
																		{
																			case 0, 1, 2:
																			{
																				new Float:oldHealth;
																				format(message, sizeof(message), "{E6BD1A}[CRIME] {FFFF00}You successfully raped %s(%i)!", playerData[otherPlayer][playerNamee], otherPlayer);
																				SendClientMessage(playerid, COLOR_WHITE, message);
																				format(message, sizeof(message), "{E6BD1A}[CRIME] {FFFF00}You were raped by %s(%i)!", playerData[playerid][playerNamee], playerid);
																				SendClientMessage(otherPlayer, COLOR_WHITE, message);
																				GetPlayerHealth(otherPlayer, oldHealth);
																				SetPlayerHealth(otherPlayer, (oldHealth - 25.0));
																				playerGiveXP(playerid, 10);
																				playerData[playerid][playerScore] = playerData[playerid][playerScore] + 1;
																				SetPlayerScore(playerid, playerData[playerid][playerScore]);

																				if(playerData[playerid][playerJob] == JOB_RAPIST)
																				{
																					new rapeChance = random(4);

																					switch (rapeChance)
																					{
																						case 0, 1:
																						{
																							// Infect the player with an STD
																							playerData[otherPlayer][rapedTimer] = SetTimerEx("raped", 3000, true, "i", otherPlayer);
																							SendClientMessage(otherPlayer, COLOR_WHITE, "{F78181}[STD] {FFFF00}You have contracted an STD.");
																							playerData[otherPlayer][hasSTD] = true;
																						}
																					}
																				}

																				playerData[playerid][streetRapes] = playerData[playerid][streetRapes] + 1;

																				if (playerData[playerid][streetRapes] == 1)
																				{
																					disableAchieve(playerid);
																					PlayerTextDrawShow(playerid, playerData[playerid][Achieve1]);
																					PlayerTextDrawShow(playerid, playerData[playerid][Achieve2]);
																					PlayerTextDrawShow(playerid, playerData[playerid][Achieve3]);
																					PlayerTextDrawShow(playerid, playerData[playerid][Achieve4]);

																					PlayerTextDrawSetString(playerid, playerData[playerid][Achieve3], "Devilishly Horny");
																					PlayerTextDrawSetString(playerid, playerData[playerid][Achieve4], "You raped a poor, innocent player.");
																					PlayerPlaySound(playerid, 1185 ,0.0, 0.0, 0.0);

																					playerData[playerid][achieveTimer] = SetTimerEx("disableAchieve", 6000, false, "i", playerid);

																					playerGiveXP(playerid, 25);
																					playerData[playerid][playerScore] = playerData[playerid][playerScore] + 2;
																					SetPlayerScore(playerid, playerData[playerid][playerScore]);
																				}

																				if (playerData[playerid][streetRapes] == 10)
																				{
																					disableAchieve(playerid);
																					PlayerTextDrawShow(playerid, playerData[playerid][Achieve1]);
																					PlayerTextDrawShow(playerid, playerData[playerid][Achieve2]);
																					PlayerTextDrawShow(playerid, playerData[playerid][Achieve3]);
																					PlayerTextDrawShow(playerid, playerData[playerid][Achieve4]);

																					PlayerTextDrawSetString(playerid, playerData[playerid][Achieve3], "Dildo Fanatic");
																					PlayerTextDrawSetString(playerid, playerData[playerid][Achieve4], "You raped 10 players.");
																					PlayerPlaySound(playerid, 1185 ,0.0, 0.0, 0.0);

																					playerData[playerid][achieveTimer] = SetTimerEx("disableAchieve", 6000, false, "i", playerid);

																					playerGiveXP(playerid, 25);
																					playerData[playerid][playerScore] = playerData[playerid][playerScore] + 2;
																					SetPlayerScore(playerid, playerData[playerid][playerScore]);
																				}

																				if (playerData[playerid][streetRobberies] == 50)
																				{
																					disableAchieve(playerid);
																					PlayerTextDrawShow(playerid, playerData[playerid][Achieve1]);
																					PlayerTextDrawShow(playerid, playerData[playerid][Achieve2]);
																					PlayerTextDrawShow(playerid, playerData[playerid][Achieve3]);
																					PlayerTextDrawShow(playerid, playerData[playerid][Achieve4]);

																					PlayerTextDrawSetString(playerid, playerData[playerid][Achieve3], "Dick Slap");
																					PlayerTextDrawSetString(playerid, playerData[playerid][Achieve4], "You raped 50 players.");
																					PlayerPlaySound(playerid, 1185 ,0.0, 0.0, 0.0);

																					playerData[playerid][achieveTimer] = SetTimerEx("disableAchieve", 6000, false, "i", playerid);

																					playerGiveXP(playerid, 25);
																					playerData[playerid][playerScore] = playerData[playerid][playerScore] + 2;
																					SetPlayerScore(playerid, playerData[playerid][playerScore]);
																				}
																			}
																			case 3:
																			{
																				format(message, sizeof(message), "{E6BD1A}[CRIME] {FFFF00}You attempted to rape %s(%i) and failed!", playerData[otherPlayer][playerNamee], otherPlayer);
																				SendClientMessage(playerid, COLOR_WHITE, message);
																				format(message, sizeof(message), "{B7B7B7}[SERVER] {FFFF00}%s(%i) tried to rape you but failed!", playerData[playerid][playerNamee], playerid);
																				SendClientMessage(otherPlayer, COLOR_WHITE, message);
																			}
																		}
																	}
																	else
																	{
																		format(message, sizeof(message), "{E6BD1A}[CRIME] {FFFF00}You attempted to rape %s(%i) and failed!", playerData[otherPlayer][playerNamee], otherPlayer);
																		SendClientMessage(playerid, COLOR_WHITE, message);
																		format(message, sizeof(message), "{B7B7B7}[SERVER] {FFFF00}%s(%i) tried to rape you but failed due to your buttplug!", playerData[playerid][playerNamee], playerid);
																		SendClientMessage(otherPlayer, COLOR_WHITE, message);
																	}

																	playerData[playerid][playerCanRape] = false;

																	if(playerData[playerid][playerJob] == JOB_RAPIST)
																	{
																		playerData[playerid][reactivateRapeStatus] = SetTimerEx("reactivateRape", 30000, false, "i", playerid);
																	}
																	else
																	{
																		playerData[playerid][reactivateRapeStatus] = SetTimerEx("reactivateRape", 120000, false, "i", playerid);
																	}

																	givePlayerWanted(playerid, 6);
																	sendWantedMessage(playerid, 6);

																}
																else
																{
																	SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot rape administrators who are on duty.");
																}
															}
															else
															{
																SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot rape people while you are in a vehicle.");
															}
														}
														else
														{
															SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}The player you're trying to rape is in a vehicle.");
														}
													}
													else
													{
														SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot rape players who are in jail.");
													}
												}
												else
												{
													SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot rape players while you are in jail.");
												}
											}
											else
											{
												SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You are not close to any players.");
											}
										}
										else
										{
											SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}The player your trying to rape is not logged in.");
										}
									}
									else
									{
										SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}The player your trying to rape isn't connected.");
									}
								}
								else
								{
									SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot do this whilst tied.");
								}
							}
							else
							{
								SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot do this whilst tazed.");
							}
						}
						else
						{
							SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot do this whilst cuffed.");
						}
					}
					else
					{
						SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You need to wait before raping another player.");
					}
				}
				else
				{
					SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}This command can only be used by civilians.");
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot rape players whilst in an event.");
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}AOD off please.");
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You must be logged in to use commands.");
	}

	return 1;
}

// COMMANDS FOR PLAYER JOBS


CMD:blowjob(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn]) // logged in
	{
		if(!playerData[playerid][isInEvent])
		{
			if(playerData[playerid][playerClass] == CLASS_CIVILIAN)
			{
				if(playerData[playerid][playerJob] == JOB_PROSTITUTE)
				{
					new otherPlayer;
					if(sscanf(params, "u", otherPlayer))
					{
						SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFF00}Usage: \"blowjob <playerid>\"");
					}
					else
					{
						if(otherPlayer != playerid)
						{
							if(IsPlayerConnected(otherPlayer)) // logged in
							{
								if(isPlayerInRangeOfPlayer(playerid, otherPlayer, 4.0))
								{
									// Invite the other user to buy a weapon
									playerData[otherPlayer][playerBJOffer] = playerData[playerid][playerNamee];

									// Send the invite
									new offer[200];
									format(offer, sizeof(offer), "{FE9A2E}[BLOWJOB OFFER] {FFFFFF}%s(%i) wishes to give you a blowjob for $800, nice - /acceptblowjob", playerData[playerid][playerNamee], playerid);
									SendClientMessage(otherPlayer, 0xFF0000FF, offer);

									new to[200];
									format(to, sizeof(to), "{FE9A2E}[OFFER SENT] {FFFFFF}You offered to give %s(%i) a blowjob!", playerData[otherPlayer][playerNamee], otherPlayer);
									SendClientMessage(playerid, 0xFF0000FF, to);
								}
								else
								{
									SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You're not close enough to that player.");
								}
							}
							else
							{
								// Offline
								SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}That player is not online.");
							}
						}
						else
						{
							SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot give a blowjob to yourself.");
						}
					}
				}
				else
				{
					SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}Only prostitutes can this command.");
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You must be a civilian to use this command.");
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot do this whilst in an event.");
		}
	}
	return 1;
}

COMMAND:acceptblowjob(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(!playerData[playerid][isInEvent])
		{
			if (playerData[playerid][playerBJOffer] == -1)
			{
				SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}There are no blowjob offers.");
			}
			else
			{
				new status = checkNameStatus(playerData[playerid][playerBJOffer]);
				if(status == -1)
				{
					// Prostitute offline
					SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}The prostitute is no longer available.");
				}
				else
				{
					// Check radius (a little larger this time)
					if(isPlayerInRangeOfPlayer(playerid, status, 2.0))
					{
						// Tell the prostitute the player accepted
						new accept[200];
						format(accept, sizeof(accept), "{FE9A2E}[OFFER ACCEPTED] {FFFFFF}%s(%i) has accepted your offer.", playerData[playerid][playerNamee], playerid);
						SendClientMessage(status, 0xFF0000FF, accept);

						SetPlayerHealth(playerid, 100);

						// Take player money
						playerTakeMoney(playerid, 800);
						playerGiveMoney(status, 800);

						// Give XP bonus
						playerGiveXP(status, 5);

						// Give Score
						playerData[status][playerScore] = playerData[status][playerScore] + 1;
						SetPlayerScore(status, playerData[status][playerScore]);

						// Blowjob animation
						ApplyAnimation(status, "BLOWJOBZ", "BJ_STAND_LOOP_W", 4.0, 1, 1, 1, 1, 0);
						playerData[status][playerUsingAnim] = true;
					}
					else
					{
						SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}The prostitute is no longer available.");
					}
				}
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot do this whilst in an event.");
		}
	}
	return 1;
}

CMD:sellgun(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn]) // logged in
	{
		if(!playerData[playerid][isInEvent])
		{
			if(playerData[playerid][playerClass] == CLASS_CIVILIAN)
			{
				if(playerData[playerid][playerJob] == JOB_WEAPONDEALER)
				{
					new otherPlayer;
					if(sscanf(params, "u", otherPlayer))
					{
						SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFF00}Usage: \"sellgun <playerid>\"");
					}
					else
					{
						if(otherPlayer != playerid)
						{
							if(IsPlayerConnected(otherPlayer)) // logged in
							{
								if(isPlayerInRangeOfPlayer(playerid, otherPlayer, 4.0))
								{
									if(playerData[otherPlayer][playerJailTime] < 1)
									{
										// Invite the other user to buy a weapon
										playerData[otherPlayer][playerGunOffer] = playerid;

										// Send the invite
										new offer[200];
										format(offer, sizeof(offer), "{FE9A2E}[WEAPON OFFER] {FFFFFF}%s(%i) wishes to sell you some weapons - /buygun", playerData[playerid][playerNamee], playerid);
										SendClientMessage(otherPlayer, 0xFF0000FF, offer);

										new to[200];
										format(to, sizeof(to), "{FE9A2E}[OFFER SENT] {FFFF00}You offered to sell weapons to %s(%i)", playerData[otherPlayer][playerNamee], otherPlayer);
										SendClientMessage(playerid, 0xFF0000FF, to);
									}
									else
									{
										SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[WEAPON DEALER] {FFFF00}That player is in jail and cannot buy weapons.");
									}
								}
								else
								{
									SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[WEAPON DEALER] {FFFF00}You're not close enough to that player.");
								}
							}
							else
							{
								// Offline
								SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}That player is not online.");
							}
						}
						else
						{
							SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot sell weapons to yourself.");
						}
					}
				}
				else
				{
					SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}Only weapon dealers can this command.");
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You must be a civilian to use this command.");
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot do this whilst in an event.");
		}
	}
	return 1;
}

COMMAND:buygun(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(!playerData[playerid][isInEvent])
		{
			if (playerData[playerid][playerJailTime] < 1)
			{
				if (playerData[playerid][playerGunOffer] == -1)
				{
					SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}There are no weapon offers.");
				}
				else
				{
					new dealerID = playerData[playerid][playerGunOffer];
					if (playerid != dealerID)
					{
						if(!IsPlayerConnected(dealerID)) // logged in
						{
							// Dealer offline
							SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}The weapon dealer is no longer available.");
						}
						else
						{
							// Check radius (a little larger this time)
							if(isPlayerInRangeOfPlayer(playerid, dealerID, 20.0))
							{
								// Tell the dealer the player accepted
								new accept[200];
								format(accept, sizeof(accept), "{FE9A2E}[OFFER ACCEPTED] {FFFFFF}%s(%i) has accepted your request and is browsing your items.", playerData[playerid][playerNamee], playerid);
								SendClientMessage(dealerID, 0xFF0000FF, accept);

								// Show dialog to the player
								playerData[playerid][playerGunDealer] = dealerID;
								ShowPlayerDialog(playerid, DIALOG_GUNDEAL, DIALOG_STYLE_LIST, "Weapon Dealer", "MP5 {D87C3E}$1,500{FFFFFF} \nCombat Shotgun {D87C3E}$3,000{FFFFFF} \nSawnoff Shotgun {D87C3E}$5,000{FFFFFF}\nDesert Eagle {D87C3E}$3,500{FFFFFF}", "Go", "Cancel");
							}
							else
							{
								SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}The weapon dealer is no longer in range.");
							}
						}
					}
					else
					{
						SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot buy your own weapons.");
					}
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot do this whilst jailed.");
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot do this whilst in an event.");
		}
	}
	return 1;
}

CMD:track(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn]) // logged in
	{
		if(playerData[playerid][playerClass] == CLASS_CIVILIAN)
		{
			if(playerData[playerid][playerJob] == JOB_HITMAN)
			{
				if(playerData[playerid][playerIsTracking])
				{
					// Disable tracker
					PlayerTextDrawHide(playerid, PlayerText:playerData[playerid][playerTracker]);
					playerData[playerid][playerIsTracking] = false;
					KillTimer(playerData[playerid][playerHitmanTrackerTimer]);
				}
				else
				{
					new otherPlayer;
					if(sscanf(params, "u", otherPlayer))
					{
						SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}Usage: \"track <playerid>\"");
					}
					else
					{
						if(otherPlayer != playerid)
						{
							if(IsPlayerConnected(otherPlayer)) // logged in
							{
								if(playerData[otherPlayer][playerHitValue] >= 1000)
								{
									playerData[playerid][playerHitmanTrackerTimer] = SetTimerEx("playerHitmanTracker", 1000, true, "ii", playerid, otherPlayer);
									playerData[playerid][playerIsTracking] = true;
									PlayerTextDrawShow(playerid, PlayerText:playerData[playerid][playerTracker]);
									SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[TRACKING] {FFFFFF}Tracker started.");
								}
								else
								{
									SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[TRACKING] {FFFF00}That player does not have a high enough hit value.");
								}
							}
							else
							{
								// Offline
								SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}That player is not online.");
							}
						}
						else
						{
							SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cant track yourself..");
						}
					}
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}Only hitmen can this command.");
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You must be a civilian to use this command.");
		}
	}
	return 1;
}

COMMAND:mech(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(!playerData[playerid][isInEvent])
		{
			if(playerData[playerid][playerClass] == CLASS_CIVILIAN)
			{
				if(playerData[playerid][playerJob] == JOB_MECHANIC)
				{
					if(IsPlayerInAnyVehicle(playerid))
					{
						ShowPlayerDialog(playerid, DIALOG_MECHANIC, DIALOG_STYLE_LIST, "Mechanic", "Repair Vehicle {D87C3E}$300{FFFFFF} \nAdd Nitro {D87C3E}$1,500{FFFFFF} \nRemove EMP {D87C3E}$2,000{FFFFFF} \nFlip Vehicle {D87C3E}$500{FFFFFF}", "Go", "Cancel");
					}
					else
					{
						SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You must be in a vehicle to use this command.");
					}
				}
				else
				{
					SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You are not a mechanic.");
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}Only civilians can use this command.");
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot do this whilst in an event.");
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You must be logged in to use commands.");
	}

	return 1;
}

COMMAND:kidnap(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(!playerData[playerid][isInEvent])
		{
			if(playerData[playerid][playerClass] == CLASS_CIVILIAN)
			{
				if(playerData[playerid][playerJob] == JOB_KIDNAPPER)
				{
					// Kidnap a victim >=)
					new otherPlayer, pKidnapped[250], lKidnapped[250];
					if(sscanf(params, "u", otherPlayer))
					{
						// Invalid command syntax
						SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFF00}Usage: \"kidnap <playerID>\"");
					}
					else
					{
						if(!playerData[playerid][playerIsTied])
						{
							if(playerid != otherPlayer)
							{
								if(IsPlayerConnected(otherPlayer))
								{
									if(playerData[otherPlayer][playerLoggedIn])
									{
										// Check if the player is in jail
										if (playerData[playerid][playerJailTime] == 0 && playerData[otherPlayer][playerJailTime] == 0)
										{
											if(isPlayerInRangeOfPlayer(playerid, otherPlayer, 4.0))
											{
												// If the player is not performing administrative duties
												if (!playerData[otherPlayer][playerAdminDuty])
												{
													// If OTHER player is in a vehicle
													if(!IsPlayerInAnyVehicle(otherPlayer))
													{
														// If PLAYER is NOT in a vehicle
														if(!IsPlayerInAnyVehicle(playerid))
														{
															if(playerData[otherPlayer][playerIsTied])
															{
																if(playerData[playerid][playerCanKidnap])
																{
																	if(IsValidVehicle(playerData[playerid][playerLastVehicleID]))
																	{
																		new FreeSlot = GetEmptySeat(playerData[playerid][playerLastVehicleID]);
																		if (FreeSlot != INVALID_SEAT_ID)
																		{
																			SetPlayerInterior(otherPlayer, 0);
																			SetPlayerVirtualWorld(otherPlayer, 0);

																			// Kidnap player
																			PutPlayerInVehicle(otherPlayer, playerData[playerid][playerLastVehicleID], FreeSlot);

																			format(pKidnapped, sizeof(pKidnapped), "{B7B7B7}[KIDNAP] {FFFF00}You have been kidnapped by %s(%i)", playerData[playerid][playerNamee], playerid);
																			SendClientMessage(otherPlayer, 0xFF0000FF, pKidnapped);

																			//Delete3DTextLabel(playerData[otherPlayer][kidnappedLabel]);
																			playerData[otherPlayer][kidnappedLabel] = Create3DTextLabel("Kidnapped", 0xFFDC2EFF, 30.0, 40.0, 50.0, 60.0, -1, 1);
																			Attach3DTextLabelToPlayer(playerData[otherPlayer][kidnappedLabel], otherPlayer, 0.0, 0.0, 0.4);

																			format(lKidnapped, sizeof(lKidnapped), "{B7B7B7}[KIDNAP] {FFFF00}You have kidnapped %s(%i)", playerData[otherPlayer][playerNamee], otherPlayer);
																			SendClientMessage(playerid, COLOR_WHITE, lKidnapped);

																			playerData[playerid][kidnapTimer] = SetTimerEx("reKidnap", 60000, false, "i", playerid);
																			playerData[playerid][playerCanKidnap] = false;

																			givePlayerWanted(playerid, 6);
																			sendWantedMessage(playerid, 6);
																			playerGiveXP(playerid, 10);

																			TogglePlayerControllable(otherPlayer, false);

																			playerData[playerid][playersKidnapped] = playerData[playerid][playersKidnapped] + 1;

																			if (playerData[playerid][playersKidnapped] == 1)
																			{
																				disableAchieve(playerid);
																				PlayerTextDrawShow(playerid, playerData[playerid][Achieve1]);
																				PlayerTextDrawShow(playerid, playerData[playerid][Achieve2]);
																				PlayerTextDrawShow(playerid, playerData[playerid][Achieve3]);
																				PlayerTextDrawShow(playerid, playerData[playerid][Achieve4]);

																				PlayerTextDrawSetString(playerid, playerData[playerid][Achieve3], "Get In My Van");
																				PlayerTextDrawSetString(playerid, playerData[playerid][Achieve4], "You kidnapped a player. Have fun!");
																				PlayerPlaySound(playerid, 1185 ,0.0, 0.0, 0.0);

																				playerData[playerid][achieveTimer] = SetTimerEx("disableAchieve", 6000, false, "i", playerid);

																				playerGiveXP(playerid, 25);
																				playerData[playerid][playerScore] = playerData[playerid][playerScore] + 2;
																				SetPlayerScore(playerid, playerData[playerid][playerScore]);
																			}

																			if (playerData[playerid][playersKidnapped] == 10)
																			{
																				disableAchieve(playerid);
																				PlayerTextDrawShow(playerid, playerData[playerid][Achieve1]);
																				PlayerTextDrawShow(playerid, playerData[playerid][Achieve2]);
																				PlayerTextDrawShow(playerid, playerData[playerid][Achieve3]);
																				PlayerTextDrawShow(playerid, playerData[playerid][Achieve4]);

																				PlayerTextDrawSetString(playerid, playerData[playerid][Achieve3], "I Need A Bigger Basement");
																				PlayerTextDrawSetString(playerid, playerData[playerid][Achieve4], "You kidnapped 10 players!");
																				PlayerPlaySound(playerid, 1185 ,0.0, 0.0, 0.0);

																				playerData[playerid][achieveTimer] = SetTimerEx("disableAchieve", 6000, false, "i", playerid);

																				playerGiveXP(playerid, 25);
																				playerData[playerid][playerScore] = playerData[playerid][playerScore] + 2;
																				SetPlayerScore(playerid, playerData[playerid][playerScore]);
																			}

																			if (playerData[playerid][playersKidnapped] == 50)
																			{
																				disableAchieve(playerid);
																				PlayerTextDrawShow(playerid, playerData[playerid][Achieve1]);
																				PlayerTextDrawShow(playerid, playerData[playerid][Achieve2]);
																				PlayerTextDrawShow(playerid, playerData[playerid][Achieve3]);
																				PlayerTextDrawShow(playerid, playerData[playerid][Achieve4]);

																				PlayerTextDrawSetString(playerid, playerData[playerid][Achieve3], "Want Some Candy?");
																				PlayerTextDrawSetString(playerid, playerData[playerid][Achieve4], "You kidnapped 50 players.");
																				PlayerPlaySound(playerid, 1185 ,0.0, 0.0, 0.0);

																				playerData[playerid][achieveTimer] = SetTimerEx("disableAchieve", 6000, false, "i", playerid);

																				playerGiveXP(playerid, 25);
																				playerData[playerid][playerScore] = playerData[playerid][playerScore] + 2;
																				SetPlayerScore(playerid, playerData[playerid][playerScore]);
																			}
																		}
																		else
																		{
																			// No car seats available
																			SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}There is no room in your vehicle to kidnap this player.");
																		}
																	}
																	else
																	{
																		SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You don't have a vehicle to put this player in.");
																	}
																}
																else
																{
																	// Player cannot kidnap
																	SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You must wait before kidnapping another victim..");
																}
															}
															else
															{
																// Player isn't tied
																SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You must tie your victim before you can kidnap them.");
															}
														}
														else
														{
															// Player is in vehicle
															SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot kidnap people while you are in a vehicle.");
														}
													}
													else
													{
														// Other player is in a vehicle
														SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}The player you're trying to kidnap is in a vehicle.");
													}
												}
												else
												{
													// Cannot kidnap an admin on duty
													SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}That player is currently performing admin duties and cannot be kidnapped!");
												}
											}
											else
											{
												// Not in range of player
												SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You are not close enough to that player.");
											}
										}
										else
										{
											// Player is in jail
											SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot kidnap people when they are jailed or when you are jailed.");
										}
									}
									else
									{
										// Cannot kidnap players who are not logged in.
										SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot kidnap players who are not logged in.");
									}
								}
								else
								{
									// Cannot kidnap players who are not connected.
									SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}That player is not connected.");
								}
							}
							else
							{
								// Cannot tie yourself
								SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot kidnap yourself.");
							}
						}
						else
						{
							SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot do this whilst tied.");
						}
					}
				}
				else
				{
					// Player is not a kidnapper
					SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}Only kidnappers can use this command.");
				}
			}
			else
			{
				// Player is not civilian
				SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}Only civilians can use this command.");
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot do this whilst in an event.");
		}
    }
    else
    {
        SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You must be logged in to use commands.");
    }
    return 1;
}

COMMAND:payransom(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if (playerData[playerid][playerIsTied])
		{
			if (playerData[playerid][playerRansomTo] == -1)
			{
				SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFF00}There are no ransom offers.");
			}
			else
			{
				if (playerData[playerid][playerMoney] >= playerData[playerid][playerRansomPrice])
				{
					new message[250];
					new ransomID = playerData[playerid][playerRansomTo];
					if (playerid != ransomID)
					{
						if(IsPlayerConnected(ransomID))
						{
							if(playerData[ransomID][playerJob] == JOB_KIDNAPPER) // offer gone
							{
								// Pay cash to ID
								playerGiveMoney(ransomID, playerData[playerid][playerRansomPrice]);
								playerTakeMoney(playerid, playerData[playerid][playerRansomPrice]);

								// Send message to cop
								format(message, sizeof(message), "{58D3F7}[RANSOM PAID] {FFFFFF}You received {FFDC2E}$%s {FFFFFF}from %s(%i)", FormatNumber(playerData[playerid][playerRansomPrice]), playerData[playerid][playerNamee], playerid);
								SendClientMessage(ransomID, COLOR_WHITE, message);
								playerGiveXP(ransomID, 5);

								playerData[playerid][playerRansomTo] = 0;
								playerData[playerid][playerRansomPrice] = 0;

								ClearAnimations(playerid);
								playerData[playerid][playerIsTied] = false;

								SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
								KillTimer(playerData[playerid][untieTimer]);
								TogglePlayerControllable(playerid, true);

								Delete3DTextLabel(playerData[playerid][kidnappedLabel]);

								SendClientMessage(playerid, COLOR_WHITE, "{58D3F7}[RANSOM PAID] {FFFF00}You have been released, run piggy!");
							}
							else
							{
								// Cop offline
								SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}The ransom offer is no longer available.");
							}
						}
						else
						{
							SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}The ransom offer is no longer available. (2)");
						}
					}
				}
				else
				{
					SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cant afford this offer.");
				}
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You aren't kidnapped.");
		}
	}

	return 1;
}

COMMAND:ransom(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
  	    if(playerData[playerid][playerClass] == CLASS_CIVILIAN)
  	    {
            // Command for ransom
            new otherPlayer, price, message[200];
            if(sscanf(params, "ui", otherPlayer, price))
            {
                // Invalid command syntax
                SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFF00}Usage: \"ransom <playerID> <price>\"");
            }
            else
            {
				if(IsPlayerConnected(otherPlayer))
				{
					if(playerData[otherPlayer][playerLoggedIn])
					{
						if(otherPlayer != playerid)
						{
							if (price > 1000 && price < 50000)
							{
								new kidnapperVID, kidnappedVID;

								kidnapperVID = GetPlayerVehicleID(playerid);
								kidnappedVID = GetPlayerVehicleID(otherPlayer);

								if (kidnapperVID == kidnappedVID)
								{
									if (playerData[otherPlayer][playerIsTied])
									{
										// Set-up some variables (reset on spawn)
										playerData[otherPlayer][playerRansomTo] = playerid;
										playerData[otherPlayer][playerRansomPrice] = price;

										format(message, sizeof(message), "{58D3F7}[RANSOM] {FFFFFF}%s(%i) requests you pay {FFDC2E}$%s {FFFFFF}for your safe release (/payransom)", playerData[playerid][playerNamee], playerid, FormatNumber(price));
										SendClientMessage(otherPlayer, COLOR_WHITE, message);

										SendClientMessage(playerid, COLOR_WHITE, "{58D3F7}[RANSOM] {FFFF00}Your ransom offer has been sent.");
									}
									else
									{
										SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}That player is not tied.");
									}
								}
								else
								{
									SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}That player is not in your vehicle.");
								}
							}
							else
							{
								SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}Ransom price must be between $1,000 and $50,000");
							}
						}
					}
					else
					{
						// Player is not logged in
						SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}This player is not logged in.");
					}
				}
				else
				{
					// Player is not online
					SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}This player is not online.");
				}
			}
        }
        else
        {
            // Player is not police
            SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}This command can only be used by civilians.");
        }
    }
    else
    {
        SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You must be logged in to use commands.");
    }

	return 1;
}

COMMAND:tie(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
	    if(!playerData[playerid][playerAdminDuty])
		{
			if(!playerData[playerid][isInEvent] && !playerData[playerid][isInlms] && !playerData[playerid][isInCVR])
			{
				if(playerData[playerid][playerClass] == CLASS_CIVILIAN)
				{
					// Tie a victim >=)
					new otherPlayer, tiedBy[24], Name[24], pTied[250], lTied[250];
					if(sscanf(params, "u", otherPlayer))
					{
						// Invalid command syntax
						SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFF00}Usage: \"tie <playerID>\"");
					}
					else
					{
						if(!playerData[playerid][playerIsCuffed])
						{
							if(!playerData[playerid][playerIsTazed])
							{
								if(!playerData[playerid][playerIsTied])
								{
									if(playerid != otherPlayer)
									{
										if(IsPlayerConnected(otherPlayer))
										{
											if(playerData[otherPlayer][playerLoggedIn])
											{
												// Check if the player is in jail
												if (playerData[playerid][playerJailTime] == 0 && playerData[otherPlayer][playerJailTime] == 0)
												{
													if(isPlayerInRangeOfPlayer(playerid, otherPlayer, 4.0))
													{
														// If the player is not performing administrative duties
														if (!playerData[otherPlayer][playerAdminDuty])
														{
															// If OTHER player is in a vehicle
															if(!IsPlayerInAnyVehicle(otherPlayer))
															{
																// If PLAYER is in a vehicle
																if(!IsPlayerInAnyVehicle(playerid))
																{
																	// Check if the player is already tazed
																	if(!playerData[otherPlayer][playerIsTied])
																	{
																		if (!playerData[otherPlayer][playerIsCuffed])
																		{
																			// Check if player has enough rope
																			if (playerData[playerid][playerRope] >= 1)
																			{
																				// Freeze the other player
																				SetPlayerSpecialAction(otherPlayer, SPECIAL_ACTION_CUFFED);

																				ClearAnimations(otherPlayer);

																				GetPlayerName(playerid, tiedBy, sizeof(Name));
																				GetPlayerName(otherPlayer, Name, sizeof(Name));

																				// Tie player
																				format(pTied, sizeof(pTied), "{B7B7B7}[TIED] {FFFF00}You have been tied by %s(%i)", tiedBy, playerid);
																				SendClientMessage(otherPlayer, 0xFF0000FF, pTied);

																				format(lTied, sizeof(lTied), "{B7B7B7}[TIED] {FFFF00}You have tied %s(%i)", Name, otherPlayer);
																				SendClientMessage(playerid, COLOR_WHITE, lTied);

																				// Set timer to expire and unfreeze player (60 seconds)
																				playerData[otherPlayer][untieTimer] = SetTimerEx("untie", 120000, false, "i", otherPlayer);

																				// Set the otherPlayer's isTied to 1
																				playerData[otherPlayer][playerIsTied] = true;

																				givePlayerWanted(playerid, 6);
																				sendWantedMessage(playerid, 6);
																				playerGiveXP(playerid, 5);

																				playerData[playerid][playerRope] = playerData[playerid][playerRope] - 1;
																			}
																			else
																			{
																				// Not enough rope
																				SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFF00}You don't have any rope.");
																			}
																		}
																		else
																		{
																			SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot tie this player.");
																		}
																	}
																	else
																	{
																		// The player is already tied
																		SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}That player is already tied.");
																	}
																}
																else
																{
																	// Player is in vehicle
																	SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot tie people while you are in a vehicle.");
																}
															}
															else
															{
																// Other player is in a vehicle
																SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}The player you're trying to tie is in a vehicle.");
															}
														}
														else
														{
															// Cannot tie an admin on duty
															SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}That player is currently performing admin duties and cannot be tied!");
														}
													}
													else
													{
														// Not in range of player
														SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You are not close enough to that player.");
													}
												}
												else
												{
													// Player is in jail
													SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot tie people when they are jailed or when you are jailed.");
												}
											}
											else
											{
												// Cannot tie players who are not logged in.
												SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot tie players who are not logged in.");
											}
										}
										else
										{
											// Cannot tie players who are not connected.
											SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}That player is not connected.");
										}
									}
									else
									{
										// Cannot tie yourself
										SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot tie yourself.");
									}
								}
								else
								{
									SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot do this whilst tied.");
								}
							}
							else
							{
								SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot do this whilst tazed.");
							}
						}
						else
						{
							SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot do this whilst cuffed.");
						}
					}
				}
				else
				{
					// Player is not civilian
					SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}Only civilians can use this command.");
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot do this whilst in an event.");
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}AOD off please.");
		}
    }
    else
    {
        SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You must be logged in to use commands.");
    }
    return 1;
}

COMMAND:untie(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(!playerData[playerid][isInEvent])
		{
			new otherID, otherName[24];

			if(sscanf(params, "u", otherID))
			{
				SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFF00}Usage: \"untie <playername/id>\"");
			}
			else
			{
				if(playerid != otherID)
				{
					if(IsPlayerConnected(otherID))
					{
						if(playerData[otherID][playerLoggedIn])
						{
							if(!IsPlayerInAnyVehicle(otherID))
							{
								if(playerData[otherID][playerIsTied])
								{
									if(isPlayerInRangeOfPlayer(playerid, otherID, 4.0))
									{
										if (!playerData[playerid][playerIsTied])
										{
											GetPlayerName(otherID, otherName, sizeof(otherName));
											new message[128], message2[128];
											format(message, sizeof(message), "{B7B7B7}[UN-TIED] {FFFF00}You have untied %s(%i)!", otherName, otherID);
											SendClientMessage(playerid, COLOR_WHITE, message);
											Delete3DTextLabel(playerData[playerid][kidnappedLabel]);

											format(message2, sizeof(message2), "{B7B7B7}[UN-TIED] {FFFF00}You have been untied by %s(%i)!", playerData[playerid][playerNamee], playerid);
											SendClientMessage(otherID, COLOR_WHITE, message2);

											playerData[otherID][playerIsTied] = false;

											SetPlayerSpecialAction(otherID, SPECIAL_ACTION_NONE);
											KillTimer(playerData[otherID][untieTimer]);

											TogglePlayerControllable(otherID, 1);
										}
										else
										{
											SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot do this whilst tied.");
										}
									}
									else
									{
										SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You are not close enough to that player.");
									}
								}
								else
								{
									SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}That player is not tied.");
								}
							}
							else
							{
								SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}That player is not logged in!");
							}
						}
						else
						{
							SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You are not close enough to that player.");
						}
					}
					else
					{
						SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}That player is not online!");
					}
				}
				else
				{
					// Cannot un-tie yourself
					SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot un-tie yourself.");
				}
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot do this whilst in an event.");
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You must be logged in to use commands.");
	}

	return 1;
}

// Courier job begin
COMMAND:courier(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(playerData[playerid][playerClass] == CLASS_CIVILIAN)
		{
			if(playerData[playerid][iscourier])
			{
				SendClientMessage(playerid, COLOR_WHITE, "{FFDC2E}[COURIER] {FFFF00}You're already on a mission. Type /cancelcourier to end the mission!");
			}
			else
			{
				new vehicleid;
				vehicleid = GetPlayerVehicleID(playerid);
				if(GetVehicleModel(vehicleid) == 593)
				{
					// Plane Courier
					ShowPlayerDialog(playerid, DIALOG_COURIER_START, DIALOG_STYLE_LIST, "Courier Mission", "Los Santos \nSan Fierro \nLas Venturas", "Go", "Cancel");
				}
				else if(GetVehicleModel(vehicleid) == 482)
				{
					// Van Courier
					//SetPlayerCheckpoint(playerid, -2521.4011, -618.5956, 132.5698, 10);
					playerData[playerid][playerLastCourierCP] = CreateDynamicRaceCP(1, -2521.4011, -618.5956, 132.5698, -2521.4011, -618.5956, 132.5698, 5, -1, -1, playerid, 100.0);
					SetPlayerMapIcon(playerid, MAP_ICON_COURIER_VAN, -2521.4011, -618.5956, 132.5698, 51, -1);
					SendClientMessage(playerid, COLOR_WHITE, "{FFDC2E}[COURIER] {FFFFFF}Pick-up the packages from the delievery HQ.");
					playerData[playerid][iscourier] = true;
					playerData[playerid][playerCourierLevel] = 3;

					//deliveryTD = TextDrawCreate(320.000000, 424.000000, "Pick-up ~g~boxes ~w~from ~y~delivery HQ");
					//TextDrawShowForPlayer(playerid, deliveryTD);
				}
				else
				{
					SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You must be inside a courier vehicle to start the courier mission.");
				}
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You must be a civilian to start courier missions.");
		}
	}
	return 1;
}

COMMAND:cancelcourier(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(playerData[playerid][playerClass] == CLASS_CIVILIAN)
		{
			if(playerData[playerid][iscourier])
			{
				// Cancel the job
				SendClientMessage(playerid, COLOR_WHITE, "{FFDC2E}[COURIER] {FFFF00}You cancelled the courier mission.");
				playerData[playerid][iscourier] = false;
				playerData[playerid][playerCourierLevel] = 0;
				RemovePlayerMapIcon(playerid, MAP_ICON_COURIER_VAN);
				DestroyDynamicRaceCP(playerData[playerid][playerLastCourierCP]);
				TextDrawHideForPlayer(playerid, TDCourier2);
				TextDrawHideForPlayer(playerid, TDCourier);
				KillTimer(playerData[playerid][courierTimer]);
				TogglePlayerControllable(playerid, 1);
				DisablePlayerCheckpoint(playerid);
				KillTimer(playerData[playerid][courierDistance]);
				PlayerTextDrawSetString(playerid, playerData[playerid][playerCourierDistanceTD], " ");
			}
			else
			{
				SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You're not on a mission.");
			}
		}
	}
	return 1;
}

// Drug Dealer commands
COMMAND:sellweed(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(!playerData[playerid][isInEvent])
		{
			if(playerData[playerid][playerClass] == CLASS_CIVILIAN)
			{
				if(playerData[playerid][playerJob] == JOB_DRUGDEALER)
				{
					new otherID, amount;

					if(sscanf(params, "ud", otherID, amount))
					{
						SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFF00}Usage: \"sellweed <playername/id> <value>\"");
					}
					else
					{
						if(amount < 1 || amount > 100 || !amount)
						{
							SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFF00}Please insert 1 - 100.");
							return 1;
						}
						if(playerid != otherID)
						{
							if(IsPlayerConnected(otherID))
							{
								if(playerData[otherID][playerLoggedIn])
								{
									if(isPlayerInRangeOfPlayer(playerid, otherID, 12.0))
									{
										if(IsPlayerInAnyVehicle(playerid))
										{
											new checkCar = GetPlayerVehicleID(playerid);
											if(GetVehicleModel(checkCar) == 423)
											{
												new takes = amount * 500;
												if (playerData[playerid][playerMoney] >= takes)
												{
													// Sell them the weed
													playerData[otherID][playerWeed] = playerData[otherID][playerWeed] + amount;

													// Take player money
													playerTakeMoney(playerid, takes);

													// Give XP bonus
													playerGiveXP(playerid, 5 * amount);

													new accept[200], forplayer[200];
													format(accept, sizeof(accept), "{FE9A2E}[WEED] {FFFF00}You sold drugs to %s(%i).", playerData[playerid][playerNamee], playerid);
													SendClientMessage(playerid, 0xFF0000FF, accept);

													format(forplayer, sizeof(forplayer), "{FE9A2E}[WEED] {FFFF00}You received drugs from %s(%i). /useweed to restore health.", playerData[playerid][playerNamee], playerid);
													SendClientMessage(otherID, 0xFF0000FF, forplayer);
												}
												else
												{
													SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You don't have enough money to purchase stock.");
												}
											}
											else
											{
												SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You must be in an ice cream truck to sell weed.");
											}
										}
										else
										{
											SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You must be in an ice cream truck to sell weed.");
										}
									}
									else
									{
										SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You're not close enough to that player.");
									}
								}
								else
								{
									SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}That player is not logged in.");
								}
							}
							else
							{
								SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}That player is not connected.");
							}
						}
						else
						{
							SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot sell weed to yourself.");
						}
					}
				}
				else
				{
					SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You must be a drug dealer to use this command.");
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}Only civilians can use this command.");
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot do this whilst in an event.");
		}
	}
	return 1;
}

COMMAND:useweed(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(!playerData[playerid][isInEvent] && !playerData[playerid][isInlms] && !playerData[playerid][isInCVR])
		{
			if(playerData[playerid][playerClass] == CLASS_CIVILIAN)
			{
				if (playerData[playerid][playerWeed] > 0)
				{
					new Float:health;
					GetPlayerHealth(playerid, health);

					if (health < 80)
					{
						if(!playerData[playerid][canWeed])
					    {
					        SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFF00}Wait before using another weed ROFL, are you gonna die?.");
					        return 1;
					    }
						// Add 20 health to the player
						SetPlayerHealth(playerid, health + 20);

						// Take 1 weed
						playerData[playerid][playerWeed] = playerData[playerid][playerWeed] - 1;

						// Info
						new info[200];
						format(info, sizeof(info), "{FE9A2E}[WEED] {FFFF00}You smoked some weed. Weed Remaining: %i", playerData[playerid][playerWeed]);
						SendClientMessage(playerid, 0xFF0000FF, info);

						Delete3DTextLabel(playerData[playerid][weedLabel]);
						playerData[playerid][canWeed] = false;
						playerData[playerid][weedLabel] = Create3DTextLabel("USED WEED", 0xFFDC2EFF, 30.0, 40.0, 50.0, 40.0, 0);
						Attach3DTextLabelToPlayer(playerData[playerid][weedLabel], playerid, 0.0, 0.0, 0.4);
						SetTimerEx("weedExpire", 3000, 0, "i", playerid);
					}
					else
					{
						SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}This command can only be used if you have less than 80 percent health.");
					}
				}
				else
				{
					SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You have no weed left.");
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}Only civilians can use this command.");
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot do this whilst in an event.");
		}
	}
	return 1;
}

COMMAND:cure(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(!playerData[playerid][isInEvent])
		{
			if(playerData[playerid][playerClass] == CLASS_MEDIC)
			{
				new otherID, price;

				if(sscanf(params, "ui", otherID, price))
				{
					SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFF00}Usage: \"cure <playername/id> <price>\"");
				}
				else
				{
					if(playerid != otherID)
					{
						if(IsPlayerConnected(otherID))
						{
							if(playerData[otherID][playerLoggedIn])
							{
								if(!IsPlayerInAnyVehicle(otherID))
								{
									if(isPlayerInRangeOfPlayer(playerid, otherID, 4.0))
									{
										if (price >= 500 && price <= 5000)
										{
											if (playerData[playerid][canCure])
											{
												if(playerData[otherID][hasSTD])
												{
													playerData[otherID][playerCureOffer] = playerid;
													playerData[otherID][playerCurePrice] = price;

													// Send the invite
													new offer[200];
													format(offer, sizeof(offer), "{FE9A2E}[MEDIC OFFER] {FFFFFF}%s(%i) wishes to cure you for {FFDC2E}%s {FFFFFF}- /acceptcure", playerData[playerid][playerNamee], playerid, FormatNumber(price));
													SendClientMessage(otherID, 0xFF0000FF, offer);

													new to[200];
													format(to, sizeof(to), "{FE9A2E}[OFFER SENT] {FFFF00}You offered to cure %s(%i) for {FFDC2E}$%s", playerData[otherID][playerNamee], otherID, FormatNumber(price));
													SendClientMessage(playerid, 0xFF0000FF, to);
												}
												else
												{
													SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}That player doesn't need curing.");
												}
											}
											else
											{
												SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}Please wait before curing another player.");
											}
										}
										else
										{
											SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}The price must be between $500 and $5000.");
										}
									}
									else
									{
										SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You're not close enough to that player.");
									}
								}
								else
								{
									SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}That player is in a vehicle.");
								}
							}
							else
							{
								SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}That player is not logged in.");
							}
						}
						else
						{
							SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}That player is not connected.");
						}
					}
					else
					{
						SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot cure yourself.");
					}
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}Only medics can use this command.");
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot do this whilst in an event.");
		}
	}
	return 1;
}


COMMAND:heal(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(!playerData[playerid][isInEvent])
		{
			if(playerData[playerid][playerClass] == CLASS_MEDIC)
			{
				new otherID, price;

				if(sscanf(params, "ui", otherID, price))
				{
					SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFF00}Usage: \"heal <playername/id> <price>\"");
				}
				else
				{
					if(playerid != otherID)
					{
						if(IsPlayerConnected(otherID))
						{
							if(playerData[otherID][playerLoggedIn])
							{
								if(!IsPlayerInAnyVehicle(otherID))
								{
									if(isPlayerInRangeOfPlayer(playerid, otherID, 4.0))
									{
										if (price >= 500 && price <= 5000)
										{
											new Float:health;
											GetPlayerHealth(otherID, health);

											if (playerData[playerid][canHeal])
											{
												if(health < 100)
												{
													playerData[otherID][playerHealOffer] = playerid;
													playerData[otherID][playerHealPrice] = price;

													// Send the invite
													new offer[200];
													format(offer, sizeof(offer), "{FE9A2E}[MEDIC OFFER] {FFFFFF}%s(%i) wishes to heal you for {FFDC2E}%s {FFFFFF}- /acceptheal", playerData[playerid][playerNamee], playerid, FormatNumber(price));
													SendClientMessage(otherID, 0xFF0000FF, offer);

													new to[200];
													format(to, sizeof(to), "{FE9A2E}[OFFER SENT] {FFFF00}You offered to heal %s(%i) for {FFDC2E}$%s", playerData[otherID][playerNamee], otherID, FormatNumber(price));
													SendClientMessage(playerid, 0xFF0000FF, to);
												}
												else
												{
													SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}That player doesn't need healing.");
												}
											}
											else
											{
												SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}Please wait before healing another player.");
											}
										}
										else
										{
											SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}The price must be between $500 and $5000.");
										}
									}
									else
									{
										SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You're not close enough to that player.");
									}
								}
								else
								{
									SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}That player is in a vehicle.");
								}
							}
							else
							{
								SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}That player is not logged in.");
							}
						}
						else
						{
							SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}That player is not connected.");
						}
					}
					else
					{
						SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot heal yourself.");
					}
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}Only medics can use this command.");
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot do this whilst in an event.");
		}
	}
	return 1;
}

COMMAND:acceptcure(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(!playerData[playerid][isInEvent])
		{
			if (playerData[playerid][playerJailTime] < 1)
			{
				if (playerData[playerid][playerCureOffer] == -1)
				{
					SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}There are no medic offers.");
				}
				else
				{
					new dealerID = playerData[playerid][playerCureOffer];
					if (playerid != dealerID)
					{
						if(!IsPlayerConnected(dealerID)) // logged in
						{
							// Dealer offline
							SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}The medic is no longer available.");
						}
						else
						{
							// Check radius (a little larger this time)
							if(isPlayerInRangeOfPlayer(playerid, dealerID, 20.0))
							{
								if (playerData[playerid][playerMoney] >= playerData[playerid][playerCurePrice])
								{
									// Tell the dealer the player accepted
									new accept[200];
									format(accept, sizeof(accept), "{FE9A2E}[OFFER ACCEPTED] {FFFFFF}%s(%i) has accepted your request and has been cured for {FFDC2E}$%s", playerData[playerid][playerNamee], playerid, FormatNumber(playerData[playerid][playerCurePrice]));
									SendClientMessage(dealerID, 0xFF0000FF, accept);

									playerTakeMoney(playerid, playerData[playerid][playerCurePrice]);
									playerGiveMoney(dealerID, playerData[playerid][playerCurePrice]);
									playerGiveXP(dealerID, 5);

									playerData[playerid][hasSTD] = false;
									KillTimer(playerData[playerid][rapedTimer]);

									SendClientMessage(playerid, COLOR_WHITE, "{FE9A2E}[OFFER ACCEPTED] {FFFFFF}You are cured.");
								}
								else
								{
									SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot afford this.");
								}
							}
							else
							{
								SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}The medic is no longer in range.");
							}
						}
					}
					else
					{
						SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot cure yourself.");
					}
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot do this whilst jailed.");
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot do this whilst in an event.");
		}
	}
	return 1;
}

COMMAND:acceptheal(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(!playerData[playerid][isInEvent])
		{
			if (playerData[playerid][playerJailTime] < 1)
			{
				if (playerData[playerid][playerHealOffer] == -1)
				{
					SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}There are no medic offers.");
				}
				else
				{
					new dealerID = playerData[playerid][playerHealOffer];
					if (playerid != dealerID)
					{
						if(!IsPlayerConnected(dealerID)) // logged in
						{
							// Dealer offline
							SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}The medic is no longer available.");
						}
						else
						{
							// Check radius (a little larger this time)
							if(isPlayerInRangeOfPlayer(playerid, dealerID, 20.0))
							{
								if (playerData[playerid][playerMoney] >= playerData[playerid][playerHealPrice])
								{
									// Tell the dealer the player accepted
									new accept[200];
									format(accept, sizeof(accept), "{FE9A2E}[OFFER ACCEPTED] {FFFFFF}%s(%i) has accepted your request and has been healed for {FFDC2E}$%s", playerData[playerid][playerNamee], playerid, FormatNumber(playerData[playerid][playerHealPrice]));
									SendClientMessage(dealerID, 0xFF0000FF, accept);

									playerTakeMoney(playerid, playerData[playerid][playerHealPrice]);
									playerGiveMoney(dealerID, playerData[playerid][playerHealPrice]);
									playerGiveXP(dealerID, 5);

									SetPlayerHealth(playerid, 100.0);

									SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You were healed.");
								}
								else
								{
									SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot afford this.");
								}
							}
							else
							{
								SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}The medic is no longer in range.");
							}
						}
					}
					else
					{
						SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot heal yourself.");
					}
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot do this whilst jailed.");
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot do this whilst in an event.");
		}
	}
	return 1;
}

// End job commands

COMMAND:placehit(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(playerData[playerid][playerClass] == CLASS_CIVILIAN)
		{
			new otherPlayer, hitAmount, message[300];
			if(sscanf(params, "ui", otherPlayer, hitAmount))
			{
				SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFF00}Usage: \"placehit <playerID> <amount>\"");
			}
			else
			{
				if(playerid != otherPlayer)
				{
					if(IsPlayerConnected(otherPlayer))
					{
						if(playerData[otherPlayer][playerLoggedIn])
						{
							if(playerData[playerid][playerJob] != JOB_HITMAN)
							{
								if(hitAmount > 999)
								{
									if (playerData[playerid][playerMoney] >= hitAmount)
									{
										if(playerData[otherPlayer][playerHitValue] > 0)
										{
											playerData[otherPlayer][playerHitValue] = playerData[otherPlayer][playerHitValue] + hitAmount;
										}
										else
										{
											playerData[otherPlayer][playerHitValue] = hitAmount;
										}

										format(message, sizeof(message), "{FFDC2E}[CONTRACT] {FFFFFF}%s(%i) has placed a contract on %s(%i) for {FFDC2E}$%s{FFFFFF}! Type {FFDC2E}/hitlist{FFFFFF} to select your prey.", playerData[playerid][playerNamee], playerid, playerData[otherPlayer][playerNamee], otherPlayer, FormatNumber(hitAmount));
										SendClientMessageToAll(COLOR_WHITE, message);

										playerTakeMoney(playerid, hitAmount);
									}
									else
									{
										SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You don't have enough money to place a hit of that size.");
									}
								}
								else
								{
									SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You need to place at least $1,000 on the players head.");
								}
							}
							else
							{
								SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot place hits when you're a hitman.");
							}
						}
						else
						{
							SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot place hits on those who are not logged in.");
						}
					}
					else
					{
						SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}That player is not connected.");
					}
				}
				else
				{
					SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot place a hit upon yourself.");
				}
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}Only civilians can use this command.");
		}
    }
    else
    {
        SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You must be logged in to use commands.");
    }
    return 1;
}


// VIP Commands
COMMAND:vipcolor(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(playerData[playerid][playerVIPLevel] >= 1)
		{
			if (playerData[playerid][vipColour])
			{
				// Disable Colour
				playerData[playerid][vipColour] = false;
				SendClientMessage(playerid, COLOR_WHITE, "{FE9A2E}[VIP] {FFFF00}Your VIP name colour has been disabled.");
			}
			else
			{
				// Enable Colour
				playerData[playerid][vipColour] = true;
				SendClientMessage(playerid, COLOR_WHITE, "{FE9A2E}[VIP] {FFFF00}Your VIP name colour has been enabled.");
			}

			newPlayerColour(playerid);
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}This command can only be used by VIPs.");
		}
	}

	return 1;
}

COMMAND:vipskin(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(playerData[playerid][playerVIPLevel] >= 2)
		{
			new skinID;

			if(sscanf(params, "i", skinID))
			{
				SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}Usage: \"vipskin <skin_id>\"");
			}
			else
			{
				if(skinID < 1 || skinID > 311)
				{
					return SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFF00}Skin ID should be 1-311");
				}
				else
				{
					new message[128];
					SetPlayerSkin(playerid, skinID);
					format(message, sizeof(message), "{FE9A2E}[VIP] {FFFF00}Your custom skin has been set.");
					SendClientMessage(playerid, COLOR_WHITE, message);
					playerData[playerid][playerCustomSkin] = skinID;
					
					SetTimerEx("checkDriveB", 2000, false, "d", playerid);
				}
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}This command can only be used by Standard VIP members.");
		}
	}

	return 1;
}

COMMAND:vcolor(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(playerData[playerid][playerVIPLevel] >= 1)
		{
			if (IsPlayerInAnyVehicle(playerid))
			{
				new
					colour1,
					colour2
				;

				if(sscanf(params, "ii", colour1, colour2))
				{
					SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFF00}Usage: \"vcolour <colour 1> <colour 2>\"");
				}
				else
				{
					if (colour1 >= 0 && colour1 <= 255 && colour2 >= 0 && colour2 <= 255)
					{
						ChangeVehicleColor(GetPlayerVehicleID(playerid), colour1, colour2);
						SendClientMessage(playerid, COLOR_WHITE, "{FE9A2E}[VIP] {FFFF00}Vehicle colour changed.");
					}
					else
					{
						SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFF00}Colour ID should be between 0 and 255.");
					}
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You must be in a vehicle to use this command.");
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}This command can only be used by VIPs.");
		}
	}

	return 1;
}

COMMAND:vsay(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(playerData[playerid][playerVIPLevel] >= 1)
		{
			new message[100];

			if(sscanf(params, "s[100]", message))
			{
				SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFF00}Usage: \"vsay <message>\"");
			}
			else
			{
				format(message, sizeof(message), "{58D3F7}(VIP) %s: {FFFF00}%s", playerData[playerid][playerNamee], message);
				SendClientMessageToAll(COLOR_WHITE, message);
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}This command can only be used by VIPs.");
		}
	}

	return 1;
}

COMMAND:psay(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(playerData[playerid][playerVIPLevel] >= 0)
		{
			new message[100];

			if(sscanf(params, "s[100]", message))
			{
				SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFF00}Usage: \"psay <message>\"");
			}
			else
			{
				format(message, sizeof(message), "{F7FF00}(Member){00FFEF}%s: {CD00FF}%s", playerData[playerid][playerNamee], message);
				SendClientMessageToAll(COLOR_WHITE, message);
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}This command can only be used by VIPs.");
		}
	}

	return 1;
}	

COMMAND:vipweapon(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(playerData[playerid][playerVIPLevel] >= 2)
		{
			// Select a spawn weapon
			ShowPlayerDialog(playerid, DIALOG_VIPGUN, DIALOG_STYLE_LIST, "VIP Spawn Weapon", "Deagle \nM4 \nSniper Rifle \nSawnoff Shotgun \nChainsaw \nMP5 \nCombat Shotgun \nMicro SMG", "Go", "Cancel");
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}This command can only be used by VIPs.");
		}
	}

	return 1;
}

// COMMAND:exitvipstore(playerid, params[])
// {
	// if(playerData[playerid][playerLoggedIn])
	// {
  	    // if(playerData[playerid][playerVIPLevel] == 3)
  	    // {
			// if(GetPlayerInterior(playerid) == 0)
			// {
				// playerData[playerid][playerCheckpointTime] = GetTickCount();

				// SetPlayerPos(playerid, -1493.1566, 920.1319, 7.1875);
				// SetPlayerInterior(playerid, 0);
				// SetPlayerVirtualWorld(playerid, 0);
			// }
			// else
			// {
				// SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFFFF}You are not inside the V.I.P Store.");
			// }
		// }
		// else
		// {
			// return 0;
		// }
	// }
	// else
	// {
		// SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFFFF}You must be logged in to use commands.");
	// }

	// return 1;
// }

// COMMAND:exitstore(playerid, params[])
// {
	// if(playerData[playerid][playerLoggedIn])
	// {
  	    // if(playerData[playerid][playerVIPLevel] == 3)
  	    // {
			// if(GetPlayerInterior(playerid) == 0)
			// {
				// playerData[playerid][playerCheckpointTime] = GetTickCount();

				// SetPlayerPos(playerid, -1494.9318, 920.0157, 7.1875);
				// SetPlayerInterior(playerid, 0);
				// SetPlayerVirtualWorld(playerid, 0);
			// }
			// else
			// {
				// SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFFFF}You are not inside the V.I.P Store.");
			// }
		// }
		// else
		// {
			// return 0;
		// }
	// }
	// else
	// {
		// SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFFFF}You must be logged in to use commands.");
	// }

	// return 1;
// }

COMMAND:hitmarker(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(playerData[playerid][playerHitmarker])
		{
			playerData[playerid][playerHitmarker] = false;
			SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFF00}You have disabled the hitmarker.");
		}
		else
		{
			playerData[playerid][playerHitmarker] = true;
			SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFF00}You have enabled the hitmarker.");
		}
	}
	return 1;
}
	
COMMAND:buystore(playerid, params[])
{
	new x = -1, total = 0, maxstore = 0;
	if(playerData[playerid][actualID] == -1)
	{
		SendClientMessage(playerid, -1, "Relog please!");
		return 1;
	}
	for(new i = 0; i < MAX_ROB_CHECKPOINT; i++)
	{
		if(IsPlayerInRangeOfPoint(playerid, 2.0, checkpointData[i][enterpointLoc][0], checkpointData[i][enterpointLoc][1], checkpointData[i][enterpointLoc][2]))
		{
			x = i;
		}
		if(checkpointData[i][storeOwner] == playerData[playerid][actualID])
			total++;
	}
	if(x == -1)
	{
		SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFF00}You must be near store checkpoint to buy store.");
	}
	else
	{
		switch(playerData[playerid][playerVIPLevel])
		{
			case 3:
				maxstore = 2;
			default:
				maxstore = 1;
		}
		if(total >= maxstore)
		{
			SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFF00}You can't buy more stores.");
		}
		else
		{
			if(playerData[playerid][playerMoney] < checkpointData[x][storePrice])
			{
				SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFF00}Not enough money to buy this store.");
			}
			else
			{
				if(checkpointData[x][storeOwner] != -1)
				{
					SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFF00}You can't buy this store, this store already owned.");
				}
				else
				{
					playerTakeMoney(playerid, checkpointData[x][storePrice]);
					new fmt[256], owner[20];
					format(fmt, 256, "storeowner/%d.owner", x);
					if(fexist(fmt))
						fremove(fmt);

					format(owner, 20, "%d", playerData[playerid][actualID]);
					new File:file = fopen(fmt, io_write);
					fwrite(file, owner);
					fclose(file);

					format(fmt, 256, "storeowner/%d.money", x);
					if(fexist(fmt))
						fremove(fmt);
					file = fopen(fmt, io_write);
					fwrite(file, "0");
					fclose(file);
					format(fmt, 256, "%s\nOwner: %s", checkpointData[x][storeName], playerData[playerid][playerNamee]);
					Update3DTextLabelText(checkpointLabel[x][0][1], COLOR_WHITE, fmt);
					checkpointData[x][storeOwner] = playerData[playerid][actualID];
					checkpointData[x][storeMoney] = 0;
					format(fmt, 256, "{B7B7B7}[SERVER] {FFFFFF}You bought %s for {FFDC2E}$%s{FFFFFF} - use /mystores to manage your stores", checkpointData[x][storeName], FormatNumber(checkpointData[x][storePrice]));
					SendClientMessage(playerid, -1, fmt);
				}
			}
		}
	}
	return 1;
}

COMMAND:mystores(playerid, params[])
{
	new stores[10] = {-1, ...}, x = 0;
	for(new i = 0; i < MAX_ROB_CHECKPOINT; i++)
	{
		if(checkpointData[i][storeOwner] == playerData[playerid][actualID])
		{
			stores[x] = i;
			x++;
		}
	}
	if(stores[0] == -1)
	{
		SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFF00}You don't own any stores.");
	}
	else
	{
		new fmt[512];
		for(new i = 0; i < 10; i++)
		{
			if(stores[i] != -1)
			{
				format(fmt, 512, "%s%s - {FFFF00}$%s{FFFFFF}\n", fmt, checkpointData[stores[i]][storeName], FormatNumber(checkpointData[stores[i]][storeMoney]));
			}
		}
		ShowPlayerDialog(playerid, DIALOG_MYSTORES, DIALOG_STYLE_LIST, "My Stores", fmt, "Options", "Close");
	}
	return 1;
}

COMMAND:savenpc(playerid, params[])
{
	new skin, fmt[512], Float:x, Float:y, Float:z, Float:a;
	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, a);
	if(!sscanf(params, "d", skin))
	{
		for(new i = 0; i < MAX_ROB_CHECKPOINT; i++)
		{
			if(IsPlayerInRangeOfPoint(playerid, 20.0, checkpointData[i][robpointLoc][0], checkpointData[i][robpointLoc][1], checkpointData[i][robpointLoc][2]))
			{
				format(fmt, 512, "%f, %f, %f, %f, %f, %f, %f, %d, %d", checkpointData[i][robpointLoc][0], checkpointData[i][robpointLoc][1], checkpointData[i][robpointLoc][2], x, y, z, a, skin, checkpointData[i][virtualWorld]);
				writeInLog("savedactor.html", fmt);
				SetActorVirtualWorld(CreateActor(skin, x, y, z, a), checkpointData[i][virtualWorld]);
				SendClientMessage(playerid, -1, "Saved");
				return 1;
			}
		}
	}
	return 1;
}

COMMAND:gotopos(playerid, params[])
{
	new i = strval(params);
	SetPlayerPos(playerid, checkpointData[i][enterpointLoc][0], checkpointData[i][enterpointLoc][1], checkpointData[i][enterpointLoc][2]);
	SetPlayerInterior(playerid, 0);
	SetPlayerVirtualWorld(playerid, 0);
	return 1;
}

