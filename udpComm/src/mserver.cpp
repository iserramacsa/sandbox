#include "mserver.h"
#include "udpserver.h"

using namespace Macsa::Comms;

MServer::MServer()
{
	udpSocket = NULL;
}

MServer::~MServer()
{
	delete udpSocket;
}

bool MServer::open(int port)
{
	bool open = false;

	if (udpSocket == NULL) {
		udpSocket = new UdpServerSocket(port);
	}
	if (udpSocket != NULL) {
		open = udpSocket->open();
	}

	return open;
}

bool MServer::close()
{
	bool closed = true;
	if (udpSocket != NULL) {
		closed = udpSocket->close();
	}

	return closed;
}

bool MServer::isOpened()
{
	bool opened = false;
	if (udpSocket != NULL) {
		opened = udpSocket->isOpened();
	}
	return opened;
}

bool MServer::receive(std::string &msg, std::string &client)
{
	msg.clear();

	if (udpSocket != NULL) {
		udpSocket->receiveFrom(msg, client);
	}

	return (msg.length() > 0);
}

bool MServer::receive(std::string &msg)
{
	msg.clear();

	if (udpSocket != NULL) {
		std::string client = "";
		udpSocket->receiveFrom(msg, client);
	}

	return (msg.length() > 0);
}

