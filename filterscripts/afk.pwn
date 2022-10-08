#include a_samp
#include zcmd

#define blue   0x375FFFFF
#define blue1  {00FFFF}
#define yellow {FFFF00}

#define afkdialog 1165

new afk[MAX_PLAYERS];

new Text3D:label[MAX_PLAYERS];

CMD:afk(playerid,params[])
{
    if(afk[playerid] == 1) return SendClientMessage(playerid,blue, "You alrady afk.");
	ShowPlayerDialog(playerid, afkdialog, DIALOG_STYLE_INPUT, "{00FFFF}Reason:", "{FFFF00}Please Type the reason of your afk", "Done", "Exit");
	return 1;
}
CMD:back(playerid,params[])
{
    if(afk[playerid] == 0) return SendClientMessage(playerid,blue, "You are not afk.");
    new string[128],pname[32];
    GetPlayerName(playerid,pname,sizeof(pname));
	format(string,sizeof(string),"%s {00FFFF}Is now Back.",pname);
	SendClientMessageToAll(blue, string);
	Delete3DTextLabel(label[playerid]);
	TogglePlayerControllable(playerid,1);
	afk[playerid] = 0;
	return 1;
}
public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(dialogid == afkdialog) {
		if(response == 0) {
			new string[128],pname[32];
			GetPlayerName(playerid,pname,sizeof(pname));
			format(string,sizeof(string),"%s {00FFFF}Is now Away from Keyboard.",pname);
			SendClientMessageToAll(blue, string);
			label[playerid] = Create3DTextLabel(" ",0xFF0000FF,30.0,40.0,50.0,15.0,0);
			Update3DTextLabelText(label[playerid], 0xFF0000FF, "AFK");
	        Attach3DTextLabelToPlayer(label[playerid], playerid, 0.0, 0.0, 0.4);
	        SendClientMessage(playerid, blue, "Type /back when you back :)");
	        TogglePlayerControllable(playerid,0);
	        afk[playerid] = 1;
	        return 1;
		}
		else if(response == 1) {
		if(!strlen(inputtext)) {
		new string[128],pname[32];
		GetPlayerName(playerid,pname,sizeof(pname));
		format(string,sizeof(string),"%s {00FFFF}Is now Away from Keyboard.",pname);
		SendClientMessageToAll(blue, string);
		label[playerid] = Create3DTextLabel(" ",0xFF0000FF,30.0,40.0,50.0,15.0,0);
		Update3DTextLabelText(label[playerid], 0xFF0000FF, "AFK");
	    Attach3DTextLabelToPlayer(label[playerid], playerid, 0.0, 0.0, 0.4);
	    SendClientMessage(playerid, blue, "Type /back when you back :)");
	    TogglePlayerControllable(playerid,0);
	    afk[playerid] = 1;
        } else if(strlen(inputtext))
		     {
	         new string[128],pname[32];
	         GetPlayerName(playerid,pname,sizeof(pname));
	         format(string,sizeof(string),"%s {00FFFF}Is now Away from Keyboard. {FFFF00}|-Reason: %s -|",pname,inputtext);
	         SendClientMessageToAll(blue, string);
             label[playerid] = Create3DTextLabel(" ",0xFF0000FF,30.0,40.0,50.0,15.0,0);
             format(string,sizeof(string),"AFK.|-Reason: %s -|",inputtext);
             Update3DTextLabelText(label[playerid], 0xFF0000FF, string);
             Attach3DTextLabelToPlayer(label[playerid], playerid, 0.0, 0.0, 0.4);
             SendClientMessage(playerid, blue, "Type /back when you back :)");
             TogglePlayerControllable(playerid,0);
             afk[playerid] = 1;
             return 1;
		 }
	  }
	}
	return 1;
}
public OnPlayerConnect(playerid)
{
 afk[playerid] = 0;
 return 1;
}
public OnPlayerDisconnect(playerid)
{
 afk[playerid] = 0;
 return 1;
}
public OnPlayerText(playerid, text[])
{
 if(afk[playerid] == 1) {
 SendClientMessage(playerid, blue, "You can't Speak while you are afk.");
 return 0;
 }
 return 1;
}
