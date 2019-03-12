#include <iostream>
#include <thread>
#include "mserver.h"
#include "mclient.h"
#include "unistd.h"

int main(int argc, char** argv)
{
	Macsa::Comms::MServer server;
	short port = atoi(argv[1]);
	if (server.open(port)) {

		std::string msg;
		std::string client;
		client.clear();
		msg.clear();

		while (server.isOpened()){
			if (server.receive(msg, client)) {
				std::cout << "** Received message: " << msg.c_str() << std::endl;
				std::cout << "** Client: " << client.c_str() << std::endl;

				sleep(1);
				Macsa::Comms::MClient udpClient;
				if (udpClient.open(client.c_str(), port)) {
					msg = "HELLO";
					udpClient.send(msg);
					server.close();
				}
			}

		}
	}

	exit(0);
}
