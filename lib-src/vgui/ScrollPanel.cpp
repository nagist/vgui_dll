//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include<VGUI_ScrollPanel.h>
#include<VGUI_ScrollBar.h>
#include<VGUI_IntChangeSignal.h>

using namespace vgui;

namespace
{
class ChangeHandler : public IntChangeSignal
{
private:
	ScrollPanel* _scrollPanel;
public:
	ChangeHandler(ScrollPanel* scrollPanel)
	{
		_scrollPanel=scrollPanel;
	}
public:
	virtual void intChanged(int value,Panel* panel)
	{
		_scrollPanel->recomputeScroll();
	}
};
}

ScrollPanel::ScrollPanel(int x,int y,int wide,int tall) : Panel(x,y,wide,tall)
{
	setPaintBorderEnabled(true);
	setPaintBackgroundEnabled(false);
	setPaintEnabled(false);

	_clientClip=new Panel(0,0,wide-16,tall-16);
	_clientClip->setParent(this);
	_clientClip->setBgColor(Color(0,128,0,0));
	_clientClip->setPaintBorderEnabled(true);
	_clientClip->setPaintBackgroundEnabled(false);
	_clientClip->setPaintEnabled(false);

	_client=new Panel(0,0,wide*2,tall*2);
	_client->setParent(_clientClip);
	_client->setPaintBorderEnabled(true);
	_client->setPaintBackgroundEnabled(false);
	_client->setPaintEnabled(false);

	_horizontalScrollBar=new ScrollBar(0,tall-16,wide-16,16,false);
	_horizontalScrollBar->setParent(this);
	_horizontalScrollBar->addIntChangeSignal(new ChangeHandler(this));
	_horizontalScrollBar->setVisible(false);

	_verticalScrollBar=new ScrollBar(wide-16,0,16,tall-16,true);
	_verticalScrollBar->setParent(this);
	_verticalScrollBar->addIntChangeSignal(new ChangeHandler(this));
	_verticalScrollBar->setVisible(false);

	_autoVisible[0]=true;
	_autoVisible[1]=true;

	validate();
}

void ScrollPanel::setSize(int wide,int tall)
{
	Panel::setSize(wide,tall);
	getPaintSize(wide,tall);

	if(_autoVisible[0])
	{
		_horizontalScrollBar->setVisible(!_horizontalScrollBar->hasFullRange());
	}

	if(_autoVisible[1])
	{
		_verticalScrollBar->setVisible(!_verticalScrollBar->hasFullRange());
	}

	if(_verticalScrollBar->isVisible())
	{
		wide-=_verticalScrollBar->getWide();
	}

	if(_horizontalScrollBar->isVisible())
	{
		tall-=_horizontalScrollBar->getTall();
	}

	_verticalScrollBar->setBounds(wide,0,_verticalScrollBar->getWide(),tall);
	_horizontalScrollBar->setBounds(0,tall,wide,_horizontalScrollBar->getTall());
	_clientClip->setSize(wide,tall);
	recomputeClientSize();
	repaint();
}

void ScrollPanel::setScrollBarVisible(bool horizontal,bool vertical)
{
	_horizontalScrollBar->setVisible(horizontal);
	_verticalScrollBar->setVisible(horizontal);

	validate();
}

Panel* ScrollPanel::getClient()
{
	return _client;
}

Panel* ScrollPanel::getClientClip()
{
	return _clientClip;
}

void ScrollPanel::setScrollValue(int horizontal,int vertical)
{
	_horizontalScrollBar->setValue(horizontal);
	_verticalScrollBar->setValue(horizontal);
	recomputeScroll();
}

void ScrollPanel::getScrollValue(int& horizontal,int& vertical)
{
	horizontal=_horizontalScrollBar->getValue();
	vertical=_verticalScrollBar->getValue();
}

void ScrollPanel::recomputeScroll()
{
	int x,y;
	getScrollValue(x,y);
	_client->setPos(-x,-y);
	_clientClip->repaint();
}

void ScrollPanel::setScrollBarAutoVisible(bool horizontal,bool vertical)
{
	_autoVisible[0]=horizontal;
	_autoVisible[1]=vertical;

	validate();
}

void ScrollPanel::recomputeClientSize()
{
	int wide=0;
	int tall=0;

	for(int i=0;i<_client->getChildCount();i++)
	{
		Panel* child=_client->getChild(i);
		if(child->isVisible())
		{
			int x,y,w,t;
			child->getPos(x,y);
			child->getVirtualSize(w,t);
			x+=w;
			y+=t;

			if(x>wide)
			{
				wide=x;
			}
			if(t>tall)
			{
				tall=t;
			}
		}
	}

	_client->setSize(wide,tall);

	_horizontalScrollBar->setRange(0,_client->getWide()-_clientClip->getWide());
	_horizontalScrollBar->setRangeWindow(_client->getWide());

	_verticalScrollBar->setRange(0,_client->getTall()-_clientClip->getTall());
	_verticalScrollBar->setRangeWindow(_client->getTall());
}

ScrollBar* ScrollPanel::getHorizontalScrollBar()
{
	return _horizontalScrollBar;
}

ScrollBar* ScrollPanel::getVerticalScrollBar()
{
	return _verticalScrollBar;
}

void ScrollPanel::validate()
{
	_horizontalScrollBar->setRangeWindowEnabled(true);
	_verticalScrollBar->setRangeWindowEnabled(true);

	int wide,tall;
	getSize(wide,tall);
	setSize(wide,tall);
	setSize(wide,tall);
	setSize(wide,tall);
	setSize(wide,tall);
}
