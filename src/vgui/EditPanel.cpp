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
#include<stdarg.h>
#include<VGUI_EditPanel.h>
#include<VGUI_InputSignal.h>
#include<VGUI_App.h>
#include<VGUI_Font.h>

using namespace vgui;

namespace
{
class FooDefaultEditPanelSignal : public InputSignal
{
public:
	FooDefaultEditPanelSignal(EditPanel* editPanel)
	{
		_editPanel=editPanel;
	}
public:
	virtual void cursorMoved(int x,int y,Panel* panel)
	{
	}
	virtual void cursorEntered(Panel* panel)
	{
	}
	virtual void cursorExited(Panel* panel)
	{
	}
	virtual void mousePressed(MouseCode code,Panel* panel)
	{
		_editPanel->requestFocus();
		_editPanel->repaint();
	}
	virtual void mouseDoublePressed(MouseCode code,Panel* panel)
	{
	}
	virtual void mouseReleased(MouseCode code,Panel* panel)
	{
	}
	virtual void mouseWheeled(int delta,Panel* panel)
	{
	}
	virtual void keyPressed(KeyCode code,Panel* panel)
	{
	}
	virtual void keyTyped(KeyCode code,Panel* panel)
	{
		bool shift=(_editPanel->isKeyDown(KEY_LSHIFT)||_editPanel->isKeyDown(KEY_RSHIFT));

		switch(code)
		{
			case KEY_UP:
			{
				_editPanel->doCursorUp();
				break;
			}
			case KEY_DOWN:
			{
				_editPanel->doCursorDown();
				break;
			}
			case KEY_LEFT:
			{
				_editPanel->doCursorLeft();
				break;
			}
			case KEY_RIGHT:
			{
				_editPanel->doCursorRight();
				break;
			}
			case KEY_HOME:
			{
				_editPanel->doCursorToStartOfLine();
				break;
			}
			case KEY_END:
			{
				_editPanel->doCursorToEndOfLine();
				break;
			}
			case KEY_BACKSPACE:
			{
				_editPanel->doCursorBackspace();
				break;
			}
			case KEY_DELETE:
			{
				_editPanel->doCursorDelete();
				break;
			}
			case KEY_ENTER:
			{
				_editPanel->doCursorNewLine();
				break;
			}
			default:
			{
				_editPanel->doCursorInsertChar(_editPanel->getApp()->getKeyCodeChar(code,shift));
				break;
			}
			case KEY_LSHIFT:
			case KEY_RSHIFT:
			case KEY_LALT:
			case KEY_RALT:
			case KEY_LCONTROL:
			case KEY_RCONTROL:
			{
				break;
			}
		}
	}
	virtual void keyReleased(KeyCode code,Panel* panel)
	{
	}
	virtual void keyFocusTicked(Panel* panel)
	{
		bool blink;
		int nextBlinkTime;
		_editPanel->getCursorBlink(blink,nextBlinkTime);

		int time=_editPanel->getApp()->getTimeMillis();
		if(time>nextBlinkTime)
		{
			_editPanel->setCursorBlink(!blink);
		}
	}
private:
	EditPanel* _editPanel;
};
}

EditPanel::EditPanel(int x,int y,int wide,int tall) : Panel(x,y,wide,tall)
{
	_cursor[0]=0;
	_cursor[1]=0;
	_font=null;
	setCursorBlink(true);
	addInputSignal(new FooDefaultEditPanelSignal(this));
	getLine(0);
}

void EditPanel::paintBackground()
{
	int wide,tall;
	getPaintSize(wide,tall);

	drawSetColor(Scheme::sc_white);
	drawFilledRect(0,0,wide,tall);
}

void EditPanel::addLine()
{
}

Dar<char>* EditPanel::getLine(int lineIndex)
{
	if(lineIndex<0)
	{
		return null;
	}

	if((lineIndex==0)&&(_lineDarDar.getCount()==0))
	{
		Dar<char>* lineDar=new Dar<char>;
		_lineDarDar.addElement(lineDar);
		return lineDar;
	}

	if(lineIndex>=_lineDarDar.getCount())
	{
		return null;
	}

	return _lineDarDar[lineIndex];
}

void EditPanel::getText(int lineIndex, int offset,char* buf,int bufLen)
{
	if((lineIndex>=0)&&(lineIndex<_lineDarDar.getCount()))
	{
		Dar<char>* dataStr=_lineDarDar[lineIndex];

		int j=0;
		for(int i=offset;i<dataStr->getCount()&&(j<bufLen-1);i++,j++)
		{
			buf[i-offset]=(*dataStr)[i];
		}
		buf[j]=0;
	}
}

