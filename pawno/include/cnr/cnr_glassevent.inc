new glassObject[232];

forward glassZChecker();
public glassZChecker()
{
	new Float:x, Float:y, Float:z;
	
	for(new i = 0; i < MAX_PLAYERS; i++)
	{
		if(IsPlayerConnected(i) && playerData[i][playerLoggedIn])
		{
			if (playerData[i][isInEvent])
			{
				if (GetPlayerVirtualWorld(i) == 500)
				{
					GetPlayerPos(i, x, y, z);
					
					if (z < 62.9024)
					{
						// Player has fallen
						SetPlayerVirtualWorld(i, 0);
						SetPlayerInterior(i, 0);
						
						playerData[i][hasSpawned] = false;
						SpawnPlayer(i);
						//SetPlayerHealth(i, 100);
						
						// Alert all those in DM this player was eliminated
						for (new p=0; p<MAX_PLAYERS; p++)
						{
							if(playerData[p][isInEvent])
							{
								new eliminated[100];
								format(eliminated, sizeof(eliminated), "{FAAC58}%s(%i) {FFFFFF}was eliminated from the event.", playerData[i][playerNamee], i);
								SendClientMessage(p, COLOR_WHITE, eliminated);
							}
						}						
					}
				}
			}
		}
	}
}

