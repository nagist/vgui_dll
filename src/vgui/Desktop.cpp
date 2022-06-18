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

#include<VGUI_Desktop.h>
#include<VGUI_TaskBar.h>
#include<VGUI_DesktopIcon.h>
#include<VGUI_MiniApp.h>
#include<VGUI_Frame.h>

using namespace vgui;

Desktop::Desktop(int x,int y,int wide,int tall) : Panel(x,y,wide,tall)
{
	setBgColor(0,128,128,0);
	setPaintBorderEnabled(false);
	setPaintBackgroundEnabled(false);
	setPaintEnabled(false);

	_background=new Panel(0,0,wide,tall-36);
	_background->setParent(this);
	_background->setBgColor(0,128,128,0);
	_foreground=new Panel(0,0,wide,tall-36);
	_foreground->setPaintBorderEnabled(false);
	_foreground->setPaintBackgroundEnabled(false);
	_foreground->setPaintEnabled(false);
	_foreground->setParent(this);

	_taskBar=new TaskBar(0,tall-36,wide,36);
	_taskBar->setParent(this);

	_cascade[0]=50;
	_cascade[1]=50;
}

void Desktop::setSize(int wide,int tall)
{
	Panel::setSize(wide,tall);
	getPaintSize(wide,tall);

	_background->setBounds(0,0,wide,tall-36);
	_foreground->setBounds(0,0,wide,tall-36);
	_taskBar->setBounds(0,tall-36,wide,36);
}

Panel* Desktop::getBackground()
{
	return _background;
}

Panel* Desktop::getForeground()
{
	return _foreground;
}

void Desktop::addIcon(DesktopIcon* icon)
{
	icon->setDesktop(this);
	icon->setParent(_foreground);
	icon->setPos(10,10);
	_desktopIconDar.addElement(icon);
}

void Desktop::iconActivated(DesktopIcon* icon)
{
	MiniApp* miniApp=icon->getMiniApp();
	Frame* frame=miniApp->createInstance();

	if(frame!=null)
	{
		frame->setPos(_cascade[0],_cascade[1]);
		frame->setParent(_foreground);
		_taskBar->addFrame(frame);
		frame->requestFocus();

		_cascade[0]+=25;
		_cascade[1]+=50;

		if(_cascade[1]>400)
		{
			_cascade[0]=50;
			_cascade[1]=50;
		}
	}
}

void Desktop::arrangeIcons()
{
	int x=15;
	int y=10;
	for(int i=0;i<_desktopIconDar.getCount();i++)
	{
		_desktopIconDar[i]->setPos(x,y);
		y+=60;

		if(y>340)
		{
			x+=50;
			y=10;
		}
	}
}
