//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include "VGUI.h"
#include "VGUI_RadioButton.h"
#include "VGUI_Image.h"

using namespace vgui;

RadioButton::RadioButton(const char* text,int x,int y,int wide,int tall) : ToggleButton(text,x,y,wide,tall)
{
	setTextAlignment(Label::a_east);

	Image* image=new Image();
	//image->setSize(20,20);
	setImage(image);
	getContentSize(wide,tall);
	Panel::setSize(wide,tall);
}

RadioButton::RadioButton(const char* text,int x,int y) : ToggleButton(text,x,y)
{
	setTextAlignment(Label::a_east);

	Image* image=new Image();
	//image->setSize(20,20);
	setImage(image);
}

void RadioButton::paintBackground()
{
	int wide,tall;
	getPaintSize(wide,tall);

	drawSetColor(Scheme::sc_secondary3);
	drawFilledRect(0,0,wide,tall);
}
