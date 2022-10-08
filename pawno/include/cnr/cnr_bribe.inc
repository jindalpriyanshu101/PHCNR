/*
	Don't forget to put LoadBribe() under OnGameModeInit();
*/
#define MINUTES 3 // in minutes
#define WANTED_LEVEL_DECREASED 3 // Wanted level decreased after pecked up the bribe pickup
#define MAX_BRIBE_PICKUP 11


#define TIMES 60000 * MINUTES
new static Float:bribeloc[MAX_BRIBE_PICKUP][3] =
{
	{-1753.6133,886.4552,25.0859},
	{-1435.0485,908.1920,6.7519},
	{-1680.7866,1047.9390,54.2640},
	{-2079.4968,1065.4240,65.1289},
	{-2449.8381,969.2932,44.8606},
	{-2614.4763,686.0366,30.4733},
	{-2705.4536,375.8990,4.5281},
	{-1831.4126,641.6037,29.9924},
	{-1947.0328,882.4800,38.5078},
	{-1978.5551,465.1226,28.8888},
	{-2467.6362,260.1174,35.1719}
},
bribepckp[MAX_BRIBE_PICKUP],
Text3D:bribelbl[MAX_BRIBE_PICKUP];

LoadBribe()
{
	for(new i = 0, s = sizeof(bribeloc); i < s; i++)
	{
		bribepckp[i] = CreateDynamicPickup(1247, 1, bribeloc[i][0], bribeloc[i][1], bribeloc[i][2]);
		bribelbl[i] = CreateDynamic3DTextLabel("{FFDC2E}[BRIBE]\n{FFFFFF}Pickup to decrease wanted level!", -1, bribeloc[i][0], bribeloc[i][1], bribeloc[i][2] + 0.2, 20.0);
	}
}

public OnPlayerPickUpDynamicPickup(playerid, pickupid)
{
	if(playerData[playerid][playerWantedLevel] > 0 && !playerData[playerid][playerAdminDuty])
	{
		for(new i = 0, s = sizeof(bribeloc); i < s; i++)
		{
			if(pickupid == bribepckp[i])
			{
				DestroyDynamicPickup(bribepckp[i]);
				DestroyDynamic3DTextLabel(bribelbl[i]);
				SetTimerEx("RespawnBribe", TIMES, false, "d", i);
				if(playerData[playerid][playerWantedLevel] <= WANTED_LEVEL_DECREASED)
				{
					playerData[playerid][playerWantedLevel] = 0;
				}
				else
				{
					playerData[playerid][playerWantedLevel] -= WANTED_LEVEL_DECREASED;
				}
				SetPlayerWantedLevel(playerid, playerData[playerid][playerWantedLevel]);
				new message[128];
				format(message, sizeof(message), "{FFDC2E}[BRIBE] {FFFFFF}Your wanted level decreased by %i!", WANTED_LEVEL_DECREASED);
				SendClientMessage(playerid, COLOR_WHITE, message);
				newPlayerColour(playerid);
				return 1;
			}
		}
	}
	if (playerData[playerid][isinFREEFORALL])
	{
 		if(pickupid == M4)
   		{
    		GivePlayerWeaponEx(playerid, 31, 100);
	    }
	    else if(pickupid == SNIPER)
	    {
     		GivePlayerWeaponEx(playerid, 34, 100);
	    }
	    else if(pickupid == AK47)
	    {
     		GivePlayerWeaponEx(playerid, 30, 100);
	    }
	    else if(pickupid == SHOTGUN)
	    {
		        GivePlayerWeaponEx(playerid, 27, 100);
	    }
	    else if(pickupid == GRENADE)
	    {
		        GivePlayerWeaponEx(playerid, 16, 2);
	    }
	    else if(pickupid == ROCKET)
	    {
		        GivePlayerWeaponEx(playerid, 35, 3);
	    }
	    else if(pickupid == CHAINSAW)
	    {
		        GivePlayerWeaponEx(playerid, 9, 1);
	    }
	    else if(pickupid == MOLOTOV)
	    {
		        GivePlayerWeaponEx(playerid, 18, 5);
	    }
	    else if(pickupid == TEC9)
	    {
		        GivePlayerWeaponEx(playerid, 32, 100);
	    }
	    else if(pickupid == DEAGLE)
	    {
		        GivePlayerWeaponEx(playerid, 24, 50);
	    }
	    else if(pickupid == JETPACK)
	    {
		        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USEJETPACK);
	    }
	}
	return 1;
}

forward RespawnBribe(i);
public RespawnBribe(i)
{
	bribepckp[i] = CreateDynamicPickup(1247, 1, bribeloc[i][0], bribeloc[i][1], bribeloc[i][2]);
	bribelbl[i] = CreateDynamic3DTextLabel("{FFDC2E}[BRIBE]\n{FFFFFF}Pickup to decrease wanted level!", -1, bribeloc[i][0], bribeloc[i][1], bribeloc[i][2] + 0.2, 10.0);
}
