//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include "VGUI.h"
#include "VGUI_Panel.h"
#include "VGUI_SurfaceBase.h"
#include "VGUI_App.h"
#include "VGUI_FocusNavGroup.h"
#include "VGUI_Border.h"
#include "VGUI_BuildGroup.h"

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
	_paintBorderEnabled=null;
	_paintBackgroundEnabled=null;
	_paintEnabled=null;
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
	// dummy
	return false;
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
	// dummy
}

void Panel::addChild(Panel* child)
{
	// dummy
}

void Panel::insertChildAt(Panel* child,int index)
{
	// dummy
}

void Panel::removeChild(Panel* child)
{
	// dummy
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
	// dummy
}

void Panel::removeInputSignal(InputSignal* s)
{
	// dummy
}

void Panel::addRepaintSignal(RepaintSignal* s)
{
}

void Panel::removeRepaintSignal(RepaintSignal* s)
{
	// dummy
}

bool Panel::isWithin(int x,int y)
{
	// dummy
	return false;
}

Panel* Panel::isWithinTraverse(int x,int y)
{
	// dummy
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
	// dummy
	return null;
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
	// dummy
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
	// dummy
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
	// dummy
	return null;
}

void Panel::getPersistanceText(char* buf,int bufLen)
{
	// dummy
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
	// dummy
}

void Panel::paintTraverse()
{
	// dummy
}

void Panel::setSurfaceBaseTraverse(SurfaceBase* surfaceBase)
{
	// dummy
}

void Panel::performLayout()
{
	// dummy
}

void Panel::internalPerformLayout()
{
}

void Panel::drawSetColor(Scheme::SchemeColor sc)
{
}

void Panel::drawSetColor(int r,int g,int b,int a)
{
}

void Panel::drawFilledRect(int x0,int y0,int x1,int y1)
{
}

void Panel::drawOutlinedRect(int x0,int y0,int x1,int y1)
{
}

void Panel::drawSetTextFont(Scheme::SchemeFont sf)
{
}

void Panel::drawSetTextFont(Font* font)
{
}

void Panel::drawSetTextColor(Scheme::SchemeColor sc)
{
}

void Panel::drawSetTextColor(int r,int g,int b,int a)
{
}

void Panel::drawSetTextPos(int x,int y)
{
}

void Panel::drawPrintText(const char* str,int strlen)
{
}

void Panel::drawPrintText(int x,int y,const char* str,int strlen)
{
}

void Panel::drawPrintChar(char ch)
{
}

void Panel::drawPrintChar(int x,int y,char ch)
{
}

void Panel::drawSetTextureRGBA(int id,const char* rgba,int wide,int tall)
{
}

void Panel::drawSetTexture(int id)
{
}

void Panel::drawTexturedRect(int x0,int y0,int x1,int y1)
{
}

void Panel::solve()
{
}

void Panel::paintTraverse(bool repaint)
{
}

void Panel::paintBackground()
{
}

void Panel::paint()
{
}

void Panel::paintBuildOverlay()
{
}

void Panel::internalCursorMoved(int x,int y)
{
}

void Panel::internalCursorEntered()
{
}

void Panel::internalCursorExited()
{
}

void Panel::internalMousePressed(MouseCode code)
{
}

void Panel::internalMouseDoublePressed(MouseCode code)
{
}

void Panel::internalMouseReleased(MouseCode code)
{
}

void Panel::internalMouseWheeled(int delta)
{
}

void Panel::internalKeyPressed(KeyCode code)
{
}

void Panel::internalKeyTyped(KeyCode code)
{
}

void Panel::internalKeyReleased(KeyCode code)
{
}

void Panel::internalKeyFocusTicked()
{
}

void Panel::internalFocusChanged(bool lost)
{
}

void Panel::internalSetCursor()
{
}
