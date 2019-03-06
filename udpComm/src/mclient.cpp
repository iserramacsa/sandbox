#include "mclient.h"
#include "udpclient.h"

using namespace Macsa::Comms;

MClient::MClient()
{
	udpSocket = NULL;
}

MClient::~MClient()
{
	delete udpSocket;
}

bool MClient::open(const char* svr, int port)
{
	bool open = false;

	if (udpSocket == NULL) {
		udpSocket = new UdpClientSocket(svr, port);
	}
	if (udpSocket != NULL) {
		open = udpSocket->open();
	}

	return open;
}

bool MClient::close()
{
	bool closed = true;
	if (udpSocket != NULL) {
		closed = udpSocket->close();
	}

	return closed;
}

bool MClient::receive(std::string &msg, std::string &client)
{
	msg.clear();

	if (udpSocket != NULL) {
		udpSocket->receiveFrom(msg, client);
	}

	return (msg.length() > 0);
}

bool MClient::send(const std::string &msg)
{
	bool sent = false;

	if(udpSocket != NULL) {
		sent = udpSocket->sendToServer(msg);
	}
	return sent;
}

