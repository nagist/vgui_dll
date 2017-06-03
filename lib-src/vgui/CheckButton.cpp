//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include<VGUI_CheckButton.h>

using namespace vgui;

namespace
{
class FooCheckImage : public Image
{
public:
	FooCheckImage(CheckButton* checkButton) : Image()
	{
		_checkButton=checkButton;
		setSize(20,20);
	}
public:
	virtual void paint()
	{
		drawSetTextFont(Scheme::sf_secondary1);
		drawSetTextColor(Scheme::sc_white);
		drawPrintChar(0,0,'g');
		drawSetTextColor(Scheme::sc_secondary2);
		drawPrintChar(0,0,'c');
		drawSetTextColor(Scheme::sc_white);
		drawPrintChar(0,0,'d');
		drawSetTextColor(Scheme::sc_black);
		drawPrintChar(0,0,'e');
		drawSetTextColor(Scheme::sc_secondary3);
		drawPrintChar(0,0,'f');
		drawSetTextColor(Scheme::sc_black);
		if(_checkButton->isSelected())
		{
			drawSetTextColor(Scheme::sc_black);
			drawPrintChar(0,0,'a');
		}
	}
protected:
	CheckButton* _checkButton;
};

}

CheckButton::CheckButton(const char* text,int x,int y,int wide,int tall) : ToggleButton(text,x,y,wide,tall)
{
	setTextAlignment(Label::a_east);
	setImage(new FooCheckImage(this));
}

CheckButton::CheckButton(const char* text,int x,int y) : ToggleButton(text,x,y)
{
	setTextAlignment(Label::a_east);
	setImage(new FooCheckImage(this));

	int wide,tall;
	getContentSize(wide,tall);
	setSize(wide,tall);
}

void CheckButton::paintBackground()
{
	int wide,tall;
	getPaintSize(wide,tall);

	drawSetColor(Scheme::sc_secondary3);
	drawFilledRect(0,0,wide,tall);
}
