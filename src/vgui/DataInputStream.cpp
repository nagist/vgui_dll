/*
 * BSD 3-Clause License
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include<VGUI_DataInputStream.h>

using namespace vgui;

DataInputStream::DataInputStream(InputStream* is)
{
	_is=is;
}

void DataInputStream::seekStart(bool& success)
{
	if(_is==null)
	{
		success=false;
		return;
	}

	_is->seekStart(success);
}

void DataInputStream::seekRelative(int count,bool& success)
{
	if(_is==null)
	{
		success=false;
		return;
	}

	_is->seekRelative(count,success);
}

void DataInputStream::seekEnd(bool& success)
{
	if(_is==null)
	{
		success=false;
		return;
	}

	_is->seekEnd(success);
}

int DataInputStream::getAvailable(bool& success)
{
	if(_is==null)
	{
		success=false;
		return 0;
	}

	return _is->getAvailable(success);
}

void DataInputStream::readUChar(uchar* buf,int count,bool& success)
{
	if(_is==null)
	{
		success=false;
		return;
	}

	_is->readUChar(buf,count,success);
}

void DataInputStream::close(bool& success)
{
	if(_is==null)
	{
		success=false;
		return;
	}

	_is->close(success);
}

void DataInputStream::close()
{
	bool success;
	_is->close(success);
}

bool DataInputStream::readBool(bool& success)
{
	if(_is==null)
	{
		success=false;
		return false;
	}

	return _is->readUChar(success)!=0;
}

char DataInputStream::readChar(bool& success)
{
	if(_is==null)
	{
		success=false;
		return 0;
	}

	return _is->readUChar(success);
}

uchar DataInputStream::readUChar(bool& success)
{
	if(_is==null)
	{
		success=false;
		return 0;
	}

	return _is->readUChar(success);
}

short DataInputStream::readShort(bool& success)
{
	if(_is==null)
	{
		success=false;
		return 0;
	}

	short ret;
	_is->readUChar((uchar*)&ret,sizeof(ret),success);
	return ret;
}

ushort DataInputStream::readUShort(bool& success)
{
	if(_is==null)
	{
		success=false;
		return 0;
	}

	ushort ret;
	_is->readUChar((uchar*)&ret,sizeof(ret),success);
	return ret;
}

int DataInputStream::readInt(bool& success)
{
	if(_is==null)
	{
		success=false;
		return 0;
	}

	int ret;
	_is->readUChar((uchar*)&ret,sizeof(ret),success);
	return ret;
}

uint DataInputStream::readUInt(bool& success)
{
	if(_is==null)
	{
		success=false;
		return 0;
	}

	uint ret;
	_is->readUChar((uchar*)&ret,sizeof(ret),success);
	return ret;
}

long DataInputStream::readLong(bool& success)
{
	if(_is==null)
	{
		success=false;
		return 0;
	}

	long ret;
	_is->readUChar((uchar*)&ret,sizeof(ret),success);
	return ret;
}

ulong DataInputStream::readULong(bool& success)
{
	if(_is==null)
	{
		success=false;
		return 0;
	}

	ulong ret;
	_is->readUChar((uchar*)&ret,sizeof(ret),success);
	return ret;
}

float DataInputStream::readFloat(bool& success)
{
	if(_is==null)
	{
		success=false;
		return 0;
	}

	float ret;
	_is->readUChar((uchar*)&ret,sizeof(ret),success);
	return ret;
}

double DataInputStream::readDouble(bool& success)
{
	if(_is==null)
	{
		success=false;
		return 0;
	}

	double ret;
	_is->readUChar((uchar*)&ret,sizeof(ret),success);
	return ret;
}

void DataInputStream::readLine(char* buf,int bufLen,bool& success)
{
	if(_is==null)
	{
		success=false;
		return;
	}

	_is->readUChar((uchar*)buf,bufLen,success);
}
