//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include "VGUI.h"
#include "VGUI_HeaderPanel.h"

using namespace vgui;

HeaderPanel::HeaderPanel(int x,int y,int wide,int tall)
{
}

void HeaderPanel::performLayout()
{
}

void HeaderPanel::addSectionPanel(Panel* panel)
{
}

void HeaderPanel::setSliderPos(int sliderIndex,int pos)
{
}

int HeaderPanel::getSectionCount()
{
	return 0;
}

void HeaderPanel::getSectionExtents(int sectionIndex,int& x0,int& x1)
{
}

void HeaderPanel::addChangeSignal(ChangeSignal* s)
{
}

void HeaderPanel::fireChangeSignal()
{
}

void HeaderPanel::privateCursorMoved(int x,int y,Panel* panel)
{
}

void HeaderPanel::privateMousePressed(MouseCode code,Panel* panel)
{
}

void HeaderPanel::privateMouseReleased(MouseCode code,Panel* panel)
{
}
