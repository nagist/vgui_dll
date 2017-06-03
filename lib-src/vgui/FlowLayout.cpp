//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============

//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include<VGUI_FlowLayout.h>
#include<VGUI_Panel.h>

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
		int x,y,wide,tall;
		Panel* child=panel->getChild(i);
		child->getBounds(x,y,wide,tall);
		child->setPos(xx,y);
		xx+=wide+_hgap;
	}
}
