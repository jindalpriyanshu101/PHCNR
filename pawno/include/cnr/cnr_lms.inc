new
	Iterator:lmsObject<MAX_LMSBOMBS>;
new Float:lmsCords[MAX_LMSBOMBS][3] = {
	{1506.1285,-1069.4294,181.2031},
	{1495.7059,-1059.8348,181.2031},
{1495.6766,-1064.7438,181.2031},
{1495.6450,-1069.9337,181.2031},
{1495.6123,-1075.3596,181.2031},
{1495.5784,-1080.8832,181.2031},
{1495.5391,-1087.4126,181.2031},
{1495.4948,-1094.5554,181.2031},
{1495.4613,-1099.7952,181.2031},
{1499.7562,-1103.3010,181.2031},
{1499.8478,-1098.7799,181.2031},
{1500.0166,-1094.1243,181.2031},
{1499.9209,-1087.9718,181.2031},
{1500.2865,-1082.7872,181.2031},
{1500.6884,-1077.0880,181.2031},
{1500.0989,-1068.3831,181.2031},
{1500.5653,-1061.7598,181.2031},
{1504.5339,-1059.8457,181.2031},
{1505.5768,-1063.5515,181.2031},
{1506.0712,-1071.3649,181.2031},
{1505.7716,-1074.0349,181.2031},
{1506.3771,-1077.0033,181.2031},
{1506.8475,-1081.4792,181.2031},
{1506.4617,-1086.3590,181.2031},
{1506.1233,-1090.6617,181.2031}, 
{1506.3118,-1095.6550,181.2031}, 
{1505.9253,-1100.5640,181.2031},
{1508.6630,-1102.1461,181.2031}, 
{1509.2245,-1099.8384,181.2031}, 
{1508.8071,-1095.5762,181.2031}, 
{1508.5352,-1090.8013,181.2031}, 
{1509.0074,-1085.7910,181.2031},
{1509.0426,-1082.3765,181.2031},
{1509.1879,-1077.9082,181.2031},
{1508.9181,-1074.0870,181.2031},
{1508.9614,-1069.8215,181.2031},
{1509.0021,-1065.8612,181.2031},
{1509.0364,-1062.5718,181.2031},
{1509.0696,-1059.3472,181.2031},
{1512.3983,-1059.8833,181.2031},
{1512.5815,-1062.0239,181.2031},
{1512.8215,-1064.8378,181.2031},
{1513.0616,-1067.6522,181.2031},
{1513.3142,-1070.6118,181.2031},
{1513.5822,-1073.7467,181.2031},
{1513.8328,-1076.6721,181.2031},
{1514.0884,-1079.6605,181.2031},
{1514.3429,-1082.6431,181.2031},
{1513.8512,-1085.7052,181.2031},
{1512.9275,-1088.2823,181.2031}, 
{1511.9915,-1091.6812,181.2031},
{1513.0765,-1094.3112,181.2031},
{1513.3645,-1097.6604,181.2031},
{1513.6282,-1100.7307,181.2031},
{1513.8704,-1103.5485,181.2031},
{1519.0703,-1101.4720,181.2031},
{1519.1686,-1098.6224,181.2031},
{1518.6881,-1095.7775,181.2031},
{1517.9375,-1092.8704,181.2031},
{1517.4718,-1089.2778,181.2031},
{1517.6533,-1085.8743,181.2031},
{1517.8470,-1082.2422,181.2031},
{1517.2373,-1079.0039,181.2031},
{1518.3839,-1075.4580,181.2031},
{1517.7598,-1072.0359,181.2031},
{1517.1816,-1068.2028,181.2031}, 
{1518.6993,-1065.6621,181.2031},
{1518.1121,-1061.9216,181.2031},
{1518.2722,-1058.8149,181.2031},
{1522.2140,-1058.9253,181.2031},
{1522.3495,-1061.8586,181.2031},
{1521.9180,-1065.7150,181.2031}, 
{1521.8937,-1069.8925,181.2031}, 
{1521.4761,-1073.6245,181.2031},
{1521.5498,-1076.6694,181.2031},
{1521.2311,-1080.1515,181.2031},
{1521.4603,-1084.5381,181.2031}, 
{1521.6918,-1088.9535,181.2031},
{1521.9218,-1093.3212,181.2031},
{1522.1301,-1097.2633,181.2031},
{1522.3265,-1100.9751,181.2031},
{1522.4648,-1103.5758,181.2031},
{1517.1544,-1089.1829,181.2031},
{1525.0632,-1073.8126,181.2031},
{1525.9830,-1067.7415,181.2031},
{1525.9971,-1061.0562,181.2031}
};

