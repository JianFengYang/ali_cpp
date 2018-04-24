 ///
 /// @file    templateQueue.cc
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-04-23 22:34:54
 ///
#include"Mylogger.h" 
#include <iostream>
using std::cout;
using std::endl;

template <typename Type,int kSize=10>
class Queue
{
public:
	Queue();
	~Queue();

	bool empty() const;
	bool full() const;
	void push(const Type &elem);
	void pop();
	Type& front();
	const Type& front() const
	{
		return _base[_front];
	}
}
