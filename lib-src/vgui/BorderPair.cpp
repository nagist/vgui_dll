//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include<VGUI_BorderPair.h>

using namespace vgui;

BorderPair::BorderPair(Border* border0,Border* border1)
{
	_border[0]=border0;
	_border[1]=border1;
}

void BorderPair::doPaint(Panel* panel)
{
	if(_border[0]!=null)
	{
		_border[0]->doPaint(panel);
	}

	if(_border[1]!=null)
	{
		_border[1]->doPaint(panel);
	}
}

void BorderPair::paint(Panel* panel)
{
	if(_border[0]!=null)
	{
		_border[0]->paint(panel);
	}

	if(_border[1]!=null)
	{
		_border[1]->paint(panel);
	}
}
