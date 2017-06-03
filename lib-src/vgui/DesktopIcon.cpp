//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include<VGUI_DesktopIcon.h>
#include<VGUI_Image.h>
#include<VGUI_InputSignal.h>
#include<VGUI_App.h>
#include<VGUI_Desktop.h>
#include<VGUI_Font.h>
#include<VGUI_MiniApp.h>

using namespace vgui;

namespace
{
class FooHandler : public InputSignal
{
public:
	FooHandler(DesktopIcon* desktopIcon)
	{
		_desktopIcon=desktopIcon;
		_dragging=false;
	}
public:
	virtual void cursorMoved(int x,int y,Panel* panel)
	{
		if(_dragging)
		{
			panel->getApp()->getCursorPos(x,y);
			_desktopIcon->setPos(x+_dragOrgPos[0]-_dragStart[0],y+_dragOrgPos[1]-_dragStart[1]);

			if(_desktopIcon->getParent()!=null)
			{
				_desktopIcon->getParent()->repaint();
			}
		}
	}
	virtual void cursorEntered(Panel* panel)
	{
	}
	virtual void cursorExited(Panel* panel)
	{
	}
	virtual void mousePressed(MouseCode code,Panel* panel)
	{
		int x,y;
		panel->getApp()->getCursorPos(x,y);
		_dragging=true;
		_dragStart[0]=x;
		_dragStart[1]=y;
		_desktopIcon->getPos(_dragOrgPos[0],_dragOrgPos[1]);

		panel->getApp()->setMouseCapture(panel);
		_desktopIcon->requestFocus();
	}
	virtual void mouseDoublePressed(MouseCode code,Panel* panel)
	{
		_desktopIcon->doActivate();
	}
	virtual void mouseReleased(MouseCode code,Panel* panel)
	{
		_dragging=false;
		panel->getApp()->setMouseCapture(null);
	}
	virtual void mouseWheeled(int delta,Panel* panel)
	{
	}
	virtual void keyPressed(KeyCode code,Panel* panel)
	{
	}
	virtual void keyTyped(KeyCode code,Panel* panel)
	{
	}
	virtual void keyReleased(KeyCode code,Panel* panel)
	{
	}
	virtual void keyFocusTicked(Panel* panel)
	{
	}
protected:
	DesktopIcon* _desktopIcon;
	bool _dragging;
	int _dragOrgPos[2];
	int _dragStart[2];
};
}

DesktopIcon::DesktopIcon(MiniApp* miniApp,Image* image) : Panel(0,0,32,50)
{
	_desktop=null;
	_miniApp=miniApp;
	setImage(image);

	if(image!=null)
	{
		int wide,tall;
		image->getSize(wide,tall);
		setSize(wide,tall);
	}

	addInputSignal(new FooHandler(this));
}

void DesktopIcon::paintBackground()
{
	Panel::paintBackground();

	int wide,tall;
	getPaintSize(wide,tall);

	if(_image!=null)
	{
		_image->doPaint(this);
	}

	Font* font=getApp()->getScheme()->getFont(Scheme::sf_primary2);

	drawSetTextFont(Scheme::sf_primary1);
	drawSetTextColor(Scheme::sc_black);

	if(_miniApp!=null)
	{
		char buf[256];
		_miniApp->getName(buf,sizeof(buf));
		int tWide,tTall;
		font->getTextSize(buf,tWide,tTall);
		drawSetTextColor(255,255,255,0);
		drawSetTextPos(wide/2-(tWide/2),tall-20);
		drawPrintText(buf,strlen(buf));
	}
}

void DesktopIcon::setDesktop(Desktop* desktop)
{
	_desktop=desktop;
}

void DesktopIcon::doActivate()
{
	if(_desktop!=null)
	{
		_desktop->iconActivated(this);
	}
}

void DesktopIcon::setImage(Image* image)
{
	_image=image;

	if(_image!=null)
	{
		int wide,tall;
		_image->getSize(wide,tall);
		setSize(wide,tall);
	}
}

MiniApp* DesktopIcon::getMiniApp()
{
	return _miniApp;
}
