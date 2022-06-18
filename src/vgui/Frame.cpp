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

#include<VGUI_Frame.h>
#include<VGUI_InputSignal.h>
#include<VGUI_App.h>
#include<VGUI_Button.h>
#include<VGUI_FrameSignal.h>
#include<VGUI_ActionSignal.h>
#include<VGUI_SurfaceBase.h>

using namespace vgui;

namespace
{
class FooDraggerSignal : public InputSignal
{
protected:
	Frame* _frame;

public:
	FooDraggerSignal(Frame* frame)
	{
		_frame=frame;
		_dragging=false;
	}

public:
	virtual void moved(int dx,int dy,bool internal,Panel* panel,Panel* parent)
	{
	}

	virtual void cursorMoved(int x,int y,Panel* panel)
	{
		if(!_dragging)
			return;

		panel=panel->getParent();
		if(panel==null)
			return;

		panel->getApp()->getCursorPos(x,y);
		Frame* frame=dynamic_cast<Frame*>(panel);
		if(frame==null)
			return;

		if(frame->isInternal())
		{
			moved(x-_dragStart[0],y-_dragStart[1],true,panel,panel->getParent());
			if(panel->getParent()!=null)
				panel->getParent()->repaint();
			panel->repaint();
		}
		else
		{
			Panel* parent=panel->getParent();
			if(parent!=null)
			{
				moved(x-_dragStart[0],y-_dragStart[1],false,panel,parent);
				if(parent->getParent()!=null)
					parent->getParent()->repaint();
				parent->repaint();
			}
		}
	}

	virtual void cursorEntered(Panel* panel)
	{
	}

	virtual void cursorExited(Panel* panel)
	{
	}

	virtual void mouseDoublePressed(MouseCode code,Panel* panel)
	{
	}

	virtual void mousePressed(MouseCode code,Panel* panel)
	{
		Panel* opanel=panel->getParent();
		if(opanel==null)
			return;

		Frame* frame=dynamic_cast<Frame*>(opanel);
		if(frame==null)
			return;

		if(code==MOUSE_LEFT)
		{
			_dragging=true;

			int x,y;
			opanel->getApp()->getCursorPos(x,y);
			_dragStart[0]=x;
			_dragStart[1]=y;
			opanel->getPos(_dragOrgPos[0],_dragOrgPos[1]);
			opanel->getSize(_dragOrgSize[0],_dragOrgSize[1]);
			if(opanel->getParent()!=null)
			{
				opanel->getParent()->getPos(_dragOrgPos2[0],_dragOrgPos2[1]);
				opanel->getParent()->getSize(_dragOrgSize2[0],_dragOrgSize2[1]);

				int x0,y0,x1,y1;
				opanel->getParent()->getAbsExtents(x0,y0,x1,y1);
				opanel->getApp()->setMouseArena(x0,y0,x1,y1,true);

				Panel* parent=opanel->getParent();
				parent->removeChild(opanel);
				parent->addChild(opanel);
			}

			opanel->getApp()->setMouseCapture(panel);
			opanel->requestFocus();
			opanel->repaintAll();
		}
	}

	virtual void mouseReleased(MouseCode code,Panel* panel)
	{
		_dragging=false;
		panel->getApp()->setMouseArena(0,0,0,0,false);
		panel->getApp()->setMouseCapture(null);
	}

	virtual void mouseWheeled(int delta,Panel* panel){}
	virtual void keyPressed(KeyCode code,Panel* panel){}
	virtual void keyTyped(KeyCode code,Panel* panel){}
	virtual void keyReleased(KeyCode code,Panel* panel){}
	virtual void keyFocusTicked(Panel* panel){}

protected:
	bool _dragging;
	int _dragOrgPos[2];
	int _dragOrgPos2[2];
	int _dragOrgSize[2];
	int _dragOrgSize2[2];
	int _dragStart[2];
};

class FooTopGripSignal : public FooDraggerSignal
{
public:
	FooTopGripSignal(Frame* frame) : FooDraggerSignal(frame)
	{
	}

