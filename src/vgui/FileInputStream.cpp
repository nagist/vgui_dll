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

#include<VGUI_FileInputStream.h>

using namespace vgui;

FileInputStream::FileInputStream(const char* fileName,bool textMode)
{
	_fp=fopen(fileName,textMode?"rt":"rb");
}

void FileInputStream::seekStart(bool& success)
{
	if(_fp==null)
	{
		success=false;
		return;
	}

	success=(fseek(_fp,0,SEEK_SET)!=0);
}

void FileInputStream::seekRelative(int count,bool& success)
{
	if(_fp==null)
	{
		success=false;
		return;
	}

	success=(fseek(_fp,SEEK_CUR,count)!=0);
}

void FileInputStream::seekEnd(bool& success)
{
	if(_fp==null)
	{
		success=false;
		return;
	}

	success=(fseek(_fp,SEEK_END,0)!=0);
}

int FileInputStream::getAvailable(bool& success)
{
	if(_fp==null)
	{
		success=false;
		return 0;
	}

	success=false;
	return 0;
}

uchar FileInputStream::readUChar(bool& success)
{
	if(_fp==null)
	{
		success=false;
		return 0;
	}

	uchar ret;
	success=(fread(&ret,sizeof(ret),1,_fp)==1);
	return ret;
}

void FileInputStream::readUChar(uchar* buf,int count,bool& success)
{
	if(_fp==null)
	{
		success=false;
		return;
	}

	success=(fread(buf,count,1,_fp)==1);
}

void FileInputStream::close(bool& success)
{
	if(_fp==null)
	{
		success=false;
		return;
	}

	success=(fclose(_fp)==0);
}

void FileInputStream::close()
{
	bool success;
	close(success);
}
