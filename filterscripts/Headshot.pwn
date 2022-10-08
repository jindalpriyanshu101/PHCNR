#include <a_samp>

#define FILTERSCRIPT

public OnFilterScriptInit()
{
	return 1;
}

public OnFilterScriptExit()
{
	return 1;
}

public OnPlayerTakeDamage(playerid, issuerid, Float: amount, weaponid, bodypart)
{
	if(issuerid != INVALID_PLAYER_ID)
	{
		if(IsPlayerConnected(issuerid))
		{
			if(weaponid == 24 || weaponid == 25 || weaponid == 33 || weaponid == 34)
			{
	            if(bodypart == 9)
	            {
					SetPlayerHealth(playerid, 0);
					GameTextForPlayer(issuerid,"~r~Headshot",2000,3);
					PlayerPlaySound(issuerid, 17802, 0.0, 0.0, 0.0);
					GameTextForPlayer(playerid,"~r~Headshot",2000,3);
					PlayerPlaySound(playerid, 17802, 0.0, 0.0, 0.0);
				}
			}
		}
    }
    return 1;
}
