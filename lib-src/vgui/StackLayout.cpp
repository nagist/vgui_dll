//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include "VGUI.h"
#include "VGUI_StackLayout.h"
#include "VGUI_Panel.h"

using namespace vgui;

StackLayout::StackLayout(int vgap,bool fitWide) : Layout()
{
	_vgap=vgap;
	_fitWide=fitWide;
}

void StackLayout::performLayout(Panel* panel)
{
	int yy=0;
	for(int i=0;i<panel->getChildCount();i++)
	{
		Panel* p=panel->getChild(i);
		int x,y,wide,tall;
		p->getBounds(x,y,wide,tall);
		p->setPos(x,yy);
		if(_fitWide)
		{
			int pwide,ptall;
			panel->getPaintSize(pwide,ptall);
			p->setSize(pwide,tall);
		}
		y+=tall+_vgap;
	}
}
