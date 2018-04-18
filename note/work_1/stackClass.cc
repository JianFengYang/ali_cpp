 ///
 /// @file    stackClass.cc
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-04-18 15:12:10
 ///
#include<string.h>
#include <iostream>
using std::cout;
using std::endl;

class Student
{
public:
	Student(int  id,const char *name)
	:_id(id)
	,_name(new char[strlen(name)+1]())
	{
		strcpy(_name,name);
		cout<<"Student(int,const char *)"<<endl;
	}

	void print() const
	{
		cout<<"id:"<<_id<<endl
			<<"name:"<<_name<<endl;
	}

	~Student()
	{
		cout<<"~Student()"<<endl;
		delete []_name;
	}
private:
	int  _id;
	char *_name;

	void *operator new(size_t sz);
	void operator delete(void *ret);
};

int main(void)
{
	Student stu(100,"yjf");
	stu.print();
	return 0;
}

