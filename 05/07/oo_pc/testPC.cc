 ///
 /// @file    testPC.cc
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-05-07 22:51:49
 ///
#include"Thread.h"
#include"TaskQueue.h"
#include<unistd.h>
#include<stdlib.h>
#include<time.h>

#include <iostream>
#include<memory>
using std::cout;
using std::endl;
using std::unique_ptr;

using namespace wd;

class Producer
:public Thread
{
public:
	Producer(TaskQueue &taskQue)
	:_taskQue(taskQue)
	{}
private:
	void run()
	{
		srand(clock());
		int cnt=20;
		while(cnt--)
		{
			int number=rand()%100;
			_taskQue.push(number);
			cout<<">>>Producer a number="<<number<<endl;
			sleep(1);
		}
	}
private:
	TaskQueue &_taskQue;
};

class Consumer
:public Thread
{
public:
	Consumer(TaskQueue &taskQue)
	:_taskQue(taskQue)
	{}
private:
	void run()
	{
		int cnt=20;
		while(cnt--)
		{
			int number=_taskQue.pop();
			cout<<">>>consume a number="<<number<<endl;
			sleep(2);
		}
	}
private:
	TaskQueue &_taskQue;
};

int main(void)
{
	TaskQueue taskQueue(10);
	unique_ptr<Thread> producer(new Producer(taskQueue));
	unique_ptr<Thread> consumer(new Consumer(taskQueue));

	producer->start();
	consumer->start();

	producer->join();
	consumer->join();

	return 0;

}
