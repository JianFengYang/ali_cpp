 ///
 /// @file    heapClass.cc
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-04-18 15:58:45
 ///
#include <stdlib.h>
#include<string.h>
#include <iostream>
using std::cout;
using std::endl;

class Student
{
public:
	Student(int id,const char *name)
	:_id(id)
	,_name(new char[strlen(name)+1]())
	{
		strcpy(_name,name);
		cout<<"Student(int ,const char *)"<<endl;
	}

	void print() const
	{
		cout<<"id:"<<_id<<endl;
		cout<<"name:"<<_name<<endl;
	}

	void destroy()
	{
		delete this;
	}
private:
	//创建stack对象时，要求构造函数和析构函数都是public
	~Student()
	{
		cout<<"~Student()"<<endl;
		delete []_name;
	}

	int _id;
	char *_name;
};

int main(void)
{
	Student *pstu=new Student(100,"yjf");
	pstu->print();
	pstu->destroy();

	return 0;
}
