//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include<stdio.h>
#include<VGUI_IntLabel.h>

using namespace vgui;

IntLabel::IntLabel(int value,int x,int y,int wide,int tall) : Label(null,x,y,wide,tall)
{
	_value=0;
	setValue(value);
}

void IntLabel::setValue(int value)
{
	if(_value!=value)
	{
		_value=value;
		repaint();
	}
}

void IntLabel::intChanged(int value,Panel* panel)
{
	setValue(value);
}

void IntLabel::paintBackground()
{
	char buf[50];
	sprintf(buf,"%d",_value);
	Panel::paintBackground();
	drawSetTextFont(Scheme::sf_primary1);
	drawSetTextColor(Scheme::sc_black);
	drawPrintText(0,0,buf,strlen(buf));
}
