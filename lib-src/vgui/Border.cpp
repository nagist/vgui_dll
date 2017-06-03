//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include<VGUI_Border.h>

using namespace vgui;

Border::Border() : Image()
{
	_inset[0]=0;
	_inset[1]=0;
	_inset[2]=0;
	_inset[3]=0;
	_panel=null;
}

Border::Border(int left,int top,int right,int bottom) : Image()
{
	_inset[0]=0;
	_inset[1]=0;
	_inset[2]=0;
	_inset[3]=0;
	_panel=null;
	setInset(left,top,right,bottom);
}

void Border::setInset(int left,int top,int right,int bottom)
{
	_inset[0]=left;
	_inset[1]=top;
	_inset[2]=right;
	_inset[3]=bottom;
}

void Border::getInset(int& left,int& top,int& right,int& bottom)
{
	left=_inset[0];
	top=_inset[1];
	right=_inset[2];
	bottom=_inset[3];
}

void Border::drawFilledRect(int x0,int y0,int x1,int y1)
{
	Image::drawFilledRect(x0-_inset[0],y0-_inset[1],x1-_inset[0],y1-_inset[1]);
}

void Border::drawOutlinedRect(int x0,int y0,int x1,int y1)
{
	Image::drawOutlinedRect(x0-_inset[0],y0-_inset[1],x1-_inset[0],y1-_inset[1]);
}

void Border::drawSetTextPos(int x,int y)
{
	Image::drawSetTextPos(x-_inset[0],y-_inset[1]);
}

void Border::drawPrintText(int x,int y,const char* str,int strlen)
{
	Image::drawPrintText(x-_inset[0],y-_inset[1],str,strlen);
}

void Border::drawPrintChar(int x,int y,char ch)
{
	Image::drawPrintChar(x-_inset[0],y-_inset[1],ch);
}
