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

#include<VGUI_Slider.h>
#include<VGUI_InputSignal.h>
#include<VGUI_App.h>
#include<VGUI_IntChangeSignal.h>
#include<VGUI_MouseCode.h>

using namespace vgui;

namespace
{
class FooDefaultSliderSignal : public InputSignal
{
private:
	Slider* _slider;
public:
	FooDefaultSliderSignal(Slider* slider)
	{
		_slider=slider;
	}
public:
	void cursorMoved(int x,int y,Panel* panel)
	{
		_slider->privateCursorMoved(x,y,panel);
	}
	void cursorEntered(Panel* panel){}
	void cursorExited(Panel* panel){}
	void mouseDoublePressed(MouseCode code,Panel* panel){}
	void mousePressed(MouseCode code,Panel* panel)
	{
		_slider->privateMousePressed(code,panel);
	}
	void mouseReleased(MouseCode code,Panel* panel)
	{
		_slider->privateMouseReleased(code,panel);
	}
	void mouseWheeled(int delta,Panel* panel){}
	void keyPressed(KeyCode code,Panel* panel){}
	void keyTyped(KeyCode code,Panel* panel){}
	void keyReleased(KeyCode code,Panel* panel){}
	void keyFocusTicked(Panel* panel){}
};
}

Slider::Slider(int x,int y,int wide,int tall,bool vertical) : Panel(x,y,wide,tall)
{
	_vertical=vertical;	
	_dragging=false;
	_value=0;
	_range[0]=0;
	_range[1]=299;
	_rangeWindow=0;
	_rangeWindowEnabled=false;
	_buttonOffset=0;
	recomputeNobPosFromValue();
	addInputSignal(new FooDefaultSliderSignal(this));
}

void Slider::setSize(int wide,int tall)
{
	Panel::setSize(wide,tall);
	recomputeNobPosFromValue();
}

bool Slider::isVertical()
{
	return _vertical;
}

void Slider::setValue(int value)
{
	int oldValue=_value;

	if(value<_range[0])
	{
		value=_range[0];
	}

	if(value>_range[1])
	{
		value=_range[1];
	}
	
	_value=value;
	recomputeNobPosFromValue();

	if(_value!=oldValue)
	{
		fireIntChangeSignal();
	}
}

int Slider::getValue()
{
	return _value;
}

void Slider::recomputeNobPosFromValue()
{
	int wide,tall;

	getPaintSize(wide,tall);

	float fwide=(float)wide;
	float ftall=(float)tall;
	float frange=(float)(_range[1]-_range[0]);
	float fvalue=(float)(_value-_range[0]);
	float fper=fvalue/frange;
	float frangewindow=(float)(_rangeWindow);
	
	if(frangewindow<0)
	{
		frangewindow=0;
	}

	if(!_rangeWindowEnabled)
	{
		frangewindow=frange;
	}

	if ( frangewindow > 0 )
	{
		if(_vertical)
		{
			float fnobsize=ftall/frangewindow*ftall;
			float freepixels = ftall - fnobsize;

			float firstpixel = freepixels * fper;

			_nobPos[0]=(int)( firstpixel );
			_nobPos[1]=(int)( firstpixel + fnobsize );

			if(_nobPos[1]>tall)
			{
				_nobPos[0]=tall-((int)fnobsize);
				_nobPos[1]=tall;
			}
		}
		else
		{
			float fnobsize=fwide/frangewindow*fwide;
			float freepixels = fwide - fnobsize;

			float firstpixel = freepixels * fper;

			_nobPos[0]=(int)( firstpixel );
			_nobPos[1]=(int)( firstpixel + fnobsize );

			if(_nobPos[1]>wide)
			{
				_nobPos[0]=wide-((int)fnobsize);
				_nobPos[1]=wide;
			}
		}
	}
	
	repaint();
}

void Slider::recomputeValueFromNobPos()
{
	int wide,tall;
	getPaintSize(wide,tall);

	float fwide=(float)wide;
	float ftall=(float)tall;
	float frange=(float)(_range[1]-_range[0]);
	float fvalue=(float)(_value-_range[0]);
	float fnob=(float)_nobPos[0];
	float frangewindow=(float)(_rangeWindow);

	if(frangewindow<0)
	{
		frangewindow=0;
	}

	if(!_rangeWindowEnabled)
	{
		frangewindow=frange;
	}

	if ( frangewindow > 0 )
	{
		float fnobsize;

		if(_vertical)
		{
			fnobsize=ftall/frangewindow*ftall;
			fvalue=frange*(fnob/(ftall-fnobsize));
		}
		else
		{
			fnobsize=fwide/frangewindow*fwide;
			fvalue=frange*(fnob/(fwide-fnobsize));
		}
	}
	// Take care of rounding issues.
	_value=(int)(fvalue+_range[0]+0.5);

	// Clamp final result
	_value = ( _value < _range[1] ) ? _value : _range[1];
}

bool Slider::hasFullRange()
{
	int wide,tall;
	getPaintSize(wide,tall);

	float fwide=(float)wide;
	float ftall=(float)tall;
	float frange=(float)(_range[1]-_range[0]);
	float frangewindow=(float)(_rangeWindow);

	if(frangewindow<0)
	{
		frangewindow=0;
	}

	if(!_rangeWindowEnabled)
	{
		frangewindow=frange;
	}

	if ( frangewindow > 0 )
	{
		if(_vertical)
		{
			if( frangewindow <= ( ftall + _buttonOffset ) )
			{
				return true;
			}
		}
		else
		{
			if( frangewindow <= ( fwide + _buttonOffset ) )
			{
				return true;
			}
		}
	}

	return false;
}
	
