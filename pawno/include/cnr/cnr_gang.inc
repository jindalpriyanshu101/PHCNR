#define MYSQL_CREATE_GANG		 10
#define MYSQL_LOAD_GANGS		 11
#define MAX_ZONES 3
enum _Gang
{
	gangID,
	gangColor[7],
	gangScore,
	gangKill,
	gangDeath,
	gangSlot,
	gangName[56],
	gangTag[4],
	gangMembers[MAX_PLAYERS],
	currentInvites[MAX_PLAYERS],
	gangLocked
}

new gangData[MAX_GANGS][_Gang];

enum _Zone
{
	Float:zoneX,
	Float:zoneY,
	Float:zoneMaxX,
	Float:zoneMaxY,
	zoneName[56],
	zoneGang,
	bool:zoneLocked,
	zoneAttacker,
	zoneGangZone,
	zoneArea,
	zoneTimer,
	zoneTime
}

new zoneData[MAX_ZONES][_Zone] = 
{
	{-2765.267, 315.188, -2637.267, 435.188, "City Hall", -1, false, -1},
	{-1563.195, -456.734, -1403.195, -296.734, "Airport", -1, false, -1},
	{-2519.446, 575.186, -2391.446, 719.186, "Juniper Hill", -1, false, -1}
};

flushGangs()
{
	for(new i = 0; i < MAX_GANGS; i++)
	{
		gangData[i][gangID] = INVALID_GANG_ID;
		gangData[i][gangScore] = -1;
		format(gangData[i][gangName], MAX_GANG_CHARS, "");
		foreach(new xxx : Player)
		{
			gangData[i][gangMembers][xxx] = 0;
			gangData[i][currentInvites][xxx] = 0;
		}
	}
	
	new query[256];
	format(query, 256, "SELECT * FROM gang");
	mysql_query(query, MYSQL_LOAD_GANGS, -1, connection);
	return 1;
}

gangCount(gid)
{
	new query[256];
	format(query, 256, "SELECT COUNT(*) AS total FROM playerdata WHERE gang = %d", gangData[gid][gangID]);
	mysql_query(query, -1, -1, connection);
	new total[10];
	mysql_store_result();
	mysql_fetch_field("total", total);
	mysql_free_result();
	return strval(total);
}

sendMessageToGangMembers(gangToSendTo, messageToSend[])
{
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i))
		{
			if(playerData[i][playerLoggedIn])
			{
				if(playerData[i][playerGang] == gangToSendTo)
				{
					SendClientMessage(i, COLOR_WHITE, messageToSend);
				}
			}
		}
	}
	
	return 1;
}

saveGang(gangid)
{
	new query[256];
	format(query, 256, "UPDATE gang SET color = '%s', score = %d, gangslot = %d, kills = %d, deaths = %d WHERE id = %d", gangData[gangid][gangColor], gangData[gangid][gangScore], gangData[gangid][gangSlot], gangData[gangid][gangKill], gangData[gangid][gangDeath], gangData[gangid][gangID]);
	mysql_query(query, -1, -1, connection);
}

removeGang(gangToRemove)
{	
	for(new x = 0; x < MAX_ZONES; x++)
	{
		if(zoneData[x][zoneGang] == gangToRemove && zoneData[x][zoneAttacker] != -1)
		{
			zoneData[x][zoneGang] = -1;
			GangZoneHideForAll(zoneData[x][zoneGangZone]);
			GangZoneShowForAll(zoneData[x][zoneGangZone], 0x000000AA);
		}
	}
	new query[256];
	format(query, 256, "UPDATE playerdata SET gang = 0, gangstatus = 0 WHERE gang = %d", gangData[gangToRemove][gangID]);
	mysql_query(query, -1, -1, connection);
	format(query, 256, "DELETE FROM gang WHERE id = %d", gangData[gangToRemove][gangID]);
	mysql_query(query, -1, -1, connection);

	for(new k = 0; k < MAX_PLAYERS; k++)
	{
		if(playerData[k][playerGang] == gangToRemove)
		{
			playerData[k][playerGang] = INVALID_GANG_ID;
			playerData[k][playerGrank] = MEMBER;
		}
	}
	gangData[gangToRemove][gangID] = INVALID_GANG_ID;
	gangData[gangToRemove][gangScore] = -1;
	
	for(new j = 0; j < MAX_PLAYERS; j++)
	{
		gangData[gangToRemove][gangMembers][j] = INVALID_PLAYER_ID;
		gangData[gangToRemove][currentInvites][j] = INVALID_PLAYER_ID;
	}
	
	format(gangData[gangToRemove][gangName], MAX_GANG_CHARS, "");
	
	
	return 1;
}

