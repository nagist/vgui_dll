//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include<VGUI_LineBorder.h>
#include<VGUI_Panel.h>

using namespace vgui;

LineBorder::LineBorder() : Border()
{
	init(1,Color(0,0,0,0));
}

LineBorder::LineBorder(int thickness) : Border()
{
	init(thickness,Color(0,0,0,0));
}

LineBorder::LineBorder(Color color) : Border()
{
	init(1,color);
}

LineBorder::LineBorder(int thickness,Color color) : Border()
{
	init(thickness,color);
}

void LineBorder::init(int thickness,Color color)
{
	setInset(thickness,thickness,thickness,thickness);
	_color=color;
}

void LineBorder::paint(Panel* panel)
{
	int wide,tall;
	panel->getSize(wide,tall);

	int r,g,b,a;
	_color.getColor(r,g,b,a);
	drawSetColor(r,g,b,a);

	drawFilledRect(0,0,wide,_inset[1]);
	drawFilledRect(0,tall-_inset[3],wide,tall);
	drawFilledRect(0,_inset[1],_inset[0],tall-_inset[3]);
	drawFilledRect(wide-_inset[2],_inset[1],wide,tall-_inset[3]);
}
