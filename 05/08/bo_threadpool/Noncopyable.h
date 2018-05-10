 ///
 /// @file    Noncopyable.h
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-05-08 15:00:27
 ///
#ifndef __WD_NONCOPYABLE_H__
#define __WD_NONCOPYABLE_H__

namespace wd
{


class Noncopyable
{
protected:
	Noncopyable(){}
	~Noncopyable(){}

	Noncopyable(const Noncopyable &rhs)=delete;
	Noncopyable &operator=(const Noncopyable &)=delete;
};

#endif

}
