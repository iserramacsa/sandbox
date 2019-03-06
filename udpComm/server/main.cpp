#include <iostream>
#include <thread>
#include "mserver.h"

int main(int argc, char** argv)
{
	Macsa::Comms::MServer server;
	if (server.open(atoi(argv[1]))) {
		int len = 5;
		while (server.isOpened() && len--) {
			std::string msg;
			std::string client;
			client.clear();
			msg.clear();

			server.receive(msg, client);

			std::cout << "** Received message: " << msg.c_str() << std::endl;
		}
	}

	exit(0);
}
