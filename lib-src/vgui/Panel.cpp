//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include <stdio.h>
#include "VGUI.h"
#include "VGUI_Panel.h"
#include "VGUI_SurfaceBase.h"
#include "VGUI_App.h"
#include "VGUI_FocusNavGroup.h"
#include "VGUI_Border.h"
#include "VGUI_BuildGroup.h"
#include "VGUI_InputSignal.h"
#include "VGUI_FocusChangeSignal.h"
#include "VGUI_FocusNavGroup.h"
#include "VGUI_TreeFolder.h"
#include "VGUI_Label.h"
#include "VGUI_Layout.h"

using namespace vgui;

Panel::Panel()
{
	init(0,0,64,64);
}

Panel::Panel(int x,int y,int wide,int tall)
{
	init(x,y,wide,tall);
}
 
void Panel::init(int x,int y,int wide,int tall)
{
	_pos[0]=x;
	_pos[1]=y;
	_size[0]=wide;
	_size[1]=tall;
	_loc[0]=0;
	_loc[1]=0;
	_needsRepaint=false;
	_parent=null;
	_surfaceBase=null;
	_visible=true;
	_minimumSize[0]=0;
	_minimumSize[1]=0;
	_cursor=null;
	_schemeCursor=Scheme::scu_arrow;
	_border=null;
	_buildGroup=null;
	_layoutInfo=null;
	_layout=null;
	_needsLayout=true;
	_focusNavGroup=null;
	_enabled=true;
	_paintBorderEnabled=true;
	_paintBackgroundEnabled=true;
	_paintEnabled=true;
	setFgColor(Scheme::sc_black);
	setBgColor(Scheme::sc_secondary3);
	setAutoFocusNavEnabled(true);
}

void Panel::setPos(int x,int y)
{
	_pos[0]=x;
	_pos[1]=y;
}

void Panel::getPos(int& x,int& y)
{
	x=_pos[0];
	y=_pos[1];
}

void Panel::setSize(int wide,int tall)
{
	if (wide<_minimumSize[0])
	{
		wide=_minimumSize[0];
	}
	if (tall<_minimumSize[1])
	{
		tall=_minimumSize[1];
	}

	_size[0]=wide;
	_size[1]=tall;
}

void Panel::getSize(int& wide,int& tall)
{
	wide=_size[0];
	tall=_size[1];
}

void Panel::setBounds(int x,int y,int wide,int tall)
{
	setPos(x,y);
	setSize(wide,tall);
}

void Panel::getBounds(int& x,int& y,int& wide,int& tall)
{
	getPos(x,y);
	getSize(wide,tall);
}

int Panel::getWide()
{
	return _size[0];
}

int Panel::getTall()
{
	return _size[1];
}

Panel* Panel::getParent()
{
	return _parent;
}

void Panel::setVisible(bool state)
{
	_visible=state;
}

bool Panel::isVisible()
{
	return _visible;
}

bool Panel::isVisibleUp()
{
	Panel* panel=this;
	while(panel)
	{
		if(panel->_visible==false)
			return false;
		panel=panel->getParent();
	}
	return true;
}

void Panel::repaint()
{
	_needsRepaint=true;
	if(_surfaceBase)
	{
		_surfaceBase->_needsSwap=true;
		_surfaceBase->invalidate(this);
	}

	for(int i=0;i<_repaintSignalDar.getCount();i++)
	{
		_repaintSignalDar[i]->panelRepainted(this);
	}
}

void Panel::repaintAll()
{
	_surfaceBase->getPanel()->repaint();
}

void Panel::getAbsExtents(int& x0,int& y0,int& x1,int& y1)
{
	x0=_loc[0];
	y0=_loc[1];
	x1=x0+_size[0];
	y1=y0+_size[1];
}

void Panel::getClipRect(int& x0,int& y0,int& x1,int& y1)
{
	x0=_clipRect[0];
	y0=_clipRect[1];
	x1=_clipRect[2];
	y1=_clipRect[3];
}

