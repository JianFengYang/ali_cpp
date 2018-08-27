 ///
 /// @file    Noncopyable.h
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-05-25 11:01:49
 ///
#ifndef _NONCOPYABLE_H
#define _NONCOPYABLE_H
namespace wd
{
class Noncopyable
{
protected:
	Noncopyable(){}
	~Noncopyable(){}

private:
	Noncopyable(const)
}
}
