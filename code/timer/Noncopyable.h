 ///
 /// @file    Noncopyable.h
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-05-10 19:54:45
 ///
#ifndef __WD_NONCOPYABLE_H__
#define __WD_NONCOPYABLE_H__

namespace wd
{
class Noncopyable
{
protected:
	Noncopyale(){}
	~Noncopyable(){}
	Noncopyable(const Noncopyable &rhs)=delete;
	Noncopyable& operator=(const Noncopyable&)=delete;
};
}

#endif
