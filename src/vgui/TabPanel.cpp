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

#include<VGUI_TabPanel.h>
#include<VGUI_ButtonGroup.h>
#include<VGUI_Border.h>
#include<VGUI_ActionSignal.h>
#include<VGUI_ToggleButton.h>

using namespace vgui;

namespace
{
class FooTabPanelTab : public ToggleButton, public ActionSignal
{
public:
	FooTabPanelTab(TabPanel* tabPanel,const char* text,int x,int y) : ToggleButton(text,x,y)
	{
		_tabPanel=tabPanel;
		addActionSignal(this);
	}
public:
	virtual bool isWithin(int x,int y)
	{
		return Panel::isWithin(x,y);
	}
	virtual void actionPerformed(Panel* panel)
	{
		_tabPanel->setSelectedTab(this);
	}
protected:
	virtual void paintBackground()
	{
		int wide,tall;
		getPaintSize(wide,tall);

		if(isSelected())
		{
			drawSetColor(Scheme::sc_secondary3);
			drawFilledRect(0,0,wide,tall);

			drawSetColor(Scheme::sc_secondary1);
			drawFilledRect(0,0,wide,1);
			drawFilledRect(0,1,1,tall-1);
			drawFilledRect(wide-1,1,wide,tall-1);

			drawSetColor(Scheme::sc_white);
			drawFilledRect(1,1,wide-1,2);
			drawFilledRect(1,2,2,tall);
			drawFilledRect(0,tall-1,1,tall);
			drawFilledRect(wide-1,tall-1,wide,tall);
		}
		else
		{
			drawSetColor(Scheme::sc_secondary2);
			drawFilledRect(0,0,wide,tall);

			drawSetColor(Scheme::sc_secondary1);
			drawFilledRect(0,0,wide,1);
			drawFilledRect(0,1,1,tall-1);
			drawFilledRect(wide-1,1,wide,tall-1);

			drawSetColor(Scheme::sc_secondary3);
			drawFilledRect(1,1,wide-1,2);
			drawFilledRect(1,2,2,tall);
			drawFilledRect(0,tall-1,1,tall);
			drawFilledRect(wide-1,tall-1,wide,tall);

			drawSetColor(Scheme::sc_white);
			drawFilledRect(0,tall-1,wide,tall);
		}
	}
protected:
	TabPanel* _tabPanel;
};

class FooClientBorder : public Border
{
protected:
	virtual void paintBorder(Panel* panel)
	{
		int wide,tall;
		panel->getSize(wide,tall);

		drawSetColor(Scheme::sc_black);
		drawFilledRect(0,0,wide-1,1);
		drawFilledRect(0,1,1,tall-1);

		drawSetColor(Scheme::sc_secondary1);
		drawFilledRect(0,tall-1,wide,tall);
		drawFilledRect(wide-1,0,wide,tall-1);
	}
};

class FooTabAreaBorder : public Border
{
protected:
	virtual void paintBorder(Panel* panel)
	{
		int wide,tall;
		panel->getSize(wide,tall);

		drawSetColor(Scheme::sc_white);
		drawFilledRect(0,tall-1,wide,tall);
	}
};
}

TabPanel::TabPanel(int x,int y,int wide,int tall) : Panel(x,y,wide,tall)
{
	_tabPlacement=tp_top;

	_clientArea=new Panel(5,5,wide-10,tall-10);
	_clientArea->setParent(this);
	_clientArea->setBorder(new FooClientBorder());

	_tabArea=new Panel(5,5,wide,5);
	_tabArea->setParent(this);
	_tabArea->setBorder(new FooTabAreaBorder());

	_selectedTab=null;
	_selectedPanel=null;
	_buttonGroup=new ButtonGroup();
}

Panel* TabPanel::addTab(const char* text)
{
	FooTabPanelTab* tab=new FooTabPanelTab(this,text,0,0);
	_tabArea->insertChildAt(tab,0);
	tab->setButtonGroup(_buttonGroup);

	Panel* panel=new Panel(0,0,20,20);
	_clientArea->insertChildAt(panel,0);
	panel->setVisible(false);

	if(_selectedTab==null)
	{
		_selectedTab=tab;
		_selectedPanel=panel;
		panel->setVisible(true);
		tab->setSelected(true);
	}

	recomputeLayout();
	return panel;
}

void TabPanel::setSelectedTab(Panel* tab)
{
	if(tab==null)
	{
		return;
	}

	if(tab==_selectedTab)
	{
		return;
	}

	for(int i=0;i<_tabArea->getChildCount();i++)
	{
		if(_tabArea->getChild(i)==tab)
		{
			_selectedPanel->setVisible(false);
			_selectedPanel=_clientArea->getChild(i);
			_selectedPanel->setVisible(true);
			_selectedTab=tab;
			break;
		}
	}

	recomputeLayout();
}

void TabPanel::recomputeLayoutTop()
{
	int x=0;
	int y=0;
	int i,wide,tall;

	int paintWide,paintTall;
	getPaintSize(paintWide,paintTall);

	const int minx=5;
	int maxx=paintWide-minx;
	int inRowCount=0;

	x=minx;
	for(i=_tabArea->getChildCount()-1;i>=0;i--)
	{
		_tabArea->getChild(i)->getPreferredSize(wide,tall);
		_tabArea->getChild(i)->setSize(wide,tall);
		if(x+wide>maxx)
		{
			if(inRowCount!=0)
			{
				int extra=(maxx-x)/inRowCount;
				int error=maxx-(inRowCount*extra)-x;
				int extraAccum=0;
				for(int j=i+inRowCount;j>i;j--)
				{
					int ww,tt,xx,yy;
					int extra2=extra;
					if(j==i+inRowCount)
					{
						extra2+=error;
					}
					_tabArea->getChild(j)->getPreferredSize(ww,tt);
					_tabArea->getChild(j)->getPos(xx,yy);
					_tabArea->getChild(j)->setBounds(xx+extraAccum,yy,ww+extra2,tt);
					extraAccum+=extra2;
				}
			}
			maxx-=minx;
			x=minx;
			y-=tall-4;
			inRowCount=0;
		}
		_tabArea->getChild(i)->setPos(x,y);
		inRowCount++;
		x+=wide-1;
	}

	int miny;
	_tabArea->getChild(0)->getPos(x,miny);
	for(i=0;i<_tabArea->getChildCount();i++)
	{
		_tabArea->getChild(i)->getPos(x,y);
		_tabArea->getChild(i)->setPos(x,y-miny);
	}

	_tabArea->getChild(0)->getSize(wide,tall);
	_tabArea->setBounds(0,5,paintWide,tall-miny);
	_tabArea->getSize(wide,tall);
	_clientArea->setBounds(0,tall+4,paintWide,paintTall-tall-5);
	_clientArea->getSize(wide,tall);

	for(i=0;i<_clientArea->getChildCount();i++)
	{
		_clientArea->getChild(i)->setBounds(5,5,wide-10,tall-10);
		_clientArea->getChild(i)->invalidateLayout(false);
	}
}

void TabPanel::recomputeLayout()
{
	if(_tabArea->getChildCount()!=0)
	{
		if(_tabPlacement==0)
		{
			recomputeLayoutTop();
		}
		repaint();
	}
}

void TabPanel::setSize(int wide,int tall)
{
	Panel::setSize(wide,tall);

	recomputeLayout();
}
