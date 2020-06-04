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

#include<VGUI_RadioButton.h>

using namespace vgui;

namespace
{
class FooRadioImage : public Image
{
public:
	FooRadioImage(RadioButton* radioButton) : Image()
	{
		_radioButton=radioButton;
		setSize(20,20);
	}
public:
	virtual void paint()
	{
		drawSetTextFont(Scheme::sf_secondary1);
		drawSetTextColor(Scheme::sc_white);
		drawPrintChar(0,0,'n');
		drawSetTextColor(Scheme::sc_secondary2);
		drawPrintChar(0,0,'j');
		drawSetTextColor(Scheme::sc_white);
		drawPrintChar(0,0,'k');
		drawSetTextColor(Scheme::sc_black);
		drawPrintChar(0,0,'l');
		drawSetTextColor(Scheme::sc_secondary3);
		drawPrintChar(0,0,'m');
		if(_radioButton->isSelected())
		{
			drawSetTextColor(Scheme::sc_black);
			drawPrintChar(0,0,'h');
		}
	}
protected:
	RadioButton* _radioButton;
};

}

RadioButton::RadioButton(const char* text,int x,int y,int wide,int tall) : ToggleButton(text,x,y,wide,tall)
{
	setTextAlignment(Label::a_east);
	setImage(new FooRadioImage(this));
}

RadioButton::RadioButton(const char* text,int x,int y) : ToggleButton(text,x,y)
{
	setTextAlignment(Label::a_east);
	setImage(new FooRadioImage(this));

	int wide,tall;
	getContentSize(wide,tall);
	setSize(wide,tall);
}

void RadioButton::paintBackground()
{
	int wide,tall;
	getPaintSize(wide,tall);

	drawSetColor(Scheme::sc_secondary3);
	drawFilledRect(0,0,wide,tall);
}