	virtual void moved(int dx,int dy,bool internal,Panel* panel,Panel* parent)
	{
		if(!_frame->isSizeable())
			return;

		if(internal)
		{
			panel->setPos(_dragOrgPos[0],_dragOrgPos[1]+dy);
			panel->setSize(_dragOrgSize[0],_dragOrgSize[1]-dy);
		}
		else
		{
			parent->setPos(_dragOrgPos2[0],_dragOrgPos2[1]+dy);
			parent->setSize(_dragOrgSize2[0],_dragOrgSize2[1]-dy);
		}
	}
};

class FooBottomGripSignal : public FooDraggerSignal
{
public:
	FooBottomGripSignal(Frame* frame) : FooDraggerSignal(frame)
	{
	}

	virtual void moved(int dx,int dy,bool internal,Panel* panel,Panel* parent)
	{
		if(!_frame->isSizeable())
			return;

		if(internal)
		{
			panel->setSize(_dragOrgSize[0],_dragOrgSize[1]+dy);
		}
		else
		{
			parent->setSize(_dragOrgSize2[0],_dragOrgSize2[1]+dy);
		}
	}
};

class FooLeftGripSignal : public FooDraggerSignal
{
public:
	FooLeftGripSignal(Frame* frame) : FooDraggerSignal(frame)
	{
	}

	virtual void moved(int dx,int dy,bool internal,Panel* panel,Panel* parent)
	{
		if(!_frame->isSizeable())
			return;

		if(internal)
		{
			panel->setPos(_dragOrgPos[0]+dx,_dragOrgPos[1]);
			panel->setSize(_dragOrgSize[0]-dx,_dragOrgSize[1]);
		}
		else
		{
			parent->setPos(_dragOrgPos2[0]+dx,_dragOrgPos2[1]);
			parent->setSize(_dragOrgSize2[0]-dx,_dragOrgSize2[1]);
		}
	}
};

class FooRightGripSignal : public FooDraggerSignal
{
public:
	FooRightGripSignal(Frame* frame) : FooDraggerSignal(frame)
	{
	}

	virtual void moved(int dx,int dy,bool internal,Panel* panel,Panel* parent)
	{
		if(!_frame->isSizeable())
			return;

		if(internal)
		{
			panel->setSize(_dragOrgSize[0]+dx,_dragOrgSize[1]);
		}
		else
		{
			parent->setSize(_dragOrgSize2[0]+dx,_dragOrgSize2[1]);
		}
	}
};

class FooTopLeftGripSignal : public FooDraggerSignal
{
public:
	FooTopLeftGripSignal(Frame* frame) : FooDraggerSignal(frame)
	{
	}

	virtual void moved(int dx,int dy,bool internal,Panel* panel,Panel* parent)
	{
		if(!_frame->isSizeable())
			return;

		if(internal)
		{
			panel->setPos(_dragOrgPos[0]+dx,_dragOrgPos[1]+dy);
			panel->setSize(_dragOrgSize[0]-dx,_dragOrgSize[1]-dy);
		}
		else
		{
			parent->setPos(_dragOrgPos2[0]+dx,_dragOrgPos2[1]+dy);
			parent->setSize(_dragOrgSize2[0]-dx,_dragOrgSize2[1]-dy);
		}
	}
};

class FooTopRightGripSignal : public FooDraggerSignal
{
public:
	FooTopRightGripSignal(Frame* frame) : FooDraggerSignal(frame)
	{
	}

	virtual void moved(int dx,int dy,bool internal,Panel* panel,Panel* parent)
	{
		if(!_frame->isSizeable())
			return;

		if(internal)
		{
			panel->setPos(_dragOrgPos[0],_dragOrgPos[1]+dy);
			panel->setSize(_dragOrgSize[0]+dx,_dragOrgSize[1]-dy);
		}
		else
		{
			parent->setPos(_dragOrgPos2[0],_dragOrgPos2[1]+dy);
			parent->setSize(_dragOrgSize2[0]+dx,_dragOrgSize2[1]-dy);
		}
	}
};

class FooBottomLeftGripSignal : public FooDraggerSignal
{
public:
	FooBottomLeftGripSignal(Frame* frame) : FooDraggerSignal(frame)
	{
	}

