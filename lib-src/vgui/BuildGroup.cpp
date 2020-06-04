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

#include<assert.h>
#include<VGUI_BuildGroup.h>
#include<VGUI_ChangeSignal.h>
#include<VGUI_App.h>
#include<VGUI_Label.h>
#include<VGUI_LineBorder.h>

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

void BuildGroup::cursorMoved(int x,int y,Panel* panel)
{
	assert(panel);

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
			panel->setSize(_dragStartPanelPos[0]+(x-_dragStartCursorPos[0]),_dragStartPanelPos[1]+(y-_dragStartCursorPos[1]));
			applySnap(panel);
		}

		panel->repaintParent();
	}
}

void BuildGroup::mousePressed(MouseCode code,Panel* panel)
{
	assert(panel);

	if(code==MOUSE_RIGHT)
	{
		int lx,ly;
		panel->getApp()->getCursorPos(lx,ly);
		panel->screenToLocal(lx,ly);

		Panel *newPanel=new Label("Label",lx,ly,0,0);
		newPanel->setBorder(new LineBorder());
		newPanel->setParent(panel);
		newPanel->setBuildGroup(this, "Label");
		panel=newPanel;
	}

	_dragging=true;
	_dragMouseCode=code;
	panel->requestFocus();

	int x,y;
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
	assert(panel);

	_dragging=false;
	panel->getApp()->setMouseCapture(null);
}

void BuildGroup::mouseDoublePressed(MouseCode code,Panel* panel)
{
	assert(panel);
}

void BuildGroup::keyTyped(KeyCode code,Panel* panel)
{
	assert(panel);

	int dx=0;
	int dy=0;

	bool shift=(panel->isKeyDown(KEY_LSHIFT)||panel->isKeyDown(KEY_RSHIFT));
	bool ctrl=(panel->isKeyDown(KEY_LCONTROL)||panel->isKeyDown(KEY_RCONTROL));

	switch(code)
	{
		case KEY_LEFT:
		{
			dx-=_snapX;
			break;
		}
		case KEY_RIGHT:
		{
			dx+=_snapX;
			break;
		}
		case KEY_UP:
		{
			dy-=_snapY;
			break;
		}
		case KEY_DOWN:
		{
			dy+=_snapY;
			break;
		}
		case KEY_C:
		{
			if(ctrl)
			{
				copyPropertiesToClipboard();
			}
			break;
		}
	}

	if(dx||dy)
	{
		//TODO: make this stuff actually snap

		int x,y,wide,tall;

		panel->getBounds(x,y,wide,tall);

		if(shift)
		{
			panel->setSize(wide+dx,tall+dy);
		}
		else
		{
			panel->setPos(x+dx,y+dy);
		}

		applySnap(panel);

		panel->repaint();
		if(panel->getParent()!=null)
		{
			panel->getParent()->repaint();
		}
	}
}

Cursor* BuildGroup::getCursor(Panel* panel)
{
	assert(panel);
	
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

void BuildGroup::applySnap(Panel* panel)
{
	assert(panel);
	
	int x,y,wide,tall;
	panel->getBounds(x,y,wide,tall);

	x=(x/_snapX)*_snapX;
	y=(y/_snapY)*_snapY;
	panel->setPos(x,y);
	
	int xx,yy;
	xx=x+wide;
	yy=y+tall;
	
	xx=(xx/_snapX)*_snapX;
	yy=(yy/_snapY)*_snapY;
	panel->setSize(xx-x,yy-y);
}

void BuildGroup::addCurrentPanelChangeSignal(ChangeSignal* s)
{
	_currentPanelChangeSignalDar.putElement(s);
}

void BuildGroup::fireCurrentPanelChangeSignal()
{
	for(int i=0;i<_currentPanelChangeSignalDar.getCount();i++)
	{
		_currentPanelChangeSignalDar[i]->valueChanged(null);
	}
}

Panel* BuildGroup::getCurrentPanel()
{
	return _currentPanel;
}

void BuildGroup::panelAdded(Panel* panel,const char* panelName)
{
	assert(panel);

	_panelDar.addElement(panel);
	_panelNameDar.addElement(vgui_strdup(panelName));
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
