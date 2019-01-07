#ifndef _MPRINTER_H
#define _MPRINTER_H

#include <vector>
#include <map>
#include <string>
#include "comms.h"
#include "mprotocol.h"

#define DEFAULT_PORT	9991

typedef  std::map<std::string, std::vector<std::string>>  FilesCache;

class MPrinter
{
	public:
		MPrinter(std::string ip, int port);
		~MPrinter();
		std::string getHostname();
		std::string getIpAddress();
		int getPort();

		bool getFilesList(FilesCache filesList, std::string extensions);


	private:
		std::string _hostname;
		std::string _ipAddress;
		int _port;

		Comms _comm;
		MProtocolClient* _protocol;
};

#endif //_MPRINTER_H