void Panel::setParent(Panel* newParent)
{
	if(_parent!=null)
		_parent->removeChild(this);

	if(newParent!=null)
	{
		_parent=newParent;
		_parent->_childDar.putElement(this);
		setSurfaceBaseTraverse(_parent->_surfaceBase);
	}
}

void Panel::addChild(Panel* child)
{
	for(int i=0;i<_childDar.getCount();i++)
	{
		if(_childDar[i]==child)
			return;
	}

	if(child->_parent!=null)
		child->_parent->removeChild(child);

	child->_parent=this;
	_childDar.putElement(child);
	child->setSurfaceBaseTraverse(_surfaceBase);
}

void Panel::insertChildAt(Panel* child,int index)
{
	for(int i=0;i<_childDar.getCount();i++)
	{
		if(_childDar[i]==child)
			return;
	}

	if(child->_parent!=null)
		child->_parent->removeChild(child);

	child->_parent=this;
	_childDar.insertElementAt(child,index);
	child->setSurfaceBaseTraverse(_surfaceBase);
}

void Panel::removeChild(Panel* child)
{
	child->_parent=null;
	child->_surfaceBase=null;
	_childDar.removeElement(child);
}

bool Panel::wasMousePressed(MouseCode code)
{
	return getApp()->wasMousePressed(code,this);
}

bool Panel::wasMouseDoublePressed(MouseCode code)
{
	return getApp()->wasMouseDoublePressed(code,this);
}

bool Panel::isMouseDown(MouseCode code)
{
	return getApp()->isMouseDown(code,this);
}

bool Panel::wasMouseReleased(MouseCode code)
{
	return getApp()->wasMouseReleased(code,this);
}

bool Panel::wasKeyPressed(KeyCode code)
{
	return getApp()->wasKeyPressed(code,this);
}

bool Panel::isKeyDown(KeyCode code)
{
	return getApp()->isKeyDown(code,this);
}

bool Panel::wasKeyTyped(KeyCode code)
{
	return getApp()->wasKeyTyped(code,this);
}

bool Panel::wasKeyReleased(KeyCode code)
{
	return getApp()->wasKeyReleased(code,this);
}

void Panel::addInputSignal(InputSignal* s)
{
	_inputSignalDar.putElement(s);
}

void Panel::removeInputSignal(InputSignal* s)
{
	_inputSignalDar.removeElement(s);
}

void Panel::addRepaintSignal(RepaintSignal* s)
{
	_repaintSignalDar.putElement(s);
}

void Panel::removeRepaintSignal(RepaintSignal* s)
{
	_repaintSignalDar.removeElement(s);
}

bool Panel::isWithin(int x,int y)
{
	screenToLocal(x,y);

	if(x<0)
		return false;
	if(y<0)
		return false;
	if(x>=_size[0])
		return false;
	if(y>=_size[1])
		return false;
	return true;
}

Panel* Panel::isWithinTraverse(int x,int y)
{
	if(!_visible)
		return null;

	if(isWithin(x,y))
	{
		for(int i=_childDar.getCount()-1;i>=0;i--)
		{
			Panel* panel=_childDar[i]->isWithinTraverse(x,y);
			if(panel!=null)
				return panel;
		}

		return this;
	}

	return null;
}

void Panel::localToScreen(int& x,int& y)
{
	x+=_loc[0];
	y+=_loc[1];
}

void Panel::screenToLocal(int& x,int& y)
{
	x-=_loc[0];
	y-=_loc[1];
}

void Panel::setCursor(Cursor* cursor)
{
	_schemeCursor=Scheme::scu_user;
	_cursor=cursor;
}

void Panel::setCursor(Scheme::SchemeCursor scu)
{
	_cursor=null;
	_schemeCursor=scu;
}

Cursor* Panel::getCursor()
{
	if(getApp()->getCursorOveride()!=null)
		return getApp()->getCursorOveride();

	if(_schemeCursor!=null)
		return getApp()->getScheme()->getCursor(_schemeCursor);

	return _cursor;
}

void Panel::setMinimumSize(int wide,int tall)
{
	_minimumSize[0]=wide;
	_minimumSize[1]=tall;
}

void Panel::getMinimumSize(int& wide,int& tall)
{
	wide=_minimumSize[0];
	tall=_minimumSize[1];
}