void EditPanel::setChar(Dar<char>* lineDar,int x,char ch,char fill)
{
	if((lineDar==null)||(x<0))
	{
		return;
	}

	int count=lineDar->getCount();
	if(x>=count)
	{
		lineDar->ensureCapacity(x+1);
		lineDar->setCount(x+1);
		for(int i=count;i<x;i++)
		{
			lineDar->setElementAt(fill,i);
		}
	}
	lineDar->setElementAt(ch,x);
}

void EditPanel::setChar(Dar<char>* lineDar,int x,char ch)
{
	setChar(lineDar,x,ch,' ');
}

int EditPanel::getLineCount()
{
	return _lineDarDar.getCount();
}

int EditPanel::getVisibleLineCount()
{
	int wide,tall;
	getPaintSize(wide,tall);

	Font* font=_font;
	if(font==null)
	{
		font=getApp()->getScheme()->getFont(Scheme::sf_primary1);
	}

	return tall/font->getTall();
}

void EditPanel::setCursorBlink(bool state)
{
	_cursorBlink=state;
	_cursorNextBlinkTime=getApp()->getTimeMillis()+400;
	repaint();
}

void EditPanel::getCursorBlink(bool& blink,int& nextBlinkTime)
{
	blink=_cursorBlink;
	nextBlinkTime=_cursorNextBlinkTime;
}

void EditPanel::shiftLineLeft(Dar<char>* lineDar,int x,int count)
{
	if((x<0)||(x>lineDar->getCount()))
	{
		return;
	}

	if(count<0)
	{
		return;
	}

	for(int i=x;i<lineDar->getCount();i++)
	{
		int xx=x-count;
		if(xx>=0)
		{
			setChar(lineDar,xx,(*lineDar)[i]);
		}
	}
	lineDar->setCount(lineDar->getCount()-count);
}

void EditPanel::shiftLineRight(Dar<char>* lineDar,int x,int count)
{
	if(x<0)
	{
		return;
	}

	if(count<0)
	{
		return;
	}

	for(int i=lineDar->getCount()-1;i>=x;i--)
	{
		setChar(lineDar,i-count,(*lineDar)[i]);
	}
}

int EditPanel::spatialCharOffsetBetweenTwoLines(Dar<char>* srcDar,Dar<char>* dstDar,int x)
{
	if((srcDar==null)||(dstDar==null))
	{
		return x;
	}

	Font* font=_font;
	if(font==null)
	{
		font=getApp()->getScheme()->getFont(Scheme::sf_primary1);
	}

	int i;

	int x0=0;
	for(i=0;i<x;i++)
	{
		char ch=' ';
		if(i<srcDar->getCount())
		{
			ch=(*srcDar)[i];
		}

		int a,b,c;
		font->getCharABCwide(ch,a,b,c);
		x0+=a+b+c;
	}

	int x1=0;
	for(i=0;;i++)
	{
		char ch=' ';
		if(i<dstDar->getCount())
		{
			ch=(*dstDar)[i];
		}

		int a,b,c;
		font->getCharABCwide(ch,a,b,c);

		int mid=x1+(a+b+c)/2;
		if (x1>x0)
		{
			if(mid>x0)
			{
			}
			else if (x1+(a+b+c)>x0)
			{
				return i+1;
			}
		}
		else
		{
			if(mid>x0)
			{
				return i;
			}
			else if(x1+(a+b+c)>x0)
			{
				return i+1;
			}
		}
		x1+=a+b+c;
	}

}

void EditPanel::paint()
{
	Font* font=_font;
	if(font==null)
	{
		font=getApp()->getScheme()->getFont(Scheme::sf_primary1);
	}

	drawSetTextFont(font);
	drawSetTextColor(Scheme::sc_black);

	int yy=0;
	for(int j=0;j<_lineDarDar.getCount();j++)
	{
		int cx=0;
		int xx=0;
		Dar<char>* lineDar=_lineDarDar[j];
		for(int i=0;i<lineDar->getCount();i++)
		{
			char ch=(*lineDar)[i];
			drawPrintChar(xx,yy,ch);

			if((_cursor[0]==i)&&(_cursor[1]==j))
			{
				cx=xx;
			}

			int a,b,c;
			font->getCharABCwide(ch,a,b,c);
			xx+=a+b+c;
		}

		if((_cursor[1]==j)&&_cursorBlink)
		{
			if(_cursor[0]>=lineDar->getCount())
			{
				int a,b,c;
				font->getCharABCwide(' ',a,b,c);
				cx=xx+(_cursor[0]-lineDar->getCount())*(a+b+c);
			}
			drawSetColor(255,0,0,0);
			drawFilledRect(cx-1,yy,cx+1,yy+font->getTall());
		}
		yy+=font->getTall();
	}
}

