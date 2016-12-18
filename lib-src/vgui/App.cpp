//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include "VGUI.h"
#include "VGUI_App.h"
#include "VGUI_SurfaceBase.h"
#include "VGUI_Panel.h"

#if defined ( WIN32 )
#include <windows.h>
#endif

using namespace vgui;

App *App::_instance=null;

App::App()
{
	init();
}

App::App(bool externalMain)
{
	init();
	_externalMain=externalMain;
}

App* App::getInstance()
{
	return _instance;
}

void App::start()
{
#if defined ( WIN32 )
	main(null,null);
#endif
	if(!_externalMain)
	{
		run();
		for(int i=0; i<_surfaceBaseDar.getCount();i++)
			_surfaceBaseDar[i]->setWindowedMode(); // ?
	}
}

void App::stop()
{
	_running=false;
}

void App::externalTick()
{
	internalTick();
}

bool App::wasMousePressed(MouseCode code,Panel* panel)
{
	return _mousePressed[code];
}

bool App::wasMouseDoublePressed(MouseCode code,Panel* panel)
{
	return _mouseDoublePressed[code];
}

bool App::isMouseDown(MouseCode code,Panel* panel)
{
	return _mouseDown[code];
}

bool App::wasMouseReleased(MouseCode code,Panel* panel)
{
	return _mouseReleased[code];
}

bool App::wasKeyPressed(KeyCode code,Panel* panel)
{
	if(panel && panel!=_keyFocus)
		return false;
	return _keyPressed[code];
}

bool App::isKeyDown(KeyCode code,Panel* panel)
{
	if(panel && panel!=_keyFocus)
		return false;
	return _keyDown[code];
}

bool App::wasKeyTyped(KeyCode code,Panel* panel)
{
	if(panel && panel!=_keyFocus)
		return false;
	return _keyTyped[code];
}

bool App::wasKeyReleased(KeyCode code,Panel* panel)
{
	if(panel && panel!=_keyFocus)
		return false;
	return _keyReleased[code];
}

void App::addTickSignal(TickSignal* s)
{
}

void App::setCursorPos(int x,int y)
{
	// dummy
}

void App::getCursorPos(int& x,int& y)
{
	_surfaceBaseDar[0]->GetMousePos(x,y);
}

void App::setMouseCapture(Panel* panel)
{
	if(panel==null)
	{
		if(_mouseCapture!=null)
			_mouseCapture->_surfaceBase->enableMouseCapture(false);
	}
	else
	{
		panel->_surfaceBase->enableMouseCapture(true);
	}
	_mouseCapture = panel;
}

void App::setMouseArena(int x0,int y0,int x1,int y1,bool enabled)
{
	setMouseArena(false);
	internalSetMouseArena(x0,y0,x1,y1,enabled);
}

void App::setMouseArena(Panel* panel)
{
	_mouseArenaPanel=panel;
}

void App::requestFocus(Panel* panel)
{
	_wantedKeyFocus=panel;
}
 
Panel* App::getFocus()
{
	return _keyFocus;
}

void App::repaintAll()
{
	for(int i=0;i<_surfaceBaseDar.getCount();i++)
	{
		_surfaceBaseDar[i]->getPanel()->repaintAll();
		_surfaceBaseDar[i]->invalidate(_surfaceBaseDar[i]->getPanel());
	}
}

void App::setScheme(Scheme* scheme)
{
	if(scheme)
	{
		_scheme=scheme;
		repaintAll();
	}
}

Scheme* App::getScheme()
{
	return _scheme;
}

void App::enableBuildMode()
{
	_wantedBuildMode=true;
}

long App::getTimeMillis()
{
#if defined ( WIN32 )
	return GetTickCount();
#else
	struct timeval tp;
	static int secbase = 0;

	gettimeofday(&tp, NULL);

	if (!secbase)
	{
		secbase = tp.tv_usec;
		return tp.tv_usec / 1000000.0;
	}

	return (tp.tv_sec - secbase) + tp.tv_usec / 1000000.0;
#endif
}

