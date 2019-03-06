#include "mprinter.h"

MPrinter::MPrinter(std::string ip, int port)
{
	_hostname.clear();
	_ipAddress.clear();
	_port = DEFAULT_PORT;

	_ipAddress = ip;
	_port = port;
}

MPrinter::~MPrinter()
{

}

std::string MPrinter::getHostname()
{
	return _hostname;
}

std::string MPrinter::getIpAddress()
{
	return _ipAddress;
}

int MPrinter::getPort()
{
	return _port;
}

bool MPrinter::getFilesList(FilesCache filesList, std::string extensions)
{
	return false;
}
