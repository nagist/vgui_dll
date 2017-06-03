//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include<math.h>
#include<VGUI_ProgressBar.h>

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

	const int segmentGap=2;
	int segmentWide=wide/_segmentCount-segmentGap;

	const float rr=0;
	const float gg=0;
	const float bb=100;

	int x=0;

	int litSeg=(int)floor(_progress);
	for(int i=litSeg;i>0;i--)
	{
		drawSetColor((int)rr,(int)gg,(int)bb,0);
		drawFilledRect(x,0,x+segmentWide,tall);
		x+=segmentWide+segmentGap;
	}
	
	if(_segmentCount>_progress)
	{
		float frac=_progress-(float)floor(_progress);
		float r=0;
		float g=255-(frac*155);
		float b=0;

		drawSetColor((int)r,(int)g,(int)b,0);
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
