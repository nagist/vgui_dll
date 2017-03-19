//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include "VGUI.h"
#include "VGUI_TreeFolder.h"
#include "VGUI_InputSignal.h"
#include "VGUI_Label.h"
#include "VGUI_Layout.h"

using namespace vgui;

class FooTreeFolderDefaultHandler : public InputSignal
{
public:
	FooTreeFolderDefaultHandler(TreeFolder* treeFolder)
	{
		_treeFolder=treeFolder;
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
		_treeFolder->setOpened(!_treeFolder->isOpened());
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
	TreeFolder* _treeFolder;
};

class FooTabFolderVerticalLayout : public Layout
{
public:
	FooTabFolderVerticalLayout()
	{
		_hgap=30;
		_vgap=3;
	}
	void performLayout(Panel* panel)
	{
		TreeFolder* folder;
		int maxx=0;
		int wide,tall,xx,yy=0;
		for(int i=0;i<panel->getChildCount();i++)
		{
			Panel* child=panel->getChild(i);
			folder=dynamic_cast<TreeFolder*>(child);
			if(folder)
				folder->invalidateLayout(true);

			child->getSize(wide,tall);
			xx=(i==0)?0:_hgap;
			child->setPos(xx,yy);

			if(xx+wide>maxx)
				maxx=xx+wide;

			yy+=tall+_vgap;
		}

		folder=dynamic_cast<TreeFolder*>(panel);
		if(folder)
		{
			if(folder->isOpened())
			{
				panel->setSize(maxx+2,yy);
			}
			else
			{
				Panel*child=panel->getChild(0);
				if(child)
				{
					int wide,tall;
					child->getSize(wide,tall);
					folder->setSize(wide,tall);
				}
			}
		}
	}
private:
	int _hgap;
	int _vgap;
};

TreeFolder::TreeFolder(const char* name) : Panel(0,0,500,500)
{
	init(name);
}

TreeFolder::TreeFolder(const char* name,int x,int y) : Panel(x,y,500,500)
{
	init(name);
}

void TreeFolder::init(const char* name)
{
	_opened=false;

	Label* label=new Label(name,0,0);
	label->addInputSignal(new FooTreeFolderDefaultHandler(this));
	label->setParent(this);

	setLayout(new FooTabFolderVerticalLayout());
}

void TreeFolder::setOpenedTraverse(bool state)
{
	setOpened(true);

	for(int i=0;i<getChildCount();i++)
	{
		Panel* p=getChild(i);
		TreeFolder* folder=dynamic_cast<TreeFolder*>(p);
		if(folder)
			folder->setOpenedTraverse(state);
	}
}

void TreeFolder::setOpened(bool state)
{
	if(_opened!=state)
	{
		_opened=state;

		TreeFolder* folder=null;
		Panel* p=this;
		while(p)
		{
			TreeFolder* panel=dynamic_cast<TreeFolder*>(p);
			if(panel)
			{
				panel->invalidateLayout(true);
				folder=panel;
			}
			p=p->getParent();
		}
		if(folder)
			folder->repaintParent();
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
		if(dynamic_cast<TreeFolder*>(child))
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
		if(folder)
		{
			y+=10;
			drawSetColor(Scheme::sc_white);
			drawFilledRect(x0-5,y-5,x0+6,y+6);
			drawSetColor(Scheme::sc_black);
			drawOutlinedRect(x0-5,y-5,x0+6,y+6);
			drawFilledRect(x0-3,y,x0+4,y+1);
			if(folder->isOpened())
				drawFilledRect(x0,y-3,x0+1,y+4);
		}
	}
}
