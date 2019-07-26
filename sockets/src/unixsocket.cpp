#include "unixsocket.h"

#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <string>
#include <cstring>

#ifdef DEBUG
	#include <iostream>
#endif

#if __cplusplus < 201103L
	#include <errno.h>
#endif

using namespace MComm;


UnixSocket::UnixSocket(int port, nSocketType type) :
	ISocket (type, port)
{
	_local.fd = -1;
	if (createSocket(_local.fd, _type) && init()) {
		int val = 1;
		setSocketOption(_local.fd, SO_REUSEPORT, val);
		_status = INITIATED;
	}
}

UnixSocket::~UnixSocket()
{
	close();
}

bool UnixSocket::bind()
{
	bool success = false;
	if (_status == INITIATED) {
		int val = 1;
		setSocketOption(_local.fd, SO_REUSEADDR, val);
		if (::bind(_local.fd, (struct sockaddr*)&_local.addr, sizeof (_local.addr)) != -1) {
			_status = BINDED;
			success = true;
		}
#ifdef DEBUG
		else {
			std::cout << __func__ << "(" << _local.fd << ") bind => " << strerror(errno)<< std::endl;
		}
#endif
	}
	return  success;
}

bool UnixSocket::listen() // TODO: Review
{
	bool success = false;

	if (_status == BINDED) {
		if(::listen(_local.fd, BACKLOG_CONNECTIONS) == 0) {
			clearSocket(_remote.addr);
			socklen_t len = sizeof (_local.addr);
			if (waitForRead(_local.fd, WAIT_FOREVER)){
				_remote.fd = ::accept(_local.fd, (struct sockaddr*)&_local.addr, &len);
				success = (_remote.fd >= 0);
			}
		}
#ifdef DEBUG
		if (!success) {
			std::cout << __func__ << "(" << _local.fd << ") listen => " << strerror(errno)<< std::endl;
		}
#endif
		if (success) {
			_status = LISTENING;
		}
	}

	return success;
}

bool UnixSocket::connect(const std::string &addr, uint16_t port)
{
	bool success = false;
	if (_local.fd != -1 && _status < LISTENING){
		initSocket(_remote.addr, addr.c_str(), port);
		success = connect(_local.fd, _remote.addr);
	}
	return success;
}

bool UnixSocket::connect(const std::string &addr, const std::string &port)
{
	bool success = false;
	if (_local.fd != -1 && _status < LISTENING){
		initSocket(_remote.addr, addr.c_str(), port.c_str());
		success = connect(_local.fd, _remote.addr);
	}
	return success;
}

bool UnixSocket::send(const std::string &tx, int timeout)
{
	bool sent = false;
	int fd = -1;
	if (_type == TCP_SOCKET){
		fd = _remote.fd;
	}
	else {
		fd = _local.fd;
	}
	if (fd != -1) {
		if (waitForWrite(fd, timeout)) {
			long bytesSent = ::send(fd, tx.c_str(), tx.length(), 0);
			if (bytesSent > 0){
				sent = ((unsigned)bytesSent == tx.length());
			}
		}
	}

	return sent;
}

bool UnixSocket::send(const std::string &tx, const std::string &dest, int timeout)
{
	bool sent = false;
	if (_type == UDP_SOCKET){
		if (waitForWrite(_local.fd, timeout)) {
			initSocket(_remote.addr, dest.c_str(), _port);
			long bytesSent = ::sendto(_local.fd, tx.c_str(), tx.length(),0, (struct sockaddr*)&_remote.addr, sizeof (_remote.addr));
			if (bytesSent > 0){
				sent = ((unsigned)bytesSent == tx.length());
			}
		}
	}

	return sent;

}

bool UnixSocket::receive(std::string &rx, int timeout)
{
	std::string dummy;
	return receive(rx, dummy, timeout);

}

bool UnixSocket::receive(std::string &rx, std::string &addr, int timeout)
{
	bool received = false;
	char buff[DEFAULT_BUFF_SIZE] = {0};

	if (_type == TCP_SOCKET && _status >= LISTENING){
		if (waitForRead(_remote.fd, timeout)) {
			received = (::recv(_remote.fd, buff, DEFAULT_BUFF_SIZE, 0) > 0);
			if (received) {
				rx = buff;
			}
		}
	}
	else {
		if (waitForRead(_local.fd, timeout)) {
			clearSocket(_remote.addr);
			socklen_t len = sizeof(_remote.addr);
			received = (::recvfrom(_local.fd, buff, DEFAULT_BUFF_SIZE, 0, (struct sockaddr*)&_remote.addr, &len) > 0);
			if (received) {
				rx = buff;
				addr = getAddress(_remote.addr);
			}
		}
	}

	return received;
}

