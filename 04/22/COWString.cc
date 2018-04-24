 ///
 /// @file    COWString.cc
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-04-22 18:51:59
 ///
#include<stdio.h>
#include<string.h>
#include <iostream>
using std::cout;
using std::endl;

class String
{
	class CharProxy
	{
	public:
		CharProxy(size_t idx,String &self)
		:_idx(idx)
		,_self(self)
		{}

		char &operator=(const char &ch);

		friend std::ostream &operator<<(std::ostream &os,
				const CharProxy &rhs);
	private:
		size_t _idx;
		String &_self;
		
	};

public:
	String();
	String(const char *);
	String(const String &rhs);
	String& operator=(const String &rhs);
	~String();

	const char &operator[](size_t idx) const
	{
		return _pstr[idx];

	}
	CharProxy operator[](size_t idx);

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
		return  *((int*)_pstr-1);

	}

	friend std::ostream &operator<<(std::ostream &os,
			const String &rhs);
	friend std::ostream& operator<<(std::ostream &os,
			const CharProxy &rhs);

private:
	void initRefcount()
	{
		*((int *)_pstr-1)=1;
	}

	void increaseRefcount()
	{
		++*((int *)_pstr-1);
	}

	void decreaseRefcount()
	{

		--*((int*)_pstr-1);
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

std::ostream& operator<<(std::ostream &os,const String &rhs)
{
	os<<rhs._pstr;
	return os;
}

std::ostream& operator<<(std::ostream &os,
		const String::CharProxy &rhs)
{
	os<<rhs._self._pstr[rhs._idx];
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
	cout<<"String(const char*)"<<endl;
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

String::CharProxy String::operator[](size_t idx)
{
	return CharProxy(idx,*this);
}

char& String::CharProxy::operator=(const char &ch)
{
	if(_self.refcount()>1)
	{
		_self.decreaseRefcount();
		char *ptmp=new char[_self.size()+5]();
		strcpy(ptmp+4,_self._pstr);
		_self._pstr=ptmp+4;
		_self.initRefcount();
	}

	_self._pstr[_idx]=ch;
	return _self._pstr[_idx];
}

int main(void)
{

	cout << "sizeof(size_t) = " << sizeof(size_t) << endl;
#if 0
	String s1;
	String s2(s1);
	cout << "s1 = " << s1 << endl;
	cout << "s2 = " << s2 << endl;
	cout << "s1' refcount = " << s1.refcount() << endl;
	cout << "s2' refcount = " << s2.refcount() << endl;
	cout << endl;
#endif

	String s3("hello,world");
	String s4(s3);
	cout << "s3 = " << s3 << endl;
	cout << "s4 = " << s4 << endl;
	cout << "s3' refcount = " << s3.refcount() << endl;
	cout << "s4' refcount = " << s4.refcount() << endl;
	printf("s3' addr = %p\n", s3.c_str());
	printf("s4' addr = %p\n", s4.c_str());

	String s5("wangdao");
	cout << "s5 = " << s5 << endl;
	cout << endl << "ִ��s5 = s3 " << endl;
	s5 = s3;
	cout << "s3' refcount = " << s3.refcount() << endl;
	cout << "s4' refcount = " << s4.refcount() << endl;
	cout << "s5' refcount = " << s5.refcount() << endl;
	cout << "s3 = " << s3 << endl;
	cout << "s4 = " << s4 << endl;
	cout << "s5 = " << s5 << endl;
	printf("s3' addr = %p\n", s3.c_str());
	printf("s4' addr = %p\n", s4.c_str());
	printf("s5' addr = %p\n", s5.c_str());

	//s3 = s5;
	s5[0] = 'X';
	cout << endl << "ִ��д���� s5[0]=��X�� ֮��:" << endl;
	cout << "s3' refcount = " << s3.refcount() << endl;
	cout << "s4' refcount = " << s4.refcount() << endl;
	cout << "s5' refcount = " << s5.refcount() << endl;
	cout << "s3 = " << s3 << endl;
	cout << "s4 = " << s4 << endl;
	cout << "s5 = " << s5 << endl;
	printf("s3' addr = %p\n", s3.c_str());
	printf("s4' addr = %p\n", s4.c_str());
	printf("s5' addr = %p\n", s5.c_str());

	cout << endl <<"ִ�ж�����s4[0] = " << s4[0] << endl;
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
