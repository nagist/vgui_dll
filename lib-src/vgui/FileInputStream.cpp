//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include "VGUI.h"
#include "VGUI_FileInputStream.h"

using namespace vgui;

FileInputStream::FileInputStream(const char* fileName,bool textMode)
{
}

void FileInputStream::seekStart(bool& success)
{
}

void FileInputStream::seekRelative(int count,bool& success)
{
}

void FileInputStream::seekEnd(bool& success)
{
}

int FileInputStream::getAvailable(bool& success)
{
	return 0;
}

uchar FileInputStream::readUChar(bool& success)
{
	return 0;
}

void FileInputStream::readUChar(uchar* buf,int count,bool& success)
{
}

void FileInputStream::close(bool& success)
{
}

void FileInputStream::close()
{
}
