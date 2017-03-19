//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include "VGUI.h"
#include "VGUI_Color.h"
#include "VGUI_App.h"

using namespace vgui;

Color::Color()
{
	init();
}

Color::Color(int r,int g,int b,int a)
{
	init();
	setColor(r,g,b,a);
}

Color::Color(Scheme::SchemeColor sc)
{
	init();
	setColor(sc);
}

void Color::init()
{
	_color[0]=0;
	_color[1]=0;
	_color[2]=0;
	_color[3]=0;
	_schemeColor=Scheme::sc_user;
}

void Color::setColor(int r,int g,int b,int a)
{
	_color[0]=r;
	_color[1]=g;
	_color[2]=b;
	_color[3]=a;
	_schemeColor=Scheme::sc_user;
}

void Color::setColor(Scheme::SchemeColor sc)
{
	_schemeColor=sc;
}

void Color::getColor(int& r,int& g,int& b,int& a)
{
	if(_schemeColor==Scheme::sc_user)
	{
		r=_color[0];
		g=_color[1];
		b=_color[2];
		a=_color[3];
	}
	else
	{
		App::getInstance()->getScheme()->getColor(_schemeColor,r,g,b,a);
	}
}

void Color::getColor(Scheme::SchemeColor& sc)
{
	sc=_schemeColor;
}

int Color::operator[](int index)
{
	int color[4];
	getColor(color[0],color[1],color[2],color[3]);
	return color[index];
}
