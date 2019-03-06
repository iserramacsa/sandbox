#include <iostream>
#include "mclient.h"
#include "unistd.h"

int main(int argc, char** argv)
{
	Macsa::Comms::MClient client;




	client.open(argv[1], atoi(argv[2]));

	int len = 5;
	while (len--) {
		client.send(argv[3]);
		if (len) {
			usleep(500000);
		}
	}

	exit(0);
}