	virtual void moved(int dx,int dy,bool internal,Panel* panel,Panel* parent)
	{
		if(!_frame->isSizeable())
			return;

		if(internal)
		{
			panel->setPos(_dragOrgPos[0]+dx,_dragOrgPos[1]);
			panel->setSize(_dragOrgSize[0]-dx,_dragOrgSize[1]+dy);
		}
		else
		{
			parent->setPos(_dragOrgPos2[0]+dx,_dragOrgPos2[1]);
			parent->setSize(_dragOrgSize2[0]-dx,_dragOrgSize2[1]+dy);
		}
	}
};

class FooBottomRightGripSignal : public FooDraggerSignal
{
public:
	FooBottomRightGripSignal(Frame* frame) : FooDraggerSignal(frame)
	{
	}

	virtual void moved(int dx,int dy,bool internal,Panel* panel,Panel* parent)
	{
		if(!_frame->isSizeable())
			return;

		if(internal)
		{
			panel->setSize(_dragOrgSize[0]+dx,_dragOrgSize[1]+dy);
		}
		else
		{
			parent->setSize(_dragOrgSize2[0]+dx,_dragOrgSize2[1]+dy);
		}
	}
};

class FooCaptionGripSignal : public FooDraggerSignal
{
public:
	FooCaptionGripSignal(Frame* frame) : FooDraggerSignal(frame)
	{
	}

	virtual void moved(int dx,int dy,bool internal,Panel* panel,Panel* parent)
	{
		if(!_frame->isSizeable())
			return;

		if(internal)
		{
			panel->setPos(_dragOrgPos[0]+dx,_dragOrgPos[1]+dy);
		}
		else
		{
			parent->setPos(_dragOrgPos2[0]+dx,_dragOrgPos2[1]+dy);
		}
	}
};

class FooCloseButtonHandler : public ActionSignal
{
public:
	FooCloseButtonHandler(Frame* frame)
	{
		_frame=frame;
	}
public:
	virtual void actionPerformed(Panel* panel)
	{
		_frame->fireClosingSignal();
	}
protected:
	Frame* _frame;
};

class FooMinimizeButtonHandler : public ActionSignal
{
public:
	FooMinimizeButtonHandler(Frame* frame)
	{
		_frame=frame;
	}
public:
	virtual void actionPerformed(Panel* panel)
	{
		_frame->fireMinimizingSignal();
	}
protected:
	Frame* _frame;
};
}

