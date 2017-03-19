//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include "VGUI.h"
#include "VGUI_ToggleButton.h"
#include "VGUI_ButtonController.h"
#include "VGUI_InputSignal.h"

using namespace vgui;

class FooDefaultToggleButtonController : public ButtonController, public InputSignal
{
public:
	FooDefaultToggleButtonController(ToggleButton* button)
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
		_button->setSelected(!_button->isEnabled());
		_button->fireActionSignal();
		_button->repaint();
	}
	void mouseDoublePressed(MouseCode code,Panel* panel)
	{
	}
	void mouseReleased(MouseCode code,Panel* panel)
	{
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
	ToggleButton* _button;
};

ToggleButton::ToggleButton(const char* text,int x,int y,int wide,int tall) : Button(text,x,y,wide,tall)
{
	setButtonController(new FooDefaultToggleButtonController(this));
}

ToggleButton::ToggleButton(const char* text,int x,int y) : Button(text,x,y)
{
	setButtonController(new FooDefaultToggleButtonController(this));
}
