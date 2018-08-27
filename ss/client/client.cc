#include "json/json.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <string>
#include <iostream>
using std::cout;
using std::endl;
using std::string;
#define ERR_EXIT(m) \
	do { \
		perror(m);\
		exit(EXIT_FAILURE);\
	}while(0)

void do_service(int sockfd);
size_t readn(int sockfd,char *buf,size_t count)
{
	size_t nleft = count;
	char * pbuf = buf;
	while(nleft > 0)
	{
		int nread = read(sockfd,pbuf,nleft);
		if( nread == -1)
		{
			if(errno == EINTR)
				continue;
			return EXIT_FAILURE;
		}else if(nread == 0 )
			break;
		pbuf += nread;
		nleft -= nread;
	}
	return (count - nleft);
}
size_t writen(int sockfd,const char *buf,size_t count)
{
	size_t nleft = count;
	const char * pbuf = buf;
	while(nleft > 0)
	{
		int nwrite = write(sockfd,pbuf,nleft);
		if(nwrite == -1)
		{
			if(errno == EINTR)
				continue;
			return EXIT_FAILURE;
		}
		nleft -= nwrite;
		pbuf += nwrite;
	}
	return (count -nleft);
}
int main(int argc, const char *argv[])
{
	if(argc !=3)
	{
		printf("./client IP Port");
		return -1;
	}
	int peerfd = socket(PF_INET, SOCK_STREAM, 0);
	if(peerfd == -1)
		ERR_EXIT("socket");

	struct sockaddr_in addr;
	memset(&addr, 0, sizeof addr);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(argv[1]);
	addr.sin_port = htons(atoi(argv[2]));
	socklen_t len = sizeof addr;
	if(connect(peerfd, (struct sockaddr*)&addr, len) == -1)
		ERR_EXIT("Connect");

	char buf[1024];
	int length;
	memset(buf, 0, sizeof(buf));
	readn(peerfd,(char*)&length,sizeof(int));
	readn(peerfd, buf, length);
	cout << buf << endl;
	do_service(peerfd);


	return 0;
}
void jsonPara(const string strData)
{
	Json::Reader reader;
	Json::Value DevsJson;
	reader.parse(strData,DevsJson);
	int siNum = DevsJson.size();
	for(int i = 0;i<siNum;++i)
	{
		Json::Value Dev = DevsJson[i];
		string Devstr = Dev.toStyledString();
		if(Devstr.c_str())
			cout << Devstr ;
	}
}


void do_service(int sockfd)
{
	char recvbuf[1024] = {0};
	char sendbuf[1024] = {0};
	while(1)
	{
		bzero(sendbuf,sizeof(sendbuf));
		read(0,sendbuf,sizeof(sendbuf)-1);
		write(sockfd,sendbuf,strlen(sendbuf));
		int len;
		bzero(recvbuf,sizeof(recvbuf));
		readn(sockfd,(char*)&len,sizeof(int));
		readn(sockfd,recvbuf,len);
		jsonPara(string(recvbuf));
	}
}




