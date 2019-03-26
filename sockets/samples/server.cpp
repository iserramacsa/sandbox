#include <iostream>
#include <unistd.h>
#include <cstdlib>

#include "unixsocket.h"

#define UNUSED(x) (void)(x)
#define TEST_PORT_UDP	8080
//#define TEST_PORT_TCP	9990
#define BCAST_ADDR	"255.255.255.255"

static bool sendBCastMessage(const std::string& msg);
static int UdpSocketsTestServer();

std::string readFromUdp(MComm::ISocket& socket, std::string& addr);
bool sendTo(MComm::ISocket& socket, const std::string& rx, std::string& addr);
std::string getResponseMessage(const std::string& rx);
//static void readFromUdp(MComm::ISocket& socket);


void printHeader(int argc, char* argv[])
{
	std::cout << "**** Starting " << argv[0]  << " ****" << std::endl;
	for (int i = 1; i < argc; i++) {
		std::cout << "** arg[" << i << "]: " << argv[i] << std::endl;
	}
}



int main (int argc, char* argv[])
{
	printHeader(argc, argv);

//	if(UdpSocketsTestServer()) {
//		exit(EXIT_FAILURE);
//	}
//	exit(EXIT_SUCCESS);
#if 1
	MComm::ISocket* socket = dynamic_cast<MComm::ISocket*>(new MComm::UnixSocket(TEST_PORT_UDP, MComm::ISocket::UDP_SOCKET));
	std::string addr = "";
	std::string tx = "";
	std::string rx = "";

	while (tx.compare("EXIT") != 0) {
		tx = readFromUdp(*socket, addr);
		rx = getResponseMessage(tx);
		if (rx.length()){
			sendTo(*socket, rx, addr);
		}
	}


	socket->close();
	delete socket;
#else
	MComm::ISocket* socket = dynamic_cast<MComm::ISocket*>(new MComm::UnixSocket(TEST_PORT_UDP, MComm::ISocket::UDP_SOCKET));
	std::string msg;
	std::string remoteAddr;

	if (!socket->bind()){
		std::cerr << "Error while binding socket!" << std::endl;
		return  EXIT_FAILURE;
	}

	while (socket->receive(msg, remoteAddr, WAIT_FOREVER)) {
		std::cout << "MSG RECEIVED: \"" << msg << "\" from " << remoteAddr << std::endl;
		if (msg.compare("HELLO?") == 0) {
			sendBCastMessage("HELLO");
//			if (socket->connect(remoteAddr, TEST_PORT_UDP)) {
//				socket->send("HELLO");
//			}
		}
		if (msg.compare("EXIT") == 0) {
			break;
		}
	}

	socket->close();
	delete socket;
#endif
	return EXIT_SUCCESS;
}

std::string readFromUdp(MComm::ISocket& socket, std::string& addr)
{
	if(socket.status() < MComm::ISocket::BINDED){
		socket.bind();
	}
	std::string rx;
	if (socket.status() == MComm::ISocket::BINDED) {
		if(socket.receive(rx, addr, WAIT_FOREVER)){
			std::cout << addr << " -> \"" << rx << "\"" << std::endl;
		}
	}

	return rx;
}

bool sendTo(MComm::ISocket& socket, const std::string& rx, std::string& addr)
{
	bool success = false;
	success = socket.send(rx, addr);
	if (success){
		std::cout << addr << " <- \"" << rx << "\"" << std::endl;
	}
	return success;
}

std::string getResponseMessage(const std::string& rx)
{
	std::string resp;

	if (rx.compare("HELLO?") == 0){
		resp = "HELLO";
	}
	if (rx.compare("EXIT") == 0){
		resp = "BYE";
	}
	return resp;
}


//////////////////////////////////////////////////////////////////////////////////////////////
bool sendBCastMessage(const std::string& msg)
{
	bool sent = false;
	MComm::ISocket* bcastSocket = dynamic_cast<MComm::ISocket*>(new MComm::UnixSocket(TEST_PORT_UDP, MComm::ISocket::UDP_SOCKET));

	if (bcastSocket && bcastSocket->enableBroadcast()) {
		sent = bcastSocket->send(msg, BCAST_ADDR);
	}

	bcastSocket->close();
	return  sent;
}

int UdpSocketsTestServer()
{
	MComm::ISocket* socket = dynamic_cast<MComm::ISocket*>(new MComm::UnixSocket(TEST_PORT_UDP, MComm::ISocket::UDP_SOCKET));
	if (!socket->bind()){
		std::cerr << "Error while binding socket!" << std::endl;
		return  EXIT_FAILURE;
	}

	std::string rx;
	std::string remote;
	if(socket->receive(rx, remote, WAIT_FOREVER)) {
		std::cerr << "Error receiving message from sever" << std::endl;
		return  EXIT_FAILURE;
	}
	else {
		std::cout << "MSG RECEIVED: \"" << rx << "\" from " << remote << std::endl;
		if (socket->connect("127.0.0.1", TEST_PORT_UDP) && socket->send("TEST OK")) {
		}
	}

	return EXIT_SUCCESS;
}
