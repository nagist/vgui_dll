//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============

//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include "VGUI.h"
#include "VGUI_FlowLayout.h"
#include "VGUI_Panel.h"

using namespace vgui;

FlowLayout::FlowLayout(int hgap) : Layout()
{
	_hgap=hgap;
}

void FlowLayout::performLayout(Panel* panel)
{
	int xx=0;
	for(int i=0;i<panel->getChildCount();i++)
	{
		Panel* p=panel->getChild(i);
		int x,y,wide,tall;
		p->getBounds(x,y,wide,tall);
		p->setPos(xx,y);
		xx+=wide+_hgap;
	}
}
