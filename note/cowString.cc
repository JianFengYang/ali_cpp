///
/// @file    cowString.cc
/// @author  (664743503@qq.com)
/// @date    2018-04-19 21:28:13
///

#include <stdio.h>
#include <string.h>
#include <iostream>
using std::cout;
using std::cin;
using std::endl;


//用一个引用计数来实现写时复制
//并且operator[]能够区分读写操作


class String
{
	class CharProxy//嵌套类
	{
		public:
			CharProxy(size_t index,String & self)
				: _index(index), _self(self)
			{}

			char & operator=(const char & ch);

			friend std::ostream & operator<<(std::ostream & os,const CharProxy & rhs);
		private:
			size_t _index;
			String & _self;
	};

public:
	String();
	String(const char *);
	String(const String &);
	String & operator=(const String & rhs);
	~String();

	CharProxy operator[](size_t index);

	size_t size()
	{
		return strlen(_pstr);
	}

	const char * c_str() const
	{
		return _pstr;
	}

	size_t getReferenceCount() const//获得引用计数的值
	{
		return ((int *)(_pstr + 1))[0];
	}

	friend std::ostream & operator<<(std::ostream & os,const String & rhs);
	friend std::ostream & operator<<(std::ostream & os,const CharProxy & rhs);

private:
	void init()//初始化引用计数
	{
		((int *)_pstr)[0] = 1;//设为1
	}

	void increaseReferenceCcount()//引用计数加1
	{
		++(((int *)_pstr - 1)[0]);
	}

	void decreaseReferenceCount()//引用计数减1
	{
		--(((int *)_pstr - 1)[0]);
	}

	void release()//当引用计数减1减至0时，释放数据空间
	{
		decreaseReferenceCount();
		if(0 == getReferenceCount())
		{
			delete [] (_pstr - 4);
			cout << "release data" << endl;
		}
	}

private:
	char * _pstr;
};

//String类的友元函数---重载输出流运算符1
std::ostream & operator<<(std::ostream & os,const String & rhs)
{
	os << rhs._pstr;
	return os;
}

//String类的友元函数---重载输出流运算符2
std::ostream & operator<<(std::ostream & os,const String::CharProxy & rhs)
{
	os << rhs._self._pstr[rhs._index];
	return os;
}


//String类初始化
String::String()
	: _pstr(new char[5]())
{
	init();
	_pstr += 4;//指针到达数据
}

//String构造函数
String::String(const char * pstr)
	: _pstr(new char[strlen(pstr)+4]())
{
	init();
	_pstr += 4;
	strcpy(_pstr,pstr);
}

//String类中的复制构造函数
String::String(const String & rhs)
	: _pstr(rhs._pstr)
{
	increaseReferenceCcount();
}

//String类的析构函数
String::~String()
{
	decreaseReferenceCount();
	if(getReferenceCount() == 1)
	{
		delete [] (_pstr - 4);
		cout << "析构一小下" << endl;
	}
}

//String类中赋值运算符重载
String & String::operator=(const String & rhs)
{
	if(this != &rhs)
	{
		release();
		_pstr = rhs._pstr;
		increaseReferenceCcount();
	}
	return *this;
}

//String类中的CharProxy类中的下标运算符重载
String::CharProxy String::operator[](size_t index)
{
	return CharProxy(index,*this);
}

//String类中的CharProxy类中的赋值运算符重载
char & String::CharProxy::operator=(const char & ch)
{
	if(_self.getReferenceCount() > 1)
	{
		_self.decreaseReferenceCount();
		char * ptmp = new char[_self.size() + 5]();
		strcpy(ptmp + 4,_self._pstr);
		_self._pstr = ptmp + 4;
		_self.init();
	}
	_self._pstr[_index] = ch;
	return _self._pstr[_index];
}

int main()
{
	String s1("i am buxiude");
	String s2(s1);

	cout << "s1=" << s1 << endl;
	cout << "s2=" << s2 << endl;
	cout << "s1 ReferenceCount=" << s1.getReferenceCount() << endl;
	cout << "s2 ReferenceCount=" << s2.getReferenceCount() << endl << endl;

	String s3(s1);
	s3[0] = 'u';
	cout << "after write operation" << endl;
	cout << "s3 referencerount=" << s3.getReferenceCount() << endl;
	cout << "s3 =" << s3 << endl;
	printf("s3 addr = %p\n",s3.c_str());

	
	String s4(s1);
	cout << "after read operation" << endl;
	cout << "s4 referencerount=" << s4.getReferenceCount() << endl;
	cout << "s4 =" << s4 << endl;
	printf("s4 addr = %p\n",s4.c_str());
	

	return 0;
}

