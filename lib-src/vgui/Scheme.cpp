//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include "VGUI.h"
#include "VGUI_Scheme.h"

using namespace vgui;

Scheme::Scheme()
{
}

void Scheme::setColor(SchemeColor sc,int r,int g,int b,int a)
{
}

void Scheme::getColor(SchemeColor sc,int& r,int& g,int& b,int& a)
{
}

void Scheme::setFont(SchemeFont sf,Font* font)
{
}

Font* Scheme::getFont(SchemeFont sf)
{
	return null;
}

void Scheme::setCursor(SchemeCursor sc,Cursor* cursor)
{
}

Cursor* Scheme::getCursor(SchemeCursor sc)
{
	return null;
}
