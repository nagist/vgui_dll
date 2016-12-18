//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include "VGUI.h"
#include "VGUI_DesktopIcon.h"
#include "VGUI_Image.h"
#include "VGUI_InputSignal.h"
#include "VGUI_App.h"
#include "VGUI_Desktop.h"
#include "VGUI_Font.h"
#include "VGUI_MiniApp.h"

using namespace vgui;

class FooHandler : public InputSignal
{
public:
	FooHandler(DesktopIcon* desktopIcon)
	{
		_desktopIcon=desktopIcon;
		_dragging=false;
	}
	void cursorMoved(int x,int y,Panel* panel)
	{
		if(_dragging)
		{
			panel->getApp()->getCursorPos(x,y);
			_desktopIcon->setPos(x+_dragOrgPos[0]-_dragStart[0],y+_dragOrgPos[1]-_dragStart[1]);
			if(_desktopIcon->getParent())
				_desktopIcon->getParent()->repaint();
		}
	}
	void cursorEntered(Panel* panel)
	{
	}
	void cursorExited(Panel* panel)
	{
	}
	void mousePressed(MouseCode code,Panel* panel)
	{
		int x,y;
		panel->getApp()->getCursorPos(x,y);
		_dragging=true;
		_dragStart[0]=x;
		_dragStart[1]=y;
		_desktopIcon->getPos(_dragStart[0],_dragStart[1]);
		panel->getApp()->setMouseCapture(panel);
		_desktopIcon->requestFocus();
	}
	void mouseDoublePressed(MouseCode code,Panel* panel)
	{
		_desktopIcon->doActivate();
	}
	void mouseReleased(MouseCode code,Panel* panel)
	{
		_dragging=false;
		panel->getApp()->setMouseCapture(null);
	}
	void mouseWheeled(int delta,Panel* panel)
	{
	}
	void keyPressed(KeyCode code,Panel* panel)
	{
	}
	void keyTyped(KeyCode code,Panel* panel)
	{
	}
	void keyReleased(KeyCode code,Panel* panel)
	{
	}
	void keyFocusTicked(Panel* panel)
	{
	}
private:
	DesktopIcon* _desktopIcon;
	bool _dragging;
	int _dragOrgPos[2];
	int _dragStart[2];
};

using namespace vgui;

DesktopIcon::DesktopIcon(MiniApp* miniApp,Image* image) : Panel(0,0,32,50)
{
	_desktop=null;
	_miniApp=miniApp;
	setImage(image);

	if(image)
	{
		int wide,tall;
		image->getSize(wide,tall);
		setSize(wide,tall);
	}

	addInputSignal(new FooHandler(this));
}

void DesktopIcon::doActivate()
{
	if(_desktop)
		_desktop->iconActivated(this);
}

void DesktopIcon::setImage(Image* image)
{
	_image=image;
	if(_image)
	{
		int wide,tall;
		_image->getSize(wide,tall);
		//_image->setSize(wide,tall);
	}
}

void DesktopIcon::setDesktop(Desktop* desktop)
{
	_desktop=desktop;
}

MiniApp* DesktopIcon::getMiniApp()
{
	return _miniApp;
}

void DesktopIcon::paintBackground()
{
	Panel::paintBackground();

	int wide,tall;
	getPaintSize(wide,tall);

	if(_image)
		_image->doPaint(this);

	Font* font=getApp()->getScheme()->getFont(Scheme::sf_primary2);
	drawSetTextFont(Scheme::sf_primary1);
	drawSetTextColor(Scheme::sc_black);
	if(_miniApp)
	{
		char buf[256];
		_miniApp->getName(buf,sizeof(buf));

		int textwide,texttall;
		font->getTextSize(buf,textwide,texttall);
		drawSetTextColor(255,255,255,0);
		drawSetTextPos(wide/2-textwide/2, tall-20);
		drawPrintText(buf,strlen(buf));
	}
}