findNextFreeGangID()
{
	for(new i = 0; i < MAX_GANGS; i++)
	{
		if(gangData[i][gangScore] == -1)
			return i;
	}
	return INVALID_GANG_ID;
}

createGang(newGangName[], creatorID)
{
	new newGangID = findNextFreeGangID();
	if(newGangID == -1)
	{
		SendClientMessage(creatorID, 0xFF0000FF, "Max gangs reached!");
		return 1;
	}
	gangData[newGangID][gangID] = -1;
	gangData[newGangID][gangSlot] = 12;
	gangData[newGangID][gangKill] = gangData[newGangID][gangScore] = gangData[newGangID][gangDeath] = 0;
	format(gangData[newGangID][gangName], 56, newGangName, 0);
	format(gangData[newGangID][gangColor], 7, "FFFFFF", 0);
	gangData[newGangID][gangMembers][creatorID] = 1;
	playerData[creatorID][playerGang] = newGangID;
	playerData[creatorID][playerGrank] = LEADER;
	new query[256], escape[56];
	mysql_real_escape_string(newGangName, escape);
	format(query, 256, "INSERT INTO gang(name, color) VALUES('%s', 'FFFFFF')", escape);
	mysql_query(query, MYSQL_CREATE_GANG, newGangID, connection);
	return 1;
}

