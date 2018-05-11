 ///
 /// @file    testThreadpool.cc
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-05-11 13:10:01
 ///


#include "Threadpool.h"

#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
using std::cout;
using std::endl;
using namespace wd;

class MyTask
{
public:
	void process()
	{
		::srand(::clock());
		int number=::rand()%100;
		cout<<">>>produce a number="<<number<<endl;

		::sleep(2);
	}
};

int main(void)
{
	Threadpool threadpool(5,10);
	Threadpool.start();
	unique_ptr<MyTask> ptask(new MyTask());

	int cnt=20;
	while(cnt--)
	{
		count<<">>>cnt="<<cnt<<endl;

		threadpool.addTask([](){
			::srand(::clock());
			int number = ::rand() % 100;
			cout << ">>> produce a number = "
			<< number << endl;
								});
	}
	threadpool.stop();
	return 0;

}
