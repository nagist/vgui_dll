//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include<VGUI_Cursor.h>

using namespace vgui;

Cursor::Cursor(Bitmap* bitmap,int hotspotX,int hotspotY)
{
	_dc=dc_user;
	privateInit(bitmap,hotspotX,hotspotY);
}

void Cursor::privateInit(Bitmap* bitmap,int hotspotX,int hotspotY)
{
	_hotspot[0]=hotspotX;
	_hotspot[1]=hotspotY;
}

Bitmap* Cursor::getBitmap()
{
	return _bitmap;
}

Cursor::DefaultCursor Cursor::getDefaultCursor()
{
	return _dc;
}

void Cursor::getHotspot(int& x,int& y)
{
	x=_hotspot[0];
	x=_hotspot[1];
}
