#include <iostream>
#include <thread>
#include "mserver.h"
//#include "mclient.h"

int main(void)
{
	Macsa::Comms::MServer server;
	//Macsa::Comms::MClient myClient;
	uint i=0;
	if (server.open(atoi("9090"))) {
		while (server.isOpened()&& i<5) {
			std::string msg;
			std::string notMeClient;
			std::string msgSend = "Soy server";
			notMeClient.clear();
			msg.clear();
			server.receive(msg, notMeClient);
			std::cout << "** client: " << notMeClient.c_str() << std::endl;
			std::cout << "** Received message: " << msg.c_str() << std::endl;
			server.send(msgSend,notMeClient);
			i++;
		}
	}

	exit(0);
}
