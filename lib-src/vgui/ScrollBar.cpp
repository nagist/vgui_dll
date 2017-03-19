//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include "VGUI.h"
#include "VGUI_ScrollBar.h"
#include "VGUI_Button.h"
#include "VGUI_Slider.h"

using namespace vgui;

ScrollBar::ScrollBar(int x,int y,int wide,int tall,bool vertical) : Panel(x,y,wide,tall)
{
	_slider=null;
	_button[0]=null;
	_button[1]=null;

	if(vertical)
	{
		setSlider(new Slider(0,wide-1,wide,tall-wide*2+2,true));
		setButton(new Button("",0,0,wide,wide),0);
		setButton(new Button("",0,tall-wide,wide,wide),1);
	}
	else
	{
		setSlider(new Slider(tall,0,wide-tall*2,tall,true));
		setButton(new Button("",0,0,tall+1,tall+1),0);
		setButton(new Button("",0,wide-tall,tall+1,tall+1),1);
	}

	setPaintBorderEnabled(true);
	setPaintBackgroundEnabled(true);
	setPaintEnabled(true);
	setButtonPressedScrollValue(15);
	validate();
}

void ScrollBar::setValue(int value)
{
}

int ScrollBar::getValue()
{
	return 0;
}

void ScrollBar::addIntChangeSignal(IntChangeSignal* s)
{
}
 
void ScrollBar::setRange(int min,int max)
{
}

void ScrollBar::setRangeWindow(int rangeWindow)
{
}

void ScrollBar::setRangeWindowEnabled(bool state)
{
}

void ScrollBar::setSize(int wide,int tall)
{
	Panel::setSize(wide,tall);

	if(!_slider||!_button[0]||!_button[1])
	{
		return;
	}

	getPaintSize(wide,tall);
	if(_slider->isVertical())
	{
		_slider->setBounds(0,wide,wide,tall-wide*2);
		_button[0]->setBounds(0,0,wide,wide);
		_button[1]->setBounds(0,tall-wide,wide,wide);
	}
	{
		_slider->setBounds(0,wide-tall*2,tall,tall);
		_button[0]->setBounds(0,0,tall,tall);
		_button[1]->setBounds(wide-tall,0,tall,tall);
	}
}

bool ScrollBar::isVertical()
{
	return false;
}

bool ScrollBar::hasFullRange()
{
	return false;
}

void ScrollBar::setButton(Button* button,int index)
{
}

Button* ScrollBar::getButton(int index)
{
	return null;
}

void ScrollBar::setSlider(Slider* slider)
{
}

Slider* ScrollBar::getSlider()
{
	return null;
}

void ScrollBar::doButtonPressed(int buttonIndex)
{
}

void ScrollBar::setButtonPressedScrollValue(int value)
{
}

void ScrollBar::validate()
{
}

void ScrollBar::fireIntChangeSignal()
{
}

void ScrollBar::performLayout()
{
}

