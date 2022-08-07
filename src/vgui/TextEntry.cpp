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

#include<VGUI_TextEntry.h>
#include<VGUI_App.h>
#include<VGUI_ActionSignal.h>
#include<VGUI_Font.h>
#include<VGUI_FocusChangeSignal.h>

using namespace vgui;

namespace
{
class FooDefaultTextEntrySignal : public FocusChangeSignal
{
public:
	FooDefaultTextEntrySignal(TextEntry* textEntry)
	{
		_textEntry=textEntry;
	}
public:
	virtual void focusChanged(bool lost,Panel* panel)
	{
		_textEntry->resetCursorBlink();
		_textEntry->doSelectNone();
	}
protected:
	TextEntry* _textEntry;
};
}

TextEntry::TextEntry(const char* text,int x,int y,int wide,int tall) : Panel(x,y,wide,tall)
{
	_font=null;
	_hideText=false;
	_cursorPos=0;
	_cursorBlinkRate=400;
	_select[0]=-1;
	_select[1]=-1;

	resetCursorBlink();
	setText(text,strlen(text));
	doGotoEndOfLine();
	addInputSignal(this);
	addFocusChangeSignal(new FooDefaultTextEntrySignal(this));
}

void TextEntry::setText(const char* text,int textLen)
{
	_lineDar.removeAll();
	_lineDar.ensureCapacity(textLen);

	for(int i=0;i<textLen;i++)
	{
		_lineDar.addElement(text[i]);
		setCharAt(text[i],i);
	}

	doGotoEndOfLine();
}

void TextEntry::setCharAt(char ch,int index)
{
	if(index<0)
	{
		return;
	}
	_lineDar.ensureCapacity(index+1);
	_lineDar.setElementAt(ch,index);
}

void TextEntry::resetCursorBlink()
{
	_cursorBlink=false;
	_cursorNextBlinkTime=getApp()->getTimeMillis()+_cursorBlinkRate;
}

void TextEntry::setTextHidden(bool bHideText)
{
	_hideText=bHideText;
	repaint();
}

int TextEntry::cursorToPixelSpace(int cursorPos)
{
	Font* font=_font;
	if(font==null)
	{
		font=getApp()->getScheme()->getFont(Scheme::sf_primary1);
	}

	int cx=0;
	for(int i=0;i<_lineDar.getCount();i++)
	{
		if(i==cursorPos)
		{
			break;
		}

		int a,b,c;
		if(_hideText)
		{
			font->getCharABCwide('*',a,b,c);
		}
		else
		{
			font->getCharABCwide(_lineDar[i],a,b,c);
		}
		cx+=a+b+c;
	}

	return cx;
}

void TextEntry::paintBackground()
{
	Font* font=_font;
	if(font==null)
	{
		font=getApp()->getScheme()->getFont(Scheme::sf_primary1);
	}

	int fTall=font->getTall();

	int x0,x1;
	if(getSelectedPixelRange(x0,x1))
	{
		drawSetColor(Scheme::sc_white);
		drawFilledRect(0,0,x0,fTall+1);
		drawFilledRect(x1,0,_size[0],fTall+1);
		drawSetColor(0,0,200,0);
		drawFilledRect(x0,0,x1,fTall+1);
	}
	else
	{
		drawSetColor(Scheme::sc_white);
		drawFilledRect(0,0,_size[0],_size[1]);
	}

	drawSetTextFont(font);
	drawSetColor(Scheme::sc_black);
	drawSetTextPos(3,0);

	for(int i=0;i<_lineDar.getCount();i++)
	{
		if(_hideText)
		{
			drawPrintChar('*');
		}
		else
		{
			drawPrintChar(_lineDar[i]);
		}
	}

	if(hasFocus())
	{
		drawSetColor(Scheme::sc_black);
		drawFilledRect(0,0,_size[0],1);
		drawFilledRect(0,_size[1]-1,_size[0],_size[1]);
		drawFilledRect(0,1,1,_size[1]-1);
		drawFilledRect(_size[0]-1,1,_size[0],_size[1]-1);

		if(!_cursorBlink)
		{
			int cx=cursorToPixelSpace(_cursorPos);
			drawSetColor(Scheme::sc_black);
			drawFilledRect(cx+3,2,cx+4,fTall-1);
		}
	}
}

