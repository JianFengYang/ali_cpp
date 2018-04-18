///
/// @file    20180412_杨剑锋.cc
/// @author  yjf(yjfhacker@gmail.com)
/// @date    2018-04-14 23:33:57
///
#include <iostream>

using std::cout;
using std::endl;
class Stack
{
	public:
		Stack(int top=0)
			:_top(top)
		{
			cout<<"Stack()"<<endl;
		}

		void push(int x)
		{
			if(!full())
			{
				_stack[_top]=x;
				_top++;
				cout<<"push success"<<endl;
			}else{
				cout<<"full"<<endl;
			}
		}

		void pop()
		{
			if(!emty())
			{	_top--;
				cout<<"pop success"<<endl;
			}else
				cout<<"empty"<<endl;
		}

		int top()
		{
			return _stack[_top];
		}
		bool emty()
		{
			if(_top==0)
				return true;
			else
				return false;
		}
		bool full()
		{
			if(_top==10)
				return true;
			else
				return false;
		}

		~Stack()
		{
			
		}

	private:
		int _top;
		int _stack[10];
};

int main(void)
{
	Stack stack;
	cout<<"empty:"<<stack.emty()<<endl;
	stack.push(10);
	cout<<"empty:"<<stack.emty()<<endl;
	
	stack.push(12);
	stack.push(14);
	cout<<"top:"<<stack.top()<<endl;
	stack.pop();
	cout<<"top:"<<stack.top()<<endl;



	return 0;

}