void Panel::requestFocus()
{
	getApp()->requestFocus(this);
}

bool Panel::hasFocus()
{
	return (getApp()->getFocus()==this)?true:false;
}

int Panel::getChildCount()
{
	return _childDar.getCount();
}

Panel* Panel::getChild(int index)
{
	return _childDar[index];
}

void Panel::setLayout(Layout* layout)
{
	_layout=layout;
	invalidateLayout(false);
}

void Panel::invalidateLayout(bool layoutNow)
{
	_needsLayout=true;
	if(layoutNow)
		internalPerformLayout();
}

void Panel::setFocusNavGroup(FocusNavGroup* focusNavGroup)
{
	_focusNavGroup=focusNavGroup;
	if(_focusNavGroup)
		_focusNavGroup->addPanel(this);
}

void Panel::requestFocusPrev()
{
	if(_focusNavGroup)
		_focusNavGroup->requestFocusPrev();
}

void Panel::requestFocusNext()
{
	if(_focusNavGroup)
		_focusNavGroup->requestFocusNext();
}

void Panel::addFocusChangeSignal(FocusChangeSignal* s)
{
	_focusChangeSignalDar.putElement(s);
}

bool Panel::isAutoFocusNavEnabled()
{
	return _autoFocusNavEnabled;
}

void Panel::setAutoFocusNavEnabled(bool state)
{
	_autoFocusNavEnabled=state;
}

void Panel::setBorder(Border* border)
{
	_border=border;
}

void Panel::setPaintBorderEnabled(bool state)
{
	_paintBorderEnabled=state;
}

void Panel::setPaintBackgroundEnabled(bool state)
{
	_paintBackgroundEnabled=state;
}

void Panel::setPaintEnabled(bool state)
{
	_paintEnabled=state;
}

void Panel::getInset(int& left,int& top,int& right,int& bottom)
{
	if(_border)
	{
		_border->getInset(left,top,right,bottom);
		return;
	}

	left=0;
	top=0;
	right=0;
	bottom=0;
}

void Panel::getPaintSize(int& wide,int& tall)
{
	if(_border!=null)
	{
		int left,top,right,bottom;
		_border->getInset(left,top,right,bottom);
		wide=_size[0]-(right+left);
		tall=_size[1]-(bottom+top);
		return;
	}

	wide=_size[0];
	tall=_size[1];
}

void Panel::setPreferredSize(int wide,int tall)
{
	_preferredSize[0]=wide;
	_preferredSize[1]=tall;
}

void Panel::getPreferredSize(int& wide,int& tall)
{
	wide=_preferredSize[0];
	tall=_preferredSize[1];
}

SurfaceBase* Panel::getSurfaceBase()
{
	return _surfaceBase;
}

bool Panel::isEnabled()
{
	return _enabled;
}

void Panel::setEnabled(bool state)
{
	_enabled=state;
}

void Panel::setBuildGroup(BuildGroup* buildGroup,const char* panelPersistanceName)
{
	_buildGroup=buildGroup;
	_buildGroup->panelAdded(this, panelPersistanceName);
}

bool Panel::isBuildGroupEnabled()
{
	if(_buildGroup==null)
		return false;
	return _buildGroup->isEnabled();
}

void Panel::removeAllChildren()
{
	_childDar.removeAll();
}

void Panel::repaintParent()
{
	if(_parent)
		_parent->repaint();
}

Panel* Panel::createPropertyPanel()
{
	TreeFolder* prop=new TreeFolder("Properties");
	TreeFolder* panel=new TreeFolder("Panel");
	panel->addChild(new Label("setPos"));
	panel->addChild(new Label("setSize"));
	panel->addChild(new Label("setBorder"));
	panel->addChild(new Label("setLayout"));
	prop->addChild(panel);
	return prop;
}

void Panel::getPersistanceText(char* buf,int bufLen)
{
	int x,y,wide,tall;
	getBounds(x,y,wide,tall);
	sprintf(buf,"->setBounds(%d,%d,%d,%d);\n",x,y,wide,tall);
}

