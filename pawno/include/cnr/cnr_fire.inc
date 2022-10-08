#define Labels // 3D Labels above the Fires showing the Health?
#define LoseHealth // Should Players and Vehicles lose Health if they stand in the fire?

#define Holding(%0) \
	((newkeys & (%0)) == (%0))
#define MaxFire 80 // How many fires max.?
#define MAX_FIRE_LOCS 6
forward OnFireKill(ID, killerid);
forward f_OnPlayerUpdate(playerid);
forward VehicleToPoint(Float:radi, vehicleid, Float:x, Float:y, Float:z);
forward HealthDown();
forward f_init();

enum FireE
{
	Float:FirePos1[3],
	Float:FirePos2[3],
	Float:FirePos3[3],
	FireLocation[128]
}
new Fire[MAX_FIRE_LOCS][FireE] =
{
	{{-1497.3844,912.7366,7.1875}, {-1499.1436,920.3471,7.1875}, {-1497.9602,926.9149,7.1875}, "The Bank"},
	{{-2454.9280,754.0857,35.1719}, {-2442.4792,749.1406,35.1786}, {-2430.9451,753.5032,35.1719}, "Supa Save"},
	{{-2630.1018,1399.5708,7.0994}, {-2619.9167,1414.8976,7.0938}, {-2623.4148,1427.1519,7.0938}, "Pleasure Dome"},
	{{-1981.5554,113.4200,27.6799}, {-1981.3134,122.8566,27.6875}, {-1981.3671,131.5959,27.6875}, "Cranberry Station"},
	{{-2633.5554,630.2707,14.4531}, {-2625.7234,630.3560,14.4531}, {-2617.7964,630.3829,14.4531}, "Hospital"},
	{{-2765.7717,375.5393,6.3347}, {-2765.6658,382.3404,6.3281}, {-2765.8542,368.8460,6.3347}, "City Hall"}
};


new
    FireObj[MaxFire],
    Float:FirePos[MaxFire][3],
	TotalFires = 0,
	FireHealth[MaxFire],
	FireHealthMax[MaxFire],
	AllFire,
	FireNow = -1,
	MinuteFire,
	LastLoc = -1;


public f_init()
{
	#if defined LoseHealth
		SetTimer("HealthDown", 600, 1);
	#endif
	FireNow = -1;
	AllFire = 0;
}
#if defined Labels
new Text3D:FireText[MaxFire];
#endif

stock AddFire(Float:x, Float:y, Float:z, Health)
{
    TotalFires++;
	new ID = TotalFires;
	FireObj[ID] = CreateObject(18689, x, y, z-2.61, 0, 0, 0.0);
	FirePos[ID][0] = x, FirePos[ID][1] = y, FirePos[ID][2] = z;
	FireHealth[ID] = Health;
	FireHealthMax[ID] = Health;
	#if defined Labels
	    new string[128];
	    format(string, sizeof(string), "%d/%d", FireHealth[ID], FireHealthMax[ID]);
	    FireText[ID] = Create3DTextLabel(string, 0xFFFFFFFF, x, y, z, 20, 0);
	#endif
}

stock DeleteFire(ID)
{
	DestroyObject(FireObj[ID]);
	TotalFires--;
	FirePos[ID][0] = 0, FirePos[ID][1] = 0, FirePos[ID][2] = 0;
	#if defined Labels
	    Delete3DTextLabel(FireText[ID]);
	#endif
}

stock DeleteAllFire()
{
	new ID;
	for(ID = 0; ID<MaxFire; ID++)
	{
		DestroyObject(FireObj[ID]);
		TotalFires= 0;
		FirePos[ID][0] = 0, FirePos[ID][1] = 0, FirePos[ID][2] = 0;
		#if defined Labels
	    	Delete3DTextLabel(FireText[ID]);
		#endif
	}
	MinuteFire = 0;
}

stock IsValidFire(ID)
{
	if( (FirePos[ID][0] != 0) && (FirePos[ID][1] != 0) && (FirePos[ID][2] != 0) ) return true;
	else return false;
}

