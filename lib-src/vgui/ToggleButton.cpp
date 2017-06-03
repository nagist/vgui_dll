//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include<VGUI_ToggleButton.h>
#include<VGUI_ButtonController.h>
#include<VGUI_InputSignal.h>

using namespace vgui;

namespace
{
class FooDefaultToggleButtonController : public ButtonController, public InputSignal
{
public:
	FooDefaultToggleButtonController(ToggleButton* button)
	{
		_button=button;
	}
public:
	virtual void addSignals(Button* button)
	{
		button->addInputSignal(this);
	}
	virtual void removeSignals(Button* button)
	{
		button->removeInputSignal(this);
	}
public:
	virtual void cursorMoved(int x,int y,Panel* panel)
	{
	}
	virtual void cursorEntered(Panel* panel)
	{
	}
	virtual void cursorExited(Panel* panel)
	{
	}
	virtual void mousePressed(MouseCode code,Panel* panel)
	{
		_button->setSelected(!_button->isEnabled());
		_button->fireActionSignal();
		_button->repaint();
	}
	virtual void mouseDoublePressed(MouseCode code,Panel* panel)
	{
	}
	virtual void mouseReleased(MouseCode code,Panel* panel)
	{
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
	ToggleButton* _button;
};

}

ToggleButton::ToggleButton(const char* text,int x,int y,int wide,int tall) : Button(text,x,y,wide,tall)
{
	setButtonController(new FooDefaultToggleButtonController(this));
}

ToggleButton::ToggleButton(const char* text,int x,int y) : Button(text,x,y)
{
	setButtonController(new FooDefaultToggleButtonController(this));
}