COMMAND:lmsevent(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(playerData[playerid][playerLevel] >= 4)
		{
			new msg[512];
			if (serverInfo[lmsOpen])
			{
				format(msg, sizeof(msg), "{FF00FF}[LMS]{FFffFF} Last Man Standing event has been closed.");
				TextDrawHideForAll(event4);
				TextDrawHideForAll(eventLms);
				SendClientMessageToAll(COLOR_WHITE, msg);
				serverInfo[lmsOpen] = false;
			}
			else
			{
				format(msg, sizeof(msg), "{FF00FF}[LMS]{FFffFF} Last Man Standing event has been started, type {00FFFF}/joinlms{FFffFF} to join event.");
				TextDrawShowForAll(event4);
				TextDrawShowForAll(eventLms);
				SendClientMessageToAll(COLOR_WHITE, msg);
				serverInfo[lmsOpen] = true;
				GameTextForPlayer(playerid, "Last Man Standing EVENT OPENED!", 5000, 5);
    			for( new i; i < MAX_LMSBOMBS; i++ )
				{
     				serverInfo[lmsBombs][i] = CreateDynamicObject( 1649, lmsCords[i][0], lmsCords[i][1], lmsCords[i][2], -90.000000, 0.000000, 0.000000, 444);
					Iter_Add(lmsObject, i);
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

COMMAND:startlms(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(playerData[playerid][playerLevel] >= 4)
		{
		    new bool:found = false;
			for(new i = 0; i < MAX_PLAYERS; i++)
			{
				if(IsPlayerConnected(i) && playerData[i][playerLoggedIn])
				{
					if (playerData[i][isInlms])
					{
					    found = true;
						TogglePlayerControllable(i, 1);
						GameTextForPlayer(i, "EVENT STARTED!", 5000, 5);
					}
				}
			}
			for( new i; i < MAX_LMSBOMBS; i++ )
			{
				Iter_Add(lmsObject, i);
			}
			KillTimer(serverInfo[lmsTimer]);
			if(found)
				serverInfo[lmsTimer] = SetTimer("LMSgameUpdate", 1500, 1 );
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

COMMAND:joinlms(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if (playerData[playerid][playerWantedLevel] == 0)
		{
			if (playerData[playerid][playerJailTime] < 1)
			{
				new msg[512];
				if (!playerData[playerid][isInlms])
				{
					if (serverInfo[lmsOpen])
					{
						for (new i = 0; i < 13; i++)
						{
							GetPlayerWeaponData(playerid, i, playerData[playerid][previousWeapons][i], playerData[playerid][previousAmmoLots][i]);
						}
						playerData[playerid][previousVirtualWorld] = GetPlayerVirtualWorld(playerid);
						playerData[playerid][previousInteriorWorld] = GetPlayerInterior(playerid);

						GetPlayerHealth(playerid, playerData[playerid][previousHealth]);
						GetPlayerArmour(playerid, playerData[playerid][previousArmour]);
      					GetPlayerPos(playerid, playerData[playerid][previousX], playerData[playerid][previousY], playerData[playerid][previousZ]);
      					SetPlayerInterior(playerid, 0);
						SetPlayerVirtualWorld(playerid, 443);
						SetPlayerArmour(playerid, 0);
						SetPlayerHealth(playerid, 100);
						ResetPlayerWeapons(playerid);
						TogglePlayerControllable(playerid, false);
      					new spot = Iter_Random(lmsObject);
						SetPlayerPos(playerid, lmsCords[spot][0], lmsCords[spot][1], lmsCords[spot][2] +0.5 );
						Iter_Remove(lmsObject, spot );
						format(msg, sizeof(msg), "{FF00FF}[LMS]{FFffFF} You joined Last Man Stand event.");
						GameTextForPlayer(playerid, "~r~THE EVENT WILL START SHORTLY!!!", 10000, 5);
						SendClientMessage(playerid, COLOR_WHITE, msg);
      					playerData[playerid][isInEvent] = true;
						playerData[playerid][isInlms] = true;
					}
					else
					{
						SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}There is no lms event open right now.");
					}
				}
				else
				{
					SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}Please leave the minigames arena before joining the lms event.");
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

COMMAND:destroylms(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(playerData[playerid][playerLevel] >= 4)
		{
			for( new i; i < MAX_LMSBOMBS; i++ )
			{
    			DestroyDynamicObject(serverInfo[lmsBombs][i]);
				Iter_Clear(lmsObject);
			}
			KillTimer(serverInfo[lmsTimer]);
			foreach(new i : Player)
			{
				if(playerData[i][isInlms])
				{
					playerData[i][isInEvent] = false;
					playerData[i][isInlms] = false;
				}
			}
		}
	}
	return 1;
}

forward LMSgameUpdate();
public LMSgameUpdate()
{
	new objectid = Iter_Random(lmsObject), Float:ObjectX, Float:ObjectY, Float:ObjectZ;
	GetDynamicObjectPos(serverInfo[lmsBombs][objectid], ObjectX, ObjectY, ObjectZ );
	//MoveDynamicObject(serverInfo[lmsBombs][objectid], ObjectX, ObjectY, ObjectZ -5, 1 );
	CreateExplosion(ObjectX,  ObjectY, ObjectZ, 0, 10.0);
	return 1;
}
