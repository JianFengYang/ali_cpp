 ///
 /// @file    InetAddress.h
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-05-09 20:29:37
 ///


#ifndef __WD_INETADDRESS_H__
#define __WD_INETADDRESS_H__

#include<netinet/in.h>
#include<string>

namespace wd
{


class InetAddress
{
public:
	explicit
	InetAddress(short port);

	InetAddress(const char *pIp,short port);

	explicit
	InetAddress(const struct sockaddr_in &addr);

	const struct sockaddr_in* getSockAddrPtr() const;

	std::string ip() const;
	unsigned short port() const;

private:
	struct sockaddr_in addr_;
};
}

#endif
