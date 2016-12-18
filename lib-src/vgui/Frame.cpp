//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include "VGUI.h"
#include "VGUI_Frame.h"

using namespace vgui;

Frame::Frame(int x,int y,int wide,int tall)
{
}

void Frame::setSize(int wide,int tall)
{
}

void Frame::setInternal(bool state)
{
}

void Frame::paintBackground()
{
}

bool Frame::isInternal()
{
	return false;
}

Panel* Frame::getClient()
{
	return null;
}

void Frame::setTitle(const char* title)
{
}

void Frame::getTitle(char* buf,int bufLen)
{
}

void Frame::setMoveable(bool state)
{
}

void Frame::setSizeable(bool state)
{
}

bool Frame::isMoveable()
{
	return false;
}

bool Frame::isSizeable()
{
	return false;
}

void Frame::addFrameSignal(FrameSignal* s)
{
}

void Frame::setVisible(bool state)
{
}

void Frame::setMenuButtonVisible(bool state)
{
}

void Frame::setTrayButtonVisible(bool state)
{
}

void Frame::setMinimizeButtonVisible(bool state)
{
}

void Frame::setMaximizeButtonVisible(bool state)
{
}

void Frame::setCloseButtonVisible(bool state)
{
}

void Frame::fireClosingSignal()
{
}

void Frame::fireMinimizingSignal()
{
}
