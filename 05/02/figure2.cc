 ///
 /// @file    figure2.cc
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-05-03 16:15:36
 ///
#include<functional>
#include<math.h> 
#include <iostream>
using std::cout;
using std::endl;

class Figure
{
public:
	typedef std::function<void()> DisplayCallback;
	typedef std::function<double()>AreaCallback;

	void setDisplayCallback(DisplayCallback &&cb)
	{
		_cb1=std::move(cb);
	}

	void setAreaCallback(AreaCallback &&cb)
	{
		_cb2=std::move(cb);
	}

	void handleDisplayCallback()
	{
		if(_cb1)
			cb1();
	}

	double handleAreaCallback()
	{	
		if(_cb2)
			return _cb2()
		else
			return 0;

	}

private:
	DisplayCallback _cb1;
	AreaCallback _cb2;
};

class Rectangle
{
public:
	Rectangle(double length,double width)
	:_length(length)
	,_width(width)
	{}

	void display()
	{
		cout<<"rectangle:";
	}

	double area()
	{
		return _length *_width;
	}

private:
	double _length;
	double _width;
};

const double PI=3.14159;

class Circle
{
public:
	Circle(double radius)
	:_radius(radius)
	{}

	void print()
	{
		cout<<"circle:"
	}

	double calArea()
	{
		return PI *_radius*_radius;
	}

private:
	double _radius;

};

class Triangle
{
public:
	Triangle(double a,double b,double c)
	:_a(a)
	,_b(b)
	,_c(c)
	{}

	void show()
	{
		cout<<"triangle:";
	}

	double statiticArea()
	{
		double p = (_a + _b + _c)/ 2;	
				return sqrt(p * (p - _a) * (p - _b) * (p - _c));
	}
private:
	double _a;
	double _b;
	double _c;
};

void printFigure(Figure &fig)
{
	fig.handleDisplayCallback();
	cout<<fig.handleAreaCallback()<<endl;
}

int main(void)
{
	Rectangle rectangle(10,11);
	Circle circle(5);
	Triangle triangle(3,4,5);

	Figure figure;
	figure.setDisplayCallback(std::bind(&Rectangle::display,
				&rectangle));
}



