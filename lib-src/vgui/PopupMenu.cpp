//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include<VGUI_PopupMenu.h>
#include<VGUI_SurfaceBase.h>

using namespace vgui;

PopupMenu::PopupMenu(int x,int y,int wide,int tall) : Menu(x,y,wide,tall)
{
}

PopupMenu::PopupMenu(int wide,int tall) : Menu(wide,tall)
{
}

void PopupMenu::showModal(Panel* panel)
{
	panel->getSurfaceBase()->createPopup(this);
}
