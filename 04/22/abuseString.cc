 ///
 /// @file    abuseString.cc
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-04-22 18:18:29
 ///
#include<string.h>

#include <iostream>
using std::cout;
using std::endl;

class String
{
public:
	//直接使用new char[num],不会初始化
	//使用new char[num]()，进行初始化
	String()
	:_pstr(new char[1])
	{}

	String(const char *pstr)
	:_pstr(new char[strlen(pstr)+1]())
	{
		strcpy(_pstr,pstr);
	}

	String(const String &rhs)
	:_pstr(new char[strlen(rhs._pstr)+1]())
	{
		strcpy(_pstr,rhs._pstr);
	}

	String &operator=(const String &rhs)
	{
		if(this!=&rhs)
		{
			delete []_pstr;
			_pstr=new char[strlen(rhs._pstr)+1]();
			strcpy(_pstr,rhs._pstr);
		}

		return *this;
	}

	String &operator+=(const String &rhs)
	{
		char *ptmp=new char[strlen(_pstr)+strlen(rhs._pstr)+1]();
		strcpy(ptmp,_pstr);
		strcat(ptmp,rhs._pstr);
		delete []_pstr;
		_pstr=ptmp;

		return *this;
	}

	~String()
	{
		delete []_pstr;
	}

	friend std::ostream &operator<<(std::ostream &os,
			const String &rhs);
	friend std::istream &operator>>(std::istream &is,
			String &rhs);
private:
	char *_pstr;
	
};

std::ostream &operator<<(std::ostream &os,const String &rhs)
{

	os<<rhs._pstr;
	return os;
}

std::istream &operator>>(std::istream &is,String &rhs)
{
	char buff[65535]={0};//cache
	memset(buff,0,sizeof(buff));
	is>>buff;
	if(rhs._pstr)
		delete []rhs._pstr;
	rhs._pstr=new char[strlen(buff)+1];
	strcpy(rhs._pstr,buff);
	return is;
}

String operator+(const String &lhs,const String &rhs)
{
	String tmp;
	tmp+=lhs;
	tmp+=rhs;
	return tmp;
}

int main(void)
{
	String s1;
	cout<<"s1="<<s1<<endl;

	cout<<"--------"<<endl;
	String s2("hello,world");
	cout<<"s2="<<s2<<endl;
	String s3("ffffffffffff");
	String s5=s2+s3;
	cout<<"s5="<<s5<<endl;

	return 0;
}
