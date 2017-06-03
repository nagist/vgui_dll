//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include<VGUI_Menu.h>
#include<VGUI_RaisedBorder.h>
#include<VGUI_StackLayout.h>

using namespace vgui;

Menu::Menu(int x,int y,int wide,int tall) : Panel(x,y,wide,tall)
{
	setBorder(new RaisedBorder());
	setLayout(new StackLayout(1,true));
}

Menu::Menu(int wide,int tall) : Panel(0,0,wide,tall)
{
	setBorder(new RaisedBorder());
	setLayout(new StackLayout(1,true));
}

void Menu::addMenuItem(Panel* panel)
{
	addChild(panel);
}
