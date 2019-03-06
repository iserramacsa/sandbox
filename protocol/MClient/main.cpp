#include "iprotocol.h"
#include "mclient.h"

#include <iostream>

void printHeader(int argc, char* argv[])
{
	std::cout << argv[0] << " " << PROTOCOL_VERSION_STR;
	for (int i = 1; i < argc; i++) {
		std::cout << "\t" << i  << " - " << argv[i];
	}
	std::cout << std::endl;
}


int main(int argc, char* argv[])
{
	printHeader(argc, argv);

	MCLient client;

//	ClientUnixSocket client;
//	if(client.open() && client.connectTo("192.168.1.64", 9991)) {

//	}

	return 0;
}
