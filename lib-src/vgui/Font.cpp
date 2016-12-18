//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include "VGUI.h"
#include "VGUI_Font.h"

using namespace vgui;

Font::Font(const char* name,int tall,int wide,float rotation,int weight,bool italic,bool underline,bool strikeout,bool symbol)
{
}

Font::Font(const char* name,void *pFileData,int fileDataLen, int tall,int wide,float rotation,int weight,bool italic,bool underline,bool strikeout,bool symbol)
{
}

void Font::init(const char* name,void *pFileData,int fileDataLen, int tall,int wide,float rotation,int weight,bool italic,bool underline,bool strikeout,bool symbol)
{
}

BaseFontPlat* Font::getPlat()
{
	return null;
}

void Font::getCharRGBA(int ch,int rgbaX,int rgbaY,int rgbaWide,int rgbaTall,uchar* rgba)
{
}

void Font::getCharABCwide(int ch,int& a,int& b,int& c)
{
}

void Font::getTextSize(const char* text,int& wide,int& tall)
{
}

int Font::getTall()
{
	return 0;
}

#ifndef _WIN32
int Font::getWide()
{
	return 0;
}
#endif

int Font::getId()
{
	return 0;
}
