///
/// @file    String.cc
/// @author  yjf(yjfhacker@gmail.com)
/// @date    2018-04-18 22:21:50
///

#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
using std::cout;
using std::endl;
using std::ws;
String::String():_pstr(new char[1]())
{};

String::String(const char *str)
:_pstr(new char [strlen(str)+1]())
{
	strcpy(_pstr,str);
}

String::String(const String &str)
:pstr(new char[str.size()+1])
{
	strcpy(_pstr,str.c_str());
}

String::~String()
{
	delete []_pstr;
}

String &String::operator=(const String &str)
{
	if(str==*this)//equal,return this
	{
		return *this;
	}
	delete []_pstr;//释放左操作数空间
	_pstr=new char[str.size()+1];
	strcpy(_pstr,str.c_str());
	return *this;
}

String &String::operator=(const char *str)
{
	delete []_pstr;
	_pstr=new char[strlen(str)+1]();
	strcpy(_pstr,str);
	return *this;
}

String &String::operator+=(const String &str)
{
	String _str(_pstr);
	delete []_pstr;
	_pstr=new char[_str.size()+str.size()+1]();

	strcpy(_pstr,_str.c_str());
	strcat(_pstr,str.c-str());

	return *this;
}

String &String::operator+=(const char *str)
{
	String temp(_pstr);
	delete []_pstr;
	_pstr=new char[temp.size()+strlen(str)+1]();
	strcpy(_pstr,temp.c_str());
	strcat(_pstr,str);

	return *this;
}

char &String::operator[](std::size_t i)
{
	if(i<size())
	{
		return _pstr[i];
	}else{
		exit(1)
	}
}

const char &String::operator[](std::size_t i) const
{
	if(i<size())
		return _pstr[i];
	else
		return;
}

std::size_t String::size() const
{
	return strlen(_pstr);
}

const char *String::c_str() const
{
	return _pstr;
}

bool operator==(const String &str1,const String &str2)
{
	if(0==strcmp(str1.c_str(),str2.c_str()))
	{
		return true;
	}else{
	return false;
	}
}

bool operator!=(const String &str1,const String &str2)
{
	if(0==strcmp(str1.c_str(),str2.c_str()))
	{
		return false;
	}
	return true;
}

bool operator<(const String &str1,const String &str2)
{
	if(str1.size()<str2.size())
	{
		return true;
	}
	return false;
}

bool operator>(const String &str1,const String &str2)
{
	if(str1.size()>str2.size())
	{
		return true;
	}
	return false;
}

std::ostream &operator<<(std::ostream &os,const String &s)
{
	return os<<s.c_str();
}

std::istream &operator>>(std::istream &is,String &s)
{
	s=""; 
	is>>ws;
	char c;
	while(is.get(c),!is.eof())
		s+=c;
	return is;
}

String operator+(const String &str1,const String &str2)
{
	String temp(str1);
	temp+=str2;
	return temp;
}

String operator+(const char *str1,const String &str2)
{
	String temp(str1);
	return temp+=str2;
}
