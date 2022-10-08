#include <a_samp>
#include <zcmd>
#include <sscanf2>

new bool:istempmuted[MAX_PLAYERS];

forward TempMute(playerid);
public OnPlayerText(playerid, text[])
{
    if(istempmuted[playerid])
    {
        SendClientMessage(playerid, 0xff0000FF, "You are muted");
        return 0;
    }
    return 1;
}

COMMAND:tempmute(playerid, params[])
{
    if(!IsPlayerAdmin(playerid))return 0;
    else
    {
        new
            id,
            seconds;
        if(sscanf(params,"ud", id, seconds))return SendClientMessage(playerid, 0xff0000FF, "ERROR: Usage /tempmute [name/id][seconds]");
        if(IsPlayerConnected(id))
        {
            istempmuted[id] = true;
            SetTimerEx("TempMute", seconds * 1000,false, "i", id);
            return 1;
        }
        else SendClientMessage(playerid, 0xff0000FF, "ERROR: Player not found!");
    }
    return 1;
}

COMMAND:unmute(playerid, params[])
{
    new
        id;
    if(sscanf(params,"u", id))return SendClientMessage(playerid, 0xff0000FF, "ERROR: Usage /unmute [name/id]");
    if(IsPlayerConnected(id))
    {
        istempmuted[playerid] = false;
        return 1;
    }
    else SendClientMessage(playerid, 0xff0000FF, "ERROR: Player not found!");
    return 1;
}

public TempMute(playerid)
{
    istempmuted[playerid] = false;
    SendClientMessage(playerid, 0xff0000FF, "You have been unmuted");
}