stock GetClosestFire(playerid)
{
	new i;
	for(i = 0; i<MaxFire; i++)
	{
	    if(IsValidFire(i) && IsPlayerInRangeOfPoint(playerid, 1, FirePos[i][0],  FirePos[i][1],  FirePos[i][2]))
	    {
	        return i;
		}
	}
	return 0;
}


public f_OnPlayerUpdate(playerid)
{
	new newkeys,l,u;
	GetPlayerKeys(playerid, newkeys, l, u);
	new i;
	if(playerData[playerid][playerClass] != CLASS_FIREFIGHTER)
		return 1;

	if(Holding(KEY_FIRE))
	{
        if(GetPlayerWeapon(playerid) == 42)
        {
            for(i = 0; i < MaxFire; i++)
 	    	{
 	        	if(IsValidFire(i))
 	        	{
 	        	    if(PlayerFaces(playerid, FirePos[i][0],  FirePos[i][1],  FirePos[i][2], 1) && IsPlayerInRangeOfPoint(playerid, 4, FirePos[i][0],  FirePos[i][1],  FirePos[i][2]))
 	        		{
 	        			playerData[playerid][helpFireman] = true;
			    		FireHealth[i]-=2;
					    #if defined Labels
				    		new string[128];
					    	format(string, sizeof(string), "%d/%d", FireHealth[i], FireHealthMax[i]);
							Update3DTextLabelText(FireText[i], 0xFFFFFFFF, string);
					    #endif
					    if(FireHealth[i] <= 0)
					    {
							DeleteFire(i);
							CallRemoteFunction("OnFireDeath", "dd", i, playerid);
						}
					}
				}
			}
		}
		else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 407)
		{
		    new Float:fx, Float:fy, Float:fz;
		    GetPlayerCameraFrontVector(playerid, fx, fy, fz);
		    for(i = 0; i<MaxFire; i++)
 	    	{
 	        	if(IsValidFire(i))
 	        	{
 	        	    if(PlayerFaces(playerid, FirePos[i][0],  FirePos[i][1],  FirePos[i][2], 4.0)) // Range15.0
 	        		{
 	        			playerData[playerid][helpFireman] = true;
			    		FireHealth[i]-=4;
					    #if defined Labels
				    		new string[128];
					    	format(string, sizeof(string), "%d/%d", FireHealth[i], FireHealthMax[i]);
							Update3DTextLabelText(FireText[i], 0xFFFFFFFF, string);
					    #endif
					    if(FireHealth[i] <= 0)
					    {
							DeleteFire(i);
							CallRemoteFunction("OnFireDeath", "dd", i, playerid);
						}
					}
				}
			}
		}
	}
	return 1;
}


Float:DistanceCameraTargetToLocation(Float:CamX, Float:CamY, Float:CamZ,   Float:ObjX, Float:ObjY, Float:ObjZ,   Float:FrX, Float:FrY, Float:FrZ) {

	new Float:TGTDistance;
	TGTDistance = floatsqroot((CamX - ObjX) * (CamX - ObjX) + (CamY - ObjY) * (CamY - ObjY) + (CamZ - ObjZ) * (CamZ - ObjZ));
	new Float:tmpX, Float:tmpY, Float:tmpZ;
	tmpX = FrX * TGTDistance + CamX;
	tmpY = FrY * TGTDistance + CamY;
	tmpZ = FrZ * TGTDistance + CamZ;
	return floatsqroot((tmpX - ObjX) * (tmpX - ObjX) + (tmpY - ObjY) * (tmpY - ObjY) + (tmpZ - ObjZ) * (tmpZ - ObjZ));
}

stock PlayerFaces(playerid, Float:x, Float:y, Float:z, Float:radius)
{
    new Float:cx,Float:cy,Float:cz,Float:fx,Float:fy,Float:fz;
    GetPlayerCameraPos(playerid, cx, cy, cz);
    GetPlayerCameraFrontVector(playerid, fx, fy, fz);
    return (radius >= DistanceCameraTargetToLocation(cx, cy, cz, x, y, z, fx, fy, fz));
}

