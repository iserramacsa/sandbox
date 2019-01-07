#include "unixsockets.h"
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>

#include <sys/types.h>
#include <sys/time.h>
#include <netdb.h>
#include <unistd.h>
#include <strings.h>
#include <vector>

#define UNUSED(x) (void)(x)

ClientUnixSocket::ClientUnixSocket()
{
	_socketFd	= -1;
	_opened		= false;
	_connected	= false;
}

ClientUnixSocket::~ClientUnixSocket()
{
	disconnect();
}

bool ClientUnixSocket::open()
{
	if(!_opened){
		_opened = ((_socketFd = socket(AF_INET, SOCK_STREAM, 0)) >= 0);
		if (!_opened) {
			error("ERROR:\tOpening socket\n");
		}
	}
	return _opened;
}

bool ClientUnixSocket::disconnect()
{
	if(_opened){
		close(_socketFd);
		_opened = false;
	}

	return !_opened;
}

bool ClientUnixSocket::send(const char *tx)
{
	bool sent = false;
	if (_connected) {
		fd_set wfds;
		FD_ZERO(&wfds);
		FD_SET(_socketFd, &wfds);
		std::string msg = tx;
		if ((select(_socketFd + 1, NULL, &wfds, NULL, NULL)) < 1){
			sent = (write(_socketFd, msg.c_str(), msg.length()) == static_cast<ssize_t>(msg.length()));
		}
	}

	return sent;
}

bool ClientUnixSocket::receive(char &rx, int timeout)
{
	bool received = false;
	if (_connected){
		struct timeval		timeval;
		fd_set				rfds;

		timeval.tv_sec = timeout;
		timeval.tv_usec = 0;
		FD_ZERO(&rfds);
		FD_SET(_socketFd, &rfds);

		if ((select(_socketFd + 1, &rfds, NULL, NULL, &timeval)) < 1){
			error("ERROR:\tReading from socket[select]\n");
		}
		else{
			received = ((read(_socketFd, &rx, 255)) > 0);
			if (!received)
				error("ERROR:\tReading from socket\n");
		}

	}
	return received;
}

