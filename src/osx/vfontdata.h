//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#ifndef __VFONTDATA_H__
#define __VFONTDATA_H__

#include "fileimage.h"

class VFontData
{
public:
	VFontData();
	~VFontData();

public:
	int GetLineWidth();
	int m_CharWidths[256];
	int m_BitmapCharWidth;
	int m_BitmapCharHeight;
	unsigned char *m_pBitmap;
};

bool LoadVFontDataFrom32BitTGA(
	FileImageStream *fp, VFontData *pData);

#endif
