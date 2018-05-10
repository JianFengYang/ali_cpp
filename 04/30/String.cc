 ///
 /// @file    String.cc
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-05-01 09:01:58
 ///
#include<string.h>
#include<vector>
#include <iostream>
using std::cout;
using std::endl;
using std::vector;

class String
{
public:
	String():_pstr(new char[1]())
	{
		cout<<"String()"<<endl;
	}

	String(const char *pstr)
	:_pstr(new char[strlen(pstr)+1]())
	{
		strcpy(_pstr,pstr);
		cout<<"String(const char *)"<<endl;
	}

	String(const String &rhs)
	:_pstr(new char[strlen(rhs._pstr+1)]())
	{
		strcpy(_pstr,rhs._pstr);
		cout<<"String(const String &)"<<endl;

	String(String &&rhs)
	:_pstr(rhs._pstr)
	{
		ths._pstr=NULL;
		cout<<"String(String&&)"<<endl;
	}

	String& operator=(const String &rhs)
	{
		cout<<"String & operator=(const String&)"<<endl;

		if(this!=&rhs)
		{
			delete []_pstr;
			_pstr=new char[strlen(rhs._pstr)+1]();
			strcpy(_pstr,rhs._pstr);
		}

		return *this;
	}

	String &operator=(String &&rhs)
	{
		cout<<"String &operator=(String &&)"<<endl;

		if(this!=&rhs)
		{
			delete []_pstr;
			_pstr=rhs._pstr;
			rhs._pstr=NULL
		}

		return *this;
	}

	~String()
	{
		delete []_pstr;
		cout<<"~String()"<<endl
	}

	friend std::ostream& operator<<(std::ostream &os,
			const String &rhs);

private:
	char *_pstr;
};
	
std::ostream& operator<<(std::ostream &os,const String &rhs)
{
	os<<rhs._pstr;
	return os;
}

String&& getString()
{
	return String("hello");
}

int main(v)

