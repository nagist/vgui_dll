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

#include<VGUI_TreeFolder.h>
#include<VGUI_InputSignal.h>
#include<VGUI_Label.h>
#include<VGUI_Layout.h>

using namespace vgui;

namespace
{
class FooTabFolderVerticalLayout : public Layout
{
public:
	FooTabFolderVerticalLayout() : Layout()
	{
		_hgap=30;
		_vgap=3;
	}
public:
	virtual void performLayout(Panel* panel)
	{
		TreeFolder* folder;

		int maxx=0;
		int wide,tall,xx,yy=0;

		for(int i=0;i<panel->getChildCount();i++)
		{
			Panel* child=panel->getChild(i);

			folder=dynamic_cast<TreeFolder*>(child);
			if(folder!=null)
			{
				folder->invalidateLayout(true);
			}

			child->getSize(wide,tall);

			if(i==0)
			{
				xx=0;
			}
			else
			{
				xx=_hgap;
			}

			child->setPos(xx,yy);

			if(xx+wide>maxx)
			{
				maxx=xx+wide;
			}

			yy+=tall+_vgap;
		}

		folder=dynamic_cast<TreeFolder*>(panel);
		if(folder!=null)
		{
			if(folder->isOpened())
			{
				panel->setSize(maxx+2,yy);
			}
			else
			{
				Panel*child=panel->getChild(0);
				if(child!=null)
				{
					child->getSize(wide,tall);
					folder->setSize(wide,tall);
				}
			}
		}
	}
protected:
	int _hgap;
	int _vgap;
};

class FooTreeFolderDefaultHandler : public InputSignal
{
public:
	FooTreeFolderDefaultHandler(TreeFolder* treeFolder)
	{
		_treeFolder=treeFolder;
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
		_treeFolder->setOpened(!_treeFolder->isOpened());
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
	TreeFolder* _treeFolder;
};
}

void TreeFolder::init(const char* name)
{
	_opened=false;

	Label* label=new Label(name,0,0);
	label->addInputSignal(new FooTreeFolderDefaultHandler(this));
	label->setParent(this);

	setLayout(new FooTabFolderVerticalLayout());
}

TreeFolder::TreeFolder(const char* name) : Panel(0,0,500,500)
{
	init(name);
}

TreeFolder::TreeFolder(const char* name,int x,int y) : Panel(x,y,500,500)
{
	init(name);
}

void TreeFolder::setOpened(bool state)
{
	if(_opened!=state)
	{
		_opened=state;

		TreeFolder* top=null;
		Panel* trav=this;
		while(trav!=null)
		{
			TreeFolder* folder=dynamic_cast<TreeFolder*>(trav);
			if(folder!=null)
			{
				folder->invalidateLayout(true);
				top=folder;
			}
			trav=trav->getParent();
		}
		if(top!=null)
		{
			top->repaintParent();
		}
	}
}

bool TreeFolder::isOpened()
{
	return _opened;
}

void TreeFolder::paintBackground()
{
	drawSetColor(Scheme::sc_black);

	const int x0=15;
	const int x1=30;
	const int y0=10;
	int y1=10;

	int i;
	for(i=1;i<getChildCount();i++)
	{
		Panel* child=getChild(i);
		int x,y,wide,tall;
		child->getBounds(x,y,wide,tall);
		if(dynamic_cast<TreeFolder*>(child)!=null)
		{
			y+=10;
		}
		else
		{
			y+=tall/2;
		}

		drawFilledRect(x0,y,x1,y+1);
		y1=y;
	}

	drawFilledRect(x0,y0,x0+1,y1);

	for(i=1;i<getChildCount();i++)
	{
		Panel* child=getChild(i);
		int x,y,wide,tall;
		child->getBounds(x,y,wide,tall);
		TreeFolder* folder=dynamic_cast<TreeFolder*>(child);
		if(folder!=null)
		{
			y+=10;
			drawSetColor(Scheme::sc_white);
			drawFilledRect(x0-5,y-5,x0+6,y+6);
			drawSetColor(Scheme::sc_black);
			drawOutlinedRect(x0-5,y-5,x0+6,y+6);
			drawFilledRect(x0-3,y,x0+4,y+1);

			if(!folder->isOpened())
			{
				drawFilledRect(x0,y-3,x0+1,y+4);
			}
		}
	}
}

void TreeFolder::setOpenedTraverse(bool state)
{
	setOpened(true);

	for(int i=0;i<getChildCount();i++)
	{
		TreeFolder* folder=dynamic_cast<TreeFolder*>(getChild(i));
		if(folder!=null)
		{
			folder->setOpenedTraverse(state);
		}
	}
}
