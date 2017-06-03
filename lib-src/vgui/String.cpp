//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

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
	printf("aa [%s]\n",aa);
	String bb("bb");
	printf("bb [%s]\n",bb);
	String cc("cc");
	printf("cc [%s]\n",cc);
	String dd("dd");
	printf("dd [%s]\n",dd);
	String aacc=aa+cc;
	printf("aacc [%s]\n",aacc);
	String aabb("aa");
	printf("}\n");
#endif
}