public VehicleToPoint(Float:radi, vehicleid, Float:x, Float:y, Float:z)
{
		new Float:oldposx, Float:oldposy, Float:oldposz;
		new Float:tempposx, Float:tempposy, Float:tempposz;
		GetVehiclePos(vehicleid, oldposx, oldposy, oldposz);
		tempposx = (oldposx -x);
		tempposy = (oldposy -y);
		tempposz = (oldposz -z);
		//printf("DEBUG: X:%f Y:%f Z:%f",posx,posy,posz);
		if (((tempposx < radi) && (tempposx > -radi)) && ((tempposy < radi) && (tempposy > -radi)) && ((tempposz < radi) && (tempposz > -radi)))
		{
			return 1;
		}
		return 0;
}

public HealthDown()
{
	new i,v,p;
	for(i = 0; i<MaxFire; i++)
	{
		if(IsValidFire(i))
		{
			for(p = 0; p<MAX_PLAYERS; p++)
			{
				if(IsPlayerInRangeOfPoint(p, 1, FirePos[i][0], FirePos[i][1], FirePos[i][2]) && !IsPlayerInAnyVehicle(p))
				{
	  				new Float:HP;
		    		GetPlayerHealth(p, HP);
	  				SetPlayerHealth(p, HP-4);
				}
			}
			for(v = 0; v<MAX_VEHICLES; v++)
			{
				if(VehicleToPoint(2, v, FirePos[i][0], FirePos[i][1], FirePos[i][2]))
				{
					new Float:HP;
		    		GetVehicleHealth(v, HP);
	  				SetVehicleHealth(v, HP-30);
				}
			}
		}
	}
}

/*COMMAND:cancelfire(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(!playerData[playerid][isInEvent])
		{
			if(playerData[playerid][playerClass] == CLASS_FIREFIGHTER)
			{
				if(!playerData[playerid][fireOnMission])
					return SendClientMessage(playerid, 0xFFFFFFFF, "{FFDC2E}[MISSION] {ffffff}You aren't on a mission, use /fire to start mission!"), 1;

				new found = false;
				playerData[playerid][fireOnMission] = false;
				foreach(new i : Player)
				{
					if(playerData[i][fireOnMission])
						found = true;
				}
				playerData[playerid][fireTotal] = false;
				SendClientMessage(playerid, 0xFFFFFFFF, "{FFDC2E}[MISSION] {ffffff}You canceled the mission!");
				RemovePlayerMapIcon(playerid, 69);
				if(!found)
					DeleteAllFire();
			}
			else
			{
				SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}Only fireman can use this command.");
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot do this whilst in an event.");
		}
	}
	return 1;
}*/

COMMAND:fire(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(!playerData[playerid][isInEvent])
		{
			if(playerData[playerid][playerClass] == CLASS_FIREFIGHTER)
			{
				//if(playerData[playerid][fireOnMission])
					//return SendClientMessage(playerid, 0xFFFFFFFF, "{FFDC2E}[MISSION] {ffffff}You already on mission, use /cancelfire to cancel mission!"), 1;

				new msg[128], rand = FireNow;
				if(rand == -1)
				{
					rand = random(MAX_FIRE_LOCS);
					while(LastLoc == rand)
					{
						rand = random(MAX_FIRE_LOCS);
					}
					FireNow = LastLoc = rand;
					AddFire(Fire[rand][FirePos1][0], Fire[rand][FirePos1][1], Fire[rand][FirePos1][2], 1000);
					AddFire(Fire[rand][FirePos2][0], Fire[rand][FirePos2][1], Fire[rand][FirePos2][2], 1000);
					AddFire(Fire[rand][FirePos3][0], Fire[rand][FirePos3][1], Fire[rand][FirePos3][2], 1000);
					MinuteFire = 3;
					SetTimer("NoticeFireman", 60 * 1000, false);
					format(msg, 128, "{FFDC2E}[DISPATCH]{FFFFFF} %s is on fire! You have %d minute(s) left to extinguish the fire!", Fire[rand][FireLocation], MinuteFire);
					GameTextForPlayer(playerid, "~r~FIRE!!!~n~~w~Go to the red marker on map!", 3000, 3);
					//
					// Remove map icon
					RemovePlayerMapIcon(playerid, 69);

					//
					// Set map icon
					SetPlayerMapIcon(playerid, 69, Fire[rand][FirePos1][0], Fire[rand][FirePos1][1], Fire[rand][FirePos1][2], 20, 0, MAPICON_GLOBAL);

				}
				else
				{
					format(msg, 128, "{FFDC2E}[DISPATCH]{FFFFFF} %s is on fire! You have %d minute(s) left to extinguish the fire!", Fire[rand][FireLocation], MinuteFire);
				}
				playerData[playerid][fireOnMission] = true;
				playerData[playerid][fireTotal] = 0;
				playerData[playerid][helpFireman] = false;
				SendClientMessage(playerid, -1, msg);
			}
			else
			{
				SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}Only fireman can use this command.");
			}
		}
		else
		{
			SendClientMessage(playerid, COLOR_WHITE, "{FF0404}[ERROR] {FFFF00}You cannot do this whilst in an event.");
		}
	}
	return 1;
}