COMMAND:g(playerid, params[])
{
	new commandSelection[128];
	
	if(playerData[playerid][playerLoggedIn])
	{
	   	new input[120], gangMessage[128];
		if(!sscanf(params, "s[128] ", commandSelection))
		{
			if(!strcmp(commandSelection, "create", true))
			{
				if(playerData[playerid][playerScore] >= 1000 && playerData[playerid][playerMoney] >= 50000)
				{
					if(playerData[playerid][playerGang] == -1)
					{
						new newGangName[MAX_GANG_CHARS];
						
						if(!sscanf(params, "s[128] s[24]", commandSelection, newGangName))
						{
							if (strlen(newGangName) > 2 && strlen(newGangName) <= 24)
							{
								for(new sho = 0; sho < MAX_GANGS; sho++)
								{
									if(gangData[sho][gangScore] != -1)
									{
										if(!strcmp(gangData[sho][gangName], newGangName, true))
										{
											SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}Gang name already taken.");
											return 1;
										}
									}
								}
								createGang(newGangName, playerid);
								playerTakeMoney(playerid, 50000);
							}
							else
							{
								SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}The gang name should be between 3 and 24 characters long.");
							}
						}
						else
						{
							SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}Usage: /g(ang) create [gang name]");
						}
					}
					else
					{
						SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}You're already in a gang, you cannot create another.");
					}
				}
				else
				{
					SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}You must have at least 1000 score and $50,000 to create a gang.");
				}
			}		
			else if(!strcmp(commandSelection, "invite", true))
			{
				if(playerData[playerid][playerGang] != -1)
				{
					new playerToInvite;
					
					if(playerData[playerid][playerGrank] != LEADER && playerData[playerid][playerGrank] != STAFF)
						return 1;

					if(!sscanf(params, "s[128] u", commandSelection, playerToInvite))
					{
						if(IsPlayerConnected(playerToInvite)) // logged in
						{
							if(playerData[playerToInvite][playerLoggedIn]) // logged in
							{
								if(playerid != playerToInvite)
								{
									if(playerData[playerToInvite][playerGang] == -1)
									{
										new 
											invitingMessage[128],
											playersGangID = playerData[playerid][playerGang];
										
										if(gangCount(playersGangID) <= gangData[playersGangID][gangSlot])
										{
											gangData[playersGangID][currentInvites][playerToInvite] = 1;
											
											format(invitingMessage, sizeof(invitingMessage), "{39BBEE}[GANG] {FFFFFF}You have invited %s(%i) to join %s.", playerData[playerToInvite][playerNamee], playerToInvite, gangData[playersGangID][gangName]);
											SendClientMessage(playerid, COLOR_WHITE, invitingMessage);
											
											format(invitingMessage, sizeof(invitingMessage), "{39BBEE}[GANG] {FFFFFF}%s(%i) has invited you to join %s, use /g(ang) join %i to join.", playerData[playerid][playerNamee], playerid, gangData[playersGangID][gangName], playersGangID);
											SendClientMessage(playerToInvite, COLOR_WHITE, invitingMessage);
										}
										else
											SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}Gang slot is full.");
									}
									else
									{
										SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}The player you're trying to invite is already in a gang.");
									}
								}
								else
								{
									SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}You're already in this gang, no need to invite yourself.");
								}
							}
							else
							{
								SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}That player is not logged in.");
							}
						}
						else
						{
							SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}That player is not connected.");
						}
					}
					else
					{
						SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}Usage: /g(ang) invite [PLAYER_ID]");
					}
				}
				else
				{
					SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}You need to be in a gang use these commands.");
				}
			}			
			else if(!strcmp(commandSelection, "leader", true))
			{
				if(playerData[playerid][playerGang] != INVALID_GANG_ID)
				{
					if(playerData[playerid][playerGrank] == LEADER)
					{
						new newLeaderID;
						
						if(!sscanf(params, "s[300] u", commandSelection, newLeaderID))
						{
							if(IsPlayerConnected(newLeaderID)) // logged in
							{
								if(playerData[newLeaderID][playerLoggedIn]) // logged in
								{
									if(playerid != newLeaderID)
									{
										if(playerData[playerid][playerGang] == playerData[newLeaderID][playerGang])
										{
											new successionMessage[128],
												playersGangID = playerData[playerid][playerGang];
											
											format(successionMessage, sizeof(successionMessage), "{39BBEE}[GANG] {FFFFFF}%s(%i) has been made the leader of %s.", playerData[newLeaderID][playerNamee], newLeaderID, gangData[playersGangID][gangName]);
											sendMessageToGangMembers(playerData[playerid][playerGang], successionMessage);
											
											playerData[playerid][playerGrank] = MEMBER;
											playerData[newLeaderID][playerGrank] = LEADER;
											savePlayerStats(playerid);
											savePlayerStats(newLeaderID);
										}
										else
										{
											SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}This player is not in your gang.");
										}
									}
									else
									{
										SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}You're already the leader of this gang.");
									}
								}
								else
								{
									SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}That player is not logged in.");
								}
							}
							else
							{
								SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}That player is not connected.");
							}
						}
						else
						{
							SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}Usage: /g(ang) leader [PLAYER_ID]");
						}
					}
					else
					{
						SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}You're not the current leader of this gang.");
					}
				}
				else
				{
					SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}You need to be in a gang use these commands.");
				}				
			}	
			else if(!strcmp(commandSelection, "kick", true))
			{
				if(playerData[playerid][playerGang] != INVALID_GANG_ID)
				{
					if(playerData[playerid][playerGrank] == LEADER || playerData[playerid][playerGrank] == STAFF)
					{
						new playerToKick;
						
						if(!sscanf(params, "s[128] u", commandSelection, playerToKick))
						{
							if(IsPlayerConnected(playerToKick)) // logged in
							{
								if(playerData[playerToKick][playerLoggedIn]) // logged in
								{
									if(playerToKick != playerid)
									{
										if(playerData[playerid][playerGang] == playerData[playerToKick][playerGang])
										{

											if(playerData[playerid][playerGrank] > playerData[playerToKick][playerGrank])
											{
												new kickedMessage[128],
													playersGangID = playerData[playerid][playerGang];
												
												format(kickedMessage, sizeof(kickedMessage), "{39BBEE}[GANG] {FFFFFF}%s(%i) %s, has kicked %s(%i) from %s gang.", playerData[playerid][playerNamee], playerid, playerData[playerToKick][playerNamee], playerToKick, gangData[playersGangID][gangName]);
												sendMessageToGangMembers(playerData[playerid][playerGang], kickedMessage);
												
												playerData[playerToKick][playerGang] = -1;
												playerData[playerToKick][playerGrank] = MEMBER;
												gangData[playersGangID][gangMembers][playerToKick] = 0;
												savePlayerStats(playerToKick);
											}
											else
											{
												SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}You can't kick that player from gang.");
											}
										}
										else
										{
											SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}The player you're trying to kick isn't in your gang.");
										}
									}
									else
									{
										SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}You cannot kick yourself from the gang - use /g leave.");
									}
								}
								else
								{
									SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}That player is not logged in.");
								}
							}
							else
							{
								SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}That player is not connected.");
							}
						}
						else
						{
							SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}Usage: /g(ang) kick [PLAYER_ID]");
						}
					}
					else
					{
						SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}You're not the leader / staff of this gang.");
					}
				}
				else
				{
					SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}You need to be in a gang use these commands.");
				}	
			}
			else if(!strcmp(commandSelection, "promote", true))
			{
				if(playerData[playerid][playerGang] != INVALID_GANG_ID)
				{
					if(playerData[playerid][playerGrank] == LEADER)
					{
						new playerToKick;
						
						if(!sscanf(params, "s[128] u", commandSelection, playerToKick))
						{
							if(IsPlayerConnected(playerToKick)) // logged in
							{
								if(playerData[playerToKick][playerLoggedIn]) // logged in
								{
									if(playerToKick != playerid)
									{
										if(playerData[playerid][playerGang] == playerData[playerToKick][playerGang])
										{

											if(playerData[playerToKick][playerGrank] != STAFF)
											{
												new kickedMessage[128];
												
												format(kickedMessage, sizeof(kickedMessage), "{39BBEE}[GANG] {FFFFFF}%s(%i) %s, has promoted %s(%i) to a gang staff.", playerData[playerid][playerNamee], playerid, playerData[playerToKick][playerNamee], playerToKick);
												sendMessageToGangMembers(playerData[playerid][playerGang], kickedMessage);
												
												playerData[playerToKick][playerGrank] = STAFF;
												savePlayerStats(playerToKick);
											}
											else
											{
												SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}That player is already a gang staff.");
											}
										}
										else
										{
											SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}The player isn't in your gang.");
										}
									}
									else
									{
										SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}You cannot promote yourself.");
									}
								}
								else
								{
									SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}That player is not logged in.");
								}
							}
							else
							{
								SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}That player is not connected.");
							}
						}
						else
						{
							SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}Usage: /g(ang) promote [PLAYER_ID]");
						}
					}
					else
					{
						SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}You're not the leader of this gang.");
					}
				}
				else
				{
					SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}You need to be in a gang use these commands.");
				}	
			}
			else if(!strcmp(commandSelection, "demote", true))
			{
				if(playerData[playerid][playerGang] != INVALID_GANG_ID)
				{
					if(playerData[playerid][playerGrank] == LEADER)
					{
						new playerToKick;
						
						if(!sscanf(params, "s[128] u", commandSelection, playerToKick))
						{
							if(IsPlayerConnected(playerToKick)) // logged in
							{
								if(playerData[playerToKick][playerLoggedIn]) // logged in
								{
									if(playerToKick != playerid)
									{
										if(playerData[playerid][playerGang] == playerData[playerToKick][playerGang])
										{

											if(playerData[playerToKick][playerGrank] == STAFF)
											{
												new kickedMessage[128];
												
												format(kickedMessage, sizeof(kickedMessage), "{39BBEE}[GANG] {FFFFFF}%s(%i) %s, has demoted %s(%i) from gang staff.", playerData[playerid][playerNamee], playerid, playerData[playerToKick][playerNamee], playerToKick);
												sendMessageToGangMembers(playerData[playerid][playerGang], kickedMessage);
												
												playerData[playerToKick][playerGrank] = MEMBER;
												savePlayerStats(playerToKick);
											}
											else
											{
												SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}That player is not your gang staff.");
											}
										}
										else
										{
											SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}The player isn't in your gang.");
										}
									}
									else
									{
										SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}You cannot promote yourself.");
									}
								}
								else
								{
									SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}That player is not logged in.");
								}
							}
							else
							{
								SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}That player is not connected.");
							}
						}
						else
						{
							SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}Usage: /g(ang) promote [PLAYER_ID]");
						}
					}
					else
					{
						SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}You're not the leader of this gang.");
					}
				}
				else
				{
					SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}You need to be in a gang use these commands.");
				}	
			}
			else if(!strcmp(commandSelection, "colour", true))
			{
				if(playerData[playerid][playerGang] != INVALID_GANG_ID)
				{
					if(playerData[playerid][playerGrank] == LEADER)
					{
						if(sscanf(params, "s[128] h", commandSelection, params))
						{
							SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}Usage: /g(ang) colour [HEX_COLOR]");
							return 1;
						}

						if(strlen(params) != 6)
						{
							SendClientMessage(playerid, 0xFF0000FF, "Invalid hex color");
							return 1;
						}

						new i = playerData[playerid][playerGang];
						format(gangData[i][gangColor], 7, params, 0);
						new msg[128];
						format(msg, 128, "{39BBEE}[GANG] {FFFFFF}Gang color has changed to {%s}%s", params, params);
						SendClientMessage(playerid, -1, msg);
						format(msg, 128, "UPDATE gang SET color = '%s' WHERE id = %d", gangData[i][gangColor], gangData[i][gangID]);
						mysql_query(msg, -1, -1, connection);
						new colour[10];
						format(colour, 10, "%s50", gangData[i][gangColor]);
						for(new x = 0; x < MAX_ZONES; x++)
						{
							if(zoneData[x][zoneGang] == i && zoneData[x][zoneAttacker] != -1)
							{
								GangZoneHideForAll(zoneData[x][zoneGangZone]);
								GangZoneShowForAll(zoneData[x][zoneGangZone], HexToInt(colour));
							}
						}
					}
					else
					{
						SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}You're not the current leader of this gang.");
					}
				}
				else
				{
					SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}You need to be in a gang use these commands.");
				}	
			}
			else if(!strcmp(commandSelection, "disband", true))
			{
				if(playerData[playerid][playerGang] != INVALID_GANG_ID)
				{
					if(playerData[playerid][playerGrank] == LEADER)
					{
						new disbandedMessage[128],
							playersGangID = playerData[playerid][playerGang];
						
						format(disbandedMessage, sizeof(disbandedMessage), "{39BBEE}[GANG] {FFFFFF}%s(%i), the leader of %s, has disbanded the gang.", playerData[playerid][playerNamee], playerid, gangData[playersGangID][gangName]);
						sendMessageToGangMembers(playersGangID, disbandedMessage);
						removeGang(playersGangID);
					}
					else
					{
						SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}You're not the current leader of this gang.");
					}
				}
				else
				{
					SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}You need to be in a gang use these commands.");
				}				
			}			
			else if(!strcmp(commandSelection, "leave", true))
			{
				if(playerData[playerid][playerGang] != INVALID_GANG_ID)
				{
					if(playerData[playerid][playerGrank] != LEADER)
					{
						new 
							playersGangID = playerData[playerid][playerGang],
							leavingMessage[128];
						
						format(leavingMessage, sizeof(leavingMessage), "{39BBEE}[GANG] {FFFFFF}%s(%i) has left the gang.", playerData[playerid][playerNamee], playerid);
						sendMessageToGangMembers(playersGangID, leavingMessage);
						
						gangData[playersGangID][gangMembers][playerid] = INVALID_PLAYER_ID;
						playerData[playerid][playerGang] = INVALID_GANG_ID;
						playerData[playerid][playerGrank] = MEMBER;
						savePlayerStats(playerid);
						
						  
						SendClientMessage(playerid, COLOR_WHITE, "{39BBEE}[GANG] {FFFFFF}You have left the gang you were in.");
						sendMessageToGangMembers(playersGangID, leavingMessage);
					}
					else
					{
						SendClientMessage(playerid, COLOR_WHITE, "{39BBEE}[GANG] {FFFFFF}You must give your leader rank to one of your member before leaving gang.");
					}
				}
				else
				{
					SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}You need to be in a gang use these commands.");
				}
			}			
			else if(!strcmp(commandSelection, "join", true))
			{
				if(playerData[playerid][playerGang] == INVALID_GANG_ID)
				{
					new gangToJoin;
					
					if(!sscanf(params, "s[128] i", commandSelection, gangToJoin))
					{
						if(gangToJoin < MAX_GANGS && gangToJoin >= 0)
						{
							if(gangData[gangToJoin][gangScore] != -1)
							{
								if(gangData[gangToJoin][currentInvites][playerid] == 1)
								{
									if(gangCount(gangToJoin) <= gangData[gangToJoin][gangSlot])
									{
										new joinedMessage[128];
										
										gangData[gangToJoin][currentInvites][playerid] = 0;
										gangData[gangToJoin][gangMembers][playerid] = 1;
										playerData[playerid][playerGang] = gangToJoin;
										
										format(joinedMessage, sizeof(joinedMessage), "{39BBEE}[GANG] {FFFFFF}%s(%i) has joined %s.", playerData[playerid][playerNamee], playerid, gangData[gangToJoin][gangName]);
										sendMessageToGangMembers(playerData[playerid][playerGang], joinedMessage);
										savePlayerStats(playerid);
									}
									else
										SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}Gang slot is full.");
								}
								else
								{
									SendClientMessage(playerid, COLOR_WHITE, "{39BBEE}[GANG] {FFFFFF}You have not been invited to join this gang.");
								}
							}
							else
							{
								SendClientMessage(playerid, COLOR_WHITE, "{39BBEE}[GANG] {FFFFFF}The gang you're trying to join doesn't exist.");
							}
						}
						else
						{
							SendClientMessage(playerid, COLOR_WHITE, "{39BBEE}[GANG] {FFFFFF}The gang you're trying to join doesn't exist.");
						}
					}
					else
					{
						SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}Usage: /g(ang) join [GANG_ID]");
					}
				}
				else
				{
					SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}You're already in a gang, you cannot join another.");
				}
			}
			else if(!strcmp(commandSelection, "list", true))
			{
				new ids[MAX_GANGS] = {-1, ...}, x = 0, y = 0;
				for(new i = 0; i < MAX_GANGS; i++)
				{
					if(gangData[i][gangScore] == -1)
						continue;

					for(x = MAX_GANGS - 1; x >= 0; x--)
					{
						if(gangData[i][gangScore] > ids[x])
						{
							for(y = 1; y <= x; y++)
								ids[y - 1] = ids[y];
							ids[x] = i;
							break;
						}
					}
				}
				new msg[512];
				format(msg, 512, "Gang ID\tGang Name\tScore\n");
				for(x = MAX_GANGS - 1; x >= 0; x--)
				{
					if(ids[x] != -1)
						format(msg, 512, "%s%d\t{%s}%s\t%d\n", msg, gangData[ids[x]][gangID], gangData[ids[x]][gangColor], gangData[ids[x]][gangName], gangData[ids[x]][gangScore]);
				}
				ShowPlayerDialog(playerid, 200, DIALOG_STYLE_TABLIST_HEADERS, "Gang List", msg, "Close", "");
			}
			else if(!strcmp(commandSelection, "help", true))
			{
				SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}/g(ang) [CREATE/INVITE/LEADER/KICK/DISBAND/LEAVE/JOIN/HELP/LIST/STATS/PROMOTE/DEMOTE]");
			}
			else if(!strcmp(commandSelection, "stats", true))
			{
				new str[128];
				if(!sscanf(params, "s[128] s[128]", commandSelection, str))
				{
					for(new x = 0; x < MAX_GANGS; x++)
					{
						if(gangData[x][gangScore] != -1)
						{
							if(!strcmp(gangData[x][gangName], str, true))
							{
								new fmt[512];
								format(fmt, 512, "{%s}%s {FFFFFF}Gang Statistic\n\n", gangData[x][gangColor], gangData[x][gangName]);
								format(fmt, 512, "%sGang Slot: {58D3F7}%d/%d\n", fmt, gangCount(x), gangData[x][gangSlot]);
								format(fmt, 512, "%s{FFFFFF}Gang Kills: {58D3F7}%d\n", fmt, gangData[x][gangKill]);
								format(fmt, 512, "%s{FFFFFF}Gang Deaths: {58D3F7}%d\n", fmt, gangData[x][gangDeath]);
								format(fmt, 512, "%s{FFFFFF}Gang K/D Ratio: {58D3F7}%.2f\n", fmt, float(gangData[x][gangKill]) / float(gangData[x][gangDeath]));
								format(fmt, 512, "%s{FFFFFF}Gang Score: {58D3F7}%d\n\n\n", fmt, gangData[x][gangScore]);
								format(fmt, 512, "%sGang Members\n\n", fmt);
								new query[128];
								format(query, 128, "SELECT playerName, gangstatus FROM playerdata where gang = %d", gangData[x][gangID]);
								mysql_query(query, -1, -1, connection);
								mysql_store_result();
								new baris[512], pnama[MAX_PLAYER_NAME], pkil;
								while(mysql_fetch_row(baris, "|", connection))
								{
									sscanf(baris, "p<|>s[30]d", pnama, pkil);
									format(fmt, 512, "%s{FFFFFF}- %s ", fmt, pnama);
									switch(pkil)
									{
										case LEADER:
										{
											format(fmt, 512, "%s{58D3F7}(Leader)\n", fmt);
										}
										case STAFF:
										{
											format(fmt, 512, "%s{58D3F7}(Staff)\n", fmt);
										}
										default:
										{
											format(fmt, 512, "%s\n", fmt);
										}
									}
								}
								ShowPlayerDialog(playerid, 200, DIALOG_STYLE_MSGBOX, "Gang Statistic", fmt, "Close", "");
								mysql_free_result();
								return 1;
							}
						}
					}
				}
				else
					SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}Usage: /g(ang) stats [GANG_NAME]");
			}
			else
			{
				if(playerData[playerid][playerGang] != INVALID_GANG_ID)
				{
					//new gangMessage[128];
					format(gangMessage, sizeof(gangMessage), "{39BBEE}[Gang Chat] {FFFFFF}%s: %s", playerData[playerid][playerNamee], params);
					sendMessageToGangMembers(playerData[playerid][playerGang], gangMessage);
					
					new loggingString[256];
					format(loggingString, sizeof(loggingString), "[Gang Chat] %s: %s", playerData[playerid][playerNamee], gangMessage, input);
					writeInLog("gangchat.html", loggingString);
				}
				else
				{
					SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}/g(ang) [CREATE/INVITE/LEADER/KICK/DISBAND/LEAVE/JOIN/HELP/LIST/STATS/PROMOTE/DEMOTE]");
				}

				for(new i = 0; i <= MAX_PLAYERS; i++)
				{
					if(IsPlayerConnected(i))
					{
					    if(playerData[playerid][playerGang] != INVALID_GANG_ID)
					    {
							if(playerData[i][playerLoggedIn])
							{
								if (playerData[i][playerLevel] >= 4)
								{
									if (playerData[i][gangspy])
									{
										new gangtext[200];
										format(gangtext, sizeof(gangtext), "{FFBF00}[GANG SPY]> %s", gangMessage, input);
										SendClientMessage(i, COLOR_WHITE, gangtext);
									}
								}
							}
						}
					}
				}
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}/g(ang) [CREATE/INVITE/LEADER/KICK/DISBAND/LEAVE/JOIN/HELP/LIST/STATS/PROMOTE/DEMOTE]");
		}
	}	
	return 1;
}

