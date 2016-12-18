//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include "VGUI.h"
#include "VGUI_Cursor.h"
#include "VGUI_Bitmap.h"

using namespace vgui;

class CursorBitmap : public Bitmap
{
public:
	CursorBitmap(int hotspotX,int hotspotY)
	{
		_hotspot[0]=hotspotX;
		_hotspot[1]=hotspotY;
	}
	virtual void getHotspot(int& x,int& y)
	{
		x=_hotspot[0];
		x=_hotspot[1];
	}
private:
	int _hotspot[2];
};

Cursor::Cursor(Cursor::DefaultCursor dc)
{
	_dc=dc;
	CursorBitmap *bitmap=new CursorBitmap(8,8);
	if(_dc!=dc_none)
	{
		/*bitmap->setSize(16,16);
		for(int y=0;y<16;y++)
			for(int x=0;x<16;x++)
				bitmap->setRGBA(x,y,0,0,0,0);
		for(int x=0;x<16;x++)
			bitmap->setRGBA(x,8,0,255,0,255);
		for(int y=0;y<16;y++)
			bitmap->setRGBA(8,y,0,0,255,255);*/
	}

	int x,y;
	bitmap->getHotspot(x,y);
	privateInit(_bitmap,x,y);
}

Cursor::Cursor(Bitmap* bitmap,int hotspotX,int hotspotY)
{
	_dc=dc_user;
	privateInit(bitmap,hotspotX,hotspotY);
}

void Cursor::getHotspot(int& x,int& y)
{
	x=_hotspot[0];
	x=_hotspot[1];
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
