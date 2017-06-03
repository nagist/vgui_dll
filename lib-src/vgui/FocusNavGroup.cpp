//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include<VGUI_FocusNavGroup.h>
#include<VGUI_Panel.h>

using namespace vgui;

FocusNavGroup::FocusNavGroup()
{
	_currentIndex=0;
}

void FocusNavGroup::addPanel(Panel* panel)
{
	_panelDar.putElement(panel);
}

void FocusNavGroup::requestFocusPrev()
{
	if(_panelDar.getCount()==0)
	{
		return;
	}
	_currentIndex--;
	if(_currentIndex<0)
	{
		_currentIndex=_panelDar.getCount()-1;
	}
	_panelDar[_currentIndex]->requestFocus();
}

void FocusNavGroup::requestFocusNext()
{
	if(_panelDar.getCount()==0)
	{
		return;
	}
	_currentIndex++;
	if(_currentIndex>=_panelDar.getCount())
	{
		_currentIndex=0;
	}
	_panelDar[_currentIndex]->requestFocus();
}

void FocusNavGroup::setCurrentPanel(Panel* panel)
{
	for(int i=0;i<_panelDar.getCount();i++)
	{
		if(_panelDar[i]==panel)
		{
			_currentIndex=i;
			break;
		}
	}
}
