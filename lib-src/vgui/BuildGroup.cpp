//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include "VGUI.h"
#include "VGUI_BuildGroup.h"
#include "VGUI_Cursor.h"
#include "VGUI_Panel.h"
#include "VGUI_ChangeSignal.h"
#include "VGUI_App.h"
#include "VGUI_Label.h"
#include "VGUI_LineBorder.h"

using namespace vgui;

BuildGroup::BuildGroup()
{
	_enabled=false;
	_snapX=4;
	_snapY=4;
	_cursor_sizenwse=new Cursor(Cursor::dc_sizenwse);
	_cursor_sizenesw=new Cursor(Cursor::dc_sizenesw);
	_cursor_sizewe=new Cursor(Cursor::dc_sizewe);
	_cursor_sizens=new Cursor(Cursor::dc_sizens);
	_cursor_sizeall=new Cursor(Cursor::dc_sizeall);
	_currentPanel=null;
	_dragging=false;
}

void BuildGroup::setEnabled(bool state)
{
	if(_enabled!=state)
	{
		if(_currentPanel!=null)
		{
			_currentPanel=null;
			fireCurrentPanelChangeSignal();
		}
		_currentPanel=null;
	}
	_enabled=state;
}

bool BuildGroup::isEnabled()
{
	return _enabled;
}

void BuildGroup::addCurrentPanelChangeSignal(ChangeSignal* s)
{
	_currentPanelChangeSignalDar.putElement(s);
}

Panel* BuildGroup::getCurrentPanel()
{
	return _currentPanel;
}

void BuildGroup::copyPropertiesToClipboard()
{
	char text[32768];
	text[0]=0;
	for(int i=0;i<_panelDar.getCount();i++)
	{
		char buf[512];
		_panelDar[i]->getPersistanceText(buf,sizeof(buf));
		strcat(text,_panelNameDar[i]);
		strcat(text,buf);
	}
	App::getInstance()->setClipboardText(text,strlen(text));
	vgui_printf("Copied to clipboard\n");
}

void BuildGroup::applySnap(Panel* panel)
{
	int x,y,wide,tall;
	panel->getBounds(x,y,wide,tall);
	x = _snapX*(x/_snapX);
	y = _snapY*(y/_snapY);
	panel->setPos(x,y);
	panel->setSize(_snapX*((x+wide)/_snapX)-x,_snapY*((y+tall)/_snapY)-y);
}

void BuildGroup::fireCurrentPanelChangeSignal()
{
	for(int i=0;i<_currentPanelChangeSignalDar.getCount();i++)
		_currentPanelChangeSignalDar[i]->valueChanged(null);
}

void BuildGroup::panelAdded(Panel* panel,const char* panelName)
{
	_panelDar.addElement(panel);
	_panelNameDar.addElement(vgui_strdup(panelName));
}

void BuildGroup::cursorMoved(int x,int y,Panel* panel)
{
	if(_dragging)
	{
		panel->getApp()->getCursorPos(x,y);
		if(_dragMouseCode==MOUSE_RIGHT)
		{
			panel->setSize(x-_dragStartCursorPos[0],y-_dragStartCursorPos[1]);
			applySnap(panel);
		}
		else
		{
			panel->setSize(_dragStartPanelPos[0]+x-_dragStartCursorPos[0],_dragStartPanelPos[1]+y-_dragStartCursorPos[1]);
			applySnap(panel);
		}
		panel->repaintParent();
	}
}

void BuildGroup::mousePressed(MouseCode code,Panel* panel)
{
	int x,y;
	panel->getApp()->getCursorPos(x,y);
	panel->screenToLocal(x,y);

	if(code==MOUSE_RIGHT)
	{
		Label *label=new Label("Label",x,y,0,0);
		label->setBorder(new LineBorder());
		label->setParent(panel);
		label->setBuildGroup(this, "Label");
		panel=label;
	}

	_dragging=true;
	_dragMouseCode=code;
	panel->requestFocus();

	panel->getApp()->getCursorPos(x,y);
	_dragStartCursorPos[0]=x;
	_dragStartCursorPos[1]=y;

	panel->getPos(x,y);
	_dragStartPanelPos[0]=x;
	_dragStartPanelPos[1]=y;

	panel->getApp()->setMouseCapture(panel);

	if(_currentPanel!=panel)
	{
		_currentPanel=panel;
		fireCurrentPanelChangeSignal();
	}
}

void BuildGroup::mouseReleased(MouseCode code,Panel* panel)
{
	_dragging=false;
	panel->getApp()->setMouseCapture(null);
}

void BuildGroup::mouseDoublePressed(MouseCode code,Panel* panel)
{
}

void BuildGroup::keyTyped(KeyCode code,Panel* panel)
{
	int dx=0;
	int dy=0;

	bool shift=(panel->isKeyDown(KEY_LSHIFT)||panel->isKeyDown(KEY_RSHIFT));
	bool ctrl=(panel->isKeyDown(KEY_LCONTROL)||panel->isKeyDown(KEY_RCONTROL));

	switch(code)
	{
	case KEY_LEFT:
		dx=-_snapX;
		break;
	case KEY_RIGHT:
		dx=_snapX;
		break;
	case KEY_UP:
		dy=-_snapY;
		break;
	case KEY_DOWN:
		dy=_snapY;
		break;
	case KEY_C:
		if(ctrl)
			copyPropertiesToClipboard();
		break;
	}

	if(dx||dy)
	{
		int x,y,wide,tall;
		panel->getBounds(x,y,wide,tall);
		if(shift)
			panel->setSize(dx+wide,dy+tall);
		else
			panel->setPos(dx+x,dy+y);

		applySnap(panel);
		panel->repaint();

		if(panel->getParent())
			panel->getParent()->repaint();
	}
}

Cursor* BuildGroup::getCursor(Panel* panel)
{
	int x,y,wide,tall;
	panel->getApp()->getCursorPos(x,y);
	panel->screenToLocal(x,y);
	panel->getSize(wide,tall);

	if(x < 2)
	{
		if(y < 4)
		{
			return _cursor_sizenwse;
		}
		else
		if(y<(tall-4))
		{
			return _cursor_sizewe;
		}
		else
		{
			return _cursor_sizenesw;
		}
	}

	return _cursor_sizeall;
}