char App::getKeyCodeChar(KeyCode code,bool shifted)
{
	// if(shifted)
	// dummy
	return 0;
}

void App::getKeyCodeText(KeyCode code,char* buf,int buflen)
{
	// dummy
}

int App::getClipboardTextCount()
{
#if defined ( WIN32 )
	int count = 0;
	if (!OpenClipboard(NULL))
		return 0;
	
	HANDLE hmem = GetClipboardData(CF_TEXT);
	if (hmem)
	{
		count = GlobalSize(hmem);
	}

	CloseClipboard();
	return count;
#else
	return 0;
#endif
}

void App::setClipboardText(const char* text,int textLen)
{
#if defined ( WIN32 )
	if (!text)
		return;

	if (textLen <= 0)
		return;

	if (!OpenClipboard(NULL))
		return;

	EmptyClipboard();

	HANDLE hmem = GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE, textLen + 1);
	if (hmem)
	{
		void *ptr = GlobalLock(hmem);
		if (ptr != null)
		{
			memset(ptr, 0, textLen + 1);
			memcpy(ptr, text, textLen);
			GlobalUnlock(hmem);

			SetClipboardData(CF_TEXT, hmem);
		}
	}
	
	CloseClipboard();
#else
#endif
}

int App::getClipboardText(int offset,char* buf,int bufLen)
{
#if defined ( WIN32 )
	if (!buf)
		return 0;

	if (bufLen <= 0)
		return 0;

	int count = 0;
	if (!OpenClipboard(NULL))
		return 0;
	
	HANDLE hmem = GetClipboardData(CF_UNICODETEXT);
	if (hmem)
	{
		int len = GlobalSize(hmem);
		count = len - offset;
		if (count <= 0)
		{
			count = 0;
		}
		else
		{
			if (bufLen < count)
			{
				count = bufLen;
			}
			void *ptr = GlobalLock(hmem);
			if (ptr)
			{
				memcpy(buf, ((char *)ptr) + offset, count);
				GlobalUnlock(hmem);
			}
		}
	}

	CloseClipboard();
	return count;
#else
	return 0;
#endif
}

void App::reset()
{
	_keyFocus=null;
	_mouseFocus=null;
	_mouseCapture=null;
	_wantedKeyFocus=null;
	_buildMode=false;
	_wantedBuildMode=false;
	_mouseArenaPanel=null;
	//Font_Reset();
	setScheme(new Scheme());
}

static bool staticSplitRegistryKey(const char *key, char *key0, int key0Len, char *key1, int key1Len)
{
	if(key==null)
	{
		return false;
	}
	
	int len=strlen(key);
	if(len<=0)
	{
		return false;
	}

	int state=0;
	int Start=-1;
	for(int i=len-1;i>=0;i--)
	{
		if(key[i]=='\\')
		{
			break;
		}
		else
		{
			Start=i;
		}
	}

	if(Start==-1)
	{
		return false;
	}
	
	vgui_strcpy(key0,Start+1,key);
	vgui_strcpy(key1,(len-Start)+1,key+Start);

	return true;
}

void App::internalSetMouseArena(int x0,int y0,int x1,int y1,bool enabled)
{
#if defined ( WIN32 )
	RECT rc;
	rc.left = x0;
	rc.top = y0;
	rc.bottom = y1;
	rc.right = x1;
	ClipCursor(enabled?&rc:NULL);
#endif
}

bool App::setRegistryString(const char* key,const char* value)
{
#if defined ( _WIN32 )
	HKEY hKey;

	HKEY hSlot = HKEY_CURRENT_USER;
	if (!strncmp(key, "HKEY_LOCAL_MACHINE", 18))
	{
		hSlot = HKEY_LOCAL_MACHINE;
		key += 19;
	}
	else if (!strncmp(key, "HKEY_CURRENT_USER", 17))
	{
		hSlot = HKEY_CURRENT_USER;
		key += 18;
	}

	char key0[256],key1[256];
	if(!staticSplitRegistryKey(key,key0,256,key1,256))
	{
		return false;
	}

	if(RegCreateKeyEx(hSlot,key0,null,null,REG_OPTION_NON_VOLATILE,KEY_WRITE,null,&hKey,null)!=ERROR_SUCCESS)
	{
		return false;
	}
		
	if(RegSetValueEx(hKey,key1,null,REG_SZ,(uchar*)value,strlen(value)+1)==ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
		return true;
	}

	RegCloseKey(hKey);

	return false;
#else
	return false;
#endif
}