void Panel::applyPersistanceText(const char* buf)
{
}

void Panel::setFgColor(Scheme::SchemeColor sc)
{
	_fgColor.setColor(sc);
}

void Panel::setBgColor(Scheme::SchemeColor sc)
{
	_bgColor.setColor(sc);
}

void Panel::setFgColor(int r,int g,int b,int a)
{
	_fgColor.setColor(r,g,b,a);
}

void Panel::setBgColor(int r,int g,int b,int a)
{
	_bgColor.setColor(r,g,b,a);
}

void Panel::getFgColor(int& r,int& g,int& b,int& a)
{
	_fgColor.getColor(r,g,b,a);
}

void Panel::getBgColor(int& r,int& g,int& b,int& a)
{
	_bgColor.getColor(r,g,b,a);
}

void Panel::setBgColor(Color color)
{
	_bgColor=color;
}

void Panel::setFgColor(Color color)
{
	_fgColor=color;
}

void Panel::getBgColor(Color& color)
{
	color=_bgColor;
}

void Panel::getFgColor(Color& color)
{
	color=_fgColor;
}

void Panel::setAsMouseCapture(bool state)
{
	if(state)
		getApp()->setMouseCapture(this);
	else
		getApp()->setMouseCapture(null);
}

void Panel::setAsMouseArena(bool state)
{
	getApp()->setMouseArena(this);
}

App* Panel::getApp()
{
	return App::getInstance();
}

void Panel::getVirtualSize(int& wide,int& tall)
{
	getSize(wide,tall);
}

void Panel::setLayoutInfo(LayoutInfo* layoutInfo)
{
	_layoutInfo=layoutInfo;
}

LayoutInfo* Panel::getLayoutInfo()
{
	return _layoutInfo;
}

bool Panel::isCursorNone()
{
	Cursor* cursor=getCursor();
	if(cursor)
		return (cursor->getDefaultCursor()==Cursor::dc_none)?true:false;
	return true;
}

void Panel::solveTraverse()
{
	if(!_visible)
		return;

	solve();

	if(_needsLayout)
		internalPerformLayout();

	solve();

	for(int i=0;i<_childDar.getCount();i++)
		_childDar[i]->solveTraverse();
}

void Panel::paintTraverse()
{
	paintTraverse(_needsRepaint);
}

void Panel::setSurfaceBaseTraverse(SurfaceBase* surfaceBase)
{
	_surfaceBase=surfaceBase;
	for(int i=0;i<_childDar.getCount();i++)
	{
		_childDar[i]->setSurfaceBaseTraverse(surfaceBase);
	}
}

void Panel::performLayout()
{
}

void Panel::internalPerformLayout()
{
	_needsLayout=false;
	if(_layout)
		_layout->performLayout(this);
	else
		performLayout();
	repaint();
}

void Panel::drawSetColor(Scheme::SchemeColor sc)
{
	int r,g,b,a;
	getApp()->getScheme()->getColor(sc,r,g,b,a);
	drawSetColor(r,g,b,a);
}

void Panel::drawSetColor(int r,int g,int b,int a)
{
	_surfaceBase->drawSetColor(r,g,b,a);
}

void Panel::drawFilledRect(int x0,int y0,int x1,int y1)
{
	_surfaceBase->drawFilledRect(x0,y0,x1,y1);
}

void Panel::drawOutlinedRect(int x0,int y0,int x1,int y1)
{
	_surfaceBase->drawOutlinedRect(x0,y0,x1,y1);
}

void Panel::drawSetTextFont(Scheme::SchemeFont sf)
{
	_surfaceBase->drawSetTextFont(getApp()->getScheme()->getFont(sf));
}

void Panel::drawSetTextFont(Font* font)
{
	_surfaceBase->drawSetTextFont(font);
}

void Panel::drawSetTextColor(Scheme::SchemeColor sc)
{
	int r,g,b,a;
	getApp()->getScheme()->getColor(sc,r,g,b,a);
	drawSetTextColor(r,g,b,a);
}

void Panel::drawSetTextColor(int r,int g,int b,int a)
{
	_surfaceBase->drawSetTextColor(r,g,b,a);
}

