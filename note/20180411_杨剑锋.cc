1.在内存布局分为几个区域，各自具备什么特点？

内存布局分为栈区，堆区，全局（静态区），文字常量区，程序代码区。

栈区空间由系统自动分配，堆区空间由程序员自己申请。
栈采用连续的整段内存空间，从高地址向低地址扩展。栈速度较快。空间比较小。
堆是用不连续的内存区域，系统用链表来存储空闲内存地址，由低地址向高地址拓展。堆速度比较慢，而且容易产生内存碎片。空间比较大。

全局（静态区）在读/写段。
文字常量区，程序代码区在只读段。

栈存放函数的参数值，局部变量的值。
堆由程序员申请，存放，释放。
程序代码区存放函数体（类的成员函数，全局函数）的二级制代码。

2.当定义类时，编译器会为类自动生成哪些函数？这些函数各自都有什么特点？

在定义类时，编译器会自动为类生成构造函数和析构函数。构造函数在对象创建时自动调用，用于完成对象成员变量的初始化，以及为指针成员动态申请内存空间。
析构函数，在对象撤销时自动调用，执行清理任务。
   
3.什么是浅拷贝，什么是深拷贝？

例如：复制调用函数在缺省状态时，
Class Computer;
//这种是属于浅拷贝，只传递了地址
Computer comp2(comp1)即等价于
comp2.brand=comp1.brand;
comp2.price=comp1.price; 

//这种是深拷贝，把数据全传递过去新开辟的内存空间
Computer(const Computer &cp)
{
	brand=new char[strlen(cp.brand)+1];
	strcpy(brand,cp.brand);
	price=cp.price;
}

4.实现一个自定义的String类，保证main函数正确执行
#include <iostream>
#include <string>
using std::cout;
using std::endl;

class String
{
public:
	String()
	:_pstr(new char[10]())
	{
		strcpy(_pstr,"yjf");
		cout<<"String()"<<endl;
	}
	
	String(const char *pstr)
	:_pstr(new char[strlen(pstr)+1]())
	{
		strcpy(_pstr,pstr);
		cout<<"String(const char *pstr)"<<endl;
	}
	
	String(const String & rhs)
	:_pstr(new char[strlen(rhs._pstr)+1]())
	{
		strcpy(_pstr,rhs._pstr);
		cout<<"String(const String&)"<<endl;
	}
	
	String & operator=(const String & rhs)
	{
		cout<<"String & operator=(const String &)"
		<<endl;
		
		if(this!=&rhs)
		{
			delete []_pstr;
			_pstr=new char[strlen(rhs._pstr)+1]();
			strcpy(_pstr,rhs._pstr);
			
		}
		return *this;
	}
	
	~String()
	{
		delete []_pstr;
		cout<<"~String()"<<endl;
	}

	void print()
	{
		cout<<"string:"<<_pstr<<endl;
	}

private:
	char * _pstr;
};

int main(void)
{
	String str1;
	str1.print();
	
	String str2 = "Hello,world";
	String str3("wangdao");
	
	str2.print();		
	str3.print();	
	
	String str4 = str3;
	str4.print();
	
	str4 = str2;
	str4.print();
	
	return 0;
}
