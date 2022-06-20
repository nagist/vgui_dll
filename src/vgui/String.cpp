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

#include<string.h>
#include<stdio.h>
#include<VGUI_String.h>

using namespace vgui;

String::String()
{
	_text="";
}

String::String(const char* text)
{
	int len=getCount(text);
	_text=new char[len+1];
	memcpy(_text,text,len);
	_text[len]=0;
}

String::String(const String& src)
{
	_text=src._text;
}

String::~String()
{
	_text=null;
}

int String::getCount(const char* text)
{
	int ctr;
	for(ctr=0;;ctr++)
	{
		if(text[ctr]==0)
		{
			break;
		}
	}
	return ctr;
}

int String::getCount()
{
	return getCount(_text);
}

String String::operator+(String text)
{
	int len0=getCount();
	int len1=text.getCount();

	String* newString=new String();
	newString->_text=new char[len0+len1+1];
	memcpy(newString->_text,_text,len0);
	memcpy(newString->_text+len0,text._text,len1);
	newString->_text[len0+len1]=0;

	return String(*newString);
}

String String::operator+(const char* text)
{
	int len0=getCount();
	int len1=getCount(text);

	String* newString=new String();
	newString->_text=new char[len0+len1+1];
	memcpy(newString->_text,_text,len0);
	memcpy(newString->_text+len0,text,len1);
	newString->_text[len0+len1]=0;

	return String(*newString);
}

bool String::operator==(String text)
{
	char *text2=text._text;

	int ctr;
	for(ctr=0;;ctr++)
	{
		if(_text[ctr]!=text2[ctr])
		{
			return false;
		}
		if(_text[ctr]==0)
		{
			break;
		}
	}
	return true;
}

bool String::operator==(const char* text)
{
	int ctr;
	for(ctr=0;;ctr++)
	{
		if(_text[ctr]!=text[ctr])
		{
			return false;
		}
		if(_text[ctr]==0)
		{
			break;
		}
	}
	return true;
}

char String::operator[](int index)
{
	return _text[index];
}

const char* String::getChars()
{
	return _text;
}

void String::test()
{
#ifdef _WIN32
	printf("{\n");
	String aa("aa");
	printf("aa [%s]\n",aa.getChars());
	String bb("bb");
	printf("bb [%s]\n",bb.getChars());
	String cc("cc");
	printf("cc [%s]\n",cc.getChars());
	String dd("dd");
	printf("dd [%s]\n",dd.getChars());
	String aacc=aa+cc;
	printf("aacc [%s]\n",aacc.getChars());
	String aabb("aa");
	printf("}\n");
#endif
}
