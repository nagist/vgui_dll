//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include <stdarg.h>
#include <stdio.h>
#include "VGUI.h"
#include "VGUI_Label.h"
#include "VGUI_TextImage.h"
#include "VGUI_TreeFolder.h"
#include "VGUI_FlowLayout.h"
#include "VGUI_TextEntry.h"
#include "VGUI_ActionSignal.h"

using namespace vgui;

class FooDumb : public Panel, public ActionSignal
{
public:
	FooDumb(Label* label) : Panel(0,0,200,20)
	{
		_label=label;
		setLayout(new FlowLayout(2));

		Label* setText=new Label("setText");
		setText->setParent(this);

		_textEntry=new TextEntry("",0,0,80,20);
		_textEntry->setParent(this);
		_textEntry->addActionSignal(this);
	}
	void actionPerformed(Panel* panel)
	{
		char buf[256];
		_textEntry->getText(0,buf,sizeof(buf));
		_label->setText(buf);
		_label->repaint();
	}
private:
	Label* _label;
	TextEntry*_textEntry;
};

Label::Label(int textBufferLen,const char* text,int x,int y,int wide,int tall) : Panel(x,y,wide,tall)
{
	init(textBufferLen,text,false);
}

Label::Label(const char* text,int x,int y,int wide,int tall): Panel(x,y,wide,tall)
{
	init(strlen(text)+1,text,false);
}

Label::Label(const char* text,int x,int y) : Panel(x,y,10,10)
{
	init(strlen(text)+1,text,true);
}

Label::Label(const char* text) : Panel(0,0,10,10)
{
	init(strlen(text)+1,text,true);
}

void Label::init(int textBufferLen,const char* text,bool textFitted)
{
	_contentFitted=textFitted;
	_textAlignment=a_center;
	_contentAlignment=a_center;
	_textImage=new TextImage(textBufferLen,text);
	_textImage->setColor(Color(Scheme::sc_black));
	_image=null;

	setText(textBufferLen,text);
}

void Label::setImage(Image* image)
{
	_image=image;
	recomputeMinimumSize();

	if(_image)
	{
		repaint();
	}
}

void Label::setText(int textBufferLen,const char* text)
{
	_textImage->setText(textBufferLen,text);
	recomputeMinimumSize();
	repaint();
}

void Label::setText(const char* format,...)
{
	char buf[4096];
	va_list argList;

	va_start(argList,format);
	int ret=vsnprintf(buf,sizeof(buf),format,argList);
	buf[sizeof(buf)-1]=0;
	va_end(argList);

	setText(strlen(buf)+1,buf);
}

void Label::setFont(Scheme::SchemeFont schemeFont)
{
	_textImage->setFont(schemeFont);
	recomputeMinimumSize();
	repaint();
}

void Label::setFont(Font* font)
{
	_textImage->setFont(font);
	recomputeMinimumSize();
	repaint();
}

void Label::getTextSize(int& wide,int& tall)
{
	_textImage->getTextSize(wide,tall);
}

void Label::getContentSize(int& wide,int& tall)
{
	int tx0,ty0,tx1,ty1,ix0,iy0,ix1,iy1,minX,minY,maxX,maxY;
	computeAlignment(tx0,ty0,tx1,ty1,ix0,iy0,ix1,iy1,minX,minY,maxX,maxY);
	wide=maxX-minX;
	tall=maxY-minY;
}

void Label::setTextAlignment(Alignment alignment)
{
	_textAlignment=alignment;
	recomputeMinimumSize();
	repaint();
}

void Label::setContentAlignment(Alignment alignment)
{
	_contentAlignment=alignment;
	recomputeMinimumSize();
	repaint();
}

Panel* Label::createPropertyPanel()
{
	Panel* panel=Panel::createPropertyPanel();
	TreeFolder* label=new TreeFolder("Label");
	panel->addChild(label);
	label->addChild(new FooDumb(this));
	label->addChild(new Label("setContentAlignment"));
	return panel;
}

void Label::setFgColor(int r,int g,int b,int a)
{
	Panel::setFgColor(r,g,b,a);
	_textImage->setColor(Color(r,g,b,a));
	repaint();
}

void Label::setFgColor(vgui::Scheme::SchemeColor sc)
{
	Panel::setFgColor(sc);
	_textImage->setColor(sc);
	repaint();
}

void Label::setContentFitted(bool state)
{
	_contentFitted=state;
	recomputeMinimumSize();
	repaint();
}

