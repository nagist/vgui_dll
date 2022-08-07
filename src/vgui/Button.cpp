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

#include<VGUI_Button.h>
#include<VGUI_ButtonController.h>
#include<VGUI_InputSignal.h>
#include<VGUI_ButtonGroup.h>
#include<VGUI_TreeFolder.h>
#include<VGUI_ActionSignal.h>

using namespace vgui;

namespace
{
class FooDefaultButtonController : public ButtonController, public InputSignal
{
public:
	FooDefaultButtonController(Button* button)
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
		if(_button->isEnabled())
		{
			if(_button->isMouseClickEnabled(code))
			{
				_button->setSelected(true);
				_button->repaint();
			}
		}
	}
	virtual void mouseDoublePressed(MouseCode code,Panel* panel)
	{
	}
	virtual void mouseReleased(MouseCode code,Panel* panel)
	{
		if(_button->isEnabled())
		{
			if(_button->isMouseClickEnabled(code))
			{
				_button->setSelected(false);
				_button->fireActionSignal();
				_button->repaint();
			}
		}
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
	Button* _button;
};
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

Button::Button(const char* text,int x,int y,int wide,int tall) : Label(text,x,y,wide,tall)
{
	init();
}

Button::Button(const char* text,int x,int y) : Label(text,x,y)
{
	init();
}

void Button::setButtonBorderEnabled(bool state)
{
	_buttonBorderEnabled=state;
	repaint();
}

void Button::setSelected(bool state)
{
	if(_buttonGroup!=null)
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

bool Button::isArmed()
{
	return _armed;
}

void Button::doClick()
{
	setSelected(true);
	fireActionSignal();
	setSelected(false);
}

bool Button::isSelected()
{
	return _selected;
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
			drawFilledRect(0,0,_size[0]-1,1);                   // top
			drawFilledRect(2,_size[1]-2,_size[0]-1,_size[1]-1); // bottom
			drawFilledRect(0,1,1,_size[1]-1);                   // left
			drawFilledRect(_size[0]-2,2,_size[0]-1,_size[1]-2); // right

			drawSetColor(Scheme::sc_white);
			drawFilledRect(1,1,_size[0]-2,2);                 // top
			drawFilledRect(1,_size[1]-1,_size[0],_size[1]);   // bottom
			drawFilledRect(1,2,2,_size[1]-2);                 // left
			drawFilledRect(_size[0]-1,1,_size[0],_size[1]-1); // right
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

void Button::setButtonGroup(ButtonGroup* buttonGroup)
{
	_buttonGroup=buttonGroup;

	if(_buttonGroup!=null)
	{
		_buttonGroup->addButton(this);
	}
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

void Button::addActionSignal(ActionSignal* s)
{
	_actionSignalDar.putElement(s);
}

void Button::fireActionSignal()
{
	for(int i=0;i<_actionSignalDar.getCount();i++)
	{
		_actionSignalDar[i]->actionPerformed(this);
	}
}

void Button::setButtonController(ButtonController* buttonController)
{
	if(_buttonController!=null)
	{
		_buttonController->removeSignals(this);
	}

	_buttonController=buttonController;
	_buttonController->addSignals(this);
}

Panel* Button::createPropertyPanel()
{
	Panel* parentPropertyPanel=Label::createPropertyPanel();

	TreeFolder* folder=new TreeFolder("Button");
	parentPropertyPanel->addChild(folder);
	folder->addChild(new Label("setSelected"));
	folder->addChild(new Label("setArmed"));

	return parentPropertyPanel;
}
