//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include<stdio.h>
#include<VGUI_TextGrid.h>
#include<VGUI_App.h>
#include<VGUI_Font.h>

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
	if((wide<=0)||(tall<=0))
	{
		return;
	}

	delete[] _grid;
	_grid=new char[wide*tall*7];
	memset(_grid,0,wide*tall*7);

	_gridSize[0]=wide;
	_gridSize[1]=tall;
}

void TextGrid::newLine()
{
	if(_xy[1]==(_gridSize[1]-1))
	{
		if(_gridSize[1]>1)
		{
			memset(&_grid[((_xy[1]*_gridSize[0])+_xy[0])*7],0,_gridSize[0]-_xy[0]);
			for(int j=1;j<_gridSize[1];j++)
			{
				memcpy(&_grid[((j-1)*_gridSize[0])*7],&_grid[(j*_gridSize[0])*7],_gridSize[0]*7);
			}
			memset(&_grid[(_xy[1]*_gridSize[0])*7],0,_gridSize[0]*7);
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

int TextGrid::vprintf(const char* format,va_list argList)
{
	char buf[2048];
	int ret=vsprintf(buf,format,argList);
	for(int i=0;i<2048;i++)
	{
		if(buf[i]==0)
		{
			break;
		}
		if(buf[i]=='\n')
		{
			newLine();
			continue;
		}
		if((_xy[0]>=0)&&(_xy[0]<_gridSize[0]))
		{
			if((_xy[1]>=0)&&(_xy[1]<_gridSize[1]))
			{
				_grid[((_xy[1]*_gridSize[0])+_xy[0])*7]=buf[i];
				_xy[0]++;
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

	int r,g,b,a;

	for(int j=0;j<_gridSize[1];j++)
	{
		for(int i=0;i<_gridSize[0];i++)
		{
			char ch=_grid[((j*_gridSize[0])+i)*7];
			if(ch!=0)
			{
				getFgColor(r,g,b,a);
				drawSetTextColor(r,g,b,a);
				drawPrintChar(fwide*i,ftall*j,ch);
			}
		}
	}
}