void Panel::drawSetTextPos(int x,int y)
{
	_surfaceBase->drawSetTextPos(x,y);
}

void Panel::drawPrintText(const char* str,int strlen)
{
	_surfaceBase->drawPrintText(str,strlen);
}

void Panel::drawPrintText(int x,int y,const char* str,int strlen)
{
	_surfaceBase->drawSetTextPos(x,y);
	_surfaceBase->drawPrintText(str,strlen);
}

void Panel::drawPrintChar(char ch)
{
	_surfaceBase->drawPrintText(&ch,1);
}

void Panel::drawPrintChar(int x,int y,char ch)
{
	_surfaceBase->drawSetTextPos(x,y);
	_surfaceBase->drawPrintText(&ch,1);
}

void Panel::drawSetTextureRGBA(int id,const char* rgba,int wide,int tall)
{
	if(_surfaceBase)
		_surfaceBase->drawSetTextureRGBA(id,rgba,wide,tall);
}

void Panel::drawSetTexture(int id)
{
	_surfaceBase->drawSetTexture(id);
}

void Panel::drawTexturedRect(int x0,int y0,int x1,int y1)
{
	_surfaceBase->drawTexturedRect(x0,y0,x1,y1);
}

void Panel::solve()
{
	_loc[0] = _pos[0];
	_loc[1] = _pos[1];

	// put into parent space
	if (_parent)
	{
		int x,y,wide,tall;
		_parent->getInset(x,y,wide,tall);

		_loc[0]+=_parent->_loc[0]+x;
		_loc[1]+=_parent->_loc[1]+y;
	}

	// set initial bounds
	_clipRect[0] = _loc[0];
	_clipRect[1] = _loc[1];

	_clipRect[2] = _loc[0] + _size[0];
	_clipRect[3] = _loc[1] + _size[1];

	// clip to parent
	if (_parent)
	{ 
		if (_clipRect[0] < _parent->_clipRect[0])
		{
			_clipRect[0] = _parent->_clipRect[0];
		}

		if (_clipRect[1] < _parent->_clipRect[1])
		{
			_clipRect[1] = _parent->_clipRect[1];
		}

		if(_clipRect[2] > _parent->_clipRect[2])
		{
			_clipRect[2] = _parent->_clipRect[2];
		}

		if(_clipRect[3] > _parent->_clipRect[3])
		{
			_clipRect[3] = _parent->_clipRect[3];
		}
	}
}

void Panel::paintTraverse(bool repaint)
{
	if(!_visible)
	{
		return;
	}

	if(_needsRepaint)
	{
		repaint=true;
	}

	_needsRepaint=false;

	if ((_clipRect[2] <= _clipRect[0]) || (_clipRect[3] <= _clipRect[1]))
	{
		repaint = false;
	}

	if (repaint && (_paintBorderEnabled || _paintBackgroundEnabled || _paintEnabled))
	{
		_surfaceBase->pushMakeCurrent(this, true);
		if (_border && _paintBorderEnabled)
		{
			_border->doPaint(this);
		}
		if (_paintBackgroundEnabled)
		{
			paintBackground();
		}
		if (_paintEnabled)
		{
			paint();
		}
		_surfaceBase->popMakeCurrent(this);
	}

	for(int i=0;i<_childDar.getCount();i++)
	{
		_childDar[i]->paintTraverse(repaint);
	}

	if (repaint)
	{
		if (isBuildGroupEnabled() && hasFocus())
		{
			_surfaceBase->pushMakeCurrent(this, false);
			paintBuildOverlay();
			_surfaceBase->popMakeCurrent(this);				
		}			
	}

	if(_surfaceBase->_needsSwap)
	{
		if(_surfaceBase->getPanel()==this)
		{
			_surfaceBase->_needsSwap=false;
			_surfaceBase->swapBuffers();
		}
	}
}

void Panel::paintBackground()
{
	int wide,tall,r,g,b,a;
	getPaintSize(wide,tall);
	getBgColor(r,g,b,a);
	drawSetColor(r,g,b,a);
	drawFilledRect(0,0,wide,tall);
}

void Panel::paint()
{
}

