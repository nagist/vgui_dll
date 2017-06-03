//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include<VGUI_MenuItem.h>

using namespace vgui;

MenuItem::MenuItem(const char* text) : Button(text,0,0)
{
	setButtonBorderEnabled(false);
	_subMenu=null;
}

MenuItem::MenuItem(const char* text,Menu* subMenu) : Button(text,0,0)
{
	setButtonBorderEnabled(false);
	_subMenu=subMenu;
}