bool App::getRegistryString(const char* key,char* value,int valueLen)
{
#if defined ( _WIN32 )
	HKEY hKey;

	HKEY hSlot = HKEY_CURRENT_USER;
	if (!strncmp(key, "HKEY_LOCAL_MACHINE", 18))
	{
		hSlot = HKEY_LOCAL_MACHINE;
		key += 19;
	}
	else if (!strncmp(key, "HKEY_CURRENT_USER", 17))
	{
		hSlot = HKEY_CURRENT_USER;
		key += 18;
	}

	char key0[256],key1[256];
	if(!staticSplitRegistryKey(key,key0,256,key1,256))
	{
		return false;
	}

	if(RegOpenKeyEx(hSlot,key0,null,KEY_READ,&hKey)!=ERROR_SUCCESS)
	{
		return false;
	}

	ulong len=valueLen;
	if(RegQueryValueEx(hKey,key1,null,null,(uchar*)value,&len)==ERROR_SUCCESS)
	{		
		RegCloseKey(hKey);
		return true;
	}

	RegCloseKey(hKey);
	return false;
#else
	return false;
#endif
}

bool App::setRegistryInteger(const char* key,int value)
{
#if defined ( _WIN32 )
	HKEY hKey;
	HKEY hSlot = HKEY_CURRENT_USER;
	if (!strncmp(key, "HKEY_LOCAL_MACHINE", 18))
	{
		hSlot = HKEY_LOCAL_MACHINE;
		key += 19;
	}
	else if (!strncmp(key, "HKEY_CURRENT_USER", 17))
	{
		hSlot = HKEY_CURRENT_USER;
		key += 18;
	}

	char key0[256],key1[256];
	if(!staticSplitRegistryKey(key,key0,256,key1,256))
	{
		return false;
	}

	if(RegCreateKeyEx(hSlot,key0,null,null,REG_OPTION_NON_VOLATILE,KEY_WRITE,null,&hKey,null)!=ERROR_SUCCESS)
	{
		return false;
	}
		
	if(RegSetValueEx(hKey,key1,null,REG_DWORD,(uchar*)&value,4)==ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
		return true;
	}

	RegCloseKey(hKey);
	return false;
#else
	return false;
#endif
}

bool App::getRegistryInteger(const char* key,int& value)
{
#if defined ( _WIN32 )
	HKEY hKey;
	HKEY hSlot = HKEY_CURRENT_USER;
	if (!strncmp(key, "HKEY_LOCAL_MACHINE", 18))
	{
		hSlot = HKEY_LOCAL_MACHINE;
		key += 19;
	}
	else if (!strncmp(key, "HKEY_CURRENT_USER", 17))
	{
		hSlot = HKEY_CURRENT_USER;
		key += 18;
	}

	char key0[256],key1[256];
	if(!staticSplitRegistryKey(key,key0,256,key1,256))
	{
		return false;
	}

	if(RegOpenKeyEx(hSlot,key0,null,KEY_READ,&hKey)!=ERROR_SUCCESS)
	{
		return false;
	}

	ulong len=4;
	if(RegQueryValueEx(hKey,key1,null,null,(uchar*)&value,&len)==ERROR_SUCCESS)
	{		
		RegCloseKey(hKey);
		return true;
	}

	RegCloseKey(hKey);
	return false;
#else
	return false;
#endif
}

void App::setCursorOveride(Cursor* cursor)
{
	_cursorOveride=cursor;
}

Cursor* App::getCursorOveride()
{
	return _cursorOveride;
}

