//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include "VGUI.h"
#include "VGUI_Label.h"

using namespace vgui;

Label::Label(int textBufferLen,const char* text,int x,int y,int wide,int tall)
{
}

Label::Label(const char* text,int x,int y,int wide,int tall)
{
}

Label::Label(const char* text,int x,int y)
{
}

Label::Label(const char* text)
{
}

void Label::init(int textBufferLen,const char* text,bool textFitted)
{
}

void Label::setImage(Image* image)
{
}

void Label::setText(int textBufferLen,const char* text)
{
}

void Label::setText(const char* format,...)
{
}

void Label::setFont(Scheme::SchemeFont schemeFont)
{
}

void Label::setFont(Font* font)
{
}

void Label::getTextSize(int& wide,int& tall)
{
}

void Label::getContentSize(int& wide,int& tall)
{
}

void Label::setTextAlignment(Alignment alignment)
{
}

void Label::setContentAlignment(Alignment alignment)
{
}

Panel* Label::createPropertyPanel()
{
	return null;
}

void Label::setFgColor(int r,int g,int b,int a)
{
}

void Label::setFgColor(vgui::Scheme::SchemeColor sc)
{
}

void Label::setContentFitted(bool state)
{
}

void Label::computeAlignment(int& tx0,int& ty0,int& tx1,int& ty1,int& ix0,int& iy0,int& ix1,int& iy1,int& minX,int& minY,int& maxX,int& maxY)
{
}

void Label::paint()
{
}

void Label::recomputeMinimumSize()
{
}