forward NoticeFireman();
public NoticeFireman()
{
	MinuteFire--;
	new msg[128], rand = FireNow;
	format(msg, 128, "{FFDC2E}[MISSION]{FFFFFF} You have %d minute(s) left to extinguish %s", MinuteFire, Fire[rand][FireLocation]);
	if(MinuteFire <= 0)
	{
		ResetFire();
		return;
	}
	else
	{
		SetTimer("NoticeFireman", 60 * 1000, false);
 }

	foreach(new i : Player)
	{
		if(playerData[i][fireOnMission])
			SendClientMessage(i, 0xFFFFFFFF, msg);
	}
}

forward ResetFire();
public ResetFire()
{
	foreach(new i : Player)
	{
		if(playerData[i][fireOnMission])
		{
			GameTextForPlayer(i, "~r~MISSION FAILED!~n~You are too late to extinguish all fire!", 5000, 3);
			playerData[i][fireOnMission] = false;
			playerData[i][fireTotal] = 0;
			RemovePlayerMapIcon(i, 69);
		}
	}
	MinuteFire = 0;
	AllFire = 0;
	FireNow = -1;
	DeleteAllFire();
}

forward OnFireDeath(f, playerid);
public OnFireDeath(f, playerid)
{
	AllFire++;
	new msg[128], rand = FireNow;
	format(msg, 128, "{FFDC2E}[MISSION]{FFFFFF} Fire on %s is extinguished!", Fire[rand][FireLocation]);
	foreach(new i : Player)
	{
		if(playerData[i][playerClass] == CLASS_FIREFIGHTER && playerData[i][helpFireman])
		{
			SendClientMessage(i, -1, "{EEEEEE}[MISSION] {FFFFFF}Fire extinguished! All emergency units on location got $2.000 as payment");
			playerGiveMoney(i, 2000);
			playerGiveXP(i, 20);
			playerData[i][helpFireman] = false;
			playerData[i][playerScore] = playerData[i][playerScore] + 1;
			SetPlayerScore(i, playerData[i][playerScore]);
			playerData[i][fireTotal]++;
			if(AllFire == 3)
			{
				if(playerData[i][fireTotal] == 3)
				{
					SendClientMessage(i, -1, "{EEEEEE}[MISSION] {FFFFFF}You extinguished all 3 fires, you are rewarded $2.000");
					playerGiveMoney(i, 2000);
				}
				playerData[i][fireOnMission] = false;
				playerData[i][fireTotal] = 0;
				SendClientMessage(i, 0xFFFFFFFF, msg);
				RemovePlayerMapIcon(i, 69);
			}
		}
	}
	if(AllFire == 3)
	{
		AllFire = 0;
		FireNow = -1;
		MinuteFire = 0;
		
	}
}
