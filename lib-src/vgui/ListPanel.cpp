//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include<VGUI_ListPanel.h>
#include<VGUI_StackLayout.h>
#include<VGUI_ScrollBar.h>
#include<VGUI_IntChangeSignal.h>
#include<VGUI_Label.h>

using namespace vgui;

namespace
{
class FooDefaultListPanelSignal : public IntChangeSignal
{
public:
	FooDefaultListPanelSignal(ListPanel* listPanel)
	{
		_listPanel=listPanel;
	}
	virtual void intChanged(int value,Panel* panel)
	{
		_listPanel->setPixelScroll(-value);
	}
protected:
	ListPanel* _listPanel;
};
}

ListPanel::ListPanel(int x,int y,int wide,int tall) : Panel(x,y,wide,tall)
{
	_vpanel=new Panel(0,0,wide-15,tall*2);
	_vpanel->setParent(this);

	setLayout(new StackLayout(1,false));
	setBgColor(0,0,100,0);

	_scroll=new ScrollBar(wide-15,0,15,tall,true);
	_scroll->setParent(this);
	_scroll->addIntChangeSignal(new FooDefaultListPanelSignal(this));
}

void ListPanel::paintBackground()
{
	Panel::paintBackground();
}

void ListPanel::addString(const char* str)
{
	addItem(new Label(str,0,0,80,20));
}

void ListPanel::addItem(Panel* panel)
{
	panel->setParent(_vpanel);
	_vpanel->invalidateLayout(true);
	Panel* last=_vpanel->getChild(_vpanel->getChildCount()-1);
	int x,y,wide,tall,vwide,vtall;
	last->getBounds(x,y,wide,tall);
	_vpanel->getSize(vwide,vtall);
	_vpanel->setSize(vwide,y+tall);
	_scroll->setRange(0,y+tall-_size[1]);
}

void ListPanel::setSize(int wide,int tall)
{
	Panel::setSize(wide,tall);
	invalidateLayout(false);
}

void ListPanel::performLayout()
{
	Panel* last=_vpanel->getChild(_vpanel->getChildCount()-1);
	if(last==null)
	{
		return;
	}

	int x,y,wide,tall;
	last->getBounds(x,y,wide,tall);

	int vwide,vtall;
	_vpanel->getSize(vwide,vtall);
	_vpanel->setSize(_size[0]-15,tall);
	_scroll->setBounds(_size[0]-15,0,15,_size[1]);
	_scroll->setRange(0,y+tall-_size[1]);
}

void ListPanel::setPixelScroll(int value)
{
	_vpanel->setPos(0,value);
	repaint();
	_vpanel->repaint();
}

void ListPanel::translatePixelScroll(int delta)
{
	int x,y;
	_vpanel->getPos(x,y);
	_vpanel->setPos(0,y+delta);
	repaint();
	_vpanel->repaint();
}
