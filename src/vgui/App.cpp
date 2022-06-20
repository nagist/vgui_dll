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

#include<stdio.h>
#include<VGUI_App.h>
#include<VGUI_SurfaceBase.h>
#include<VGUI_Panel.h>
#include<VGUI_TickSignal.h>
#include<VGUI_Font.h>

using namespace vgui;

static char *staticKeyTrans[KEY_LAST];
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

	int i;
	for(i=0;i<MOUSE_LAST;i++)
	{
		_mousePressed[i]=false;
		_mouseDoublePressed[i]=false;
		_mouseDown[i]=false;
		_mouseReleased[i]=false;
	}

	for(i=0;i<KEY_LAST;i++)
	{
		_keyPressed[i]=false;
		_keyTyped[i]=false;
		_keyDown[i]=false;
		_keyReleased[i]=false;
	}

	// build key to text translation table
	// first byte unshifted key
	// second byte shifted key
	// the rest is the name of the key
#if defined ( _WIN32 )
	staticKeyTrans[KEY_0]				="0)KEY_0";
	staticKeyTrans[KEY_1]				="1!KEY_1";
	staticKeyTrans[KEY_2]				="2@KEY_2";
	staticKeyTrans[KEY_3]				="3#KEY_3";
	staticKeyTrans[KEY_4]				="4$KEY_4";
	staticKeyTrans[KEY_5]				="5%KEY_5";
	staticKeyTrans[KEY_6]				="6^KEY_6";
	staticKeyTrans[KEY_7]				="7&KEY_7";
	staticKeyTrans[KEY_8]				="8*KEY_8";
	staticKeyTrans[KEY_9]				="9(KEY_9";
	staticKeyTrans[KEY_A]				="aAKEY_A";
	staticKeyTrans[KEY_B]				="bBKEY_B";
	staticKeyTrans[KEY_C]				="cCKEY_C";
	staticKeyTrans[KEY_D]				="dDKEY_D";
	staticKeyTrans[KEY_E]				="eEKEY_E";
	staticKeyTrans[KEY_F]				="fFKEY_F";
	staticKeyTrans[KEY_G]				="gGKEY_G";
	staticKeyTrans[KEY_H]				="hHKEY_H";
	staticKeyTrans[KEY_I]				="iIKEY_I";
	staticKeyTrans[KEY_J]				="jJKEY_J";
	staticKeyTrans[KEY_K]				="kKKEY_K";
	staticKeyTrans[KEY_L]				="lLKEY_L";
	staticKeyTrans[KEY_M]				="mMKEY_M";
	staticKeyTrans[KEY_N]				="nNKEY_N";
	staticKeyTrans[KEY_O]				="oOKEY_O";
	staticKeyTrans[KEY_P]				="pPKEY_P";
	staticKeyTrans[KEY_Q]				="qQKEY_Q";
	staticKeyTrans[KEY_R]				="rRKEY_R";
	staticKeyTrans[KEY_S]				="sSKEY_S";
	staticKeyTrans[KEY_T]				="tTKEY_T";
	staticKeyTrans[KEY_U]				="uUKEY_U";
	staticKeyTrans[KEY_V]				="vVKEY_V";
	staticKeyTrans[KEY_W]				="wWKEY_W";
	staticKeyTrans[KEY_X]				="xXKEY_X";
	staticKeyTrans[KEY_Y]				="yYKEY_Y";
	staticKeyTrans[KEY_Z]				="zZKEY_Z";
	staticKeyTrans[KEY_PAD_0]			="0\0KEY_PAD_0";
	staticKeyTrans[KEY_PAD_1]			="1\0KEY_PAD_1";
	staticKeyTrans[KEY_PAD_2]			="2\0KEY_PAD_2";
	staticKeyTrans[KEY_PAD_3]			="3\0KEY_PAD_3";
	staticKeyTrans[KEY_PAD_4]			="4\0KEY_PAD_4";
	staticKeyTrans[KEY_PAD_5]			="5\0KEY_PAD_5";
	staticKeyTrans[KEY_PAD_6]			="6\0KEY_PAD_6";
	staticKeyTrans[KEY_PAD_7]			="7\0KEY_PAD_7";
	staticKeyTrans[KEY_PAD_8]			="8\0KEY_PAD_8";
	staticKeyTrans[KEY_PAD_9]			="9\0KEY_PAD_9";
	staticKeyTrans[KEY_PAD_DIVIDE]		="//KEY_PAD_DIVIDE";
	staticKeyTrans[KEY_PAD_MULTIPLY]	="**KEY_PAD_MULTIPLY";
	staticKeyTrans[KEY_PAD_MINUS]		="--KEY_PAD_MINUS";
	staticKeyTrans[KEY_PAD_PLUS]		="++KEY_PAD_PLUS";
	staticKeyTrans[KEY_PAD_ENTER]		="\0\0KEY_PAD_ENTER";
	staticKeyTrans[KEY_PAD_DECIMAL]		=".\0KEY_PAD_DECIMAL";
	staticKeyTrans[KEY_LBRACKET]		="[{KEY_LBRACKET";
	staticKeyTrans[KEY_RBRACKET]		="]}KEY_RBRACKET";
	staticKeyTrans[KEY_SEMICOLON]		=";:KEY_SEMICOLON";
	staticKeyTrans[KEY_APOSTROPHE]		="'\"KEY_APOSTROPHE";
	staticKeyTrans[KEY_BACKQUOTE]		="`~KEY_BACKQUOTE";
	staticKeyTrans[KEY_COMMA]			=",<KEY_COMMA";
	staticKeyTrans[KEY_PERIOD]			=".>KEY_PERIOD";
	staticKeyTrans[KEY_SLASH]			="/?KEY_SLASH";
	staticKeyTrans[KEY_BACKSLASH]		="\\|KEY_BACKSLASH";
	staticKeyTrans[KEY_MINUS]			="-_KEY_MINUS";
	staticKeyTrans[KEY_EQUAL]			="=+KEY_EQUAL";
	staticKeyTrans[KEY_ENTER]			="\0\0KEY_ENTER";
	staticKeyTrans[KEY_SPACE]			="  KEY_SPACE";
	staticKeyTrans[KEY_BACKSPACE]		="\0\0KEY_BACKSPACE";
	staticKeyTrans[KEY_TAB]				="\0\0KEY_TAB";
	staticKeyTrans[KEY_CAPSLOCK]		="\0\0KEY_CAPSLOCK";
	staticKeyTrans[KEY_NUMLOCK]			="\0\0KEY_NUMLOCK";
	staticKeyTrans[KEY_ESCAPE]			="\0\0KEY_ESCAPE";
	staticKeyTrans[KEY_SCROLLLOCK]		="\0\0KEY_SCROLLLOCK";
	staticKeyTrans[KEY_INSERT]			="\0\0KEY_INSERT";
	staticKeyTrans[KEY_DELETE]			="\0\0KEY_DELETE";
	staticKeyTrans[KEY_HOME]			="\0\0KEY_HOME";
	staticKeyTrans[KEY_END]				="\0\0KEY_END";
	staticKeyTrans[KEY_PAGEUP]			="\0\0KEY_PAGEUP";
	staticKeyTrans[KEY_PAGEDOWN]		="\0\0KEY_PAGEDOWN";
	staticKeyTrans[KEY_BREAK]			="\0\0KEY_BREAK";
	staticKeyTrans[KEY_LSHIFT]			="\0\0KEY_LSHIFT";
	staticKeyTrans[KEY_RSHIFT]			="\0\0KEY_RSHIFT";
	staticKeyTrans[KEY_LALT]			="\0\0KEY_LALT";
	staticKeyTrans[KEY_RALT]			="\0\0KEY_RALT";
	staticKeyTrans[KEY_LCONTROL]		="\0\0KEY_LCONTROL";
	staticKeyTrans[KEY_RCONTROL]		="\0\0KEY_RCONTROL";
	staticKeyTrans[KEY_LWIN]			="\0\0KEY_LWIN";
	staticKeyTrans[KEY_RWIN]			="\0\0KEY_RWIN";
	staticKeyTrans[KEY_APP]				="\0\0KEY_APP";
	staticKeyTrans[KEY_UP]				="\0\0KEY_UP";
	staticKeyTrans[KEY_LEFT]			="\0\0KEY_LEFT";
	staticKeyTrans[KEY_DOWN]			="\0\0KEY_DOWN";
	staticKeyTrans[KEY_RIGHT]			="\0\0KEY_RIGHT";
	staticKeyTrans[KEY_F1]				="\0\0KEY_F1";
	staticKeyTrans[KEY_F2]				="\0\0KEY_F2";
	staticKeyTrans[KEY_F3]				="\0\0KEY_F3";
	staticKeyTrans[KEY_F4]				="\0\0KEY_F4";
	staticKeyTrans[KEY_F5]				="\0\0KEY_F5";
	staticKeyTrans[KEY_F6]				="\0\0KEY_F6";
	staticKeyTrans[KEY_F7]				="\0\0KEY_F7";
	staticKeyTrans[KEY_F8]				="\0\0KEY_F8";
	staticKeyTrans[KEY_F9]				="\0\0KEY_F9";
	staticKeyTrans[KEY_F10]				="\0\0KEY_F10";
	staticKeyTrans[KEY_F11]				="\0\0KEY_F11";
	staticKeyTrans[KEY_F12]				="\0\0KEY_F12";