bool UnixSocket::enableBroadcast()
{
	bool success = false;
	int bcast = 1;
	if (_local.fd > -1){
		success = setSocketOption(_local.fd, SO_BROADCAST, bcast);
	}
	return  success;
}

bool UnixSocket::close()
{
	bool success = false;
	success = (::close(_local.fd) == 0);
	return  success;
}

bool UnixSocket::init()
{
	return  initSocket(_local.addr, "", _port);
}

bool UnixSocket::createSocket(int &fd, nSocketType type)
{
	int protocol;
	int sockType;
	switch (type) {
		case UDP_SOCKET:
			sockType = SOCK_DGRAM;
			protocol = IPPROTO_UDP;
			break;
		case TCP_SOCKET:
			sockType = SOCK_STREAM;
			protocol = IPPROTO_TCP;
			break;
	}

	if (fd == -1)
	{
		fd = socket(AF_INET, sockType, protocol);
#ifdef DEBUG
		if (errno != 0) {
			std::cout << __func__ << "(" << fd << ") => " << strerror(errno)<< std::endl;
		}
#endif
	}
	return (fd != -1);
}

bool UnixSocket::initSocket(sockaddr_in &socket, const char *addr, uint16_t port)
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

bool UnixSocket::initSocket(sockaddr_in &socket, const char *addr, const char *port)
{
	bool success = false;

	clearSocket(socket);
	socket.sin_family = AF_INET;

	if (setAddress(socket, addr))  {
		if (strlen(port)) {
			// Lookup the service:
			std::string proto;
			switch (_type) {
				case UDP_SOCKET:
					proto = UDP_PROTOCOL;
					break;
				case TCP_SOCKET:
					proto = TCP_PROTOCOL;
					break;
			}

			struct servent *sp = getservbyname( port, proto.c_str());
			if (sp != NULL) {
				success = true;
				socket.sin_port = (uint16_t) sp->s_port;
			}
		}
		else {
			success = true;
			socket.sin_port = 0;
		}
	}
	return success;
}

bool UnixSocket::setAddress(sockaddr_in &socket, const char *addr)
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
	if (errno != 0) {
		std::cout << __func__ << " => " << strerror(errno)<< std::endl;
	}
#endif
	return success;
}

void UnixSocket::clearSocket(sockaddr_in &socket)
{
	memset((char *) &socket, 0, sizeof(socket));
}

bool UnixSocket::setSocketOption(int &fd, int optName, int &optValue)
{
	bool success = (0 == setsockopt(fd, SOL_SOCKET, optName, &optValue, sizeof (optValue)));
#ifdef DEBUG
	if (errno != 0) {
		std::cout << __func__ << " => " << strerror(errno)<< std::endl;
	}
#endif
	return success;
}

bool UnixSocket::waitForRead(int fd, int timeout)
{
	bool ready = false;
	struct timeval *ptout = NULL;
	struct timeval tout;
	if (timeout >= 0){
		tout.tv_sec = timeout/100;
		tout.tv_usec = (timeout - tout.tv_sec * 100) * 1000;
		ptout = &tout;
	}

	fd_set wfds;
	FD_ZERO(&wfds);
	FD_SET(fd, &wfds);

	ready = (select(fd + 1, NULL, &wfds, NULL, ptout) >= 0);

	return ready;
}

bool UnixSocket::waitForWrite(int fd, int timeout)
{
	bool ready = false;
	struct timeval *ptout = NULL;
	struct timeval tout;
	if (timeout >= 0){
		tout.tv_sec = timeout/100;
		tout.tv_usec = (timeout - tout.tv_sec * 100) * 1000;
		ptout = &tout;
	}

	fd_set rfds;
	FD_ZERO(&rfds);
	FD_SET(fd, &rfds);

	ready = (select(fd + 1, &rfds, NULL, NULL, ptout) >= 0);

	return ready;
}

bool UnixSocket::connect(int fd, const sockaddr_in &socket)
{
	bool success = false;
	success = (::connect(fd, (struct sockaddr*) &socket, sizeof (socket)) == 0);

#ifdef DEBUG
	if (errno != 0) {
		std::cout << __func__ << " => " << strerror(errno)<< std::endl;
	}
#endif

	return success;
}

std::string UnixSocket::getAddress(const sockaddr_in &socket) const
{
	return inet_ntoa(socket.sin_addr);
}
