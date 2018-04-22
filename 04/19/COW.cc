///
/// @file    COW.cc
/// @author  yjf(yjfhacker@gmail.com)
/// @date    2018-04-21 14:28:20
///
#include<stdio.h>
#include<string.h>

#include <iostream>
using std::cout;
using std::endl;

class String
{
	public:
		String();
		String(const char *);
		String(const String &rhs);
		String &operator=(const String &rhs);
		~String();

		const char &operator[](size_t idx) const
		{
			return _pstr[idx];
		}
		char &operator[](size_t idx);

		size_t size()
		{
			return strlen(_pstr);
		}

		const char *c_str() const
		{
			return _pstr;
		}

		size_t refcount() const
		{
			return *((int*)(_pstr-4));

		}

		friend std::ostream &operator<<(std::ostream &os,
				const String &rhs);
	private:
		void initRefcount()
		{
			*((int*)(_pstr-4))=1;
		}

		void increaseRefcount()
		{
			++*((int*)(_pstr-4));
		}

		void decreaseRefcount()
		{
			--*((int *)(_pstr-4));
		}

		void release()
		{
			decreaseRefcount();
			if(refcount()==0)
			{
				delete [](_pstr-4);
				cout<<"release data"<<endl;
			}
		}

	private:
		char *_pstr;

};

std::ostream &operator<<(std::ostream &os,const String &rhs)
{

	os<<rhs._pstr;
	return os;
}

String::String()
	:_pstr(new char[5]())
{
	cout<<"String()"<<endl;
	_pstr+=4;
	initRefcount();
}

String::String(const char *pstr)
	:_pstr(new char[strlen(pstr)+5]())
{
	cout<<"String(const char *)"<<endl;
	_pstr+=4;
	initRefcount();
	strcpy(_pstr,pstr);
}

String::String(const String &rhs)
	:_pstr(rhs._pstr)
{
	increaseRefcount();
}

String& String::operator=(const String &rhs)
{
	if(this!=&rhs)
	{
		release();
		_pstr=rhs._pstr;
		increaseRefcount();
	}
	return *this;
}

String::~String()
{
	release();
	cout<<"~String()"<<endl;
}

char& String::operator[](size_t idx)
{
	if(refcount()>1)
	{
		decreaseRefcount();
		char *ptmp=new char[size()+5]();
		strcpy(ptmp+4,_pstr);
		_pstr=ptmp+4;
		initRefcount();
	}

	return _pstr[idx];
}

int main()
{
	String s3("hello,world");
	String s4(s3);
	cout<<"s3="<<s3<<endl;
	cout<<"s4="<<s4<<endl;

	cout<<"s3 refcount="<<s3.refcount()<<endl;
	cout<<"s4 refcount="<<s4.refcount()<<endl;

	printf("s3 addr=%p\n",s3.c_str());
	printf("s4 addr=%p\n",s4.c_str());

	String s5("wangdao");
	cout<<"s5="<<s5<<endl;
	cout<<endl<<"-s5=s3-"<<endl;
	s5=s3;
	cout<<"s3 refcount="<<s3.refcount()<<endl;
	cout<<"s4 refcount="<<s4.refcount()<<endl;
	cout<<"s5 refcount="<<s5.refcount()<<endl;

	cout << "s3 = " << s3 << endl;
	cout << "s4 = " << s4 << endl;
	cout << "s5 = " << s5 << endl;
	printf("s3' addr = %p\n", s3.c_str());
	printf("s4' addr = %p\n", s4.c_str());
	printf("s5' addr = %p\n", s5.c_str());

	s5[0] = 'X';
	cout << endl << "执行写操作 s5[0]=‘X’ 之后:" << endl;
	cout << "s3' refcount = " << s3.refcount() << endl;
	cout << "s4' refcount = " << s4.refcount() << endl;
	cout << "s5' refcount = " << s5.refcount() << endl;
	cout << "s3 = " << s3 << endl;
	cout << "s4 = " << s4 << endl;
	cout << "s5 = " << s5 << endl;
	printf("s3' addr = %p\n", s3.c_str());
	printf("s4' addr = %p\n", s4.c_str());
	printf("s5' addr = %p\n", s5.c_str());

	cout << endl <<"执行读操作s4[0] = " << s4[0] << endl;
	cout << "s3' refcount = " << s3.refcount() << endl;
	cout << "s4' refcount = " << s4.refcount() << endl;
	cout << "s5' refcount = " << s5.refcount() << endl;
	cout << "s3 = " << s3 << endl;
	cout << "s4 = " << s4 << endl;
	cout << "s5 = " << s5 << endl;
	printf("s3' addr = %p\n", s3.c_str());
	printf("s4' addr = %p\n", s4.c_str());
	printf("s5' addr = %p\n", s5.c_str());


	return 0;
}

