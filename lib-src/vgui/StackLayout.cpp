//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include<VGUI_StackLayout.h>
#include<VGUI_Panel.h>

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
		int x,y,wide,tall;
		Panel* child=panel->getChild(i);
		child->getBounds(x,y,wide,tall);
		child->setPos(x,yy);

		if(_fitWide)
		{
			int pwide,ptall;
			panel->getPaintSize(pwide,ptall);
			child->setSize(pwide,tall);
		}
		y+=tall+_vgap;
	}
}
