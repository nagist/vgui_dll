//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include "vfontdata.h"

VFontData::VFontData()
{
	m_BitmapCharWidth = m_BitmapCharHeight = 0;
	m_pBitmap = NULL;
}

VFontData::~VFontData()
{
	if (m_pBitmap)
		delete [] m_pBitmap;
}

bool LoadVFontDataFrom32BitTGA(FileImageStream *fp, VFontData *pData)
{
	FileImage fileImage;

	unsigned char *pInLine, *pOutLine;
	int i, x, y;
	int rightX;

	if (!Load32BitTGA(fp, &fileImage))
		return false;

	pData->m_pBitmap = new unsigned char [fileImage.m_Width*fileImage.m_Height];
	if (pData->m_pBitmap)
	{
		pData->m_BitmapCharWidth = fileImage.m_Width/256;
		pData->m_BitmapCharHeight = fileImage.m_Height;

		for (i = 0; i < 256; i++)
		{
			rightX = 0;
			pInLine = &fileImage.m_pData[i*pData->m_BitmapCharWidth*4];
			pOutLine = &pData->m_pBitmap[i*pData->m_BitmapCharWidth];

			for (y = 0; y < pData->m_BitmapCharHeight; y++)
			{
				for (x = 0; x < pData->m_BitmapCharWidth; x++)
				{
					if (pInLine[x*4+0] != 0 || pInLine[x*4+1] != 0 || pInLine[x*4 +2] != 0 || pInLine[x*4+2] != 0)
					{
						pOutLine[x] = 1;
						if (x > rightX)
							rightX = x;
					}
					else
						pOutLine[x] = 0;
				}
				pInLine += 256*pData->m_BitmapCharWidth*4;
				pOutLine += 256*pData->m_BitmapCharWidth;
			}
			pData->m_CharWidths[i] = (i == 32) ? pData->m_BitmapCharWidth/4 : rightX;
		}
	}

	return true;
}
