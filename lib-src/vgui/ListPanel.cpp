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

#include<VGUI_ListPanel.h>
#include<VGUI_StackLayout.h>
#include<VGUI_ScrollBar.h>
#include<VGUI_IntChangeSignal.h>
#include<VGUI_Label.h>

using namespace vgui;

namespace
{
class FooDefaultListPanelSignal : public IntChangeSignal
{
public:
	FooDefaultListPanelSignal(ListPanel* listPanel)
	{
		_listPanel=listPanel;
	}
	virtual void intChanged(int value,Panel* panel)
	{
		_listPanel->setPixelScroll(-value);
	}
protected:
	ListPanel* _listPanel;
};
}

ListPanel::ListPanel(int x,int y,int wide,int tall) : Panel(x,y,wide,tall)
{
	_vpanel=new Panel(0,0,wide-15,tall*2);
	_vpanel->setParent(this);

	setLayout(new StackLayout(1,false));
	setBgColor(0,0,100,0);

	_scroll=new ScrollBar(wide-15,0,15,tall,true);
	_scroll->setParent(this);
	_scroll->addIntChangeSignal(new FooDefaultListPanelSignal(this));
}

void ListPanel::paintBackground()
{
	Panel::paintBackground();
}

void ListPanel::addString(const char* str)
{
	addItem(new Label(str,0,0,80,20));
}

void ListPanel::addItem(Panel* panel)
{
	panel->setParent(_vpanel);
	_vpanel->invalidateLayout(true);
	Panel* last=_vpanel->getChild(_vpanel->getChildCount()-1);
	int x,y,wide,tall,vwide,vtall;
	last->getBounds(x,y,wide,tall);
	_vpanel->getSize(vwide,vtall);
	_vpanel->setSize(vwide,y+tall);
	_scroll->setRange(0,y+tall-_size[1]);
}

void ListPanel::setSize(int wide,int tall)
{
	Panel::setSize(wide,tall);
	invalidateLayout(false);
}

void ListPanel::performLayout()
{
	Panel* last=_vpanel->getChild(_vpanel->getChildCount()-1);
	if(last==null)
	{
		return;
	}

	int x,y,wide,tall;
	last->getBounds(x,y,wide,tall);

	int vwide,vtall;
	_vpanel->getSize(vwide,vtall);
	_vpanel->setSize(_size[0]-15,tall);
	_scroll->setBounds(_size[0]-15,0,15,_size[1]);
	_scroll->setRange(0,y+tall-_size[1]);
}

void ListPanel::setPixelScroll(int value)
{
	_vpanel->setPos(0,value);
	repaint();
	_vpanel->repaint();
}

void ListPanel::translatePixelScroll(int delta)
{
	int x,y;
	_vpanel->getPos(x,y);
	_vpanel->setPos(0,y+delta);
	repaint();
	_vpanel->repaint();
}
