//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include<VGUI_Font.h>

using namespace vgui;

void Font::getTextSize(const char* text,int& wide,int& tall)
{
	wide=0;
	tall=0;

	if(text==null)
	{
		return;
	}

	tall=getTall();

	int xx=0;
	for(int i=0;;i++)
	{
		char ch=text[i];

		if(ch==0)
		{
			break;
		}
		if(ch=='\n')
		{
			tall+=getTall();
			xx=0;
			continue;
		}

		int a,b,c;
		getCharABCwide(ch,a,b,c);
		xx+=a+b+c;
		if(xx>wide)
		{
			wide=xx;
		}
	}
}

int Font::getId()
{
	return _id;
}

BaseFontPlat* Font::getPlat()
{
	return _plat;
}
