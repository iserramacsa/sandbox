#include "mclient.h"
#include "posix/udpclientbcast.h"

using namespace Macsa::Comms;

MClient::MClient()
{
	_udpSocket = NULL;
}

MClient::~MClient()
{
	delete _udpSocket;
}

bool MClient::open(const char* svr, int port)
{
	bool open = false;

	if (_udpSocket == NULL) {
#if BCAST
		_udpSocket = new BcastClientSocket(svr, port);
#else
		_udpSocket = new UdpClientSocket(svr, port);
#endif
	}
	if (_udpSocket != NULL) {
		open = _udpSocket->open();
	}

	return open;
}

bool MClient::close()
{
	bool closed = true;
	if (_udpSocket != NULL) {
		closed = _udpSocket->close();
	}

	return closed;
}

bool MClient::receive(std::string &msg, std::string &client)
{
	msg.clear();

	if (_udpSocket != NULL) {
		_udpSocket->receiveFrom(msg, client);
	}

	return (msg.length() > 0);
}

bool MClient::send(const std::string &msg)
{
	bool sent = false;

	if(_udpSocket != NULL) {
		sent = _udpSocket->sendToServer(msg);
	}
	return sent;
}

