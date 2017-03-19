//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include "VGUI.h"
#include "VGUI_MenuSeparator.h"

using namespace vgui;

MenuSeparator::MenuSeparator(const char* text) : Label(text)
{
	setFont(Scheme::sf_primary3);
}

void MenuSeparator::paintBackground()
{
	int wide,tall;
	getPaintSize(wide,tall);
	drawSetColor(Scheme::sc_secondary3);
	drawFilledRect(0,0,wide,tall);

	int textWide,textTall;
	int gap=2;
	int tgap=1;
	getTextSize(textWide,textTall);

	if(textWide>0)
	{
		textWide+=4;
	}

	int wide2=(textWide/2);
	int tall2=textTall/2-1;
	int x0=(wide/2)-wide2;
	int x1=(wide/2)+wide2;
	drawSetColor(Scheme::sc_secondary1);
	drawFilledRect(gap,tall2,x0,tall2+1);
	drawFilledRect(x1,tall2,wide-gap,tall2+1);
	drawSetColor(Scheme::sc_white);
	drawFilledRect(gap,tall2+tgap,x0,tall2+tgap*2);
	drawFilledRect(x1,tall2+tgap,wide-gap,tall2+tgap*2);
}