COMMAND:capture(playerid, params[])
{
	if(playerData[playerid][playerGang] != INVALID_GANG_ID)
	{
		if(playerData[playerid][playerGrank] == LEADER || playerData[playerid][playerGrank] == STAFF)
		{
			new gang = playerData[playerid][playerGang];

			if(!gangData[gang][gangLocked])
			{
				for (new zone=0; zone<MAX_ZONES; zone++) {
					if(IsPlayerInDynamicArea(playerid, zoneData[zone][zoneArea]))
					{
						if(gang != zoneData[zone][zoneGang])
						{
							if(!zoneData[zone][zoneLocked])
							{
								gangData[gang][gangLocked] = true;
								zoneData[zone][zoneLocked] = true;
								zoneData[zone][zoneAttacker] = gang;
								zoneData[zone][zoneTime] = 120;
								zoneData[zone][zoneTimer] = SetTimerEx("AttackingZones", 1000, true, "d", zone);
								new gcolour[10], str[128];
								format(gcolour, 10, "%s50", gangData[gang][gangColor]);
								GangZoneFlashForAll(zoneData[zone][zoneGangZone], HexToInt(gcolour));
								format(str, 128, "{39BBEE}[GANG WAR] {FFFFFF}%s gang is attacking %s territory", gangData[gang][gangName], zoneData[zone][zoneName]);
								SendClientMessageToAll(-1, str);
								if(zoneData[zone][zoneGang] != -1)
								{
									format(str, 128, "{FF0000}[GANG ATTACK] {FFFFFF}%s gang is attacking your gang territory (%s)", gangData[gang][gangName], zoneData[zone][zoneName]);
									sendMessageToGangMembers(zoneData[zone][zoneGang], str);
								}
								break;
							}
							else
							{
								SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}This zone is locked.");
							}
						}
						else
						{
							SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}Your gang already owned this zone.");
						}
					}
				}
			}
			else
			{
				SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}Please wait before capturing another zones.");
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}You're not the leader / staff of this gang.");
		}
	}
	else
	{
		SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}You need to be in a gang use these commands.");
	}
	return 1;
}

COMMAND:territory(playerid, params[])
{
	new fmt[512], gid;
	for (new zone=0; zone<MAX_ZONES; zone++) {
		gid = zoneData[zone][zoneGang];
		if(gid != -1)
			format(fmt, 512, "%s{FFFFFF}%s - Owned by {%s}%s\n", fmt, zoneData[zone][zoneName], gangData[gid][gangColor], gangData[gid][gangName]);
		else
			format(fmt, 512, "%s{FFFFFF}%s - {FF0000}Unowned\n", fmt, zoneData[zone][zoneName]);
	}
	ShowPlayerDialog(playerid, 200, DIALOG_STYLE_MSGBOX, "CZCNR Territory", fmt, "Close", "");
	return 1;	
}