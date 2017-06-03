//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include<VGUI_App.h>
#include<VGUI_SurfaceBase.h>
#include"vgui_linux.h"
#include<sys/time.h>

using namespace vgui;

void App::platTick()
{
}

void App::setCursorPos(int x,int y)
{
}

void App::getCursorPos(int& x,int& y)
{
	_surfaceBaseDar[0]->GetMousePos(x,y);
}

void App::internalSetMouseArena(int x0,int y0,int x1,int y1,bool enabled)
{
}

long App::getTimeMillis()
{
	struct timeval tp;
	static int secbase = 0;

	gettimeofday(&tp, NULL);

	if (!secbase)
	{
		secbase = tp.tv_sec;
		return tp.tv_usec / 1000000.0;
	}

	return (tp.tv_sec - secbase) * 1000 + tp.tv_usec / 1000.0;
}

void App::setClipboardText(const char* text,int textLen)
{
}

int App::getClipboardTextCount()
{
	return 0;
}

int App::getClipboardText(int offset,char* buf,int bufLen)
{
	return 0;
}

bool App::setRegistryString(const char* key,const char* value)
{
	return false;
}

bool App::getRegistryString(const char* key,char* value,int valueLen)
{
	return false;
}

bool App::setRegistryInteger(const char* key,int value)
{
	return false;
}

bool App::getRegistryInteger(const char* key,int& value)
{
	return false;
}

App* App::getInstance()
{
	return _instance;
}
