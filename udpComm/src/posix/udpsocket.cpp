#include "udpsocket.h"
#include <unistd.h>
#include <cstring>
#include <netdb.h>

#ifdef DEBUG
#include <iostream>
#endif

#define BUFLEN (1024 * 5) //Max length of buffer
using namespace Macsa::Comms;
#define UDP_PROTOCOL "udp"

UdpSocket::UdpSocket()
{
	_fdSocket = -1;
	_opened = false;
	_port  = -1;
}

UdpSocket::~UdpSocket()
{
}

bool UdpSocket::isOpened()
{
	return _opened;
}

int UdpSocket::port()
{
	return _port;
}

bool UdpSocket::close()
{
	if (_fdSocket != -1) {
		::close(_fdSocket);
		_opened = false;
		_fdSocket = -1;
	}
	return (!_opened);
}

bool UdpSocket::createSocket(int &fd, int type, int protocol)
{
	if (fd == -1)
	{
		fd = socket(AF_INET, type, protocol);
#ifdef DEBUG
		std::cout << __func__ << " => " << strerror(errno)<< std::endl;
#endif
	}

	return (fd != -1);
}

bool UdpSocket::initSocket(sockaddr_in &socket, const char *addr, const char *port)
{
	bool success = false;

	clearSocket(socket);
	socket.sin_family = AF_INET;

	if (setAddress(socket, addr))  {
		if (strlen(port)) {
			// Lookup the service:
			struct servent *sp = getservbyname( port, UDP_PROTOCOL);
			if (sp != NULL) {
				success = true;
				socket.sin_port = (short) sp->s_port;
			}
		}
		else {
			success = true;
			socket.sin_port = 0;
		}
	}

	return success;
}

bool UdpSocket::initSocket(sockaddr_in &socket, const char *addr, short port)
{
	bool success = false;

	clearSocket(socket);
	socket.sin_family = AF_INET;

	if (setAddress(socket, addr))  {
		if (port == 0) {
			socket.sin_port = 0;
			success = true;
		}
		else {
			socket.sin_port = htons(port);
			success = true;
		}
	}

	return success;
}

bool UdpSocket::bindSocket(int &fd, struct sockaddr_in &socket)
{
	int result = (bind(fd , (struct sockaddr*)&socket, sizeof(socket)) != -1);
#ifdef DEBUG
	std::cout << __func__ << " => " << strerror(errno)<< std::endl;
#endif
	return (result != -1);
}

bool UdpSocket::setSocketOption(int &fd, int optName, int &optValue)
{
	int result = setsockopt(fd, SOL_SOCKET, optName, &optValue, sizeof (optValue));
#ifdef DEBUG
	std::cout << __func__ << " => " << strerror(errno)<< std::endl;
#endif
	return (result != -1);
}


void UdpSocket::clearSocket(struct sockaddr_in &socket)
{
	// zero out the structure
	memset((char *) &socket, 0, sizeof(socket));
}

bool UdpSocket::setAddress(sockaddr_in &socket, const char *addr)
{
	bool success = false;

	if (strlen(addr)) {
		if  (isdigit(*addr)) {
			//Numeric IP address:
			socket.sin_addr.s_addr = inet_addr(addr);
			success = (inet_aton(addr, &socket.sin_addr) != -1);
		}
		else {
			//Assume a hostname
			struct hostent *hp = gethostbyname(addr);
			if (hp != NULL &&  hp->h_addrtype == AF_INET) {
				success = true;
				socket.sin_addr = *(struct in_addr *)hp->h_addr_list[0];
			}
		}
	}
	else {
		success = true;
		socket.sin_addr.s_addr = INADDR_ANY;
	}
#ifdef DEBUG
	if (!success) {
		std::cout << __func__ << " => " << strerror(errno)<< std::endl;
	}
#endif
	return success;
}

