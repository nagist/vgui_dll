//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include "VGUI.h"
#include "VGUI_DataInputStream.h"

using namespace vgui;

DataInputStream::DataInputStream(InputStream* is)
{
	_is=is;
}

void DataInputStream::seekStart(bool& success)
{
	if(_is)
		return _is->seekStart(success);
	success=false;
}

void DataInputStream::seekRelative(int count,bool& success)
{
	if(_is)
		return _is->seekRelative(count,success);
	success=false;
}

void DataInputStream::seekEnd(bool& success)
{
	if(_is)
		return _is->seekEnd(success);
	success=false;
}

int DataInputStream::getAvailable(bool& success)
{
	if(_is)
		return _is->getAvailable(success);
	success=false;
	return 0;
}

/*uchar DataInputStream::readUChar(bool& success)
{
	if(_is)
		return _is->readUChar(success);
	success=false;
	return 0;
}*/

void DataInputStream::readUChar(uchar* buf,int count,bool& success)
{
	if(_is)
		return _is->readUChar(buf,count,success);
	success=false;
}

void DataInputStream::close(bool& success)
{
	if(_is)
		return _is->close(success);
	success=false;
}

void DataInputStream::close()
{
	bool success;
	_is->close(success);
}

bool DataInputStream::readBool(bool& success)
{
	if(_is)
		return _is->readUChar(success)!=0;
	success=false;
	return false;
}

char DataInputStream::readChar(bool& success)
{
	if(_is)
		return _is->readUChar(success);
	success=false;
	return 0;
}

uchar DataInputStream::readUChar(bool& success)
{
	if(_is)
		return _is->readUChar(success);
	success=false;
	return 0;
}

short DataInputStream::readShort(bool& success)
{
	if(_is)
	{
		short ret;
		_is->readUChar((uchar*)&ret,sizeof(ret),success);
		return ret;
	}
	success=false;
	return 0;
}

ushort DataInputStream::readUShort(bool& success)
{
	if(_is)
	{
		ushort ret;
		_is->readUChar((uchar*)&ret,sizeof(ret),success);
		return ret;
	}
	success=false;
	return 0;
}

int DataInputStream::readInt(bool& success)
{
	if(_is)
	{
		int ret;
		_is->readUChar((uchar*)&ret,sizeof(ret),success);
		return ret;
	}
	success=false;
	return 0;
}

uint DataInputStream::readUInt(bool& success)
{
	if(_is)
	{
		uint ret;
		_is->readUChar((uchar*)&ret,sizeof(ret),success);
		return ret;
	}
	success=false;
	return 0;
}

long DataInputStream::readLong(bool& success)
{
	if(_is)
	{
		long ret;
		_is->readUChar((uchar*)&ret,sizeof(ret),success);
		return ret;
	}
	success=false;
	return 0;
}

ulong DataInputStream::readULong(bool& success)
{
	if(_is)
	{
		ulong ret;
		_is->readUChar((uchar*)&ret,sizeof(ret),success);
		return ret;
	}
	success=false;
	return 0;
}

float DataInputStream::readFloat(bool& success)
{
	if(_is)
	{
		float ret;
		_is->readUChar((uchar*)&ret,sizeof(ret),success);
		return ret;
	}
	success=false;
	return 0;
}

double DataInputStream::readDouble(bool& success)
{
	if(_is)
	{
		double ret;
		_is->readUChar((uchar*)&ret,sizeof(ret),success);
		return ret;
	}
	success=false;
	return 0;
}

void DataInputStream::readLine(char* buf,int bufLen,bool& success)
{
	if(_is)
		return _is->readUChar((uchar*)buf,bufLen,success);
	success=false;
}
