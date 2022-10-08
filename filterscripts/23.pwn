#include <a_samp>
#include <zcmd>
#include <sscanf2>

#define RED             0xE60000FF
#define ORANGE          0xF97804FF
#define ADMIN_RED       0xFB0000FF

public OnFilterScriptInit()
{
    if (!fexist("TempBans.ban"))
    {
        new File:open = fopen("TempBans.ban",io_write);
        if (open) fclose(open);
    }
    return 1;
}

public OnPlayerConnect(playerid)
{
    TempBanCheck(playerid);
    return 1;
}

COMMAND:tempban(playerid, params[])
{
    if (IsPlayerAdmin(playerid))
    {
        new
            numdays,
            giveplayerid,
            string[128],
            reason[100];
        if(sscanf(params, "uds[100]", giveplayerid, numdays, reason))
        {
            SendClientMessage(playerid, ORANGE, "USAGE: /tempban [name/id] [day] [reason]");
            SendClientMessage(playerid, ORANGE, "FUNCTION: Temporarily bans a player. You must enter the month, day and hour numbers. You set them, not add.");
            return 1;
        }
        if(IsPlayerConnected(giveplayerid))
        {
            new
                ip[15];
            GetPlayerIp(giveplayerid, ip, 15);
            new File:tempban = fopen("TempBans.ban", io_append);
            if (tempban)
            {
                new year,month,day;
                getdate(year, month, day);
                day += numdays;
                if (IsMonth31(month))
                {
                    if (day > 31)
                    {
                        month += 1;
                        if (month > 12)
                        {
                            year += 1;
                            while(day > 31) day -= 31;
                        }
                        else while(day > 31) day -= 31;
                    }
                }
                else if (!IsMonth31(month))
                {
                    if (day > 30)
                    {
                        month += 1;
                        if (month > 12)
                        {
                            year += 1;
                            while(day > 30) day -= 30;
                        }
                        else while(day > 30) day -= 30;
                    }
                }
                else if (!IsMonth31(month) && IsMonth29(year) && month == 2)
                {
                    if (day > 29)
                    {
                        month += 1;
                        if (month > 12)
                        {
                            year += 1;
                            while(day > 29) day -= 29;
                        }
                        else while(day > 29) day -= 29;
                    }
                }
                else if (!IsMonth31(month) && !IsMonth29(year) && month == 2)
                {
                    if (day > 28)
                    {
                        month += 1;
                        if (month > 12)
                        {
                            year += 1;
                            while(day > 28) day -= 28;
                        }
                        else while(day > 28) day -= 28;
                    }
                }
                format(string, sizeof string, "%d|%d|%d|%s\n", day, month, year, ip);
                fwrite(tempban, string);
                fclose(tempban);
            }
            format(string,128,"|- Administrator %s temporarily banned %s for %d day(s). [Reason: %s] -|",playername(playerid),playername(giveplayerid),numdays,reason);
            SendClientMessageToAll(ADMIN_RED,string);
            Kick(giveplayerid);
        }
        else SendClientMessage(playerid, RED, "Player not found!");
    }
    else SendClientMessage(playerid, RED, "You are not an admin.");
    return true;
}

stock IsMonth31(month)
{
    switch (month)
    {
        case 1: return 1;
        case 3: return 1;
        case 5: return 1;
        case 7: return 1;
        case 8: return 1;
        case 10: return 1;
        case 12: return 1;
        default: return 0;
    }
    return 0;
}

stock IsMonth29(year)
{
    new y = 2000;
    for(new i = 4; i < 3000; i += 4) if ((y+i) == year) return 1;
    return 0;
}

stock TempBanCheck(playerid)
{
    new ip[15];
    new str[128];
    new load[4][32];
    new ban_day, ban_month, ban_year, ban_ip[15];
    GetPlayerIp(playerid, ip, sizeof ip);
    new year, month, day;
    getdate(year, month, day);
    new File:file = fopen("TempBans.ban",io_read);
    if (file)
    {
        while (fread(file, str, sizeof str))
        {
            split(str, load, '|');

            ban_day = strval(load[0]);
            ban_month = strval(load[1]);
            ban_year = strval(load[2]);
            strmid(ban_ip, load[3], 0, strlen(load[3])-1, 15);
            if (!(year >= ban_year && month >= ban_month && day >= ban_day && !strcmp(ban_ip, ip, true)))
            {
                format(str, sizeof str, "|- You are temporarily banned from this server until: %d/%d/%d -|", ban_day, ban_month, ban_year);
                SendClientMessage(playerid, ADMIN_RED, str);
                return Kick(playerid);
            }
        }
    }
    return true;
}

stock split(const strsrc[], strdest[][], delimiter)
{
    new i, li;
    new aNum;
    new len;

    while(i <= strlen(strsrc)){
        if(strsrc[i]==delimiter || i==strlen(strsrc)){
            len = strmid(strdest[aNum], strsrc, li, i, 128);
            strdest[aNum][len] = 0;
            li = i+1;
            aNum++;
        }
        i++;
    }
    return 1;
}

playername(playerid)
{
    new pName[MAX_PLAYER_NAME];
    GetPlayerName(playerid, pName, MAX_PLAYER_NAME);
    return pName;
}