#endif
}

void App::externalTick()
{
	internalTick();
}

void App::run()
{
	_running=true;

	while(_running)
	{
		internalTick();
	}

	setMouseArena(0,0,0,0,false);
}

void App::start()
{
#if defined ( _WIN32 )
	main(__argc,__argv);
#endif
	if(_externalMain)
	{
		return;
	}
	run();

	for(int i=0;i<_surfaceBaseDar.getCount();i++)
	{
		_surfaceBaseDar[i]->setWindowedMode();
	}
}

void App::stop()
{
	_running=false;
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

void App::updateMouseFocus(int x,int y,SurfaceBase* surfaceBase)
{
	if(_mouseCapture!=null)
	{
		setMouseFocus(_mouseCapture);
		return;
	}

	if(surfaceBase->isWithin(x,y))
	{
		Panel* focus=surfaceBase->getPanel()->isWithinTraverse(x,y);

		if(focus!=null)
		{
			setMouseFocus(focus);
		}
	}
}

void App::internalCursorMoved(int x,int y,SurfaceBase* surfaceBase)
{
	surfaceBase->getPanel()->localToScreen(x,y);

	if(!_buildMode)
	{
		//cursor has moved, so make sure the mouseFocus is current
		updateMouseFocus(x,y,surfaceBase);

		//UpdateMouseFocus would have set _mouseFocus current, so tell the panel with the mouseFocus the mouse has moved
		if(_mouseFocus!=null)
		{
			_mouseFocus->internalCursorMoved(x,y);
		}
	}
}

void App::internalMousePressed(MouseCode code,SurfaceBase* surfaceBzase)
{
	//set mouse state
	_mousePressed[code]=1;
	_mouseDown[code]=1;

	if(!_buildMode)
	{
		if(_mouseFocus!=null)
		{
			_mouseFocus->internalMousePressed(code);
		}
	}
}

void App::internalMouseDoublePressed(MouseCode code,SurfaceBase* surfaceBase)
{
	//set mouse state
	_mouseDoublePressed[code]=1;

	if(!_buildMode)
	{
		if(_mouseFocus!=null)
		{
			_mouseFocus->internalMouseDoublePressed(code);
		}
	}
}

void App::internalMouseReleased(MouseCode code,SurfaceBase* surfaceBase)
{
	//set mouse state
	_mouseReleased[code]=1;
	_mouseDown[code]=0;

	if(!_buildMode)
	{
		if(_mouseFocus!=null)
		{
			_mouseFocus->internalMouseReleased(code);
		}
	}
}

void App::internalMouseWheeled(int delta,SurfaceBase* surfaceBase)
{
	if(!_buildMode)
	{
		if(_keyFocus!=null)
		{
			_keyFocus->internalMouseWheeled(delta);
		}
	}
}

void App::internalKeyPressed(KeyCode code,SurfaceBase* surfaceBase)
{
	if((code < 0)||(code >= KEY_LAST))
	{
		return;
	}

	//set key state
	_keyPressed[code]=1;
	_keyDown[code]=1;

	if(!_buildMode)
	{
		if(_keyFocus!=null)
		{
			_keyFocus->internalKeyPressed(code);
		}
	}
}

void App::internalKeyTyped(KeyCode code,SurfaceBase* surfaceBase)
{
	if((code < 0)||(code >= KEY_LAST))
	{
		return;
	}

	//set key state
	_keyTyped[code]=1;

	if(!_buildMode)
	{
		if(_keyFocus!=null)
		{
			_keyFocus->internalKeyTyped(code);
		}
	}
}

void App::internalKeyReleased(KeyCode code,SurfaceBase* surfaceBase)
{
	if((code < 0)||(code >= KEY_LAST))
	{
		return;
	}

	//set key state
	_keyReleased[code]=1;
	_keyDown[code]=0;

	if(!_buildMode)
	{
		if(_keyFocus!=null)
		{
			_keyFocus->internalKeyReleased(code);
		}
	}
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
	if((panel!=null)&&(panel!=_keyFocus))
	{
		return false;
	}

	return _keyPressed[code];
}

bool App::isKeyDown(KeyCode code,Panel* panel)
{
	if((panel!=null)&&(panel!=_keyFocus))
	{
		return false;
	}

	return _keyDown[code];
}

bool App::wasKeyTyped(KeyCode code,Panel* panel)
{
	if((panel!=null)&&(panel!=_keyFocus))
	{
		return false;
	}

	return _keyTyped[code];
}

bool App::wasKeyReleased(KeyCode code,Panel* panel)
{
	if((panel!=null)&&(panel!=_keyFocus))
	{
		return false;
	}

	return _keyReleased[code];
}

void App::addTickSignal(TickSignal* s)
{
	_tickSignalDar.putElement(s);
}

void App::internalTick()
{
	int i;

	if(getTimeMillis()<_nextTickMillis)
	{
		return;
	}
	platTick();

	int cursorX,cursorY;
	getCursorPos(cursorX,cursorY);

	bool mouseOverAnySurface=false;
	for(i=0;i<_surfaceBaseDar.getCount();i++)
	{
		updateMouseFocus(cursorX,cursorY,_surfaceBaseDar[i]);

		if(_surfaceBaseDar[i]->isWithin(cursorX,cursorY))
		{
			mouseOverAnySurface=true;
		}

		_surfaceBaseDar[i]->setEmulatedCursorPos(cursorX,cursorY);
	}
	if(!mouseOverAnySurface)
	{
		setMouseFocus(null);
	}

	if(_mouseFocus!=null)
	{
		_mouseFocus->internalSetCursor();
	}

	for(i=0;i<_tickSignalDar.getCount();i++)
	{
		_tickSignalDar[i]->ticked();
	}

	if(_keyFocus!=null)
	{
		_keyFocus->internalKeyFocusTicked();
	}

	//clear mouse and key states
	for(i=0;i<MOUSE_LAST;i++)
	{
		_mousePressed[i]=false;
		_mouseDoublePressed[i]=false;
		_mouseReleased[i]=false;
	}
	for(i=0;i<KEY_LAST;i++)
	{
		_keyPressed[i]=false;
		_keyTyped[i]=false;
		_keyReleased[i]=false;
	}

	for(i=0;i<_surfaceBaseDar.getCount();i++)
	{
		if(_surfaceBaseDar[i]->hasFocus())
		{
			break;
		}
	}
	if(i==_surfaceBaseDar.getCount())
	{
		_wantedKeyFocus=null;
	}

	if(_keyFocus!=_wantedKeyFocus)
	{
		if(_keyFocus!=null)
		{
			_keyFocus->internalFocusChanged(true);
			_keyFocus->repaint();
		}
		if(_wantedKeyFocus!=null)
		{
			_wantedKeyFocus->internalFocusChanged(false);
			_wantedKeyFocus->repaint();
		}
	}

	_keyFocus=_wantedKeyFocus;
	_buildMode=_wantedBuildMode;

	for(i=0;i<_surfaceBaseDar.getCount();i++)
	{
		_surfaceBaseDar[i]->getPanel()->solveTraverse();
		_surfaceBaseDar[i]->applyChanges();
	}

	if(_mouseArenaPanel!=null)
	{
		SurfaceBase* sur=_mouseArenaPanel->getSurfaceBase();
		if(sur!=null)
		{
			int x,y,extents[4];
			sur->getPanel()->getPos(x,y);
			_mouseArenaPanel->getAbsExtents(extents[0],extents[1],extents[2],extents[3]);
			internalSetMouseArena(x+extents[0],y+extents[1],x+extents[2],y+extents[3],true);
		}
	}

	_nextTickMillis=getTimeMillis()+_minimumTickMillisInterval;
}

void App::setMouseCapture(Panel* panel)
{
	if(panel==null)
	{
		if(_mouseCapture!=null)
		{
			_mouseCapture->_surfaceBase->enableMouseCapture(false);
		}
	}
	else
	{
		panel->_surfaceBase->enableMouseCapture(true);
	}

	_mouseCapture = panel;
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
	if(scheme!=null)
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
	if(shifted)
	{
		return staticKeyTrans[code][1];
	}
	else
	{
		return staticKeyTrans[code][0];
	}
}

void App::getKeyCodeText(KeyCode code,char* buf,int buflen)
{
	if (!buf)
		return;

	// copy text into buf up to buflen in length
	// skip 2 in staticKeyTrans because the first two are for getKeyCodeChar
	for (int i = 0; i < buflen; i++)
	{
		char ch = staticKeyTrans[code][i+2];
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
	_tickSignalDar.removeAll();
	Font_Reset();
	setScheme(new Scheme());
}

void App::setMouseArena(Panel* panel)
{
	_mouseArenaPanel=panel;
}

void App::setMouseArena(int x0,int y0,int x1,int y1,bool enabled)
{
	setMouseArena(0);
	internalSetMouseArena(x0,y0,x1,y1,enabled);
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

void App::setMouseFocus(Panel* newMouseFocus)
{
	if(_mouseFocus!=newMouseFocus)
	{
		_oldMouseFocus=_mouseFocus;
		_mouseFocus=newMouseFocus;

		if(_oldMouseFocus!=null)
		{
			_oldMouseFocus->internalCursorExited();
		}

		if(_mouseFocus!=null)
		{
			_mouseFocus->internalCursorEntered();
		}
	}
}
