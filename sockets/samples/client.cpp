#include <iostream>
#include <unistd.h>
#include <cstdlib>

#include "unixsocket.h"

#define TEST_PORT_UDP	8080
//#define TEST_PORT_TCP	9990
#define BCAST_ADDR	"192.168.1.255"

#define UNUSED(x) (void)(x)

#include <thread>
#include <condition_variable>


static bool sendBCastMessage(const std::string& msg);
static int UdpSocketsTestClient();

static void readFromSocket(MComm::ISocket* socket);
std::mutex mtx;
std::condition_variable cv;

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

//	if(UdpSocketsTestClient()) {
//		exit(EXIT_FAILURE);
//	}
//	exit(EXIT_SUCCESS);
#if 1
	MComm::ISocket* socket = dynamic_cast<MComm::ISocket*>(new MComm::UnixSocket(TEST_PORT_UDP, MComm::ISocket::UDP_SOCKET));
	std::thread t = std::thread(&readFromSocket, socket);
	while (socket->status() < MComm::ISocket::BINDED) {
		sleep(1);
	}

	sendBCastMessage("HELLO?");
	{
		std::unique_lock<std::mutex>lck(mtx);
		cv.wait(lck);
	}
	sendBCastMessage("EXIT");
	{
		std::unique_lock<std::mutex>lck(mtx);
		cv.wait(lck);
	}
/*
	if (socket->connect("192.168.1.64", TEST_PORT_UDP)){
		if(socket->send("HELLO?", "192.168.1.64")) {
			std::unique_lock<std::mutex>lck(mtx);
			cv.wait(lck);
		}
		if(socket->send("EXIT", "192.168.1.64")) {
			std::unique_lock<std::mutex>lck(mtx);
			cv.wait(lck);
		}
	}
*/
	socket->close();
	t.join();

	delete socket;

#else
	sendBCastMessage("HELLO?");

	MComm::ISocket* socket = dynamic_cast<MComm::ISocket*>(new MComm::UnixSocket(TEST_PORT_UDP, MComm::ISocket::UDP_SOCKET));
	if (!socket->bind()){
		std::cerr << "Error while binding socket!" << std::endl;
		return  EXIT_FAILURE;
	}

	std::string rx;
	std::string remote;
	while(socket->receive(rx, remote, WAIT_FOREVER)){
		std::cout << "MSG RECEIVED: \"" << rx << "\" from " << remote << std::endl;
		if (rx.compare("HELLO") == 0) {
			if (socket->connect(remote, TEST_PORT_UDP)){
				//if (socket->send("EXIT")){
				if(sendBCastMessage("EXIT")) {
					std::cout << "MSG SENT: \"" << "EXIT" << "\" to " << remote << std::endl;
				}
			}
			break;
		}
	}

	socket->close();

	std::cout << "**** Stoping " << argv[0]  << " ****" << std::endl;
	delete socket;
#endif
	exit(EXIT_SUCCESS);
}

void readFromSocket(MComm::ISocket* socket)
{
	std::string rx = "";
	std::string addr = "";

	if (socket->status() < MComm::ISocket::BINDED){
		if (!socket->bind()){
			std::cerr << "Error while binding socket!" << std::endl;
			socket->close();
			delete socket;
			exit(EXIT_FAILURE);
		}
	}

	while (rx.compare("BYE") != 0){
		if (socket->receive(rx, addr,  WAIT_FOREVER)) {
			std::cout << "MSG RECEIVED: \"" << rx << "\" from " << addr << std::endl;
			if ((rx.back() != '?') && rx.compare("EXIT")){
				std::unique_lock<std::mutex>lck(mtx);
				cv.notify_all();
			}
		}
	}
}

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

int UdpSocketsTestClient()
{
	MComm::ISocket* socket = dynamic_cast<MComm::ISocket*>(new MComm::UnixSocket(TEST_PORT_UDP, MComm::ISocket::UDP_SOCKET));
	if (!socket->bind()){
		std::cerr << "Error while binding socket!" << std::endl;
		return  EXIT_FAILURE;
	}

	if (socket->connect("127.0.0.1", TEST_PORT_UDP) && socket->send("TEST")) {
		std::string rx;
		std::string remote;
		if(!socket->receive(rx, remote, WAIT_FOREVER)) {
			std::cerr << "Error receiving message from sever" << std::endl;
			return  EXIT_FAILURE;
		}
		else {
			std::cout << "MSG RECEIVED: \"" << rx << "\" from " << remote << std::endl;
		}
	}

	return EXIT_SUCCESS;
}
