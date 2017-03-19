//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include <stdio.h>
#include "VGUI.h"
#include "VGUI_TextGrid.h"
#include "VGUI_App.h"
#include "VGUI_Font.h"

using namespace vgui;

TextGrid::TextGrid(int gridWide,int gridTall,int x,int y,int wide,int tall) : Panel(x,y,wide,tall)
{
	_grid=null;
	_gridSize[0]=0;
	_gridSize[1]=0;
	setXY(0,0);
	setBgColor(255,255,255,0);
	setFgColor(0,0,0,0);
	setGridSize(gridWide,gridTall);
}

void TextGrid::setGridSize(int wide,int tall)
{
	if(wide<=0||tall<=0)
		return;
	delete[] _grid;
	_grid=new char[wide*tall*7];
	memset(_grid,0,wide*tall*7);
	_gridSize[0]=wide;
	_gridSize[1]=tall;
}

void TextGrid::newLine()
{
	if(_xy[1]==_gridSize[1]-1)
	{
		if(_gridSize[1]>1)
		{
			memset(&_grid[(_gridSize[0]*_xy[1]+_xy[0])*7],0,_gridSize[0]-_xy[0]);
			for(int i=1;i<_gridSize[1];i++)
				memcpy(&_grid[(_gridSize[0]*(i-1))*7],&_grid[(_gridSize[0]*i)*7],_gridSize[0]*7);
			memset(&_grid[(_gridSize[0]*_xy[1])*7],0,_gridSize[0]*7);
		}
		_xy[0]=0;
	}
	else
	{
		_xy[0]=0;
		_xy[1]++;
	}
}

void TextGrid::setXY(int x,int y)
{
	_xy[0]=x;
	_xy[1]=y;
}

/*void TextGrid::setBgColor(int r,int g,int b)
{
	_bgColor[0]=r;
	_bgColor[1]=g;
	_bgColor[2]=b;
}

void TextGrid::setFgColor(int r,int g,int b)
{
	_fgColor[0]=r;
	_fgColor[1]=g;
	_fgColor[2]=b;
}*/

int TextGrid::vprintf(const char* format,va_list argList)
{
	char buf[2048];
	int ret=vsprintf(buf,format,argList);
	for(int i=0;i<2048;i++)
	{
		if(buf[i]==0)
			break;
		if(buf[i]=='\n')
		{
			newLine();
			continue;
		}
		if(_xy[0]>=0)
		{
			if(_xy[0]<_gridSize[0])
			{
				if(_xy[1]>=0&&_xy[1]<_gridSize[1])
				{
					_grid[(_gridSize[0]*_xy[1]+_xy[0])*7]=buf[i];
					_xy[0]++;
				}
			}
		}
	}
	repaint();
	return ret;
}

int TextGrid::printf(const char* format,...)
{
	va_list argList;
	va_start(argList,format);
	return vprintf(format,argList);
}

void TextGrid::paintBackground()
{
	Panel::paintBackground();
	Font* font=getApp()->getScheme()->getFont(Scheme::sf_primary2);

	int abc[3];
	font->getCharABCwide('W',abc[0],abc[1],abc[2]);
	int fwide=abc[0]+abc[1]+abc[2];
	int ftall=font->getTall();
	drawSetTextFont(Scheme::sf_primary2);

	int ypos=0;
	for(int y=0;y<_gridSize[1];y++)
	{
		int xpos=0;
		for(int x=0;x<_gridSize[0];x++)
		{
			char c=_grid[(_gridSize[0]*y+x)*7];
			if(c!=0)
			{
				int r,g,b,a;
				getFgColor(r,g,b,a);
				drawSetTextColor(r,g,b,a);
				drawPrintChar(xpos,ypos,c);
			}
			xpos+=fwide;
		}
		ypos+=ftall;
	}
}
