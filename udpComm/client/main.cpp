#include <iostream>
#include "mclient.h"
#include "mserver.h"
#include "unistd.h"

int main(int argc, char** argv)
{
	Macsa::Comms::MClient client;
	Macsa::Comms::MServer server;

	int port = atoi(argv[1]);
	std::string msg = argv[2];

	if (client.openBcast(port)){
		client.sendBCast(msg);
		if(server.open(port)) {
			std::string msg;
			std::string responder;
			if (server.receive(msg, responder)) {
				if(client.open(responder.c_str(), port)) {
					msg = "BYE!";
					client.send(msg);
				}
			}
		}

	}

//	client.open(argv[1], atoi(argv[2]));

//	int len = 5;
//	while (len--) {
//		client.send(argv[3]);
//		if (len) {
//			usleep(500000);
//		}
//	}

	exit(0);
}
