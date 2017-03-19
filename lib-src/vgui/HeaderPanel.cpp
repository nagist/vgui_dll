//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include "VGUI.h"
#include "VGUI_HeaderPanel.h"
#include "VGUI_App.h"
#include "VGUI_InputSignal.h"
#include "VGUI_ChangeSignal.h"

using namespace vgui;

class HeaderPanelSignal : public InputSignal
{
public:
	HeaderPanelSignal(HeaderPanel* headerPanel)
	{
		_headerPanel=headerPanel;
	}
	void cursorMoved(int x,int y,Panel* panel)
	{
		_headerPanel->privateCursorMoved(x,y,panel);
	}
	void cursorEntered(Panel* panel)
	{
	}
	void cursorExited(Panel* panel)
	{
	}
	void mousePressed(MouseCode code,Panel* panel)
	{
		_headerPanel->privateMousePressed(code,panel);
	}
	void mouseDoublePressed(MouseCode code,Panel* panel)
	{
	}
	void mouseReleased(MouseCode code,Panel* panel)
	{
		_headerPanel->privateMouseReleased(code,panel);
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
	HeaderPanel* _headerPanel;
};

HeaderPanel::HeaderPanel(int x,int y,int wide,int tall) : Panel(x,y,wide,tall)
{
	_sliderWide=11;
	_dragging=false;
	_sectionLayer=new Panel(0,0,wide,tall);
	_sectionLayer->setPaintBorderEnabled(false);
	_sectionLayer->setPaintBackgroundEnabled(false);
	_sectionLayer->setPaintEnabled(false);
	_sectionLayer->setParent(this);
}

void HeaderPanel::performLayout()
{
	int wide,tall;
	getPaintSize(wide,tall);
	_sectionLayer->setBounds(0,0,wide,tall);

	int tx=0;
	for(int i=0;i<_sectionPanelDar.getCount();i++)
	{
		int x,y;
		_sliderPanelDar[i]->getPos(x,y);
		int t=x+_sliderWide/2;
		_sectionPanelDar[i]->setBounds(tx,0,t-tx,tall);
		tx=t;
	}
}

void HeaderPanel::addSectionPanel(Panel* panel)
{
	invalidateLayout(true);

	int x=0,y,wide,tall; // uninitialize
	for(int i=0;i<_sectionPanelDar.getCount();i++)
	{
		_sectionPanelDar[i]->getBounds(x,y,wide,tall);
		x+=wide+_sliderWide;
	}
	_sectionPanelDar.addElement(panel);

	panel->setPos(x,0);
	panel->setParent(_sectionLayer);
	panel->setBounds(x,y,wide,tall);

	getPaintSize(wide,tall);

	Panel* p1=new Panel(0,0,_sliderWide,tall);
	p1->setPaintBorderEnabled(false);
	p1->setPaintBackgroundEnabled(false);
	p1->setPaintEnabled(false);
	p1->setPos(x+wide,0);
	p1->addInputSignal(new HeaderPanelSignal(this));
	p1->setCursor(getApp()->getScheme()->getCursor(Scheme::scu_sizewe));
	p1->setParent(this);
	_sliderPanelDar.addElement(p1);

	invalidateLayout(false);
	fireChangeSignal();
	repaint();
}

void HeaderPanel::setSliderPos(int sliderIndex,int pos)
{
	_sliderPanelDar[sliderIndex]->setPos(pos-_sliderWide/2,0);

	invalidateLayout(false);
	fireChangeSignal();
	repaint();
}

int HeaderPanel::getSectionCount()
{
	return _sectionPanelDar.getCount();
}

void HeaderPanel::getSectionExtents(int sectionIndex,int& x0,int& x1)
{
	int x,y,wide,tall;
	_sectionPanelDar[sectionIndex]->getBounds(x,y,wide,tall);
	x0=x;
	x1=x+wide;
}

void HeaderPanel::addChangeSignal(ChangeSignal* s)
{
	_changeSignalDar.putElement(s);
}

void HeaderPanel::fireChangeSignal()
{
	invalidateLayout(true);

	for(int i=0;i<_changeSignalDar.getCount();i++)
		_changeSignalDar[i]->valueChanged(this);
}

void HeaderPanel::privateCursorMoved(int x,int y,Panel* panel)
{
	if(_dragging)
	{
		getApp()->getCursorPos(x,y);
		screenToLocal(x,y);
		setSliderPos(_dragSliderIndex,x+_dragSliderStartPos-_dragSliderStartX);
		invalidateLayout(false);
		repaint();
	}
}

void HeaderPanel::privateMousePressed(MouseCode code,Panel* panel)
{
	int x,y;
	getApp()->getCursorPos(x,y);
	screenToLocal(x,y);

	for(int i=0;i<_sliderPanelDar.getCount();i++)
	{
		if(_sliderPanelDar[i]==panel)
		{
			int mx,my;
			panel->getPos(mx,my);
			_dragging=true;
			_dragSliderIndex=i;
			_dragSliderStartPos=mx+_sliderWide/2;
			_dragSliderStartX=mx;
			panel->setAsMouseCapture(true);
			break;
		}
	}
}

void HeaderPanel::privateMouseReleased(MouseCode code,Panel* panel)
{
}
