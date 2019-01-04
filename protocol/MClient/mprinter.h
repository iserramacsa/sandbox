#ifndef _MPRINTER_H
#define _MPRINTER_H

#include <string>
#include "comms.h"

#define DEFAULT_PORT	9991

class MPrinter
{
	public:
		MPrinter(std::string ip, int port);
		~MPrinter();
		std::string getHostname();
		std::string getIpAddress();
		int getPort();


	private:
		std::string _hostname;
		std::string _ipAddress;
		int _port;

		Comms _comm;
};

#endif //_MPRINTER_H
