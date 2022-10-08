#define MAX_BAG_LOCATIONS 43

enum moneyBag
{
	bagID,
	bagValue,
	bagType,
	Float:bagXYZ[3],
	bagTitle[25],
	Text3D:bagLabel
}

new moneyBagInfo[MAX_BAG_LOCATIONS][moneyBag] =
{
	/*
	    - bagID		    - The unique ID of the bag
		- bagValue		- Value of the bag
		- XP/MONEY 		- 1 for money, 2 for XP
		- bagXYZ		- Location
		- bagTitle		- The title (Downtown San Fierro)
	*/
	
	// Missions
	{2, 10900, 1, {-1481.4622,691.2758,1.3203}, "Esplanade East"},
	{2, 21345, 1, {-1704.7704,562.3779,24.6057}, "Easter Basin"},
	{3, 17689, 1, {-1979.7714,431.4383,24.9759}, "Downtown"},
	{4, 24123, 1, {-2083.1931,254.6825,39.3953}, "Doherty"},
	{5, 15674, 1, {-1962.3040,104.9817,27.6875}, "Cranberry Station"},
	{6, 13453, 1, {-2286.2783,-13.8594,35.3203}, "Garcia"},
	{7, 20100, 1, {-2223.0466,113.6112,35.3203}, "Garcia"},
	{8, 20000, 1, {-2199.3811,367.5616,35.3203}, "King's"},
	{9, 19898, 1, {-2285.7937,-17.5240,34.8773}, "Garcia"},
	{10, 14000, 1, {-2452.0447,5.1259,25.1828}, "Hashbury"},
	{11, 24000, 1, {-2653.3491,106.6617,3.6200}, "Ocean Flats"},
	{12, 17896, 1, {-2883.8442,227.6897,3.6754}, "Ocean Flats"},
	{13, 21234, 1, {-2770.3799,388.3070,4.0334}, "City Hall"},
	{14, 12421, 1, {-2810.0803,412.4345,4.0565}, "City Hall"},
	{15, 16574, 1, {-2779.2068,768.7475,50.5995}, "Palisades"},
	{16, 22345, 1, {-2647.1404,790.7414,49.9766}, "Palisades"},
	{17, 18768, 1, {-2440.6797,937.9563,44.9739}, "Juniper Hill"},
	{18, 23543, 1, {-2299.4360,1101.1323,79.5239}, "Juniper Hollow"},
	{19, 16789, 1, {-2669.7151,1450.0897,6.6537}, "Battery Point"},
	{20, 21345, 1, {-2052.5342,1227.0645,31.2183}, "Calton Heights"},
	{21, 12345, 1, {-1832.6597,1544.0736,6.7411}, "Esplanade North"},
	{22, 24323, 1, {-1948.7843,872.5396,38.5078}, "Downtown"},
	{23, 19876, 1, {-1821.7623,-170.2575,8.9526}, "Doherty"},
	{24, 23213, 1, {-1664.9622,-404.0125,13.7180}, "Airport"},
	{25, 17658, 1, {-1085.4250,414.8973,13.7033}, "Airport"},
	{26, 21234, 1, {-1686.7516,-441.9021,13.7005}, "Airport"},
	{27, 19999, 1, {-1610.5676,872.2232,9.2298}, "Downtown"},
	{28, 22222, 1, {-1782.4066,760.6703,24.4519}, "Financial"},
	{29, 21111, 1, {-2323.7312, 1007.5217, 50.6953}, "Juniper Hollow"},
	{30, 18988, 1, {-1480.1875, 1081.4640, 7.1846}, "Esplanade East"},
	{31, 22333, 1, {-1421.0746, 887.9710, 7.1875}, "Esplanade East"},
	{32, 18888, 1, {-1904.4598, 288.8323, 41.0469}, "Downtown"},
	{33, 13456, 1, {-1904.9045, 219.7438, 35.1504}, "Downtown"},
	{34, 20999, 1, {-1959.0493, 103.1213, 26.2734}, "Cranberry Station"},
	{35, 18888, 1, {-1969.2363, 152.2529, 27.6875}, "Cranberry Station"},
	{36, 17777, 1, {-2043.3934, -33.0418, 35.4254}, "Doherty"},
	{37, 16666, 1, {-2151.1548, -102.4534, 35.3203}, "Doherty"},
	{38, 15555, 1, {-2238.3506, -102.8241, 35.3203}, "Garcia"},
	{39, 21200, 1, {-1471.2797,1018.9509,2.4992}, "Esplanade East"},
	{40, 30000, 1, {-2662.7729,1583.8047,63.8962}, "Gant Bridge"},
	{41, 20000, 1, {-2796.5085,1094.4554,28.3203}, "Palisades"},
	{42, 21234, 1, {-2507.9353,751.9516,39.5859}, "Juniper Hill"},
	{43, 28000, 1, {-2425.8428,721.8315,45.3962}, "Juniper Hill"}
	//{43, 40000, 1, {1604.183349, 1157.920654, 10.812500}, "Las Venturas Airport"},
	//{44, 40000, 1, {1645.757690, 1349.336791, 10.799027}, "Las Venturas Airport"},
	//{45, 40000, 1, {1669.532592, 2036.920410, 11.367187}, "Redsands West"},
	//{46, 40000, 1, {1636.607910, 2224.634765, 11.062500}, "Redsands West"},
	//{47, 40000, 1, {2275.400146, 2267.694824, 10.820312}, "Roca Escalante"},
	//{48, 40000, 1, {2401.107177, 2526.143798, 10.820312}, "Roca Escalante"},
	//{49, 40000, 1, {2109.749267, 2329.810302, 11.742187}, "The Emerald Isle"},
	//{50, 40000, 1, {2019.337646, 2350.670654, 10.820312}, "The Emerald Isle"},
	//{51, 40000, 1, {1874.943969, 2389.542724, 10.820312}, "Redsands East"},
	//{52, 40000, 1, {1843.580932, 2564.750488, 11.023437}, "Julius Thruway North"},
	//{53, 40000, 1, {2148.466796, 2716.021728, 10.820312}, "Spinybed"}
};

