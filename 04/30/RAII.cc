 ///
 /// @file    RAII.cc
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-04-30 15:37:08
 ///
 
#include <iostream>
using std::cout;
using std::endl;

template< typename T>
class RAII
{
public:
	explicit
	RAII(T *pointer)
	:_pointer(pointer)
	{}

	T* operator->()
	{
		return _pointer;
	}

	T& operator*()
	{
		return *_pointer;
	}

	T* get()
	{
		return _pointer;
	}

	~RAII()
	{
		if(_pointer)
		{
			delete _pointer;
			cout<<"~RAII()"<<endl;
		}
	}

	RAII(const RAII &rhs)=delete;
	RAII& operator=(const RAII &rhs)=delete;

private:
	T *_pointer;

};

class Point
{
public: 
	Point(int ix=0,int iy=0)
	:_ix(ix)
	,_iy(iy)
	{
		cout<<"Point(int,int)"<<endl;
	}

	void display() const
	{
		cout<<"("<<_ix
			<<","<<_iy
			<<")"<<endl;
	}
	

	~Point()
	{
		cout<<"~Point()"<<endl;
	}

	friend std::ostream & operator<<(std::ostream &os,
			const Point &rhs);
private:
	int _ix;
	int _iy;
};

std::ostream & operator<<(std::ostream &os,const Point &rhs)
{
	os<<"("<<rhs._ix
	  <<","<<rhs._iy
	  <<")";

	return os;
}