stock createGlass()
{
    glassObject[0] = CreateDynamicObject(1649, 1343.73621, 1533.04810, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[1] = CreateDynamicObject(1649, 1369.83630, 1536.32813, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[2] = CreateDynamicObject(1649, 1369.83630, 1539.64807, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[3] = CreateDynamicObject(1649, 1369.83630, 1542.96814, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[4] = CreateDynamicObject(1649, 1369.83630, 1546.26794, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[5] = CreateDynamicObject(1649, 1369.83630, 1549.54785, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[6] = CreateDynamicObject(1649, 1369.83630, 1552.84790, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[7] = CreateDynamicObject(1649, 1369.83630, 1556.16785, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[8] = CreateDynamicObject(1649, 1369.83630, 1559.46777, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[9] = CreateDynamicObject(1649, 1369.83630, 1562.76782, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[10] = CreateDynamicObject(1649, 1369.83630, 1566.06775, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[11] = CreateDynamicObject(1649, 1365.49634, 1536.32813, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[12] = CreateDynamicObject(1649, 1365.49634, 1539.64807, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[13] = CreateDynamicObject(1649, 1365.49634, 1542.96814, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[14] = CreateDynamicObject(1649, 1365.49634, 1546.26794, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[15] = CreateDynamicObject(1649, 1365.49634, 1549.54785, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[16] = CreateDynamicObject(1649, 1365.49634, 1552.84790, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[17] = CreateDynamicObject(1649, 1365.49634, 1556.16785, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[18] = CreateDynamicObject(1649, 1365.49634, 1559.46777, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[19] = CreateDynamicObject(1649, 1365.49634, 1562.76782, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[20] = CreateDynamicObject(1649, 1365.49634, 1566.06775, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[21] = CreateDynamicObject(1649, 1361.15625, 1536.32813, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[22] = CreateDynamicObject(1649, 1361.15625, 1539.64807, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[23] = CreateDynamicObject(1649, 1361.15625, 1542.96814, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[24] = CreateDynamicObject(1649, 1361.15625, 1546.26794, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[25] = CreateDynamicObject(1649, 1361.15625, 1549.54785, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[26] = CreateDynamicObject(1649, 1361.15625, 1552.84790, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[27] = CreateDynamicObject(1649, 1361.15625, 1556.16785, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[28] = CreateDynamicObject(1649, 1361.15625, 1559.46777, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[29] = CreateDynamicObject(1649, 1361.15625, 1562.76782, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[30] = CreateDynamicObject(1649, 1361.15625, 1566.06775, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[31] = CreateDynamicObject(1649, 1356.77625, 1536.32813, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[32] = CreateDynamicObject(1649, 1356.77625, 1539.64807, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[33] = CreateDynamicObject(1649, 1356.77625, 1542.96814, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[34] = CreateDynamicObject(1649, 1356.77625, 1546.26794, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[35] = CreateDynamicObject(1649, 1356.77625, 1549.54785, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[36] = CreateDynamicObject(1649, 1356.77625, 1552.84790, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[37] = CreateDynamicObject(1649, 1356.77625, 1556.16785, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[38] = CreateDynamicObject(1649, 1356.77625, 1559.46777, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[39] = CreateDynamicObject(1649, 1356.77625, 1562.76782, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[40] = CreateDynamicObject(1649, 1356.77625, 1566.06775, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[41] = CreateDynamicObject(1649, 1352.43616, 1536.32813, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[42] = CreateDynamicObject(1649, 1352.43616, 1539.64807, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[43] = CreateDynamicObject(1649, 1352.43616, 1542.96814, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[44] = CreateDynamicObject(1649, 1352.43616, 1546.26794, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[45] = CreateDynamicObject(1649, 1352.43616, 1549.54785, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[46] = CreateDynamicObject(1649, 1352.43616, 1552.84790, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[47] = CreateDynamicObject(1649, 1352.43616, 1556.16785, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[48] = CreateDynamicObject(1649, 1352.43616, 1559.46777, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[49] = CreateDynamicObject(1649, 1352.43616, 1562.76782, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[50] = CreateDynamicObject(1649, 1352.43616, 1566.06775, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[51] = CreateDynamicObject(1649, 1348.07617, 1536.32813, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[52] = CreateDynamicObject(1649, 1348.07617, 1539.64807, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[53] = CreateDynamicObject(1649, 1348.07617, 1542.96814, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[54] = CreateDynamicObject(1649, 1348.07617, 1546.26794, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[55] = CreateDynamicObject(1649, 1348.07617, 1549.54785, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[56] = CreateDynamicObject(1649, 1348.07617, 1552.84790, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[57] = CreateDynamicObject(1649, 1348.07617, 1556.16785, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[58] = CreateDynamicObject(1649, 1348.07617, 1559.46777, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[59] = CreateDynamicObject(1649, 1348.07617, 1562.76782, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[60] = CreateDynamicObject(1649, 1348.07617, 1566.06775, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[61] = CreateDynamicObject(1649, 1369.83630, 1533.04810, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[62] = CreateDynamicObject(1649, 1365.49634, 1533.04810, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[63] = CreateDynamicObject(1649, 1361.15625, 1533.04810, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[64] = CreateDynamicObject(1649, 1356.77625, 1533.04810, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[65] = CreateDynamicObject(1649, 1352.43616, 1533.04810, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[66] = CreateDynamicObject(1649, 1348.07617, 1533.04810, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[67] = CreateDynamicObject(1649, 1343.73621, 1533.04810, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[68] = CreateDynamicObject(1649, 1343.73621, 1536.32813, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[69] = CreateDynamicObject(1649, 1343.73621, 1539.64807, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[70] = CreateDynamicObject(1649, 1343.73621, 1542.96814, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[71] = CreateDynamicObject(1649, 1343.73621, 1546.26794, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[72] = CreateDynamicObject(1649, 1343.73621, 1549.54785, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[73] = CreateDynamicObject(1649, 1343.73621, 1552.84790, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[74] = CreateDynamicObject(1649, 1343.73621, 1556.16785, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[75] = CreateDynamicObject(1649, 1343.73621, 1559.46777, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[76] = CreateDynamicObject(1649, 1343.73621, 1562.76782, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[77] = CreateDynamicObject(1649, 1343.73621, 1566.06775, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[78] = CreateDynamicObject(1649, 1343.73621, 1533.04810, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[79] = CreateDynamicObject(1649, 1343.73621, 1536.32813, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[80] = CreateDynamicObject(1649, 1343.73621, 1539.64807, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[81] = CreateDynamicObject(1649, 1343.73621, 1542.96814, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[82] = CreateDynamicObject(1649, 1343.73621, 1546.26794, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[83] = CreateDynamicObject(1649, 1343.73621, 1549.54785, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[84] = CreateDynamicObject(1649, 1343.73621, 1552.84790, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[85] = CreateDynamicObject(1649, 1343.73621, 1556.16785, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[86] = CreateDynamicObject(1649, 1343.73621, 1559.46777, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[87] = CreateDynamicObject(1649, 1343.73621, 1562.76782, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[88] = CreateDynamicObject(1649, 1343.73621, 1566.06775, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[89] = CreateDynamicObject(1649, 1348.07617, 1533.04810, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[90] = CreateDynamicObject(1649, 1348.07617, 1536.32813, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[91] = CreateDynamicObject(1649, 1348.07617, 1539.64807, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[92] = CreateDynamicObject(1649, 1348.07617, 1542.96814, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[93] = CreateDynamicObject(1649, 1348.07617, 1546.26794, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[94] = CreateDynamicObject(1649, 1348.07617, 1549.54785, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[95] = CreateDynamicObject(1649, 1348.07617, 1552.84790, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[96] = CreateDynamicObject(1649, 1348.07617, 1556.16785, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[97] = CreateDynamicObject(1649, 1348.07617, 1559.46777, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[98] = CreateDynamicObject(1649, 1348.07617, 1562.76782, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[99] = CreateDynamicObject(1649, 1348.07617, 1566.06775, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[100] = CreateDynamicObject(1649, 1352.43616, 1533.04810, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[101] = CreateDynamicObject(1649, 1352.43616, 1536.32813, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[102] = CreateDynamicObject(1649, 1352.43616, 1539.64807, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[103] = CreateDynamicObject(1649, 1352.43616, 1542.96814, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[104] = CreateDynamicObject(1649, 1352.43616, 1546.26794, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[105] = CreateDynamicObject(1649, 1352.43616, 1549.54785, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[106] = CreateDynamicObject(1649, 1352.43616, 1552.84790, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[107] = CreateDynamicObject(1649, 1352.43616, 1556.16785, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[108] = CreateDynamicObject(1649, 1352.43616, 1559.46777, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[109] = CreateDynamicObject(1649, 1352.43616, 1562.76782, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[110] = CreateDynamicObject(1649, 1352.43616, 1566.06775, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[111] = CreateDynamicObject(1649, 1356.77625, 1566.06775, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[112] = CreateDynamicObject(1649, 1356.77625, 1562.76782, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[113] = CreateDynamicObject(1649, 1356.77625, 1559.46777, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[114] = CreateDynamicObject(1649, 1356.77625, 1556.16785, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[115] = CreateDynamicObject(1649, 1356.77625, 1552.84790, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[116] = CreateDynamicObject(1649, 1356.77625, 1549.54785, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[117] = CreateDynamicObject(1649, 1356.77625, 1546.26794, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[118] = CreateDynamicObject(1649, 1356.77625, 1542.96814, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[119] = CreateDynamicObject(1649, 1356.77625, 1539.64807, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[120] = CreateDynamicObject(1649, 1356.77625, 1536.32813, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[121] = CreateDynamicObject(1649, 1356.77625, 1533.04810, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[122] = CreateDynamicObject(1649, 1361.15625, 1533.04810, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[123] = CreateDynamicObject(1649, 1361.15625, 1536.32813, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[124] = CreateDynamicObject(1649, 1361.15625, 1539.64807, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[125] = CreateDynamicObject(1649, 1361.15625, 1542.96814, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[126] = CreateDynamicObject(1649, 1361.15625, 1546.26794, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[127] = CreateDynamicObject(1649, 1361.15625, 1549.54785, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[128] = CreateDynamicObject(1649, 1361.15625, 1552.84790, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[129] = CreateDynamicObject(1649, 1361.15625, 1556.16785, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[130] = CreateDynamicObject(1649, 1361.15625, 1559.46777, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[131] = CreateDynamicObject(1649, 1361.15625, 1562.76782, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[132] = CreateDynamicObject(1649, 1361.15625, 1566.06775, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[133] = CreateDynamicObject(1649, 1365.49634, 1566.06775, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[134] = CreateDynamicObject(1649, 1365.49634, 1562.76782, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[135] = CreateDynamicObject(1649, 1365.49634, 1559.46777, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[136] = CreateDynamicObject(1649, 1365.49634, 1556.16785, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[137] = CreateDynamicObject(1649, 1365.49634, 1552.84790, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[138] = CreateDynamicObject(1649, 1365.49634, 1549.54785, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[139] = CreateDynamicObject(1649, 1365.49634, 1546.26794, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[140] = CreateDynamicObject(1649, 1365.49634, 1542.96814, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[141] = CreateDynamicObject(1649, 1365.49634, 80.78530, 100.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[142] = CreateDynamicObject(1649, 1365.49634, 1536.32813, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[143] = CreateDynamicObject(1649, 1365.49634, 1533.04810, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[144] = CreateDynamicObject(1649, 1365.49634, 1539.64807, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[145] = CreateDynamicObject(1649, 1369.83630, 1533.04810, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[146] = CreateDynamicObject(1649, 1369.83630, 1536.32813, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[147] = CreateDynamicObject(1649, 1369.83630, 1539.64807, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[148] = CreateDynamicObject(1649, 1369.83630, 1542.96814, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[149] = CreateDynamicObject(1649, 1369.83630, 1546.26794, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[150] = CreateDynamicObject(1649, 1369.83630, 1549.54785, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[151] = CreateDynamicObject(1649, 1369.83630, 1552.84790, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[152] = CreateDynamicObject(1649, 1369.83630, 1556.16785, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[153] = CreateDynamicObject(1649, 1369.83630, 1559.46777, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[154] = CreateDynamicObject(1649, 1369.83630, 1562.76782, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[155] = CreateDynamicObject(1649, 1369.83630, 1566.06775, 80.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[156] = CreateDynamicObject(1649, 1369.83630, 1566.06775, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[157] = CreateDynamicObject(1649, 1369.83630, 1562.76782, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[158] = CreateDynamicObject(1649, 1369.83630, 1559.46777, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[159] = CreateDynamicObject(1649, 1369.83630, 1556.16785, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[160] = CreateDynamicObject(1649, 1369.83630, 1552.84790, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[161] = CreateDynamicObject(1649, 1369.83630, 1549.54785, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[162] = CreateDynamicObject(1649, 1369.83630, 1546.26794, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[163] = CreateDynamicObject(1649, 1369.83630, 1542.96814, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[164] = CreateDynamicObject(1649, 1369.83630, 1539.64807, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[165] = CreateDynamicObject(1649, 1369.83630, 1536.32813, 120.78530,   -90.00000, 0.06000, 0.00000, 500);
	glassObject[166] = CreateDynamicObject(1649, 1369.83630, 1533.04810, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[167] = CreateDynamicObject(1649, 1365.49634, 1533.04810, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[168] = CreateDynamicObject(1649, 1365.49634, 1536.32813, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[169] = CreateDynamicObject(1649, 1365.49634, 1539.64807, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[170] = CreateDynamicObject(1649, 1365.49634, 1542.96814, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[171] = CreateDynamicObject(1649, 1365.49634, 1546.26794, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[172] = CreateDynamicObject(1649, 1365.49634, 1549.54785, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[173] = CreateDynamicObject(1649, 1365.49634, 1552.84790, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[174] = CreateDynamicObject(1649, 1365.49634, 1556.16785, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[175] = CreateDynamicObject(1649, 1365.49634, 1559.46777, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[176] = CreateDynamicObject(1649, 1365.49634, 1562.76782, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[177] = CreateDynamicObject(1649, 1365.49634, 1566.06775, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[178] = CreateDynamicObject(1649, 1361.15625, 1566.06775, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[179] = CreateDynamicObject(1649, 1361.15625, 1562.76782, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[180] = CreateDynamicObject(1649, 1361.15625, 1559.46777, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[181] = CreateDynamicObject(1649, 1361.15625, 1556.16785, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[182] = CreateDynamicObject(1649, 1361.15625, 1552.84790, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[183] = CreateDynamicObject(1649, 1361.15625, 1549.54785, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[184] = CreateDynamicObject(1649, 1361.15625, 1546.26794, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[185] = CreateDynamicObject(1649, 1361.15625, 1542.96814, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[186] = CreateDynamicObject(1649, 1361.15625, 1539.64807, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[187] = CreateDynamicObject(1649, 1361.15625, 1536.32813, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[188] = CreateDynamicObject(1649, 1361.15625, 1533.04810, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[189] = CreateDynamicObject(1649, 1356.77625, 1533.04810, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[190] = CreateDynamicObject(1649, 1356.77625, 1536.32813, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[191] = CreateDynamicObject(1649, 1356.77625, 1539.64807, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[192] = CreateDynamicObject(1649, 1356.77625, 1542.96814, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[193] = CreateDynamicObject(1649, 1356.77625, 1546.26794, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[194] = CreateDynamicObject(1649, 1356.77625, 1549.54785, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[195] = CreateDynamicObject(1649, 1356.77625, 1552.84790, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[196] = CreateDynamicObject(1649, 1356.77625, 1556.16785, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[197] = CreateDynamicObject(1649, 1356.77625, 1559.46777, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[198] = CreateDynamicObject(1649, 1356.77625, 1562.76782, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[199] = CreateDynamicObject(1649, 1356.77625, 1566.06775, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[200] = CreateDynamicObject(1649, 1352.43616, 1566.06775, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[201] = CreateDynamicObject(1649, 1352.43616, 1562.76782, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[202] = CreateDynamicObject(1649, 1352.43616, 1559.46777, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[203] = CreateDynamicObject(1649, 1352.43616, 1556.16785, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[204] = CreateDynamicObject(1649, 1352.43616, 1552.84790, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[205] = CreateDynamicObject(1649, 1352.43616, 1549.54785, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[206] = CreateDynamicObject(1649, 1352.43616, 1546.26794, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[207] = CreateDynamicObject(1649, 1352.43616, 1542.96814, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[208] = CreateDynamicObject(1649, 1352.43616, 1539.64807, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[209] = CreateDynamicObject(1649, 1352.43616, 1536.32813, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[210] = CreateDynamicObject(1649, 1352.43616, 1533.04810, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[211] = CreateDynamicObject(1649, 1348.07617, 1533.04810, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[212] = CreateDynamicObject(1649, 1348.07617, 1536.32813, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[213] = CreateDynamicObject(1649, 1348.07617, 1539.64807, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[214] = CreateDynamicObject(1649, 1348.07617, 1542.96814, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[215] = CreateDynamicObject(1649, 1348.07617, 1546.26794, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[216] = CreateDynamicObject(1649, 1348.07617, 1549.54785, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[217] = CreateDynamicObject(1649, 1348.07617, 1552.84790, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[218] = CreateDynamicObject(1649, 1348.07617, 1556.16785, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[219] = CreateDynamicObject(1649, 1348.07617, 1559.46777, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[220] = CreateDynamicObject(1649, 1348.07617, 1562.76782, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[221] = CreateDynamicObject(1649, 1348.07617, 1566.06775, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[222] = CreateDynamicObject(1649, 1343.73621, 1566.06775, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[223] = CreateDynamicObject(1649, 1343.73621, 1562.76782, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[224] = CreateDynamicObject(1649, 1343.73621, 1559.46777, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[225] = CreateDynamicObject(1649, 1343.73621, 1556.16785, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[226] = CreateDynamicObject(1649, 1343.73621, 1552.84790, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[227] = CreateDynamicObject(1649, 1343.73621, 1549.54785, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[228] = CreateDynamicObject(1649, 1343.73621, 1546.26794, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[229] = CreateDynamicObject(1649, 1343.73621, 1542.96814, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[230] = CreateDynamicObject(1649, 1343.73621, 1539.64807, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	glassObject[231] = CreateDynamicObject(1649, 1343.73621, 1536.32813, 120.78530,   -90.00000, 0.00000, 0.00000, 500);
	
}

stock destroyGlass()
{
    for(new i = 0; i < 232; i++)
    {
        DestroyDynamicObject(glassObject[i]);
    }	
	
	KillTimer(glassTimer);
}

COMMAND:glassevent(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(playerData[playerid][playerLevel] >= 4)
		{
			if (serverInfo[GlassEvent])
			{
				// Close Event
				serverInfo[GlassEvent] = 0;
				SendClientMessageToAll(COLOR_WHITE, "{58D3F7}[EVENT CLOSED] {FFFFFF}An administrator has closed the glass event.");
				TextDrawHideForAll(event1);
				TextDrawHideForAll(eventglass);
			}
			else
			{
				destroyGlass();
				createGlass();
						
				// Open Event
				serverInfo[GlassEvent] = 1;
				
				TextDrawShowForAll(event1);
				TextDrawShowForAll(eventglass);
				SendClientMessageToAll(COLOR_WHITE, "{58D3F7}[EVENT OPENED] {FFFFFF}An administrator has started a glass event! Type {FFDC2E}/joinglass{FFFFFF} to participate.");
				SendClientMessage(playerid, COLOR_WHITE, "{58D3F7}[EVENT HELP] {FFFFFF}To start the event, first type /glassevent again to close entry, then type /startglass to unfreeze players.");
				SendClientMessage(playerid, COLOR_WHITE, "{58D3F7}[EVENT HELP] {FFFFFF}When finished, please /destroyglass to free up object space.");
				
				GameTextForPlayer(playerid, "GLASS EVENT OPENED!", 5000, 5);
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

COMMAND:startglass(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(playerData[playerid][playerLevel] >= 4)
		{
			for(new i = 0; i < MAX_PLAYERS; i++)
			{
				if(IsPlayerConnected(i) && playerData[i][playerLoggedIn])
				{
					if (playerData[i][isInEvent])
					{	
						TogglePlayerControllable(i, 1);
						GameTextForPlayer(i, "GLASS EVENT STARTED!", 5000, 5);
						
						glassTimer = SetTimer("glassZChecker", 3000, true);
					}
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

COMMAND:destroyglass(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if(playerData[playerid][playerLevel] >= 4)
		{
			destroyGlass();
			
			SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}Glass destroyed.");
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

COMMAND:joinglass(playerid, params[])
{
	if(playerData[playerid][playerLoggedIn])
	{
		if (playerData[playerid][playerWantedLevel] == 0)
		{
			if (playerData[playerid][playerJailTime] < 1)
			{
				if (!playerData[playerid][isInDM])
				{
					if (serverInfo[GlassEvent])
					{
						// Can join event
						new randSpawn = random(16);
						switch(randSpawn)
						{
							case 0:
							{
								SetPlayerPos(playerid, 1369.2458,1543.2581,121.7853);
							}
							case 1:
							{
								SetPlayerPos(playerid, 1368.9705,1536.9867,121.7853);
							}
							case 2:
							{
								SetPlayerPos(playerid, 1362.3881,1536.2117,121.7853);
							}
							case 3:
							{
								SetPlayerPos(playerid, 1353.7930,1536.2815,121.7853);
							}
							case 4:
							{
								SetPlayerPos(playerid, 1345.2679,1536.1851,121.7853);
							}
							case 5:
							{
								SetPlayerPos(playerid, 1344.3031,1541.8740,121.7853);
							}
							case 6:
							{
								SetPlayerPos(playerid, 1344.0515,1549.2239,121.7853);
							}
							case 7:
							{
								SetPlayerPos(playerid, 1344.1140,1555.8215,121.7853);
							}
							case 8:
							{
								SetPlayerPos(playerid, 1343.8903,1562.3712,121.7853);
							}
							case 9:
							{
								SetPlayerPos(playerid, 1351.2740,1562.5129,121.7853);
							}
							case 10:
							{
								SetPlayerPos(playerid, 1360.0631,1562.7482,121.7853);
							}
							case 11:
							{
								SetPlayerPos(playerid, 1368.4116,1562.7269,121.7853);
							}
							case 12:
							{
								SetPlayerPos(playerid, 1369.0094,1557.1337,121.7853);
							}
							case 13:
							{
								SetPlayerPos(playerid, 1362.0298,1555.7686,121.7853);
							}
							case 14:
							{
								SetPlayerPos(playerid, 1353.4861,1555.7090,121.7853);
							}
							case 15:
							{
								SetPlayerPos(playerid, 1348.0072,1556.0461,121.7853);
							}
							case 16:
							{
								SetPlayerPos(playerid, 1351.2379,1550.5306,121.7853);
							}
							case 17:
							{
								SetPlayerPos(playerid, 1356.5472,1546.4508,121.7853);
							}
							case 18:
							{
								SetPlayerPos(playerid, 1361.5311,1542.7629,121.7853);
							}
							case 19:
							{
								SetPlayerPos(playerid, 1361.5311,1542.7629,121.7853);
							}
						}
						
						// No team during DM
						SetPlayerTeam(playerid, NO_TEAM);
						
						SetPlayerVirtualWorld(playerid, 500);
						
						playerData[playerid][isInEvent] = true;
						TogglePlayerControllable(playerid, 0);
						
						// Remove armour
						SetPlayerArmour(playerid, 0);
						SetPlayerHealth(playerid, 5000);
						
						ResetPlayerWeapons(playerid);
						playerData[playerid][adminWeapon] = true;
						GivePlayerWeaponEx(playerid, 25, 5000);
						
						GameTextForPlayer(playerid, "THE EVENT WILL START SHORTLY!~n~~P~You are temporarily frozen", 10000, 5);
					}
					else
					{
						SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}There is no glass event open right now.");
					}
				}
				else
				{
					SendClientMessage(playerid, COLOR_WHITE, "{B7B7B7}[SERVER] {FFFFFF}Please leave the minigames arena before joining the glass event.");
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

