//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include<VGUI_Desktop.h>
#include<VGUI_TaskBar.h>
#include<VGUI_DesktopIcon.h>
#include<VGUI_MiniApp.h>
#include<VGUI_Frame.h>

using namespace vgui;

Desktop::Desktop(int x,int y,int wide,int tall) : Panel(x,y,wide,tall)
{
	setBgColor(0,128,128,0);
	setPaintBorderEnabled(false);
	setPaintBackgroundEnabled(false);
	setPaintEnabled(false);

	_background=new Panel(0,0,wide,tall-36);
	_background->setParent(this);
	_background->setBgColor(0,128,128,0);
	_foreground=new Panel(0,0,wide,tall-36);
	_foreground->setPaintBorderEnabled(false);
	_foreground->setPaintBackgroundEnabled(false);
	_foreground->setPaintEnabled(false);
	_foreground->setParent(this);

	_taskBar=new TaskBar(0,tall-36,wide,36);
	_taskBar->setParent(this);

	_cascade[0]=50;
	_cascade[1]=50;
}

void Desktop::setSize(int wide,int tall)
{
	Panel::setSize(wide,tall);
	getPaintSize(wide,tall);

	_background->setBounds(0,0,wide,tall-36);
	_foreground->setBounds(0,0,wide,tall-36);
	_taskBar->setBounds(0,tall-36,wide,36);
}

Panel* Desktop::getBackground()
{
	return _background;
}

Panel* Desktop::getForeground()
{
	return _foreground;
}

void Desktop::addIcon(DesktopIcon* icon)
{
	icon->setDesktop(this);
	icon->setParent(_foreground);
	icon->setPos(10,10);
	_desktopIconDar.addElement(icon);
}

void Desktop::iconActivated(DesktopIcon* icon)
{
	MiniApp* miniApp=icon->getMiniApp();
	Frame* frame=miniApp->createInstance();

	if(frame!=null)
	{
		frame->setPos(_cascade[0],_cascade[1]);
		frame->setParent(_foreground);
		_taskBar->addFrame(frame);
		frame->requestFocus();

		_cascade[0]+=25;
		_cascade[1]+=50;

		if(_cascade[1]>400)
		{
			_cascade[0]=50;
			_cascade[1]=50;
		}
	}
}

void Desktop::arrangeIcons()
{
	int x=15;
	int y=10;
	for(int i=0;i<_desktopIconDar.getCount();i++)
	{
		_desktopIconDar[i]->setPos(x,y);
		y+=60;

		if(y>340)
		{
			x+=50;
			y=10;
		}
	}
}
