#define MAX_BRIBES 200

new BribeTimer[MAX_PLAYERS];
new Bribe[MAX_BRIBES];

CMD:createbribe(playerid, params[])
{
    if(!IsPlayerAdmin(playerid)) return SendClientMessage(playerid, -1, "You are not a RCON admin.");
    new Float:p[3];
    GetPlayerPos(playerid, p[0], p[1], p[2]);
    for(new i = 0; i < MAX_BRIBES; i++)
    {
        Bribe[i] = CreatePickup(1247, 1, p[0], p[1], p[2], GetPlayerVirtualWorld(playerid);
    }
    SendClientMessage(playerid, -1, "You created a Bribe at your Location.");
    return 1;
}
