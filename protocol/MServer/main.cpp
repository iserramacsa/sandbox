#include "iprotocol.h"
#include <iostream>


int main(int argc, char* argv[])
{
	std::cout << argv[0] << " " << PROTOCOL_VERSION_STR;
	for (int i = 1; i < argc; i++) {
		std::cout << "\t" << i  << " - " << argv[i];
	}
	std::cout << std::endl;

	return 0;
}
