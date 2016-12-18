//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include "VGUI.h"
#include "VGUI_TreeFolder.h"

using namespace vgui;

TreeFolder::TreeFolder(const char* name) : Panel(0,0,500,500)
{
	init(name);
}

TreeFolder::TreeFolder(const char* name,int x,int y) : Panel(x,y,500,500)
{
	init(name);
}

void TreeFolder::init(const char* name)
{
	// dummy
}

void TreeFolder::setOpenedTraverse(bool state)
{
	// dummy
}

void TreeFolder::setOpened(bool state)
{
	if(_opened!=state)
	{
		_opened=state;

		TreeFolder* folder=null;
		Panel* p=this;
		while(p)
		{
			TreeFolder* panel=dynamic_cast<TreeFolder*>(p);
			if(panel)
			{
				panel->invalidateLayout(true);
				folder=panel;
			}
			p=p->getParent();
		}
		if(folder)
			folder->repaintParent();
	}
}

bool TreeFolder::isOpened()
{
	return _opened;
}

void TreeFolder::paintBackground()
{
	// dummy
}
