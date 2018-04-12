#include<iostream>
#include<string.h>
using std::cout;
using std::endl;

class String
{
public:
	String()
	:_pstr(new char[10]())
	{
		strcpy(_pstr,"yjf");
		cout<<"String()"<<endl;
	}
	
	String(const char *pstr)
	:_pstr(new char[strlen(pstr)+1]())
	{
		strcpy(_pstr,pstr);
		cout<<"String(const char *pstr)"<<endl;
	}
	
	String(const String & rhs)
	:_pstr(new char[strlen(rhs._pstr)+1]())
	{
		strcpy(_pstr,rhs._pstr);
		cout<<"String(const String&)"<<endl;
	}
	
	String & operator=(const String & rhs)
	{
		cout<<"String & operator=(const String &)"
		<<endl;
		
		if(this!=&rhs)
		{
			delete []_pstr;
			_pstr=new char[strlen(rhs._pstr)+1]();
			strcpy(_pstr,rhs._pstr);
			
		}
		return *this;
	}
	
	~String()
	{
		delete []_pstr;
		cout<<"~String()"<<endl;
	}

	void print()
	{
		cout<<"string:"<<_pstr<<endl;
	}

private:
	char * _pstr;
};

int main(void)
{
	String str1;
	str1.print();
	
	String str2 = "Hello,world";
	String str3("wangdao");
	
	str2.print();		
	str3.print();	
	
	String str4 = str3;
	str4.print();
	
	str4 = str2;
	str4.print();
	
	return 0;
}
