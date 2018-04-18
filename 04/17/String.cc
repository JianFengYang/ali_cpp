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
		cout<<"String()"<<endl;
	}

	String(const char *pstr)
	:_pstr(new char[strlen(pstr)+1]())
	{
		strcpy(_pstr,pstr);
		cout<<"String(const char *)"<<endl;
		cout<<_pstr<<endl;
	}

	String(const String &rhs)
	:_pstr(new char[strlen(rhs._pstr)+1]())
	{
		strcpy(_pstr,rhs._pstr);
		cout<<"String(const String &)"<<endl
		cout<<_pstr<<endl;
	}
	~String()
	{
		delete []_pstr;
		cout<<"~String()"<<endl;
	}

	String &operator=(const String &rhs)
	{
		cout<<"String &operator=(const String &)"
			<<endl;
		if(this!=&rhs)
		{
			delete []_pstr;
			_pstr=new char[strlen(rhs._pstr)+1]();
			strcpy(_pstr,rhs._pstr);
		}

		return *this;
	}
	String &operator=(const char *);

	String &operator+=(const String &);
	String &operator+=(const char *);

	char &operator[](std::size_t index);
	const char &operator[](std::size_t index) const;

	std::size_t size() const;
	const char* c_str() const;

	friend bool operator==(const String &, const String &);
	friend bool operator!=(const String &, const String &);

	friend bool operator<(const String &, const String &);
	friend bool operator>(const String &, const String &);
	friend bool operator<=(const String &, const String &);
	friend bool operator>=(const String &, const String &);

	friend std::ostream &operator<<(std::ostream &os, const String &s);
	friend std::istream &operator>>(std::istream &is, String &s);

private:
	char * _pstr;
};

String operator+(const String &, const String &);
String operator+(const String &, const char *);
String operator+(const char *, const String &);
