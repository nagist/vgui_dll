//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

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
