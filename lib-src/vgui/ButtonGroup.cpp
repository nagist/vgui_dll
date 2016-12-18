//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include "VGUI.h"
#include "VGUI_ButtonGroup.h"
#include "VGUI_Button.h"

using namespace vgui;

void ButtonGroup::addButton(Button* button)
{
	for(int i=0;i<_buttonDar.getCount();i++)
	{
		if(_buttonDar[i]==button)
			return;
	}
	_buttonDar.addElement(button);
}

void ButtonGroup::setSelected(Button* button)
{
	for(int i=0;i<_buttonDar.getCount();i++)
	{
		if(_buttonDar[i]==button)
			continue;
		_buttonDar[i]->setSelectedDirect(false);
	}
	button->setSelectedDirect(true);
}
