//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include "VGUI.h"
#include "VGUI_TextImage.h"
#include "VGUI_App.h"
#include "VGUI_Scheme.h"
#include "VGUI_Font.h"

using namespace vgui;

TextImage::TextImage(int textBufferLen,const char* text) : Image()
{
	init(textBufferLen,text);
}

TextImage::TextImage(const char* text) : Image()
{
	init(strlen(text)+1,text);
}

void TextImage::init(int textBufferLen,const char* text)
{
	_text=null;
	_font=null;
	_textBufferLen=0;
	_schemeFont=Scheme::sf_primary1;
	setText(textBufferLen,text);

	int wide,tall;
	getTextSize(wide,tall);
	setSize(wide,tall);
}

void TextImage::getTextSize(int& wide,int& tall)
{
	wide=0;
	tall=0;

	if(_text)
	{
		Font* font=getFont();
		if(font)
			font->getTextSize(_text,wide,tall);
	}
}

void TextImage::getTextSizeWrapped(int& wideo,int& tallo)
{
	wideo=0;
	tallo=0;

	if(_text)
	{
		int wide,tall;
		getSize(wide,tall);

		Font* font=getFont();

		int yAdd=font->getTall();
		int x=0,y=0;

		for(int i=0;;i++)
		{
			int ch=_text[i];

			int a,b,c;
			font->getCharABCwide(ch,a,b,c);

			int len=a+b+c;

			if(!ch)
			{
				break;
			}
			else if(ch=='\r')
			{
				continue;
			}
			else if(ch=='\n')
			{
				x=0;
				y+=yAdd;
			}
			else if(ch==' ')
			{
				char nextch = _text[i+1];
				font->getCharABCwide(ch,a,b,c);
				if((nextch!='\0')&&(nextch!='\n')&&(nextch!='\r'))
				{
					x+=a+b+c;
					if(x>wide)
					{
						x=0;
						y+=yAdd;
					}
				}
			}
			else
			{
				int ctr=1;
				for(;_text[i+ctr];ctr++)
				{
					if((_text[i+ctr]=='\n')||(_text[i+ctr]=='\r')||(_text[i+ctr]==' '))
						break;
					int a,b,c;
					font->getCharABCwide(_text[i+ctr],a,b,c);
					len+=a+b+c;
				}
				if(x+len>wide)
				{
					x=0;
					y+=yAdd;
				}
				for(int j=0;j<ctr;j++)
				{
					font->getCharABCwide(_text[i+j],a,b,c);
					x+=a+b+c;
					if(x>wideo)
						wideo=x;
					if(y+yAdd>tallo)
						tallo=y+yAdd;
				}
				i+=ctr-1;
			}
		}
	}
}

Font* TextImage::getFont()
{
	if(!_font)
	{
		return App::getInstance()->getScheme()->getFont(_schemeFont);
	}
	return _font;
}

void TextImage::setText(int textBufferLen,const char* text)
{
	if(textBufferLen>_textBufferLen)
	{
		delete[] _text;
		_textBufferLen=textBufferLen;
		_text=new char[textBufferLen];
		if(!_text)
			_textBufferLen=0;
	}

	if(_text)
		vgui_strcpy(_text,_textBufferLen,text);

	int wide,tall;
	getTextSize(wide,tall);
	Image::setSize(wide,tall);
}

void TextImage::setText(const char* text)
{
	setText(strlen(text)+1,text);
}

void TextImage::setFont(vgui::Scheme::SchemeFont schemeFont)
{
	_schemeFont=schemeFont;
}

void TextImage::setFont(vgui::Font* font)
{
	_font=font;
}

void TextImage::setSize(int wide,int tall)
{
	Image::setSize(wide,tall);
}

void TextImage::paint(Panel* panel)
{
	int wide,tall;
	getSize(wide,tall);

	if(!_text)
		return;

	Color color;
	getColor(color);

	int r,g,b,a;
	color.getColor(r,g,b,a);
	drawSetTextColor(r,g,b,a);

	Font* font=getFont();
	drawSetTextFont(font);

	int yAdd=font->getTall();
	int x=0,y=0;

	for(int i=0;;i++)
	{
		int ch=_text[i];

		int a,b,c;
		font->getCharABCwide(ch,a,b,c);

		int len=a+b+c;

		if(!ch)
		{
			break;
		}
		else if(ch=='\r')
		{
			continue;
		}
		else if(ch=='\n')
		{
			x=0;
			y+=yAdd;
		}
		else if(ch==' ')
		{
			char nextch = _text[i+1];
			font->getCharABCwide(ch,a,b,c);
			if((nextch!='\0')&&(nextch!='\n')&&(nextch!='\r'))
			{
				x+=a+b+c;
				if(x>wide)
				{
					x=0;
					y+=yAdd;
				}
			}
		}
		else
		{
			int ctr=1;
			for(;_text[i+ctr];ctr++)
			{
				if((_text[i+ctr]=='\n')||(_text[i+ctr]=='\r')||(_text[i+ctr]==' '))
					break;
				int a,b,c;
				font->getCharABCwide(_text[i+ctr],a,b,c);
				len+=a+b+c;
			}
			if(x+len>wide)
			{
				x=0;
				y+=yAdd;
			}
			for(int j=0;j<ctr;j++)
			{
				font->getCharABCwide(_text[i+j],a,b,c);
				drawPrintChar(x,y,_text[i+j]);
				x+=a+b+c;
			}
			i+=ctr-1;
		}
	}
}
