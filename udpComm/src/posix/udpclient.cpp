#include "udpclient.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>

#ifdef DEBUG
#include <iostream>
#endif

#define BUFLEN 1400 //Max length of buffer
using namespace Macsa::Comms;

UdpClientSocket::UdpClientSocket(std::string svr, int port)
{
	_server = svr;
	_fdSocket = -1;
	_port = port;
	_opened = false;
}

UdpClientSocket::~UdpClientSocket()
{
	close();
}

bool UdpClientSocket::open()
{
	if (!_opened) {
		if (createSocket(_fdSocket)) {
			_opened = initSocket(_svraddr, _server.c_str(), _port);
		}
		if(!_opened && _fdSocket != -1) {
			close();
		}
	}

	return _opened;
}

bool UdpClientSocket::close()
{
	if (_opened) {
		::close(_fdSocket);
		_opened = false;
	}
	return (!_opened);
}

bool UdpClientSocket::receiveFrom(std::string& msg, std::string &server)
{
	int len;
	char buff[BUFLEN] = {0};
	socklen_t slen = sizeof (_svraddr);
	//try to receive some data, this is a blocking call
	if ((len = recvfrom(_fdSocket, buff, BUFLEN, 0, (struct sockaddr *) &_svraddr, &slen)) == -1)
	{
#ifdef DEBUG
		std::cout << __func__ << " => " << strerror(errno)<< std::endl;
#endif
	}
	else {
		msg = buff;
		server = inet_ntoa(_svraddr.sin_addr);
#ifdef DEBUG
		//print details of the client/peer and the data received
		printf("Received packet from %s:%d\n", server.c_str(), ntohs(_svraddr.sin_port));
		printf("Data: %s\n" , msg.c_str());
#endif
	}

	return (len > 0);
}

bool UdpClientSocket::sendTo(const std::string &msg, const std::string &addr)
{
	bool sent = false;
	int flags = 0;

	sent = (sendto(_fdSocket, msg.c_str(), msg.length(), flags, (struct sockaddr *) &_svraddr, sizeof (_svraddr)) != -1);

#ifdef DEBUG
	std::cout << __func__ << " => " << strerror(errno)<< std::endl;
#endif

	return sent;
}

bool UdpClientSocket::sendToServer(const std::string &msg)
{
	return sendTo(msg, _server);
}

void UdpClientSocket::setServer(std::string svr, int port)
{
	if(_opened){
		_server = svr;
		_port = port;
	}
}
