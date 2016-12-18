//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include "VGUI.h"
#include "VGUI_BitmapTGA.h"
#include "VGUI_DataInputStream.h"

using namespace vgui;

BitmapTGA::BitmapTGA(InputStream* is,bool invertAlpha)
{
	loadTGA(is,invertAlpha);
}

bool BitmapTGA::loadTGA(InputStream* is,bool invertAlpha)
{
	if(!is)
		return false;

	DataInputStream dis(is);
	// dummy
	return true;
}
