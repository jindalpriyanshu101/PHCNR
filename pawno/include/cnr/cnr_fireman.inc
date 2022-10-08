#include <a_samp>

#define COLOR_DARKGOLD 0x808000AA
#define COLOR_RED 0xFF0000AA
#define COLOR_YELLOW 0xFFFF00AA
#define COLOR_AQUA 0x00FFFFFF
#define COL_GREEN   "{6EF83C}"
#define TEAM_AZTECAS_COLOR 0x01FCFFC8
new FiremanJob[256];
new info;


COMMAND:itfaiye(playerid, params[])
{
    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 407)
    {
            FiremanJob[playerid] = 1;
            new name[MAX_PLAYER_NAME], string[90];
            GetPlayerName(playerid, name, sizeof(name));
   	        format(string, sizeof(string), "* %s Ýtfaiyeci olarak göreve basladi.", name );
	    	SendClientMessageToAll(COLOR_AQUA, string);
	    	GameTextForPlayer(playerid, "~g~!!~w~You start~r~Working~b~Good luck ~g~!!!...", 2000, 5);
			SetPlayerCheckpoint(playerid,1099.0345,-1194.4751,18.1079,4);
			GivePlayerWeapon(playerid, 42, 99999);
			SendClientMessage(playerid,COLOR_YELLOW,"* Yangina Git!");
			return 1;
		}
		SendClientMessage(playerid, COLOR_RED,"Sadece araba içinde itfaiyeci görevine baslayabilirsiniz.");
	}
    return 0;
}
public busroutestoptimer(playerid)
{
	if(IsPlayerConnected(playerid))
	{
	    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 407)
	    {
	        TogglePlayerControllable(playerid, 1);
	        SendClientMessage(playerid, TEAM_AZTECAS_COLOR, "Acele et!");
	    }
	}
}