void Panel::paintBuildOverlay()
{
	int wide,tall;
	getSize(wide,tall);
	drawSetColor(Scheme::sc_black);
	drawFilledRect(0,0,wide,2);
	drawFilledRect(0,tall-2,wide,tall);
	drawFilledRect(0,2,2,tall-2);
	drawFilledRect(wide-2,2,wide,tall-2);
}

void Panel::internalCursorMoved(int x,int y)
{
	if(isCursorNone())
		return;

	if(isBuildGroupEnabled())
	{
		_buildGroup->cursorMoved(x,y,this);
		return;
	}

	screenToLocal(x,y);

	for(int i=0;i<_inputSignalDar.getCount();i++)
		_inputSignalDar[i]->cursorMoved(x,y,this);
}

void Panel::internalCursorEntered()
{
	if(isCursorNone())
		return;

	if(isBuildGroupEnabled())
		return;

	for(int i=0;i<_inputSignalDar.getCount();i++)
		_inputSignalDar[i]->cursorEntered(this);
}

void Panel::internalCursorExited()
{
	if(isCursorNone())
		return;

	if(isBuildGroupEnabled())
		return;

	for(int i=0;i<_inputSignalDar.getCount();i++)
		_inputSignalDar[i]->cursorExited(this);
}

void Panel::internalMousePressed(MouseCode code)
{
	if(isCursorNone())
		return;

	if(isBuildGroupEnabled())
	{
		_buildGroup->mousePressed(code,this);
		return;
	}

	for(int i=0;i<_inputSignalDar.getCount();i++)
		_inputSignalDar[i]->mousePressed(code,this);
}

void Panel::internalMouseDoublePressed(MouseCode code)
{
	if(isCursorNone())
		return;

	if(isBuildGroupEnabled())
	{
		_buildGroup->mouseDoublePressed(code,this);
		return;
	}

	for(int i=0;i<_inputSignalDar.getCount();i++)
		_inputSignalDar[i]->mouseDoublePressed(code,this);
}

void Panel::internalMouseReleased(MouseCode code)
{
	if(isCursorNone())
		return;

	if(isBuildGroupEnabled())
	{
		_buildGroup->mouseReleased(code,this);
		return;
	}

	for(int i=0;i<_inputSignalDar.getCount();i++)
		_inputSignalDar[i]->mouseReleased(code,this);
}

void Panel::internalMouseWheeled(int delta)
{
	if(isBuildGroupEnabled())
		return;

	for(int i=0;i<_inputSignalDar.getCount();i++)
		_inputSignalDar[i]->mouseWheeled(delta,this);
}

void Panel::internalKeyPressed(KeyCode code)
{
	if(isBuildGroupEnabled())
		return;

	for(int i=0;i<_inputSignalDar.getCount();i++)
		_inputSignalDar[i]->keyPressed(code,this);
}

void Panel::internalKeyTyped(KeyCode code)
{
	if(isBuildGroupEnabled())
		return;

	for(int i=0;i<_inputSignalDar.getCount();i++)
		_inputSignalDar[i]->keyTyped(code,this);
}

void Panel::internalKeyReleased(KeyCode code)
{
	if(isBuildGroupEnabled())
		return;

	for(int i=0;i<_inputSignalDar.getCount();i++)
		_inputSignalDar[i]->keyReleased(code,this);
}

void Panel::internalKeyFocusTicked()
{
	if(isBuildGroupEnabled())
		return;

	for(int i=0;i<_inputSignalDar.getCount();i++)
		_inputSignalDar[i]->keyFocusTicked(this);
}

void Panel::internalFocusChanged(bool lost)
{
	if(!lost)
	{
		if(_focusNavGroup)
			_focusNavGroup->setCurrentPanel(this);
	}

	for(int i=0;i<_focusChangeSignalDar.getCount();i++)
		_focusChangeSignalDar[i]->focusChanged(lost,this);
}

void Panel::internalSetCursor()
{
	if(isBuildGroupEnabled())
		_buildGroup->getCursor(this);

	if(_surfaceBase)
		_surfaceBase->setCursor(getCursor());
}
