//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include "VGUI.h"
#include "VGUI_ProgressBar.h"

using namespace vgui;

ProgressBar::ProgressBar(int segmentCount)
{
	_segmentCount=segmentCount;
	_progress=0;
}

void ProgressBar::paintBackground()
{
	int wide,tall;
	getPaintSize(wide,tall);
	drawSetColor(Scheme::sc_secondary2);
	drawFilledRect(0,0,wide,tall);

	int x=0;
	int segmentWide=wide/_segmentCount-2;
	for(int i=(int)_progress;i>=0;i--)
	{
		drawSetColor(0,0,100,0);
		drawFilledRect(x,0,x+segmentWide,tall);
		x+=segmentWide+2;
	}
	
	if(_segmentCount>_progress)
	{
		drawSetColor(0,0,255-(_progress-(int)_progress)*155,0);
		drawFilledRect(x,0,x+segmentWide,tall);
	}
}

void ProgressBar::setProgress(float progress)
{
	if(_progress!=progress)
	{
		_progress=progress;
		repaint();
	}
}

int ProgressBar::getSegmentCount()
{
	return _segmentCount;
}
