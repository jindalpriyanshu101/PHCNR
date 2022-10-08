#define MAX_BUFFER 100

#define TEXTDRAWS_ANIMATION_0 0
#define TEXTDRAWS_ANIMATION_1 1

CreateDynamicTextdraws( index )
{
	switch( index )
	{
		case TEXTDRAWS_ANIMATION_0:
		{
			TDEditor_TD[0] = TextDrawCreate(250.800155, 0.346672, "Welcome");
TextDrawLetterSize(TDEditor_TD[0], 0.400000, 1.600000);
TextDrawAlignment(TDEditor_TD[0], 1);
TextDrawColor(TDEditor_TD[0], -16711681);
TextDrawSetShadow(TDEditor_TD[0], 0);
TextDrawSetOutline(TDEditor_TD[0], 0);
TextDrawBackgroundColor(TDEditor_TD[0], 255);
TextDrawFont(TDEditor_TD[0], 3);
TextDrawSetProportional(TDEditor_TD[0], 1);
TextDrawSetShadow(TDEditor_TD[0], 0);

TDEditor_TD[1] = TextDrawCreate(315.600097, 0.346642, "To");
TextDrawLetterSize(TDEditor_TD[1], 0.400000, 1.600000);
TextDrawAlignment(TDEditor_TD[1], 1);
TextDrawColor(TDEditor_TD[1], -65281);
TextDrawSetShadow(TDEditor_TD[1], 0);
TextDrawSetOutline(TDEditor_TD[1], 0);
TextDrawBackgroundColor(TDEditor_TD[1], 255);
TextDrawFont(TDEditor_TD[1], 3);
TextDrawSetProportional(TDEditor_TD[1], 1);
TextDrawSetShadow(TDEditor_TD[1], 0);

TDEditor_TD[2] = TextDrawCreate(338.000030, 0.346668, "United_States_CnR");
TextDrawLetterSize(TDEditor_TD[2], 0.400000, 1.600000);
TextDrawAlignment(TDEditor_TD[2], 1);
TextDrawColor(TDEditor_TD[2], -1523963137);
TextDrawSetShadow(TDEditor_TD[2], 0);
TextDrawSetOutline(TDEditor_TD[2], 0);
TextDrawBackgroundColor(TDEditor_TD[2], 255);
TextDrawFont(TDEditor_TD[2], 3);
TextDrawSetProportional(TDEditor_TD[2], 1);
TextDrawSetShadow(TDEditor_TD[2], 0);



//Player TextDraws:

TDEditor_PTD[playerid][0] = CreatePlayerTextDraw(playerid, 16.399974, 304.240142, "United_States_CnR");
PlayerTextDrawLetterSize(playerid, TDEditor_PTD[playerid][0], 0.638400, 3.399465);
PlayerTextDrawAlignment(playerid, TDEditor_PTD[playerid][0], 1);
PlayerTextDrawColor(playerid, TDEditor_PTD[playerid][0], 16777215);
PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][0], 0);
PlayerTextDrawSetOutline(playerid, TDEditor_PTD[playerid][0], 0);
PlayerTextDrawBackgroundColor(playerid, TDEditor_PTD[playerid][0], 16711935);
PlayerTextDrawFont(playerid, TDEditor_PTD[playerid][0], 0);
PlayerTextDrawSetProportional(playerid, TDEditor_PTD[playerid][0], 1);
PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][0], 0);
 return 1;	return 1;
}

public OnAnimFinish( playerid, index )
{
	switch( index )
	{
		case TEXTDRAWS_ANIMATION_0:
		{
			TextDraw_Grow(playerid,TEXTDRAWS_ANIMATION_1,100,2500, 0, 4, 1.3, 4.0);
		}
		case TEXTDRAWS_ANIMATION_1:
		{
			TextDraw_Pulsate(playerid,TEXTDRAWS_ANIMATION_FINISH,10,100,0,4 );
		}
		case TEXTDRAWS_ANIMATION_FINISH:
		{
			TextDraw_Hide( playerid, 0, -1 );
		}
	}

	return 1;
}