void TextEntry::cursorMoved(int x,int y,Panel* panel)
{
}

void TextEntry::cursorEntered(Panel* panel)
{
}

void TextEntry::cursorExited(Panel* panel)
{
}

void TextEntry::mousePressed(MouseCode code,Panel* panel)
{
	resetCursorBlink();
	requestFocus();
	repaint();
}

void TextEntry::mouseDoublePressed(MouseCode code,Panel* panel)
{
}

void TextEntry::mouseReleased(MouseCode code,Panel* panel)
{
}

void TextEntry::mouseWheeled(int delta,Panel* panel)
{
}

void TextEntry::keyPressed(KeyCode code,Panel* panel)
{
}

void TextEntry::keyTyped(KeyCode code,Panel* panel)
{
	bool shift=(panel->isKeyDown(KEY_LSHIFT)||panel->isKeyDown(KEY_RSHIFT));
	bool ctrl=(panel->isKeyDown(KEY_LCONTROL)||panel->isKeyDown(KEY_RCONTROL));

	if(ctrl)
	{
		switch(code)
		{
			case KEY_C:
			{
				doCopySelected();
				break;
			}
			case KEY_V:
			{
				doPaste();
				break;
			}
		}
	}
	else
	{
		char ch;
		switch(code)
		{
			case KEY_ENTER:
			case KEY_TAB:
			case KEY_LSHIFT:
			case KEY_RSHIFT:
			{
				break;
			}
			case KEY_INSERT:
			{
				if(shift)
				{
					doPaste();
				}
				break;
			}
			case KEY_DELETE:
			{
				if(shift)
				{
					doDeleteSelected();
				}
				else
				{
					doDelete();
				}
				break;
			}
			case KEY_LEFT:
			{
				doGotoLeft();
				break;
			}
			case KEY_RIGHT:
			{
				doGotoRight();
				break;
			}
			case KEY_HOME:
			{
				doGotoFirstOfLine();
				break;
			}
			case KEY_END:
			{
				doGotoEndOfLine();
				break;
			}
			case KEY_BACKSPACE:
			{
				doBackspace();
				break;
			}
			default:
			{
				ch=getApp()->getKeyCodeChar(code,(panel->isKeyDown(KEY_LSHIFT)||panel->isKeyDown(KEY_RSHIFT)));
				if(ch!=0)
				{
					doInsertChar(ch);
				}
				break;
			}
		}
	}

	_select[1]=_cursorPos;

	if(code==KEY_ENTER)
	{
		fireActionSignal();
	}
}

void TextEntry::keyReleased(KeyCode code,Panel* panel)
{
}
 
void TextEntry::keyFocusTicked(Panel* panel)
{
	int time=getApp()->getTimeMillis();
	if(time>_cursorNextBlinkTime)
	{
		_cursorBlink=!_cursorBlink;
		_cursorNextBlinkTime=time+_cursorBlinkRate;
		repaint();
	}
}

void TextEntry::selectCheck()
{
	if (!(isKeyDown(KEY_LSHIFT) || isKeyDown(KEY_RSHIFT)))
	{
		_select[0] = -1;
	}
	else if (_select[0] == -1)
	{
		_select[0] = _cursorPos;
	}
}

void TextEntry::doGotoLeft()
{
	selectCheck();
	_cursorPos--;

	if(_cursorPos<0)
	{
		_cursorPos=0;
	}

	resetCursorBlink();
	repaint();
}

void TextEntry::doGotoRight()
{
	selectCheck();
	_cursorPos++;

	if(_cursorPos>_lineDar.getCount())
	{
		_cursorPos=_lineDar.getCount();
	}

	resetCursorBlink();
	repaint();
}

