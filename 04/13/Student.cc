 ///
 /// @file    Student.cc
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-04-13 13:28:43
 ///
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <iostream>
using std::cout;
using std::endl;

class Student
{
public:
	Student(double id,const char *name)
	:_id(id)
	,_name(new char[strlen(name)+1]())
	{
		strcpy(_name,name);
		cout<<"Student(int,const char *)"<<endl;
	}

	void print() const
	{
		cout<<"id:"<<_id<<endl;
		cout<<"name:"<<_name<<endl;
	}

	void *operator new(size_t sz)
	{
		cout<<"void *operator new(size_t sz)"<<endl;
		void *ret=malloc(sz);
		return ret;
	}

	void operator delete(void *ret)
	{
		cout<<"void operator delete(void *)"<<endl;
		free(ret);
	}

	~Student()
	{
		cout<<"~Student()"<<endl;
		delete []_name;
	}

private:
	double _id;
	char *_name;
};

int main(void)
{
	cout<<"sizeof(Student=)"<<sizeof(Student)<<endl;
	Student *pstu=new Student(1001,"Jack");
	pstu->print();

	delete pstu;
	return 0;
}
