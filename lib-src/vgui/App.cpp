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
#include "VGUI_TickSignal.h"
#include "VGUI_Font.h"

using namespace vgui;

App *App::_instance=null;
char *_keyTrans[KEY_LAST];

App::App()
{
	init();
}

App::App(bool externalMain)
{
	init();
	_externalMain=externalMain;
}

void App::start()
{
#if defined ( WIN32 )
	main(__argc,__argv);
#endif
	if(!_externalMain)
	{
		run();
		for(int i=0; i<_surfaceBaseDar.getCount();i++)
			_surfaceBaseDar[i]->setWindowedMode();
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
	_tickSignalDar.putElement(s);
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

char App::getKeyCodeChar(KeyCode code,bool shifted)
{
	return _keyTrans[code][shifted?1:0];
}

void App::getKeyCodeText(KeyCode code,char* buf,int buflen)
{
	if (!buf)
		return;

	// copy text into buf up to buflen in length
	// skip 2 in _keyTrans because the first two are for GetKeyCodeChar
	for (int i = 0; i < buflen; i++)
	{
		char ch = _keyTrans[code][i+2];
		buf[i] = ch;
		if (ch == 0)
			break;
	}
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
	Font_Reset();
	setScheme(new Scheme());
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
	_instance=this;
	_externalMain=false;
	_running=false;
	_keyFocus=null;
	_oldMouseFocus=null;
	_mouseFocus=null;
	_mouseCapture=null;
	_wantedKeyFocus=null;
	_scheme=new Scheme();
	_buildMode=false;
	_wantedBuildMode=false;
	_mouseArenaPanel=null;
	_cursorOveride=null;
	_nextTickMillis=getTimeMillis();
	_minimumTickMillisInterval=50;

	for(int i=0;i<MOUSE_LAST;i++)
	{
		_mousePressed[i]=false;
		_mouseDoublePressed[i]=false;
		_mouseDown[i]=false;
		_mouseReleased[i]=false;
	}

	for(int i=0;i<KEY_LAST;i++)
	{
		_keyPressed[i]=false;
		_keyTyped[i]=false;
		_keyDown[i]=false;
		_keyReleased[i]=false;
	}
#if defined ( WIN32 )
	_keyTrans[KEY_0]			="0)KEY_0";
	_keyTrans[KEY_1]			="1!KEY_1";
	_keyTrans[KEY_2]			="2@KEY_2";
	_keyTrans[KEY_3]			="3#KEY_3";
	_keyTrans[KEY_4]			="4$KEY_4";
	_keyTrans[KEY_5]			="5%KEY_5";
	_keyTrans[KEY_6]			="6^KEY_6";
	_keyTrans[KEY_7]			="7&KEY_7";
	_keyTrans[KEY_8]			="8*KEY_8";
	_keyTrans[KEY_9]			="9(KEY_9";
	_keyTrans[KEY_A]			="aAKEY_A";
	_keyTrans[KEY_B]			="bBKEY_B";
	_keyTrans[KEY_C]			="cCKEY_C";
	_keyTrans[KEY_D]			="dDKEY_D";
	_keyTrans[KEY_E]			="eEKEY_E";
	_keyTrans[KEY_F]			="fFKEY_F";
	_keyTrans[KEY_G]			="gGKEY_G";
	_keyTrans[KEY_H]			="hHKEY_H";
	_keyTrans[KEY_I]			="iIKEY_I";
	_keyTrans[KEY_J]			="jJKEY_J";
	_keyTrans[KEY_K]			="kKKEY_K";
	_keyTrans[KEY_L]			="lLKEY_L";
	_keyTrans[KEY_M]			="mMKEY_M";
	_keyTrans[KEY_N]			="nNKEY_N";
	_keyTrans[KEY_O]			="oOKEY_O";
	_keyTrans[KEY_P]			="pPKEY_P";
	_keyTrans[KEY_Q]			="qQKEY_Q";
	_keyTrans[KEY_R]			="rRKEY_R";
	_keyTrans[KEY_S]			="sSKEY_S";
	_keyTrans[KEY_T]			="tTKEY_T";
	_keyTrans[KEY_U]			="uUKEY_U";
	_keyTrans[KEY_V]			="vVKEY_V";
	_keyTrans[KEY_W]			="wWKEY_W";
	_keyTrans[KEY_X]			="xXKEY_X";
	_keyTrans[KEY_Y]			="yYKEY_Y";
	_keyTrans[KEY_Z]			="zZKEY_Z";
	_keyTrans[KEY_PAD_0]		="0\0KEY_PAD_0";
	_keyTrans[KEY_PAD_1]		="1\0KEY_PAD_1";
	_keyTrans[KEY_PAD_2]		="2\0KEY_PAD_2";
	_keyTrans[KEY_PAD_3]		="3\0KEY_PAD_3";
	_keyTrans[KEY_PAD_4]		="4\0KEY_PAD_4";
	_keyTrans[KEY_PAD_5]		="5\0KEY_PAD_5";
	_keyTrans[KEY_PAD_6]		="6\0KEY_PAD_6";
	_keyTrans[KEY_PAD_7]		="7\0KEY_PAD_7";
	_keyTrans[KEY_PAD_8]		="8\0KEY_PAD_8";
	_keyTrans[KEY_PAD_9]		="9\0KEY_PAD_9";
	_keyTrans[KEY_PAD_DIVIDE]	="//KEY_PAD_DIVIDE";
	_keyTrans[KEY_PAD_MULTIPLY]	="**KEY_PAD_MULTIPLY";
	_keyTrans[KEY_PAD_MINUS]	="--KEY_PAD_MINUS";
	_keyTrans[KEY_PAD_PLUS]		="++KEY_PAD_PLUS";
	_keyTrans[KEY_PAD_ENTER]	="\0\0KEY_PAD_ENTER";
	_keyTrans[KEY_PAD_DECIMAL]	=".\0KEY_PAD_DECIMAL";
	_keyTrans[KEY_LBRACKET]		="[{KEY_LBRACKET";
	_keyTrans[KEY_RBRACKET]		="]}KEY_RBRACKET";
	_keyTrans[KEY_SEMICOLON]	=";:KEY_SEMICOLON";
	_keyTrans[KEY_APOSTROPHE]	="'\"KEY_APOSTROPHE";
	_keyTrans[KEY_BACKQUOTE]	="`~KEY_BACKQUOTE";
	_keyTrans[KEY_COMMA]		=",<KEY_COMMA";
	_keyTrans[KEY_PERIOD]		=".>KEY_PERIOD";
	_keyTrans[KEY_SLASH]		="/?KEY_SLASH";
	_keyTrans[KEY_BACKSLASH]	="\\|KEY_BACKSLASH";
	_keyTrans[KEY_MINUS]		="-_KEY_MINUS";
	_keyTrans[KEY_EQUAL]		="=+KEY_EQUAL";
	_keyTrans[KEY_ENTER]		="\0\0KEY_ENTER";
	_keyTrans[KEY_SPACE]		="  KEY_SPACE";
	_keyTrans[KEY_BACKSPACE]	="\0\0KEY_BACKSPACE";
	_keyTrans[KEY_TAB]			="\0\0KEY_TAB";
	_keyTrans[KEY_CAPSLOCK]		="\0\0KEY_CAPSLOCK";
	_keyTrans[KEY_NUMLOCK]		="\0\0KEY_NUMLOCK";
	_keyTrans[KEY_ESCAPE]		="\0\0KEY_ESCAPE";
	_keyTrans[KEY_SCROLLLOCK]	="\0\0KEY_SCROLLLOCK";
	_keyTrans[KEY_INSERT]		="\0\0KEY_INSERT";
	_keyTrans[KEY_DELETE]		="\0\0KEY_DELETE";
	_keyTrans[KEY_HOME]			="\0\0KEY_HOME";
	_keyTrans[KEY_END]			="\0\0KEY_END";
	_keyTrans[KEY_PAGEUP]		="\0\0KEY_PAGEUP";
	_keyTrans[KEY_PAGEDOWN]		="\0\0KEY_PAGEDOWN";
	_keyTrans[KEY_BREAK]		="\0\0KEY_BREAK";
	_keyTrans[KEY_LSHIFT]		="\0\0KEY_LSHIFT";
	_keyTrans[KEY_RSHIFT]		="\0\0KEY_RSHIFT";
	_keyTrans[KEY_LALT]			="\0\0KEY_LALT";
	_keyTrans[KEY_RALT]			="\0\0KEY_RALT";
	_keyTrans[KEY_LCONTROL]		="\0\0KEY_LCONTROL";
	_keyTrans[KEY_RCONTROL]		="\0\0KEY_RCONTROL";
	_keyTrans[KEY_LWIN]			="\0\0KEY_LWIN";
	_keyTrans[KEY_RWIN]			="\0\0KEY_RWIN";
	_keyTrans[KEY_APP]			="\0\0KEY_APP";
	_keyTrans[KEY_UP]			="\0\0KEY_UP";
	_keyTrans[KEY_LEFT]			="\0\0KEY_LEFT";
	_keyTrans[KEY_DOWN]			="\0\0KEY_DOWN";
	_keyTrans[KEY_RIGHT]		="\0\0KEY_RIGHT";
	_keyTrans[KEY_F1]			="\0\0KEY_F1";
	_keyTrans[KEY_F2]			="\0\0KEY_F2";
	_keyTrans[KEY_F3]			="\0\0KEY_F3";
	_keyTrans[KEY_F4]			="\0\0KEY_F4";
	_keyTrans[KEY_F5]			="\0\0KEY_F5";
	_keyTrans[KEY_F6]			="\0\0KEY_F6";
	_keyTrans[KEY_F7]			="\0\0KEY_F7";
	_keyTrans[KEY_F8]			="\0\0KEY_F8";
	_keyTrans[KEY_F9]			="\0\0KEY_F9";
	_keyTrans[KEY_F10]			="\0\0KEY_F10";
	_keyTrans[KEY_F11]			="\0\0KEY_F11";
	_keyTrans[KEY_F12]			="\0\0KEY_F12";
#endif
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
	_surfaceBaseDar.putElement(surfaceBase);
}

void App::surfaceBaseDeleted(SurfaceBase* surfaceBase)
{
	_surfaceBaseDar.removeElement(surfaceBase);
	_mouseFocus=null;
	_mouseCapture=null;
	_keyFocus=null;
}

void App::internalTick()
{
	if(getTimeMillis()<_nextTickMillis)
		return;

	platTick();

	int x,y;
	getCursorPos(x,y);

	bool within=false;
	for(int i=0;i<_surfaceBaseDar.getCount();i++)
	{
		updateMouseFocus(x,y,_surfaceBaseDar[i]);

		if(_surfaceBaseDar[i]->isWithin(x,y))
			within=true;

		_surfaceBaseDar[i]->setEmulatedCursorPos(x,y);
	}

	if(!within)
		setMouseFocus(null);

	if(_mouseFocus)
		_mouseFocus->internalSetCursor();

	for(int i=0;i<_tickSignalDar.getCount();i++)
	{
		_tickSignalDar[i]->ticked();
	}

	if(_keyFocus)
		_keyFocus->internalKeyFocusTicked();

	for(int i=0;i<MOUSE_LAST;i++)
	{
		_mousePressed[i]=false;
		_mouseDoublePressed[i]=false;
		_mouseDown[i]=false;
		_mouseReleased[i]=false;
	}

	for(int i=0;i<KEY_LAST;i++)
	{
		_keyPressed[i]=false;
		_keyTyped[i]=false;
		_keyDown[i]=false;
		_keyReleased[i]=false;
	}

	int j=0;
	for(;j<_surfaceBaseDar.getCount();j++)
	{
		if(_surfaceBaseDar[j]->hasFocus())
			break;
	}
	if(j==_surfaceBaseDar.getCount())
		_wantedKeyFocus=null;

	if(_keyFocus!=_wantedKeyFocus)
	{
		if(_keyFocus)
		{
			_keyFocus->internalFocusChanged(true);
			_keyFocus->repaint();
		}

		if(_wantedKeyFocus)
		{
			_wantedKeyFocus->internalFocusChanged(false);
			_wantedKeyFocus->repaint();
		}
	}
	_keyFocus=_wantedKeyFocus;
	_buildMode=_wantedBuildMode;

	for(int i=0;i<_surfaceBaseDar.getCount();i++)
	{
		_surfaceBaseDar[i]->getPanel()->solveTraverse();
		_surfaceBaseDar[i]->applyChanges();
	}

	if(_mouseArenaPanel)
	{
		SurfaceBase* surfaceBase=_mouseArenaPanel->getSurfaceBase();
		if(surfaceBase)
		{
			int x,y;
			surfaceBase->getPanel()->getPos(x,y);

			int x0,y0,x1,y1;
			_mouseArenaPanel->getAbsExtents(x0,y0,x1,y1);
			internalSetMouseArena(x+x0,y+y0,x+x1,y+y1,true);
		}
	}

	_nextTickMillis=getTimeMillis()+_minimumTickMillisInterval;
}
