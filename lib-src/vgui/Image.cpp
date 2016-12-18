//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include "VGUI.h"
#include "VGUI_Image.h"

using namespace vgui;

Image::Image()
{
}

void Image::setPos(int x,int y)
{
}

void Image::getPos(int& x,int& y)
{
}

void Image::getSize(int& wide,int& tall)
{
}

void Image::setColor(Color color)
{
}

void Image::getColor(Color& color)
{
}

void Image::setSize(int wide,int tall)
{
}

void Image::drawSetColor(Scheme::SchemeColor sc)
{
}

void Image::drawSetColor(int r,int g,int b,int a)
{
}

void Image::drawFilledRect(int x0,int y0,int x1,int y1)
{
}

void Image::drawOutlinedRect(int x0,int y0,int x1,int y1)
{
}

void Image::drawSetTextFont(Scheme::SchemeFont sf)
{
}

void Image::drawSetTextFont(Font* font)
{
}

void Image::drawSetTextColor(Scheme::SchemeColor sc)
{
}

void Image::drawSetTextColor(int r,int g,int b,int a)
{
}

void Image::drawSetTextPos(int x,int y)
{
}

void Image::drawPrintText(const char* str,int strlen)
{
}

void Image::drawPrintText(int x,int y,const char* str,int strlen)
{
}

void Image::drawPrintChar(char ch)
{
}

void Image::drawPrintChar(int x,int y,char ch)
{
}

void Image::drawSetTextureRGBA(int id,const char* rgba,int wide,int tall)
{
}

void Image::drawSetTexture(int id)
{
}

void Image::drawTexturedRect(int x0,int y0,int x1,int y1)
{
}

void Image::paint(Panel* panel)
{
}

void Image::doPaint(Panel* panel)
{
}
