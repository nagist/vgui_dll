//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include "VGUI.h"
#include "VGUI_Font.h"

using namespace vgui;

BaseFontPlat* Font::getPlat()
{
	return _plat;
}

void Font::getTextSize(const char* text,int& wide,int& tall)
{
	wide=0;
	tall=0;

	if(text)
	{
		int x=0;
		tall=getTall();
		for(int i=0;text[i];i++)
		{
			if(text[i]=='\n')
			{
				x=0;
				tall+=getTall();
				continue;
			}

			int a,b,c;
			getCharABCwide(text[i],a,b,c);
			x+=a+b+c;
			if(x>wide)
				wide=x;
		}
	}
}

int Font::getId()
{
	return _id;
}
