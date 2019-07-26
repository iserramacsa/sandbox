#include "udpserverbcast.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>

#ifdef DEBUG
#include <iostream>
#endif

#define BUFLEN (1024 * 5) //Max length of buffer
using namespace Macsa::Comms;

#define DEFAULT_BCAST_ADDR	"127.255.255.255"

BCastServerSocket::BCastServerSocket(std::string svr, int port)
{
	_bcastAddr = DEFAULT_BCAST_ADDR;
	if (svr.length()) {
		_bcastAddr = svr;
	}
	_port = -1;
	if (port){
		_port = port;
	}
}

BCastServerSocket::~BCastServerSocket()
{

}

bool BCastServerSocket::open()
{
	if (!_opened) {
		int soBroadcast = 1;
		if (createSocket(_fdSocket) && setSocketOption(_fdSocket, SO_BROADCAST, soBroadcast)) {
			struct sockaddr_in bcAddr;
			if (initSocket(bcAddr, _bcastAddr.c_str(), std::to_string(_port).c_str())) {
				_opened = bindSocket(_fdSocket, bcAddr);
			}
		}
	}

	return _opened;
}

bool BCastServerSocket::close()
{
	if (_opened) {
		::close(_fdSocket);
		_opened = false;
	}
	return (!_opened);
}

bool BCastServerSocket::receiveFrom(std::string& msg, std::string &addr)
{
	int len;
	char buff[BUFLEN]={0};
	struct sockaddr_in addrClient;
	socklen_t slen = sizeof (addrClient);
	//try to receive some data, this is a blocking call
	len = recvfrom(_fdSocket, buff, BUFLEN, 0, (struct sockaddr *) &addrClient, &slen);
	if (len == -1)
	{
#ifdef DEBUG
		std::cout << __func__ << " => " << strerror(errno)<< std::endl;
#endif
	}
	else {
		msg = buff;
		addr = inet_ntoa(addrClient.sin_addr);
#ifdef DEBUG
		//print details of the client/peer and the data received
		printf("Received packet from %s:%d\n", addr.c_str(), ntohs(addrClient.sin_port));
		printf("Data: %s\n" , msg.c_str());
#endif
	}

	return (len > 0);
}
/*
bool BCastServerSocket::receiveMsg(std::string& msg)
{
	int len;
	struct msghdr msgh;
	memset((char *)&msgh, 0, sizeof (msgh));
	int flags = 0;
	//try to receive some data, this is a blocking call
	len = recvmsg(_fdSocket, &msgh, flags);
	if (len == -1)
	{
#ifdef DEBUG
		std::cout << __func__ << " => " << strerror(errno)<< std::endl;
#endif
	}
	else {
#ifdef DEBUG
		std::cout << __func__ << " print message:" << std::endl;
		msg.clear();
		struct cmsghdr *cmsgh =  CMSG_FIRSTHDR(&msgh);
		int control = 0;
		while (cmsgh  != NULL) {
			std::cout << " control: " << std::to_string(control) << "\r\n\t" << std::flush;
			for (size_t b = 0; b < cmsgh->cmsg_len; ++b) {
				unsigned char byte = CMSG_DATA(cmsgh)[b];
				msg += (char)byte;
				std::cout << byte << " " << std::flush;

			}
			std::cout << std::endl;
			cmsgh = CMSG_NXTHDR(&msgh, cmsgh);
			control++;
		}
#endif
	}

	//print details of the client/peer and the data received
//	printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
//	printf("Data: %s\n" , msg.c_str());

	return (msg.length() > 0);
}
*/

bool BCastServerSocket::sendTo(std::string &msg, const std::string &addr)
{
	msg.clear();
#ifdef DEBUG
		std::cout << __func__ << " client " << addr << std::endl;
#endif
/*
	//print details of the client/peer and the data received
	printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
	printf("Data: %s\n" , buf);

	//now reply the client with the same data
	if (sendto(s, buf, recv_len, 0, (struct sockaddr*) &si_other, slen) == -1)
	{
#ifdef DEBUG
		std::cout << __func__ << " => " << strerror(errno)<< std::endl;
#endif
	}
	*/

	return false;
}
