//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include "VGUI.h"
#include "VGUI_BorderLayout.h"

using namespace vgui;

BorderLayout::BorderLayout(int inset)
{
	_inset=inset;
}

void BorderLayout::performLayout(Panel* panel)
{
	// dummy
}

LayoutInfo* BorderLayout::createLayoutInfo(Alignment alignment)
{
	//return new LayoutInfo(alignment);
	// dummy
	return 0;
}