Frame::Frame(int x,int y,int wide,int tall) : Panel(x,y,wide,tall)
{
	_title=null;
	_internal=true;
	_moveable=true;
	_sizeable=true;
	_title=vgui_strdup("Untitled");
	setMinimumSize(64,33);

	bool showGrip=false;

	_topGrip=new Panel(15,0,wide-30,5);
	_topGrip->setParent(this);
	_topGrip->setCursor(new Cursor(Cursor::dc_sizens));
	_topGrip->addInputSignal(new FooTopGripSignal(this));
	_topGrip->setPaintBorderEnabled(false);
	_topGrip->setPaintBackgroundEnabled(false);
	_topGrip->setPaintEnabled(false);

	_bottomGrip=new Panel(15,tall-5,wide-30,5);
	_bottomGrip->setParent(this);
	_bottomGrip->setCursor(new Cursor(Cursor::dc_sizens));
	_bottomGrip->addInputSignal(new FooBottomGripSignal(this));
	_bottomGrip->setPaintBorderEnabled(false);
	_bottomGrip->setPaintBackgroundEnabled(false);
	_bottomGrip->setPaintEnabled(false);

	_leftGrip=new Panel(0,15,5,tall-30);
	_leftGrip->setParent(this);
	_leftGrip->setCursor(new Cursor(Cursor::dc_sizewe));
	_leftGrip->addInputSignal(new FooLeftGripSignal(this));
	_leftGrip->setPaintBorderEnabled(false);
	_leftGrip->setPaintBackgroundEnabled(false);
	_leftGrip->setPaintEnabled(false);

	_rightGrip=new Panel(wide-5,15,5,tall-30);
	_rightGrip->setParent(this);
	_rightGrip->setCursor(new Cursor(Cursor::dc_sizewe));
	_rightGrip->addInputSignal(new FooRightGripSignal(this));
	_rightGrip->setPaintBorderEnabled(false);
	_rightGrip->setPaintBackgroundEnabled(false);
	_rightGrip->setPaintEnabled(false);

	_topLeftGrip=new Panel(0,0,15,15);
	_topLeftGrip->setParent(this);
	_topLeftGrip->setCursor(new Cursor(Cursor::dc_sizenwse));
	_topLeftGrip->addInputSignal(new FooTopLeftGripSignal(this));
	_topLeftGrip->setPaintBorderEnabled(false);
	_topLeftGrip->setPaintBackgroundEnabled(false);
	_topLeftGrip->setPaintEnabled(false);

	_topRightGrip=new Panel(wide-15,0,15,15);
	_topRightGrip->setParent(this);
	_topRightGrip->setCursor(new Cursor(Cursor::dc_sizenesw));
	_topRightGrip->addInputSignal(new FooTopRightGripSignal(this));
	_topRightGrip->setPaintBorderEnabled(false);
	_topRightGrip->setPaintBackgroundEnabled(false);
	_topRightGrip->setPaintEnabled(false);

	_bottomLeftGrip=new Panel(0,tall-15,15,15);
	_bottomLeftGrip->setParent(this);
	_bottomLeftGrip->setCursor(new Cursor(Cursor::dc_sizenesw));
	_bottomLeftGrip->addInputSignal(new FooBottomLeftGripSignal(this));
	_bottomLeftGrip->setPaintBorderEnabled(false);
	_bottomLeftGrip->setPaintBackgroundEnabled(false);
	_bottomLeftGrip->setPaintEnabled(false);

	_bottomRightGrip=new Panel(wide-15,tall-15,15,15);
	_bottomRightGrip->setParent(this);
	_bottomRightGrip->setCursor(new Cursor(Cursor::dc_sizenwse));
	_bottomRightGrip->addInputSignal(new FooBottomRightGripSignal(this));
	_bottomRightGrip->setPaintBorderEnabled(false);
	_bottomRightGrip->setPaintBackgroundEnabled(false);
	_bottomRightGrip->setPaintEnabled(false);

	_captionGrip=new Panel(5,5,wide-10,23);
	_captionGrip->setParent(this);
	_captionGrip->setCursor(new Cursor(Cursor::dc_sizeall));
	_captionGrip->addInputSignal(new FooCaptionGripSignal(this));
	_captionGrip->setPaintBorderEnabled(false);
	_captionGrip->setPaintBackgroundEnabled(false);
	_captionGrip->setPaintEnabled(false);

	_client=new Panel(5,29,wide-10,tall-34);
	_client->setParent(this);
	_client->addInputSignal(new FooDraggerSignal(this));

	_trayButton=new Button(".",wide-85,8,18,18);
	_trayButton->setParent(this);

	_minimizeButton=new Button("2",wide-65,8,18,18);
	_minimizeButton->setFont(Scheme::sf_secondary1);
	_minimizeButton->setParent(this);
	_minimizeButton->addActionSignal(new FooMinimizeButtonHandler(this));

	_maximizeButton=new Button("1",wide-45,8,18,18);
	_maximizeButton->setFont(Scheme::sf_secondary1);
	_maximizeButton->setParent(this);

	_closeButton=new Button("r",wide-25,8,18,18);
	_closeButton->setFont(Scheme::sf_secondary1);
	_closeButton->setParent(this);
	_closeButton->addActionSignal(new FooCloseButtonHandler(this));

	_menuButton=new Button("s",7,8,18,18);
	_menuButton->setFont(Scheme::sf_secondary1);
	_menuButton->setParent(this);
}

void Frame::setSize(int wide,int tall)
{
	if((getWide()==wide)&&(getTall()==tall))
	{
		return;
	}

	Panel::setSize(wide,tall);

	_topGrip->setBounds(15,0,_size[0]-30,5);
	_bottomGrip->setBounds(15,_size[1]-5,_size[0]-30,5);
	_leftGrip->setBounds(0,15,5,_size[1]-30);
	_rightGrip->setBounds(_size[0]-5,15,5,_size[1]-30);
	_topLeftGrip->setBounds(0,0,15,15);
	_topRightGrip->setBounds(_size[0]-15,0,15,15);
	_bottomLeftGrip->setBounds(0,_size[1]-15,15,15);
	_bottomRightGrip->setBounds(_size[0]-15,_size[1]-15,15,15);
	_captionGrip->setSize(_size[0]-10,23);
	_client->setSize(_size[0]-10,_size[1]-34);
	_trayButton->setPos(_size[0]-85,8);
	_minimizeButton->setPos(_size[0]-65,8);
	_maximizeButton->setPos(_size[0]-45,8);
	_closeButton->setPos(_size[0]-25,8);
	_client->invalidateLayout(false);
}

