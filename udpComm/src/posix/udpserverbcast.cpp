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

#define DEFAULT_BCAST_ADDR	"255.255.255.255"

BCastServerSocket::BCastServerSocket(std::string svr, int port) :
	UdpServerSocket(port)
{
	_bcastAddr = DEFAULT_BCAST_ADDR;
	if (svr.length()) {
		_bcastAddr = svr;
	}
	_port = 0;
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
		if (UdpServerSocket::open()) {
			_opened = setSocketOption(_fdSocket, SO_REUSEADDR, soBroadcast);

		}
	}
	return _opened;
}
