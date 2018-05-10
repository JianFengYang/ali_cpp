 ///
 /// @file    figure.cc
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-05-03 15:35:53
 ///
#include<math.h> 
#include <iostream>
using std::cout;

using std::endl;

class Figure
{
public:
	virtual void display()=0;
	virtual double area()=0;
};

class Rectangle
:public Figure
{
public:
	Rectangle(double length,double width)
	:_length(length)
	,_width(width)
	{}

	void display()
	{
		cout<<"rectangle";
	}

	double area()
	{
		return _length*_width;
	}

private:
	double _length;
	double _width;
};

const double PI=3.14159;

class Circle
:public Figure
{
public:
	Circle(double radius)
	:_radius(radius)
	{}

	void display()
	{
		cout<<"Circle:";



	}


	double area()
	{
		return PI*_radius*_radius;
	}

private:
	double _radius;
};

class Triangle
:public Figure
{
public:
	Triangle(double a,double b,double c)
	:_a(a)
	,_b(b)
	,_c(c)
	{}

	void display()
	{
		cout<<"triangle:";
	}

	double area()
	{
		double p=(_a+_b+_c)/2;
		return sqrt(p*(p-_a)*(p-_b)*(p-_c));
	}

private:
	double _a;
	double _b;
	double _c;
};

void printFigure(Figure *fig)
{
	fig->display();
	cout<<fig->area()<<endl;
}

int main(void)
{
	Rectangle rectangle(10,11);
	Circle circle(5);
	Triangle triangle(3,4,5);
	printFigure(&rectangle);
	printFigure(&circle);
	printFigure(&triangle);

	return 0;
}
