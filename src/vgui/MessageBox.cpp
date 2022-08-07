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

#include<VGUI_MessageBox.h>
#include<VGUI_ActionSignal.h>
#include<VGUI_Label.h>
#include<VGUI_Button.h>

using namespace vgui;

namespace
{
class FooButtonHandler : public ActionSignal
{
private:
	MessageBox* _messageBox;
public:
	FooButtonHandler(MessageBox* messageBox)
	{
		_messageBox=messageBox;
	}
public:
	virtual void actionPerformed(Panel* panel)
	{
		_messageBox->fireActionSignal();
	}
};
}

MessageBox::MessageBox(const char* title,const char* text,int x,int y) : Frame(x,y,64,64)
{
	setTitle(title);
	setMenuButtonVisible(false);
	setTrayButtonVisible(false);
	setMinimizeButtonVisible(false);
	setMaximizeButtonVisible(false);
	setCloseButtonVisible(false);
	setSizeable(false);

	_messageLabel=new Label(text);
	_messageLabel->setParent(getClient());

	_okButton=new Button("Ok",10,10);
	_okButton->setParent(getClient());
	_okButton->addActionSignal(new FooButtonHandler(this));

	int wide,tall;
	_messageLabel->getSize(wide,tall);
	setSize(wide+100,tall+100);
}

void MessageBox::addActionSignal(ActionSignal* s)
{
	_actionSignalDar.putElement(s);
}

void MessageBox::fireActionSignal()
{
	for(int i=0;i<_actionSignalDar.getCount();i++)
	{
		_actionSignalDar[i]->actionPerformed(this);
	}
}

void MessageBox::performLayout()
{
	int wide,tall;
	getClient()->getSize(wide,tall);

	_messageLabel->setPos((wide/2)-(_messageLabel->getWide()/2),(tall/2)-(_messageLabel->getTall()/2));
	_okButton->setPos((wide/2)-(_okButton->getWide()/2),(tall/2)-(_okButton->getTall()/2));
}