bool ClientUnixSocket::connectTo(const char *address, int port)
{
	if(_opened && isValidConnectionData(address, port)){
		struct sockaddr_in	serverAddr;
		struct hostent		*server;

		bzero((char *) &serverAddr, sizeof(serverAddr));

		serverAddr.sin_family = AF_INET;
		if(!(server = gethostbyname(address))){
			error("ERROR:\tNo such host\n");
		}
		else {
			bcopy((char *) server->h_addr,
				  (char *)&serverAddr.sin_addr.s_addr,
				  server->h_length);
			serverAddr.sin_port = htons(port);
			_connected = connectToServer(_socketFd, ( struct sockaddr * ) &serverAddr);
		}
	}

	return _connected;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClientUnixSocket::connectToServer(int fd, struct sockaddr * addr)
{
	int success = connect(fd, addr, sizeof(*addr));

	if (success == -1) {
		perror(__PRETTY_FUNCTION__);
	}

	return (success == 0);
}

bool ClientUnixSocket::isValidConnectionData(const char *address, int port)
{
	bool validAddress = false;
	bool validPort = false;
	std::string add = address;

	if (add.size() >= 7) {
		std::vector<int> ints;
		size_t pos = add.find_first_of(".");
		while (pos != add.npos){
			ints.push_back(std::atoi(add.substr(0, pos).c_str()));
			add = add.substr(pos + 1);
			pos = add.find_first_of(".");
		}
		ints.push_back(std::atoi(add.substr(0, pos).c_str()));
		if (ints.size() == 4){
			validAddress = (ints.at(0) >= 0 && ints.at(0) <= 255);
			validAddress &= (ints.at(1) >= 0 && ints.at(1) <= 255);
			validAddress &= (ints.at(2) >= 0 && ints.at(2) <= 255);
			validAddress &= (ints.at(3) >= 0 && ints.at(3) <= 255);
		}
	}
	validPort = (port > 0 && port < 0xFFFF);

	return validAddress && validPort;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ServerUnixSocket::ServerUnixSocket()
{
	_socketFd	= -1;
	_opened		= false;
	_connected	= false;
}

ServerUnixSocket::~ServerUnixSocket()
{
	disconnect();
}

bool ServerUnixSocket::open()
{
	if(!_opened){
		_opened = ((_socketFd = socket(AF_INET, SOCK_STREAM, 0)) >= 0);
		if (!_opened) {
			error("ERROR:\tOpening socket\n");
		}
	}
	return _opened;
}

bool ServerUnixSocket::disconnect()
{
	if(!_opened){
		close(_socketFd);
		_opened = false;
	}

	return _opened;
}

bool ServerUnixSocket::send(const char *tx)
{
	bool sent = false;
	if (_connected) {
		fd_set wfds;
		FD_ZERO(&wfds);
		FD_SET(_socketFd, &wfds);
		std::string msg = tx;
		if ((select(_socketFd + 1, NULL, &wfds, NULL, NULL)) < 1){
			sent = (write(_socketFd, msg.c_str(), msg.length()) == static_cast<ssize_t>(msg.length()));
		}
	}

	return sent;
}

bool ServerUnixSocket::receive(char &rx, int timeout)
{
	bool received = false;
	if (_connected){
		struct timeval		timeval;
		fd_set				rfds;

		timeval.tv_sec = timeout;
		timeval.tv_usec = 0;
		FD_ZERO(&rfds);
		FD_SET(_socketFd, &rfds);

		if ((select(_socketFd + 1, &rfds, NULL, NULL, &timeval)) < 1){
			error("ERROR:\tReading from socket[select]\n");
		}
		else{
			received = ((read(_socketFd, &rx, 255)) > 0);
			if (!received)
				error("ERROR:\tReading from socket\n");
		}

	}
	return received;
}

bool ServerUnixSocket::listenPort(int port)
{
	UNUSED(port);
/*
	if(_opened){
		struct sockaddr_in	serverAddr;
		bzero((char *) &serverAddr, sizeof(serverAddr));

		serverAddr.sin_family = AF_INET;
		serverAddr.sin_port = htons(port);
		serverAddr.sin_addr.s_addr = INADDR_ANY;

		if((bind(_socketFd, (struct sockaddr *) &serverAddr, sizeof(serverAddr))) < 0){
			error ("ERROR:\tOn binding\n");
		}
		else {

			//	Wait for connection
			/////////////////////////////////////////////////////////////////////////////////////////
			struct sockaddr_in clientAddr;
			listen(_socketFd, 5);
			unsigned int clientLen = sizeof(clientAddr);
			if ((_socketFd = accept(_socketFd, (struct sockaddr *) &clientAddr, &clientLen)) < 0){
				error("ERROR:\tOn accept\n");
			}
			return true;
			/////////////////////////////////////////////////////////////////////////////////////////

		}
		return true;


		if(!(server = gethostbyname(address))){
			error("ERROR:\tNo such host\n");
		}
		else {
			bcopy((char *) server->h_addr,
				  (char *)&serverAddr.sin_addr.s_addr,
				  server->h_length);
			serverAddr.sin_port = htons(port);
			_connected = (connect(_socketFd,(struct sockaddr *) &serverAddr,sizeof(serverAddr)) >= 0);
		}
	}

	return _connected;

	/////////////////////////////////////////////////////////////////////////////////////////


	while (_connected){
		struct timeval		timeval;
		fd_set				rfds;
		std::string rx;
		timeval.tv_sec = -1;
		timeval.tv_usec = 0;
		FD_ZERO(&rfds);
		FD_SET(_socketFd, &rfds);

		if ((select(_socketFd + 1, &rfds, NULL, NULL, &timeval)) < 1){
			error("ERROR:\tReading from socket[select]\n");
		}
		else{
			if ((read(_socketFd, &rx, 255)) > 0)
				error("ERROR:\tReading from socket\n");
		}

	}
	*/
	return false;
}
