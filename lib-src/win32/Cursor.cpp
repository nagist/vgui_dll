//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include<VGUI_Cursor.h>
#include<VGUI_Bitmap.h>

using namespace vgui;

class CursorBitmap : public Bitmap
{
private:
	int _hotspot[2];
public:
	CursorBitmap(Cursor::DefaultCursor dc)
	{
		_hotspot[0]=8;
		_hotspot[1]=8;

		if(dc!=Cursor::dc_none)
		{
			int wide=16;
			int tall=16;
			setSize(wide,tall);

			int i,j;
			for(j=0;j<16;j++)
			{
				for(i=0;i<16;i++)
				{
					setRGBA(i,j,0,0,0,0);
				}
			}
			for(i=0;i<16;i++)
			{
				setRGBA(i,8,0,255,0,255);
			}
			for(i=0;i<16;i++)
			{
				setRGBA(8,i,0,0,255,255);
			}
		}
	}
	virtual void getHotspot(int& x,int& y)
	{
		x=_hotspot[0];
		y=_hotspot[1];
	}
};

Cursor::Cursor(Cursor::DefaultCursor dc)
{
	_dc=dc;
	CursorBitmap *cursorBitmap=new CursorBitmap(_dc);

	int hx,hy;
	cursorBitmap->getHotspot(hx,hy);
	privateInit(_bitmap,hx,hy);
}
