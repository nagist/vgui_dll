/*
 * BSD 3-Clause License
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include<stdarg.h>
#include<stdio.h>
#include<VGUI_Label.h>
#include<VGUI_TextImage.h>
#include<VGUI_TreeFolder.h>
#include<VGUI_FlowLayout.h>
#include<VGUI_TextEntry.h>
#include<VGUI_ActionSignal.h>

using namespace vgui;

namespace
{
class FooDumb : public Panel, public ActionSignal
{
private:
	Label* _label;
	TextEntry*_textEntry;
public:
	FooDumb(Label* label) : Panel(0,0,200,20)
	{
		_label=label;

		setLayout(new FlowLayout(2));

		Label* lll=new Label("setText");
		lll->setParent(this);

		_textEntry=new TextEntry("",0,0,80,20);
		_textEntry->setParent(this);
		_textEntry->addActionSignal(this);
	}
public:
	void actionPerformed(Panel* panel)
	{
		char buf[256];
		_textEntry->getText(0,buf,sizeof(buf));
		_label->setText(buf);
		_label->repaint();
	}
};
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

void Label::setFont(Scheme::SchemeFont schemeFont)
{
	_textImage->setFont(schemeFont);
	recomputeMinimumSize();
	repaint();
}

void Label::setImage(Image* image)
{
	_image=image;
	recomputeMinimumSize();

	if(_image!=null)
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
	int ret=_vsnprintf(buf,sizeof(buf),format,argList);
	buf[sizeof(buf)-1]=0;
	va_end(argList);

	setText(strlen(buf)+1,buf);
}

void Label::computeAlignment(int& tx0,int& ty0,int& tx1,int& ty1,int& ix0,int& iy0,int& ix1,int& iy1,int& minX,int& minY,int& maxX,int& maxY)
{
	int wide,tall;
	getPaintSize(wide,tall);

	int tWide,tTall;
	getTextSize(tWide,tTall);

	int iWide=0;
	int iTall=0;

	if(_image!=null)
	{
		_image->getSize(iWide,iTall);
	}

	ix0=0;
	iy0=0;
	ix1=iWide;
	iy1=iTall;

	tx0=0;
	ty0=0;
	tx1=tWide;
	ty1=tTall;

	switch(_textAlignment)
	{
		// left
		case Label::a_northwest:
		case Label::a_west:
		case Label::a_southwest:
		{
			tx0=ix0-tWide;
			break;
		}
		// center
		case Label::a_north:
		case Label::a_center:
		case Label::a_south:
		{
			tx0=((ix1-ix0)/2)-((tx1-tx0)/2);
			break;
		}
		// right
		case Label::a_northeast:
		case Label::a_east:
		case Label::a_southeast:
		{
			tx0=ix1;
			break;
		}
	}

	switch(_textAlignment)
	{
		// top
		case Label::a_northwest:
		case Label::a_north:
		case Label::a_northeast:
		{
			ty0=iy0-tTall;
			break;
		}
		// center
		case Label::a_west:
		case Label::a_center:
		case Label::a_east:
		{
			ty0=((iy1-iy0)/2)-((ty1-ty0)/2);
			break;
		}
		// south
		case Label::a_southwest:
		case Label::a_south:
		case Label::a_southeast:
		{
			ty0=iy1;
			break;
		}
	}

	tx1=tx0+tWide;
	ty1=ty0+tTall;

	minX=tx0;
	minY=ty0;

	if(ix0<minX)
	{
		minX=ix0;
	}
	if(iy0<minY)
	{
		minY=iy0;
	}

	maxX=tx1;
	maxY=ty1;

	if(ix1>maxX)
	{
		maxX=ix1;
	}
	if(iy1>maxY)
	{
		maxY=iy1;
	}

	tx0-=minX;
	ty0-=minY;
	tx1-=minX;
	ty1-=minY;

	ix0-=minX;
	iy0-=minY;
	ix1-=minX;
	iy1-=minY;

	maxX-=minX;
	maxY-=minY;
	minX=0;
	minY=0;

	int offX,offY;
	switch(_contentAlignment)
	{
		// left
		case Label::a_northwest:
		case Label::a_west:
		case Label::a_southwest:
		{
			offX=0;
			break;
		}
		// center
		case Label::a_north:
		case Label::a_center:
		case Label::a_south:
		{
			offX=(wide/2)-((maxX-minX)/2);
			break;
		}
		// right
		case Label::a_northeast:
		case Label::a_east:
		case Label::a_southeast:
		{
			offX=minX+wide-maxX;
			break;
		}
	}

	switch(_contentAlignment)
	{
		// top
		case Label::a_northwest:
		case Label::a_north:
		case Label::a_northeast:
		{
			offY=0;
			break;
		}
		// center
		case Label::a_west:
		case Label::a_center:
		case Label::a_east:
		{
			offY=(tall/2)-(maxY/2);
			break;
		}
		// south
		case Label::a_southwest:
		case Label::a_south:
		case Label::a_southeast:
		{
			offY=tall-maxY;
			break;
		}
	}

	tx0+=offX;
	ty0+=offY;
	tx1+=offX;
	ty1+=offY;

	ix0+=offX;
	iy0+=offY;
	ix1+=offX;
	iy1+=offY;

	minX+=offX;
	minY+=offY;
	maxX+=offX;
	maxY+=offY;

	int pad=4;
	minX-=pad;
	minY-=pad;
	maxX+=pad;
	maxY+=pad;
}

void Label::paint()
{
	int tx0,ty0,tx1,ty1,ix0,iy0,ix1,iy1,minX,minY,maxX,maxY;
	computeAlignment(tx0,ty0,tx1,ty1,ix0,iy0,ix1,iy1,minX,minY,maxX,maxY);

	if(_image!=null)
	{
		_image->setPos(ix0,iy0);
		_image->doPaint(this);
	}

	if(_textImage!=null)
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
	Panel* parentPropertyPanel=Panel::createPropertyPanel();

	TreeFolder* folder=new TreeFolder("Label");
	parentPropertyPanel->addChild(folder);
	folder->addChild(new FooDumb(this));
	folder->addChild(new Label("setContentAlignment"));

	return parentPropertyPanel;
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

void Label::setFont(Font* font)
{
	_textImage->setFont(font);
	recomputeMinimumSize();
	repaint();
}

void Label::setFgColor(int r,int g,int b,int a)
{
	Panel::setFgColor(r,g,b,a);
	Color color=Color(r,g,b,a);
	_textImage->setColor(color);
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
