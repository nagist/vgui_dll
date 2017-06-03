//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include<VGUI_Surface.h>
#include<VGUI_Panel.h>

using namespace vgui;

Surface::Surface(Panel* embeddedPanel) : SurfaceBase(embeddedPanel)
{
	createPlat();
	recreateContext();
}

void Surface::createPopup(Panel* embeddedPanel)
{
	embeddedPanel->setParent(null);
	new Surface(embeddedPanel);
}

void Surface::GetMousePos( int &x, int &y )
{
}
