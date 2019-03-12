#include "udpserver.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>

#ifdef DEBUG
#include <iostream>
#endif

#define BUFLEN (1024 * 5) //Max length of buffer
using namespace Macsa::Comms;

UdpServerSocket::UdpServerSocket(int port) :
	UdpSocket ()
{
	_port = port;
}

UdpServerSocket::~UdpServerSocket()
{
	close();
}

bool UdpServerSocket::open()
{
	if (!_opened) {
		if (createSocket(_fdSocket)){
			struct sockaddr_in addrSvr;
			if (initSocket(addrSvr, "", _port)) {
				_opened = bindSocket(_fdSocket, addrSvr);
			}
		}
		if  (!_opened && _fdSocket != -1){
			close();
		}
	}

	return _opened;
}

bool UdpServerSocket::receiveFrom(std::string& msg, std::string &addr)
{
	int len;
	char buff[BUFLEN] = {0};
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
bool UdpServerSocket::receiveMsg(std::string& msg)
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

bool UdpServerSocket::sendTo(const std::string &msg, const std::string &addr)
{
	bool sent = false;
	int flags = 0;
	//struct sockaddr * _client;
	sent = (sendto(_fdSocket, msg.c_str(), msg.length(), flags, (struct sockaddr *) &addr, sizeof (&addr)) != -1);

#ifdef DEBUG
	std::cout << __func__ << " => " << strerror(errno)<< std::endl;
#endif

	return sent;
}