void Slider::addIntChangeSignal(IntChangeSignal* s)
{
	_intChangeSignalDar.putElement(s);
}

void Slider::fireIntChangeSignal()
{	
	for(int i=0;i<_intChangeSignalDar.getCount();i++)
	{
		_intChangeSignalDar[i]->intChanged(getValue(),this);
	}
}

void Slider::paintBackground()
{
	int wide,tall;
	getPaintSize(wide,tall);

	if (_vertical)
	{
		drawSetColor(Scheme::sc_secondary1);
		drawFilledRect(0,0,wide,1);           // top
		drawFilledRect(0,tall-1,wide,tall);   // bottom
		drawFilledRect(0,1,1,tall-1);         // left
		drawFilledRect(wide-1,1,wide,tall-1); // right

		drawSetColor(Scheme::sc_secondary2);
		drawFilledRect(1,1,wide-1,2);
		drawFilledRect(1,2,3,tall-1);
		drawFilledRect(2,_nobPos[1],wide-1,_nobPos[1]+1);

		drawSetColor(Scheme::sc_secondary3);
		drawFilledRect(2,2,wide-1,tall-1);

		drawSetColor(Scheme::sc_primary1);
		drawFilledRect(0,_nobPos[0],wide,_nobPos[0]+1);      // top
		drawFilledRect(0,_nobPos[1],wide,_nobPos[1]+1);      // bottom
		drawFilledRect(0,_nobPos[0]+1,1,_nobPos[1]);         // left
		drawFilledRect(wide-1,_nobPos[0]+1,wide,_nobPos[1]); // right

		drawSetColor(Scheme::sc_primary3);
		drawFilledRect(1,_nobPos[0]+1,wide-1,_nobPos[0]+2);
		drawFilledRect(1,_nobPos[0]+2,2,_nobPos[1]);

		drawSetColor(Scheme::sc_primary2);
		drawFilledRect(2,_nobPos[0]+2,wide-1,_nobPos[1]);
	}
	else
	{
		//!! doesn't work

		drawSetColor(Scheme::sc_secondary3);
		drawFilledRect(0,0,wide,tall);

		drawSetColor(Scheme::sc_black);
		drawOutlinedRect(0,0,wide,tall);

		drawSetColor(Scheme::sc_primary2);
		drawFilledRect(_nobPos[0],0,_nobPos[1],tall);
		
		drawSetColor(Scheme::sc_black);
		drawOutlinedRect(_nobPos[0],0,_nobPos[1],tall);
	}
}

void Slider::setRange(int min,int max)
{
	if(max<min)
	{
		max=min;
	}

	if(min>max)
	{
		min=max;
	}

	_range[0]=min;
	_range[1]=max;
}

void Slider::getRange(int& min,int& max)
{
	min=_range[0];
	max=_range[1];
}

void Slider::privateCursorMoved(int x,int y,Panel* panel)
{
	if(!_dragging)
	{
		return;
	}

	getApp()->getCursorPos(x,y);
	screenToLocal(x,y);

	int wide,tall;
	getPaintSize(wide,tall);

	if(_vertical)
	{
		_nobPos[0]=_nobDragStartPos[0]+(y-_dragStartPos[1]);
		_nobPos[1]=_nobDragStartPos[1]+(y-_dragStartPos[1]);

		if(_nobPos[1]>tall)
		{
			_nobPos[0]=tall-(_nobPos[1]-_nobPos[0]);
			_nobPos[1]=tall;
		}
		
		if(_nobPos[0]<0)
		{
			_nobPos[1]=_nobPos[1]-_nobPos[0];
			_nobPos[0]=0;
		}
	}
	else
	{
		_nobPos[0]=_nobDragStartPos[0]+(x-_dragStartPos[0]);
		_nobPos[1]=_nobDragStartPos[1]+(x-_dragStartPos[0]);

		if(_nobPos[1]>wide)
		{
			_nobPos[0]=wide-(_nobPos[1]-_nobPos[0]);
			_nobPos[1]=wide;
		}
		
		if(_nobPos[0]<0)
		{
			_nobPos[1]=_nobPos[1]-_nobPos[0];
			_nobPos[0]=0;
		}
	}

	recomputeValueFromNobPos();
	repaint();
	fireIntChangeSignal();
}

void Slider::privateMousePressed(MouseCode code,Panel* panel)
{
	int x,y;
	getApp()->getCursorPos(x,y);
	screenToLocal(x,y);

	if(_vertical)
	{
		if((y>=_nobPos[0])&&(y<_nobPos[1]))
		{
			_dragging=true;
			getApp()->setMouseCapture(this);
			_nobDragStartPos[0]=_nobPos[0];
			_nobDragStartPos[1]=_nobPos[1];
			_dragStartPos[0]=x;
			_dragStartPos[1]=y;
		}
	}
	else
	{
		if((x>=_nobPos[0])&&(x<_nobPos[1]))
		{
			_dragging=true;
			getApp()->setMouseCapture(this);
			_nobDragStartPos[0]=_nobPos[0];
			_nobDragStartPos[1]=_nobPos[1];
			_dragStartPos[0]=x;
			_dragStartPos[1]=y;
		}
	}

}

void Slider::privateMouseReleased(MouseCode code,Panel* panel)
{
	_dragging=false;
	getApp()->setMouseCapture(null);
}

void Slider::getNobPos(int& min, int& max)
{
	min=_nobPos[0];
	max=_nobPos[1];
}

void Slider::setRangeWindow(int rangeWindow)
{
	_rangeWindow=rangeWindow;
}

void Slider::setRangeWindowEnabled(bool state)
{
	_rangeWindowEnabled=state;
}

void Slider::setButtonOffset(int buttonOffset)
{
	_buttonOffset=buttonOffset;
}