forward autoMoneyBag();
public autoMoneyBag()
{
	if (serverInfo[moneybagid] != -1)
	{
		// Remove the money bag, no one found it!
		new MoneybagID = serverInfo[moneybagid];
		DestroyPickup(moneyBagInfo[MoneybagID][bagID]);
		DestroyDynamic3DTextLabel(moneyBagInfo[MoneybagID][bagLabel]);
  		TextDrawHideForAll(Moneybag);
		TextDrawHideForAll(Moneybag1);
		serverInfo[moneybagid] = -1;
		SendClientMessageToAll(COLOR_WHITE, "{58D3F7}[Briefcase] {FFFFFF}Ooo No! The event has ended, no one found the Briefcase.");
	}
	else
	{
		// Place a random money bag
		new randomBag = random(MAX_BAG_LOCATIONS);
		
		moneyBagInfo[randomBag][bagID] = CreatePickup(1210, 23, moneyBagInfo[randomBag][bagXYZ][0], moneyBagInfo[randomBag][bagXYZ][1], moneyBagInfo[randomBag][bagXYZ][2], -1);
		moneyBagInfo[randomBag][bagLabel] = CreateDynamic3DTextLabel("[BRIEFCASE]", COLOR_YELLOW, moneyBagInfo[randomBag][bagXYZ][0], moneyBagInfo[randomBag][bagXYZ][1], moneyBagInfo[randomBag][bagXYZ][2] - 0.1, 40.0);
		
		serverInfo[moneybagid] = randomBag;

		new bagInfo[200];
		
		//Texdraw
		format(bagInfo, sizeof(bagInfo), "Briefcase Info: %s", moneyBagInfo[randomBag][bagTitle]);
		TextDrawSetString(Moneybag1, bagInfo);
		TextDrawShowForAll(Moneybag);
  		TextDrawShowForAll(Moneybag1);
		
		//SendClient
		format(bagInfo, sizeof(bagInfo), "{58D3F7}[Briefcase] {FFFFFF}Come On! A Briefcase has been hidden in {FFDC2E}%s{FFFFFF}!", moneyBagInfo[randomBag][bagTitle]);
		SendClientMessageToAll(COLOR_WHITE, bagInfo);
	}
}


COMMAND:startcase(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(playerData[playerid][playerLevel] >= 5)
		{
			autoMoneyBag();
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}You do not have the correct permissions to use this command.");
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}You must be logged in to use commands.");
	}
		
	return 1;
}

COMMAND:gotocase(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(playerData[playerid][playerLevel] >= 5)
		{
			if (serverInfo[moneybagid] == -1)
			{
				SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}There is no Briefcase active.");
			}
			else
			{
				// Go to bag
				new gotobag = serverInfo[moneybagid];
				SetPlayerPos(playerid, moneyBagInfo[gotobag][bagXYZ][0] + 2.0, moneyBagInfo[gotobag][bagXYZ][1], moneyBagInfo[gotobag][bagXYZ][2] + 1.0);
				SetPlayerVirtualWorld(playerid, 0);
				SetPlayerInterior(playerid, 0);
				
				SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}You teleported to the Briefcase.");
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}You do not have the correct permissions to use this command.");
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}You must be logged in to use commands.");
	}
		
	return 1;
}

