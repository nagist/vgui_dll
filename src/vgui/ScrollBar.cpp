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

#include<VGUI_ScrollBar.h>
#include<VGUI_Slider.h>
#include<VGUI_IntChangeSignal.h>
#include<VGUI_Button.h>
#include<VGUI_ActionSignal.h>

using namespace vgui;


namespace
{
class FooDefaultScrollBarIntChangeSignal : public IntChangeSignal
{
public:
	FooDefaultScrollBarIntChangeSignal(ScrollBar* scrollBar)
	{
		_scrollBar=scrollBar;
	}
	virtual void intChanged(int value,Panel* panel)
	{
		_scrollBar->fireIntChangeSignal();
	}
protected:
	ScrollBar* _scrollBar;
};

class FooDefaultButtonSignal : public ActionSignal
{
public:
	ScrollBar* _scrollBar;
	int        _buttonIndex;
public:
	FooDefaultButtonSignal(ScrollBar* scrollBar,int buttonIndex)
	{
		_scrollBar=scrollBar;
		_buttonIndex=buttonIndex;
	}
public:
	virtual void actionPerformed(Panel* panel)
	{
		_scrollBar->doButtonPressed(_buttonIndex);
	}
};

}

ScrollBar::ScrollBar(int x,int y,int wide,int tall,bool vertical) : Panel(x,y,wide,tall)
{
	_slider=null;
	_button[0]=null;
	_button[1]=null;
	
	if(vertical)
	{
		setSlider(new Slider(0,wide-1,wide,(tall-(wide*2))+2,true));
		setButton(new Button("",0,0,wide,wide),0);
		setButton(new Button("",0,tall-wide,wide,wide),1);
	}
	else
	{
		// untested code
		setSlider(new Slider(tall,0,wide-(tall*2),tall,false));
		setButton(new Button("",0,0,tall+1,tall+1),0);
		setButton(new Button("",wide-tall,0,tall+1,tall+1),1);
	}

	setPaintBorderEnabled(true);
	setPaintBackgroundEnabled(true);
	setPaintEnabled(true);
	setButtonPressedScrollValue(15);

	validate();
 }

void ScrollBar::setSize(int wide,int tall)
{
	Panel::setSize(wide,tall);

	if(_slider==null)
	{
		return;
	}

	if(_button[0]==null)
	{
		return;
	}

	if(_button[1]==null)
	{
		return;
	}

	getPaintSize(wide,tall);

	if(_slider->isVertical())
	{
		_slider->setBounds(0,wide,wide,tall-(wide*2));
		//_slider->setBounds(0,0,wide,tall);
		_button[0]->setBounds(0,0,wide,wide);
		_button[1]->setBounds(0,tall-wide,wide,wide);
	}
	else
	{
		_slider->setBounds(tall,0,wide-(tall*2),tall);
		//_slider->setBounds(0,0,wide,tall);
		_button[0]->setBounds(0,0,tall,tall);
		_button[1]->setBounds((wide-tall),0,tall,tall);
	}
}

void ScrollBar::performLayout()
{
}

void ScrollBar::setValue(int value)
{
	_slider->setValue(value);
}

int ScrollBar::getValue()
{
	return _slider->getValue();
}

void ScrollBar::addIntChangeSignal(IntChangeSignal* s)
{
	_intChangeSignalDar.putElement(s);
	_slider->addIntChangeSignal(new FooDefaultScrollBarIntChangeSignal(this));
}

void ScrollBar::setRange(int min,int max)
{
	_slider->setRange(min,max);
}

void ScrollBar::fireIntChangeSignal()
{
	for(int i=0;i<_intChangeSignalDar.getCount();i++)
	{
		_intChangeSignalDar[i]->intChanged(_slider->getValue(),this);
	}
}

bool ScrollBar::isVertical()
{
	return _slider->isVertical();
}

bool ScrollBar::hasFullRange()
{
	return _slider->hasFullRange();
}

//LEAK: new and old slider will leak
void ScrollBar::setButton(Button* button,int index)
{
	if(_button[index]!=null)
	{
		removeChild(_button[index]);
	}
	_button[index]=button;
	addChild(_button[index]);

	_button[index]->addActionSignal(new FooDefaultButtonSignal(this,index));

	validate();

	//_button[index]->setVisible(false);
}

Button* ScrollBar::getButton(int index)
{
	return _button[index];
}

//LEAK: new and old slider will leak
void ScrollBar::setSlider(Slider *slider)
{
	if(_slider!=null)
	{
		removeChild(_slider);
	}
	_slider=slider;
	addChild(_slider);

	_slider->addIntChangeSignal(new FooDefaultScrollBarIntChangeSignal(this));

	validate();
}

Slider *ScrollBar::getSlider()
{
	return _slider;
}

void ScrollBar::doButtonPressed(int buttonIndex)
{
	if(buttonIndex==0)
	{
		_slider->setValue(_slider->getValue()-_buttonPressedScrollValue);
	}
	else
	{
		_slider->setValue(_slider->getValue()+_buttonPressedScrollValue);
	}

}

void ScrollBar::setButtonPressedScrollValue(int value)
{
	_buttonPressedScrollValue=value;
}

void ScrollBar::setRangeWindow(int rangeWindow)
{
	_slider->setRangeWindow(rangeWindow);
}

void ScrollBar::setRangeWindowEnabled(bool state)
{
	_slider->setRangeWindowEnabled(state);
}

void ScrollBar::validate()
{
	if(_slider!=null)
	{
		int buttonOffset=0;

		for(int i=0;i<2;i++)
		{
			if(_button[i]!=null)
			{
				if(_button[i]->isVisible())
				{
					if(_slider->isVertical())
					{					
						buttonOffset+=_button[i]->getTall();
					}
					else
					{
						buttonOffset+=_button[i]->getWide();
					}
				}
			}
		}

		_slider->setButtonOffset(buttonOffset);
	}

	int wide,tall;
	getSize(wide,tall);
	setSize(wide,tall);
}
