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
