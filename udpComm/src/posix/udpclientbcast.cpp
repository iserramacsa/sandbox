#include "udpclientbcast.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>

#ifdef DEBUG
#include <iostream>
#endif

using namespace Macsa::Comms;

BcastClientSocket::BcastClientSocket(std::string svr, int port) :
	UdpClientSocket(svr, port)
{
}

BcastClientSocket::~BcastClientSocket()
{
	close();
}

bool BcastClientSocket::open()
{
	if (!_opened) {
		UdpClientSocket::open();
		if(_opened){
			int soBroadcast = 1;
			_opened = setSocketOption(_fdSocket, SO_BROADCAST, soBroadcast);
		}
	}
	return _opened;
}
