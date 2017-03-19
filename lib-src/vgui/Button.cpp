//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include "VGUI.h"
#include "VGUI_Button.h"
#include "VGUI_ButtonController.h"
#include "VGUI_InputSignal.h"
#include "VGUI_ButtonGroup.h"
#include "VGUI_TreeFolder.h"
#include "VGUI_ActionSignal.h"

using namespace vgui;

class FooDefaultButtonController : public ButtonController, public InputSignal
{
public:
	FooDefaultButtonController(Button* button)
	{
		_button=button;
	}
	void addSignals(Button* button)
	{
		button->addInputSignal(this);
	}
	void removeSignals(Button* button)
	{
		button->removeInputSignal(this);
	}
	void cursorMoved(int x,int y,Panel* panel)
	{
	}
	void cursorEntered(Panel* panel)
	{
	}
	void cursorExited(Panel* panel)
	{
	}
	void mousePressed(MouseCode code,Panel* panel)
	{
		if(_button->isEnabled()&&_button->isMouseClickEnabled(code))
		{
			_button->setSelected(true);
			_button->repaint();
		}
	}
	void mouseDoublePressed(MouseCode code,Panel* panel)
	{
	}
	void mouseReleased(MouseCode code,Panel* panel)
	{
		if(_button->isEnabled()&&_button->isMouseClickEnabled(code))
		{
			_button->setSelected(false);
			_button->fireActionSignal();
			_button->repaint();
		}
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
	Button* _button;
};

Button::Button(const char* text,int x,int y,int wide,int tall) : Label(text,x,y,wide,tall)
{
	init();
}

Button::Button(const char* text,int x,int y) : Label(text,x,y)
{
	init();
}

void Button::init()
{
	_armed=false;
	_selected=false;
	_buttonBorderEnabled=true;
	_mouseClickMask=0;
	_buttonController=null;
	_buttonGroup=null;
	setMouseClickEnabled(MOUSE_LEFT,true);
	setButtonController(new FooDefaultButtonController(this));
}

void Button::setSelected(bool state)
{
	if(_buttonGroup)
	{
		_buttonGroup->setSelected(this);
		return;
	}
	setSelectedDirect(state);
}

void Button::setSelectedDirect(bool state)
{
	_selected=state;
	repaint();
}

void Button::setArmed(bool state)
{
	_armed=state;
	repaint();
}

bool Button::isSelected()
{
	return _selected;
}

void Button::doClick()
{
	setSelected(true);
	fireActionSignal();
	setSelected(false);
}

void Button::addActionSignal(ActionSignal* s)
{
	_actionSignalDar.putElement(s);
}

void Button::setButtonGroup(ButtonGroup* buttonGroup)
{
	_buttonGroup=buttonGroup;
	if(_buttonGroup)
		_buttonGroup->addButton(this);
}

bool Button::isArmed()
{
	return false;
}

void Button::setButtonBorderEnabled(bool state)
{
	_buttonBorderEnabled=state;
	repaint();
}

void Button::setMouseClickEnabled(MouseCode code,bool state)
{
	if(state)
	{
		//set bit to 1
		_mouseClickMask|=1<<((int)(code+1));
	}
	else
	{
		//set bit to 0
		_mouseClickMask&=~(1<<((int)(code+1)));
	}	
}

bool Button::isMouseClickEnabled(MouseCode code)
{
	if(_mouseClickMask&(1<<((int)(code+1))))
	{
		return true;
	}
	return false;
}

void Button::fireActionSignal()
{
	for(int i=0;i<_actionSignalDar.getCount();i++)
		_actionSignalDar[i]->actionPerformed(this);
}

Panel* Button::createPropertyPanel()
{
	Panel* panel=Label::createPropertyPanel();
	TreeFolder* folder=new TreeFolder("Button");
	panel->addChild(folder);
	folder->addChild(new Label("setSelected"));
	folder->addChild(new Label("setArmed"));
	return panel;
}

void Button::setButtonController(ButtonController* buttonController)
{
	if(_buttonController)
		_buttonController->removeSignals(this);
	_buttonController=buttonController;
	_buttonController->addSignals(this);
}

void Button::paintBackground()
{
	int wide,tall;
	getPaintSize(wide,tall);

	if(isSelected())
	{
		drawSetColor(Scheme::sc_secondary2);
		drawFilledRect(0,0,wide,tall);
	}
	else
	{
		drawSetColor(Scheme::sc_secondary3);
		drawFilledRect(0,0,wide,tall);
		if(_buttonBorderEnabled)
		{
			drawSetColor(Scheme::sc_secondary1);
			drawFilledRect(0,0,_size[0]-1,1);
			drawFilledRect(2,_size[1]-2,_size[0]-1,_size[1]-1);
			drawFilledRect(0,1,1,_size[1]-1);
			drawFilledRect(_size[0]-2,2,_size[0]-1,_size[1]-2);
			drawSetColor(Scheme::sc_white);
			drawFilledRect(1,1,_size[0]-2,2);
			drawFilledRect(1,_size[1]-1,_size[0],_size[1]);
			drawFilledRect(1,2,2,_size[1]-2);
			drawFilledRect(_size[0]-1,1,_size[0],_size[1]-1);
		}
	}

	if(isArmed())
	{
		drawSetColor(Scheme::sc_white);
		drawFilledRect(0,0,wide,2);
		drawFilledRect(0,2,2,tall);
		drawSetColor(Scheme::sc_secondary2);
		drawFilledRect(2,tall-2,wide,tall);
		drawFilledRect(wide-2,2,wide,tall-1);
		drawSetColor(Scheme::sc_secondary1);
		drawFilledRect(1,tall-1,wide,tall);
		drawFilledRect(wide-1,1,wide,tall-1);
	}
}