void App::setMinimumTickMillisInterval(int interval)
{
	_minimumTickMillisInterval=interval;
}

void App::main(int argc,char* argv[])
{
	//dummy
}

void App::run()
{
	_running=true;
	do
		internalTick();
	while(_running);
	setMouseArena(0,0,0,0,false);
}
 
void App::internalCursorMoved(int x,int y,SurfaceBase* surfaceBase)
{
	surfaceBase->getPanel()->localToScreen(x,y);
	if(!_buildMode)
	{
		updateMouseFocus(x,y,surfaceBase);
		if(_mouseFocus)
			_mouseFocus->internalCursorMoved(x,y);
	}
}

void App::internalMousePressed(MouseCode code,SurfaceBase* surfaceBase)
{
	_mousePressed[code]=true;
	_mouseDown[code]=true;
	if(!_buildMode)
	{
		if(_mouseFocus)
			_mouseFocus->internalMousePressed(code);
	}
}

void App::internalMouseDoublePressed(MouseCode code,SurfaceBase* surfaceBase)
{
	_mouseDoublePressed[code]=true;
	if(!_buildMode)
	{
		if(_mouseFocus)
			_mouseFocus->internalMouseDoublePressed(code);
	}
}

void App::internalMouseReleased(MouseCode code,SurfaceBase* surfaceBase)
{
	_mouseReleased[code]=true;
	_mouseDown[code]=false;
	if(!_buildMode)
	{
		if(_mouseFocus)
			_mouseFocus->internalMouseReleased(code);
	}
}

void App::internalMouseWheeled(int delta,SurfaceBase* surfaceBase)
{
	if(!_buildMode)
	{
		if(_mouseFocus)
			_mouseFocus->internalMouseWheeled(delta);
	}
}

void App::internalKeyPressed(KeyCode code,SurfaceBase* surfaceBase)
{
	if(code < 0||code >= KEY_LAST)
		return;

	_keyPressed[code]=true;
	_keyDown[code]=true;
	if(!_buildMode)
	{
		if(_mouseFocus)
			_mouseFocus->internalKeyPressed(code);
	}
}

void App::internalKeyTyped(KeyCode code,SurfaceBase* surfaceBase)
{
	if(code < 0||code >= KEY_LAST)
		return;

	_keyTyped[code]=true;
	if(!_buildMode)
	{
		if(_mouseFocus)
			_mouseFocus->internalKeyTyped(code);
	}
}

void App::internalKeyReleased(KeyCode code,SurfaceBase* surfaceBase)
{
	if(code < 0||code >= KEY_LAST)
		return;

	_keyReleased[code]=true;
	_keyDown[code]=false;
	if(!_buildMode)
	{
		if(_mouseFocus)
			_mouseFocus->internalKeyReleased(code);
	}
}

void App::init()
{
	// dummy
}

void App::updateMouseFocus(int x,int y,SurfaceBase* surfaceBase)
{
	if(_mouseCapture!=null)
		setMouseFocus(_mouseCapture);
	else
	{
		if(surfaceBase->isWithin(x,y))
		{
			Panel* panel=surfaceBase->getPanel()->isWithinTraverse(x,y);
			if(panel!=null)
				setMouseFocus(panel);
		}
	}
}

void App::setMouseFocus(Panel* newMouseFocus)
{
	if(_mouseFocus!=newMouseFocus)
	{
		_oldMouseFocus=_mouseFocus;
		_mouseFocus=newMouseFocus;
		if(_oldMouseFocus!=null)
			_oldMouseFocus->internalCursorExited();
		if(_mouseFocus!=null)
			_mouseFocus->internalCursorEntered();
	}
}

void App::surfaceBaseCreated(SurfaceBase* surfaceBase)
{
	// dummy
}

void App::surfaceBaseDeleted(SurfaceBase* surfaceBase)
{
	// dummy
}

void App::platTick()
{
#if defined ( _WIN32 )
#endif
}

void App::internalTick()
{
	// dummy
}
