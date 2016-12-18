//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include "VGUI.h"
#include "VGUI_CheckButton.h"

using namespace vgui;

CheckButton::CheckButton(const char* text,int x,int y,int wide,int tall) : ToggleButton(text,x,y,wide,tall)
{
	setTextAlignment(Label::a_east);
	Image* image = new Image();
	//image->setSize(20,20);
	setImage(image);
	getContentSize(wide,tall);
	setSize(wide,tall);
}

CheckButton::CheckButton(const char* text,int x,int y) : ToggleButton(text,x,y)
{
	setTextAlignment(Label::a_east);
	Image* image = new Image();
	//image->setSize(20,20);
	setImage(image);
}

void CheckButton::paintBackground()
{
	int wide,tall;
	getPaintSize(wide,tall);
	drawSetColor(Scheme::sc_secondary3);
	drawFilledRect(0,0,wide,tall);
}
