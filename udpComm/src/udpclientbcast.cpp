#include "udpclientbcast.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>

#ifdef DEBUG
#include <iostream>
#endif

#define BUFLEN 1400 //Max length of buffer
using namespace Macsa::Comms;

BcastClientSocket::BcastClientSocket(std::string svr, int port)
{
	_server = svr;
	_fdSocket = -1;
	_port = port;
	_opened = false;
}

BcastClientSocket::~BcastClientSocket()
{
	close();
}

bool BcastClientSocket::open()
{
	if (!_opened) {
		int soBroadcast = 1;
		if (createSocket(_fdSocket) && setSocketOption(_fdSocket, SO_REUSEADDR, soBroadcast)) {
			struct sockaddr_in bcAddr;
			if (initSocket(bcAddr, _server.c_str(), _port)) {
				_opened = bindSocket(_fdSocket, bcAddr);
			}

		}
		if(!_opened && _fdSocket != -1) {
			close();
		}
	}

	return _opened;
}

bool BcastClientSocket::receiveFrom(std::string& msg, std::string &server)
{
	int len = 0;
	char buff[BUFLEN] = {0};
//	socklen_t slen = sizeof (_svraddr);
//	//try to receive some data, this is a blocking call
//	if ((len = recvfrom(_fdSocket, buff, BUFLEN, 0, (struct sockaddr *) &_svraddr, &slen)) == -1)
//	{
//#ifdef DEBUG
//		std::cout << __func__ << " => " << strerror(errno)<< std::endl;
//#endif
//	}
//	else {
//		msg = buff;
//		server = inet_ntoa(_svraddr.sin_addr);
//#ifdef DEBUG
//		//print details of the client/peer and the data received
//		printf("Received packet from %s:%d\n", server.c_str(), ntohs(_svraddr.sin_port));
//		printf("Data: %s\n" , msg.c_str());
//#endif
//	}

	return (len > 0);
}

bool BcastClientSocket::sendTo(const std::string &msg, const std::string &addr)
{
	bool sent = false;
//	int flags = 0;

//	sent = (sendto(_fdSocket, msg.c_str(), msg.length(), flags, (struct sockaddr *) &_svraddr, sizeof (_svraddr)) != -1);

//#ifdef DEBUG
//	std::cout << __func__ << " => " << strerror(errno)<< std::endl;
//#endif

	return sent;
}