COMMAND:bcase(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if (serverInfo[moneybagid] != -1)
		{
			// Show Briefcase location
			new MoneybagID = serverInfo[moneybagid];
			
			new bagInfo[200];
			format(bagInfo, sizeof(bagInfo), "{58D3F7}[Briefcase] {FFFFFF}The Briefcase is hidden in {FFDC2E}%s{FFFFFF}!.", moneyBagInfo[MoneybagID][bagTitle]);
			SendClientMessage(playerid, COLOR_WHITE, bagInfo);


            new bagIn[200];
   			//Texdraw
   			format(bagIn, sizeof(bagIn), "Briefcase: %s", moneyBagInfo[MoneybagID][bagTitle]);
		 	TextDrawSetString(Moneybag1, bagIn);
			TextDrawShowForPlayer(playerid, Moneybag);
	  		TextDrawShowForPlayer(playerid, Moneybag1);
		}
		else
		{
			// No money bag exists
			SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}There is no Briefcase hidden.");
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}You must be logged in to use commands.");
	}
		
	return 1;
}

/*
COMMAND:pickup(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if (serverInfo[moneybagid] != -1)
		{
			// Show money bag location
   			new MoneybagID = serverInfo[moneybagid];
			
   			if(IsPlayerInRangeOfPoint(playerid, 4.0, moneyBagInfo[MoneybagID][bagXYZ][0], moneyBagInfo[MoneybagID][bagXYZ][1], moneyBagInfo[MoneybagID][bagXYZ][2]))
			{
				// Player found money bag
				for(new p; p < MAX_PLAYERS; p++)
				{
					new pName[24];
					GetPlayerName(p, pName, sizeof(pName));

					if(!strcmp(pName, playerData[playerid][playerNamee]))
					{
						new moneybagmsg[200];
						format(moneybagmsg, sizeof(moneybagmsg), "{58D3F7}[Briefcase] {FFFFFF}Well done! You found a Briefcase worth {FFDC2E}$%s{FFFFFF}.", FormatNumber(moneyBagInfo[MoneybagID][bagValue]));
						SendClientMessage(p, COLOR_WHITE, moneybagmsg);
					}
					else
					{
						new moneybagmsg[200];
						format(moneybagmsg, sizeof(moneybagmsg), "{58D3F7}[Briefcase] {FFFFFF}%s(%i) found a Briefcase worth {FFDC2E}$%s{FFFFFF}!", playerData[playerid][playerNamee], playerid, FormatNumber(moneyBagInfo[MoneybagID][bagValue]));
						SendClientMessage(p, COLOR_WHITE, moneybagmsg);
					}
				}

				playerGiveMoney(playerid, moneyBagInfo[MoneybagID][bagValue]);
				playerGiveXP(playerid, 20);

				DestroyPickup(moneyBagInfo[MoneybagID][bagID]);
				DestroyDynamic3DTextLabel(moneyBagInfo[MoneybagID][bagLabel]);
				TextDrawHideForAll(Moneybag);//right?
				TextDrawHideForAll(Moneybag1);
				serverInfo[moneybagid] = -1;
				playerData[playerid][moneyBags] = playerData[playerid][moneyBags] + 1;

				if(playerData[playerid][moneyBags] == 1)
				{
					disableAchieve(playerid);
					PlayerTextDrawShow(playerid, playerData[playerid][Achieve1]);
					PlayerTextDrawShow(playerid, playerData[playerid][Achieve2]);
					PlayerTextDrawShow(playerid, playerData[playerid][Achieve3]);
					PlayerTextDrawShow(playerid, playerData[playerid][Achieve4]);

					PlayerTextDrawSetString(playerid, playerData[playerid][Achieve3], "Easy Money");
					PlayerTextDrawSetString(playerid, playerData[playerid][Achieve4], "You found and claimed your first Briefcase.");
					PlayerPlaySound(playerid, 1185 ,0.0, 0.0, 0.0);
					TextDrawHideForAll(Moneybag);//right?
					TextDrawHideForAll(Moneybag1);

					playerData[playerid][achieveTimer] = SetTimerEx("disableAchieve", 8000, false, "i", playerid);
				}
 			}
			else
			{
				SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}You're not close enough to a Briefcase.");
			}
		}
		else
		{
			// No money bag exists
			SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}There is no Briefcase hidden.");
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}You must be logged in to use commands.");
	}

	return 1;
}*/
