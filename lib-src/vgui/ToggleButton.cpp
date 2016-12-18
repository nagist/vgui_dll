//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include "VGUI.h"
#include "VGUI_ToggleButton.h"

using namespace vgui;

ToggleButton::ToggleButton(const char* text,int x,int y,int wide,int tall) : Button(text,x,y,wide,tall)
{
}

ToggleButton::ToggleButton(const char* text,int x,int y) : Button(text,x,y)
{
}