void Label::computeAlignment(int& tx0,int& ty0,int& tx1,int& ty1,int& ix0,int& iy0,int& ix1,int& iy1,int& minX,int& minY,int& maxX,int& maxY)
{
	int wide, tall;
	getPaintSize(wide, tall);

	int tWide,tTall;
	getTextSize(tWide, tTall);

	int iWide = 0;
	int iTall = 0;

	if (_image)
	{
		_image->getSize(iWide, iTall);
	}

	ix0 = 0;
	iy0 = 0;
	ix1 = iWide;
	iy1 = iTall;

	tx0 = 0;
	ty0 = 0;
	tx1 = tWide;
	ty1 = tTall;

	switch (_textAlignment)
	{
		case Label::a_northwest:
		case Label::a_west:
		case Label::a_southwest:
		{
			tx0 = ix0 - tWide;
			break;
		}
		case Label::a_north:
		case Label::a_center:
		case Label::a_south:
		{
			tx0 = ((ix1 - ix0) / 2) - ((tx1 - tx0) / 2);
			break;
		}
		case Label::a_northeast:
		case Label::a_east:
		case Label::a_southeast:
		{
			tx0 = ix1;
			break;
		}
	}

	switch (_textAlignment)
	{
		case Label::a_northwest:
		case Label::a_north:
		case Label::a_northeast:
		{
			ty0 = iy0 - tTall;
			break;
		}
		case Label::a_west:
		case Label::a_center:
		case Label::a_east:
		{
			ty0 = ((iy1 - iy0) / 2) - ((ty1 - ty0) / 2);
			break;
		}
		case Label::a_southwest:
		case Label::a_south:
		case Label::a_southeast:
		{
			ty0 = iy1;
			break;
		}
	}

	tx1 = tx0 + tWide;
	ty1 = ty0 + tTall;

	minX = tx0;
	minY = ty0;

	if (minX > ix0)
		minX = ix0;
	if (minY > iy0)
		minY = iy0;

	maxX = tx1;
	maxY = ty1;

	if (maxX < ix1)
		maxX = ix1;
	if (maxY < iy1)
		maxY = iy1;

	tx0 -= minX;
	ty0 -= minY;
	tx1 -= minX;
	ty1 -= minY;
	ix0 -= minX;
	iy0 -= minY;
	ix1 -= minX;
	iy1 -= minY;
	maxX -= minX;
	maxY -= minY;
	minX = 0;
	minY = 0;

	int offX, offY;
	switch (_contentAlignment)
	{
		case Label::a_northwest:
		case Label::a_west:
		case Label::a_southwest:
		{
			offX = 0;
			break;
		}
		case Label::a_north:
		case Label::a_center:
		case Label::a_south:
		{
			offX = (wide / 2) - ((maxX - minX) / 2);
			break;
		}
		case Label::a_northeast:
		case Label::a_east:
		case Label::a_southeast:
		{
			offX = wide + maxX - minX;
			break;
		}
	}

	switch (_contentAlignment)
	{
		case Label::a_northwest:
		case Label::a_north:
		case Label::a_northeast:
		{
			offY = 0;
			break;
		}
		case Label::a_west:
		case Label::a_center:
		case Label::a_east:
		{
			offY = (tall / 2) - (maxY / 2);
			break;
		}
		case Label::a_southwest:
		case Label::a_south:
		case Label::a_southeast:
		{
			offY = tall - maxY;
			break;
		}
	}

	tx0 += offX;
	ty0 += offY;
	tx1 += offX;
	ty1 += offY;
	ix0 += offX;
	iy0 += offY;
	ix1 += offX;
	iy1 += offY;
	minX += offX;
	minY += offY;
	maxX += offX;
	maxY += offY;

	int pad = 4;
	minX -= pad;
	minY -= pad;
	maxX += pad;
	maxY += pad;
}

void Label::paint()
{
	int tx0,ty0,tx1,ty1,ix0,iy0,ix1,iy1,minX,minY,maxX,maxY;
	computeAlignment(tx0,ty0,tx1,ty1,ix0,iy0,ix1,iy1,minX,minY,maxX,maxY);

	if(_image)
	{
		_image->setPos(ix0,iy0);
		_image->doPaint(this);
	}

	if(_textImage)
	{
		_textImage->setPos(tx0,ty0);
		_textImage->doPaint(this);
	}

	if(hasFocus())
	{
		drawSetColor(Scheme::sc_primary2);
		drawOutlinedRect(tx0,ty0,tx1,ty1);
	}
}

void Label::recomputeMinimumSize()
{
	int wide,tall;
	getContentSize(wide,tall);
	setPreferredSize(wide,tall);

	if(_contentFitted)
	{
		setSize(wide,tall);
	}
}
