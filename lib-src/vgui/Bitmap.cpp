//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include<VGUI_Bitmap.h>
#include<VGUI_Panel.h>
#include<VGUI_SurfaceBase.h>

using namespace vgui;

Bitmap::Bitmap() : Image()
{
	_rgba=null;
	_id=0;
	_uploaded=false;
}

void Bitmap::setSize(int wide,int tall)
{
	Image::setSize(wide,tall);

	if(_rgba!=null)
	{
		delete[] _rgba;
	}

	_rgba=new uchar[wide*tall*4];
}

void Bitmap::setRGBA(int x,int y,uchar r,uchar g,uchar b,uchar a)
{
	if(_rgba==null)
	{
		return;
	}

	int wide,tall;
	getSize(wide,tall);

	if ((x>=0)&&(x<wide)&&(y>=0)&&(y<tall))
	{
		_rgba[((y*wide)+x)*4]=r;
		_rgba[((y*wide)+x)*4+1]=g;
		_rgba[((y*wide)+x)*4+2]=b;
		_rgba[((y*wide)+x)*4+3]=a;
	}
}

void Bitmap::paint(Panel* panel)
{
	if(_rgba==null)
	{
		return;
	}

	int wide,tall;
	getSize(wide,tall);

	if(_id==0)
	{
		if(panel->getSurfaceBase()==null)
		{
			return;
		}

		_id=panel->getSurfaceBase()->createNewTextureID();
	}

	if(!_uploaded)
	{
		drawSetTextureRGBA(_id,(const char*)_rgba,wide,tall);
		_uploaded=true;
	}
	
	Color color;
	getColor(color);

	int r,g,b,a;
	color.getColor(r,g,b,a);
	drawSetTexture(_id);
	drawSetColor(r,g,b,a);

	int x,y;
	getPos(x,y);
	drawTexturedRect(x,y,x+wide,y+tall);
}
