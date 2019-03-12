#include <iostream>
#include "mclient.h"
#include "mserver.h"
#include "unistd.h"

int main(int argc, char** argv)
{
	Macsa::Comms::MClient me,BcMe;
	Macsa::Comms::MServer myServer;
	BcMe.openBcast("255.255.255.255",atoi("9090"));
	BcMe.sendBcast("SOY CLIENTE BROADCAST");
	BcMe.closeBcast();
	if (myServer.open(atoi("9090"))) {
		while (myServer.isOpened()) {
			std::string msg;
			std::string notMeServer;
			msg.clear();
			notMeServer.clear();
			if (myServer.receive(msg,notMeServer)){
				std::cout << "** Received message: " << msg.c_str() << std::endl;
				myServer.close();
				me.open(notMeServer.c_str(),atoi("9090"));
				me.send("SOY CLIENTE");
				me.close();
			}
		}

	}
	exit(0);
}
