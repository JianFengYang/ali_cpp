 ///
 /// @file    InetAddress.h
 /// @author  yjf(yjfhacker@gmail.com)
 /// @date    2018-05-16 19:39:46
 ///


#ifndef _WD_INETADDRESS_H
#define _WD_INETADDRESS_H


#include <netinet/in.h>
#include <string>

namespace wd
{
class InetAddress
{
public:
	InetAddress(short port);
	InetAddress(const char *pIp,short port);
	InetAddress(const struct sockaddr_in &addr);

	const struct sockaddr_in* getSockAddrPtr() const;
	std::string ip() const;
	unsigned short port() const;

private:
	struct sockaddr_in _addr;
};
}

#endif
