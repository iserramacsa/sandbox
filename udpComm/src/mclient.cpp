#include "mclient.h"
#include "posix/udpclientbcast.h"

using namespace Macsa::Comms;
#define BCAST_ADDR	"255.255.255.255"

MClient::MClient()
{
	_udpSocket = NULL;
	_bcastSocket = NULL;
}

MClient::~MClient()
{
	delete _udpSocket;
	delete _bcastSocket;
}

bool MClient::open(const char* svr, int port)
{
	bool open = false;

	if (_udpSocket == NULL) {
		_udpSocket = new UdpClientSocket(svr, port);
	}
	if (_udpSocket != NULL) {
		open = _udpSocket->open();
	}

	return open;
}

bool MClient::openBcast(int port)
{
	bool open = false;
	if (_bcastSocket == NULL){
		_bcastSocket = new BcastClientSocket(BCAST_ADDR, port);
	}
	if (_bcastSocket != NULL){
		open = _bcastSocket->open();
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

bool MClient::sendBCast(const std::string &msg)
{
	bool sent = false;

	if(_bcastSocket != NULL) {
		sent = _bcastSocket->sendToServer(msg);
	}
	return sent;
}