void TextEntry::doGotoFirstOfLine()
{
	selectCheck();
	_cursorPos=0;

	resetCursorBlink();
	repaint();
}

void TextEntry::doGotoEndOfLine()
{
	selectCheck();
	_cursorPos=_lineDar.getCount();

	resetCursorBlink();
	repaint();
}

void TextEntry::doInsertChar(char ch)
{
	_lineDar.setCount(_lineDar.getCount()+1);
	for(int i=_lineDar.getCount()-1;i>=_cursorPos;i--)
	{
		setCharAt(_lineDar[i],i+1);
	}
	setCharAt(ch,_cursorPos);
	_cursorPos++;

	resetCursorBlink();
	repaint();
}

void TextEntry::doBackspace()
{
	if(_cursorPos==0)
	{
		return;
	}

	if(_lineDar.getCount()==0)
	{
		return;
	}

	for(int i=_cursorPos;i<_lineDar.getCount();i++)
	{
		setCharAt(_lineDar[i],i-1);
	}
	_lineDar.setCount(_lineDar.getCount()-1);
	_cursorPos--;

	resetCursorBlink();
	repaint();
}

void TextEntry::doDelete()
{
	if(_lineDar.getCount()==0)
	{
		return;
	}

	if(_cursorPos!=_lineDar.getCount())
	{
		return;
	}

	for(int i=_cursorPos+1;i<_lineDar.getCount();i++)
	{
		setCharAt(_lineDar[i],i-1);
	}
	_lineDar.setCount(_lineDar.getCount()-1);
	_cursorPos--;

	resetCursorBlink();
	repaint();
}

void TextEntry::doSelectNone()
{
	_select[0]=-1;
	repaint();
}

bool TextEntry::getSelectedRange(int& cx0,int& cx1)
{
	if(_select[0]==-1)
	{
		return false;
	}

	cx0=_select[0];
	cx1=_select[1];
	int temp;
	if(cx1<cx0){temp=cx0;cx0=cx1;cx1=temp;}

	return true;
}

bool TextEntry::getSelectedPixelRange(int& cx0,int& cx1)
{
	if(!getSelectedRange(cx0,cx1))
	{
		return false;
	}

	cx0=cursorToPixelSpace(cx0);
	cx1=cursorToPixelSpace(cx1);
	return true;
}

void TextEntry::doCopySelected()
{
	int x0,x1;
	if(getSelectedRange(x0,x1))
	{
		char buf[256];
		int i=0;
		for(;i<199;i++)
		{
			if(x0+i>=x1)
			{
				break;
			}
			buf[i]=_lineDar[x0+i];
		}
		buf[i]=0;
		getApp()->setClipboardText(buf,i);
	}
}

void TextEntry::doPaste()
{
	char buf[256];
	int c=getApp()->getClipboardText(0,buf,sizeof(buf));
	for(int i=0;i<c-1;i++)
	{
		doInsertChar(buf[i]);
	}
}

void TextEntry::doPasteSelected()
{
	doDeleteSelected();
	doPaste();
}

void TextEntry::doDeleteSelected()
{

}

void TextEntry::getText(int offset,char* buf,int bufLen)
{
	if(buf==null)
	{
		return;
	}

	for(int i=offset;i<bufLen-1;i++)
	{
		buf[i-offset]=0;
		if(i>=_lineDar.getCount())
		{
			break;
		}
		buf[i-offset]=_lineDar[i];
	}
	buf[bufLen-1]=0;
}

void TextEntry::addActionSignal(ActionSignal* s)
{
	_actionSignalDar.putElement(s);
}

void TextEntry::fireActionSignal()
{
	for(int i=0;i<_actionSignalDar.getCount();i++)
	{
		_actionSignalDar[i]->actionPerformed(this);
	}
}

void TextEntry::setFont(Font* font)
{
	_font=font;
}
