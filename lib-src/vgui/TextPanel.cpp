//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include<VGUI_TextPanel.h>
#include<VGUI_TextImage.h>

using namespace vgui;

TextPanel::TextPanel(const char* text,int x,int y,int wide,int tall) : Panel(x,y,wide,tall)
{
	_textImage=new TextImage(text);
	_textImage->setSize(wide,tall);
}

void TextPanel::setText(const char* text)
{
	_textImage->setText(text);
}

void TextPanel::setFont(vgui::Scheme::SchemeFont schemeFont)
{
	_textImage->setFont(schemeFont);
}

void TextPanel::setFont(vgui::Font* font)
{
	_textImage->setFont(font);
}

void TextPanel::paint()
{
	_textImage->doPaint(this);
}

void TextPanel::setSize(int wide,int tall)
{
	Panel::setSize(wide,tall);
	getPaintSize(wide,tall);
	_textImage->setSize(wide,tall);
}

void TextPanel::setFgColor(int r,int g,int b,int a)
{
	Panel::setFgColor(r,g,b,a);
	_textImage->setColor(Color(r,g,b,a));
}

void TextPanel::setFgColor(Scheme::SchemeColor sc)
{
	Panel::setFgColor(sc);
	_textImage->setColor(Color(sc));
}

TextImage* TextPanel::getTextImage()
{
	return _textImage;
}