void EditPanel::doCursorUp()
{
	_cursor[0]=spatialCharOffsetBetweenTwoLines(getLine(_cursor[1]),getLine(_cursor[1]-1),_cursor[0]);
	_cursor[1]--;

	if(_cursor[1]<0)
	{
		_cursor[1]=0;
	}

	setCursorBlink(true);
	repaint();
}

void EditPanel::doCursorDown()
{
	int lCount=getVisibleLineCount();
	_cursor[0]=spatialCharOffsetBetweenTwoLines(getLine(_cursor[1]),getLine(_cursor[1]+1),_cursor[0]);

	if(lCount>getLineCount())
	{
		lCount=getLineCount();
	}

	if(_cursor[1]+1>=lCount)
	{
		return;
	}

	_cursor[1]++;
	setCursorBlink(true);
	repaint();
}

void EditPanel::doCursorLeft()
{
	_cursor[0]--;

	if(_cursor[0]<0)
	{
		_cursor[0]=0;
	}

	setCursorBlink(true);
	repaint();
}

void EditPanel::doCursorRight()
{
	_cursor[0]++;
	setCursorBlink(true);
	repaint();
}

void EditPanel::doCursorToStartOfLine()
{
	_cursor[0]=0;
	setCursorBlink(true);
	repaint();
}

void EditPanel::doCursorToEndOfLine()
{
	Dar<char>* lineDar=getLine(_cursor[1]);
	if(lineDar==null)
	{
		return;
	}
	_cursor[0]=lineDar->getCount();
	setCursorBlink(true);
	repaint();
}

void EditPanel::doCursorInsertChar(char ch)
{
	Dar<char>* lineDar=getLine(_cursor[1]);
	if(lineDar==null)
	{
		return;
	}
	shiftLineRight(lineDar,_cursor[0],1);
	setChar(lineDar,_cursor[0],ch);
	doCursorRight();
	repaint();
}

void EditPanel::doCursorBackspace()
{
	Dar<char>* lineDar=getLine(_cursor[1]);
	if(lineDar==null)
	{
		return;
	}

	if(_cursor[0]==0)
	{
		Dar<char>* prevLineDar=getLine(_cursor[1]-1);
		if(prevLineDar==null)
		{
			return;
		}

		int len=prevLineDar->getCount();
		for(int i=0;i<lineDar->getCount();i++)
		{
			setChar(prevLineDar,len+i,(*lineDar)[i]);
		}

		if(_cursor[1]>=0)
		{
			_lineDarDar.removeElementAt(_cursor[1]);
			doCursorUp();
			_cursor[0]=prevLineDar->getCount();
		}
		repaint();
	}
	else
	{
		shiftLineLeft(lineDar,_cursor[0],1);
		doCursorLeft();
		repaint();
	}
}

void EditPanel::doCursorNewLine()
{
	Dar<char>* lineDar=getLine(_cursor[1]);
	if(lineDar==null)
	{
		return;
	}

	Dar<char>* newLineDar=new Dar<char>;
	_lineDarDar.insertElementAt(newLineDar,_cursor[1]+1);

	for(int i=_cursor[0];i<lineDar->getCount();i++)
	{
		setChar(newLineDar,i-_cursor[0],(*lineDar)[i]);
	}
	lineDar->setCount(_cursor[0]);

	_cursor[0]=0;
	doCursorDown();
	repaint();
}

void EditPanel::doCursorDelete()
{
	Dar<char>* lineDar=getLine(_cursor[1]);
	if(lineDar==null)
	{
		return;
	}

	doCursorRight();
	shiftLineRight(lineDar,_cursor[0],1);
	doCursorLeft();
	repaint();
}

void EditPanel::doCursorPrintf(char* format,...)
{
	va_list argList;
	va_start(argList,format);
	char    buf[8192];
	vsprintf(buf,format,argList);
	va_end(argList);

	for(int i=0;i<sizeof(buf);i++)
	{
		if(buf[i]==0)
		{
			break;
		}
		if(buf[i]=='\n')
		{
			doCursorNewLine();
			continue;
		}
		doCursorInsertChar(buf[i]);
	}

	repaint();
}

void EditPanel::setFont(Font* font)
{
	_font=font;
	repaint();
}