void Frame::setInternal(bool state)
{
	_internal=state;
}

bool Frame::isInternal()
{
	return _internal;
}

Panel* Frame::getClient()
{
	return _client;
}

void Frame::setTitle(const char* title)
{
	delete[] _title;
	_title=vgui_strdup(title);
	repaint();
}

void Frame::getTitle(char* buf,int bufLen)
{
	vgui_strcpy(buf,bufLen,_title);
}

void Frame::setMoveable(bool state)
{
	_moveable=state;
}

void Frame::setSizeable(bool state)
{
	_sizeable=state;
}

bool Frame::isMoveable()
{
	return _moveable;
}

bool Frame::isSizeable()
{
	return _sizeable;
}

void Frame::paintBackground()
{
	int wide=_size[0];
	int tall=_size[1];

	const int captionTall=23;

	Scheme::SchemeColor color1=Scheme::sc_secondary1;
	Scheme::SchemeColor color2=Scheme::sc_secondary2;
	Scheme::SchemeColor color3=Scheme::sc_secondary3;

	if(getSurfaceBase()->hasFocus())
	{
		Panel* trav=getApp()->getFocus();
		while(trav!=null)
		{
			if(trav==this)
			{
				color1=Scheme::sc_primary1;
				color2=Scheme::sc_primary2;
				color3=Scheme::sc_primary3;
			}
			trav=trav->getParent();
		}
	}

	drawSetColor(color3);
	drawFilledRect(5,5,wide-5,28);

	drawSetColor(Scheme::sc_white);
	drawFilledRect(120,10,wide-70,11);
	drawFilledRect(120,15,wide-70,16);
	drawFilledRect(120,20,wide-70,21);

	drawSetColor(color1);
	drawFilledRect(120,12,wide-70,13);
	drawFilledRect(120,17,wide-70,18);
	drawFilledRect(120,22,wide-70,23);

	drawSetColor(color1);
	drawFilledRect(1,0,wide-1,5);
	drawFilledRect(1,tall-5,wide-1,tall);
	drawFilledRect(0,1,5,tall-1);
	drawFilledRect(wide-5,1,wide,tall-1);
	drawFilledRect(5,5,6,6);
	drawFilledRect(wide-6,5,wide-5,6);
	drawFilledRect(5,28,wide-5,29);

	drawSetColor(Scheme::sc_black);
	drawFilledRect(13,2,wide-13,3);
	drawFilledRect(13,tall-3,wide-13,tall-2);
	drawFilledRect(2,13,3,tall-13);
	drawFilledRect(wide-3,13,wide-2,tall-13);

	drawSetColor(color2);
	drawFilledRect(14,3,wide-12,4);
	drawFilledRect(14,tall-2,wide-12,tall-1);
	drawFilledRect(3,14,4,tall-12);
	drawFilledRect(wide-2,14,wide-1,tall-12);

	if(_title!=null)
	{
		drawSetTextFont(Scheme::sf_primary1);
		drawSetTextColor(Scheme::sc_black);
		drawPrintText(28,7,_title,strlen(_title));
	}
}

void Frame::addFrameSignal(FrameSignal* s)
{
	_frameSignalDar.putElement(s);
}

void Frame::fireClosingSignal()
{
	for(int i=0;i<_frameSignalDar.getCount();i++)
	{
		_frameSignalDar[i]->closing(this);
	}
}

void Frame::fireMinimizingSignal()
{
	for(int i=0;i<_frameSignalDar.getCount();i++)
	{
		_frameSignalDar[i]->minimizing(this,false);
	}
}

void Frame::setVisible(bool state)
{
	Panel::setVisible(state);

	if(getParent()!=null)
	{
		getParent()->repaint();
	}
}

void Frame::setMenuButtonVisible(bool state)
{
	_menuButton->setVisible(state);
}

void Frame::setTrayButtonVisible(bool state)
{
	_trayButton->setVisible(state);
}

void Frame::setMinimizeButtonVisible(bool state)
{
	_minimizeButton->setVisible(state);
}

void Frame::setMaximizeButtonVisible(bool state)
{
	_maximizeButton->setVisible(state);
}

void Frame::setCloseButtonVisible(bool state)
{
	_closeButton->setVisible(state);
}
