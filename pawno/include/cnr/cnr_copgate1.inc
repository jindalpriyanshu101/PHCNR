

forward GateCheck();
public GateCheck()
{
	//Close
    for(new g=0, all=sizeof(gates); g<all; g++)
    {
        if(gates[g][ag_timer] && (gettime() > gates[g][ag_timer]))
        {
            if(gates[g][ag_status] == false)
            {
	        	gates[g][ag_timer] = 0;
				MoveObject(gates[g][ag_id], gates[g][agclosePos][0], gates[g][agclosePos][1], gates[g][agclosePos][2], 8.0);
			}
		}
    }
	//Open Gate Automatic to Player
	for(new i=0, t=GetMaxPlayers(); i<t; i++)
	{
	    if(!IsPlayerConnected(i)) continue;

	    for(new g=0, all=sizeof(gates); g<all; g++)
	    {
	        if(IsPlayerInRangeOfPoint(i, 10.0, gates[g][agclosePos][0], gates[g][agclosePos][1], gates[g][agclosePos][2])
	        {
	    		if((playerData[i][playerClass] == gates[g][ag_team]) && (gettime() > gates[g][ag_timer]))
	    		{
	    		    switch(gates[g][ag_status])
	    		    {
	    		        case false:
	    		        {
							gates[g][ag_timer] = gettime() + 5;//Wait 5sec.
	    		            MoveObject(gates[g][ag_id], gates[g][ag_openPos][0], gates[g][ag_openPos][1], gates[g][ag_openPos][2], 8.0);
	    		        }
	    		    }
	    		    return 1;
	    		}
			}
		}
	 }
	 return 1;
}


    
