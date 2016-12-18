//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include "VGUI.h"
#include "VGUI_SurfaceBase.h"

using namespace vgui;

SurfaceBase::SurfaceBase(Panel* embeddedPanel)
{
}

SurfaceBase::~SurfaceBase()
{
}

Panel* SurfaceBase::getPanel()
{
	return null;
}

void SurfaceBase::requestSwap()
{
}

void SurfaceBase::resetModeInfo()
{
}

int SurfaceBase::getModeInfoCount()
{
	return 0;
}

bool SurfaceBase::getModeInfo(int mode,int& wide,int& tall,int& bpp)
{
	return false;
}

App* SurfaceBase::getApp()
{
	return null;
}

void SurfaceBase::setEmulatedCursorVisible(bool state)
{
}

void SurfaceBase::setEmulatedCursorPos(int x,int y)
{
}

void SurfaceBase::setTitle(const char* title)
{
}

bool SurfaceBase::setFullscreenMode(int wide,int tall,int bpp)
{
	return false;
}

void SurfaceBase::setWindowedMode()
{
}

void SurfaceBase::setAsTopMost(bool state)
{
}

void SurfaceBase::createPopup(Panel* embeddedPanel)
{
}

bool SurfaceBase::hasFocus()
{
	return false;
}

bool SurfaceBase::isWithin(int x,int y)
{
	return false;
}

int SurfaceBase::createNewTextureID(void)
{
	return 0;
}

void SurfaceBase::GetMousePos( int &x, int &y )
{
}

void SurfaceBase::addModeInfo(int wide,int tall,int bpp)
{
}

void SurfaceBase::drawSetColor(int r,int g,int b,int a)
{
}

void SurfaceBase::drawFilledRect(int x0,int y0,int x1,int y1)
{
}

void SurfaceBase::drawOutlinedRect(int x0,int y0,int x1,int y1)
{
}

void SurfaceBase::drawSetTextFont(Font* font)
{
}

void SurfaceBase::drawSetTextColor(int r,int g,int b,int a)
{
}

void SurfaceBase::drawSetTextPos(int x,int y)
{
}

void SurfaceBase::drawPrintText(const char* text,int textLen)
{
}

void SurfaceBase::drawSetTextureRGBA(int id,const char* rgba,int wide,int tall)
{
}

void SurfaceBase::drawSetTexture(int id)
{
}

void SurfaceBase::drawTexturedRect(int x0,int y0,int x1,int y1)
{
}

void SurfaceBase::invalidate(Panel *panel)
{
}

void SurfaceBase::enableMouseCapture(bool state)
{
}

void SurfaceBase::setCursor(Cursor* cursor)
{
}

void SurfaceBase::swapBuffers()
{
}

void SurfaceBase::pushMakeCurrent(Panel* panel,bool useInsets)
{
}

void SurfaceBase::popMakeCurrent(Panel* panel)
{
}

void SurfaceBase::applyChanges()
{
}
