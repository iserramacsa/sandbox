#include "mclient.h"
#include "comms/unixsockets.h"

MCLient::MCLient()
{
//	_socket = new ClientUnixSocket();
//	_comm = new Comms(*_socket);

}
MCLient::~MCLient()
{

}

void MCLient::connectToPrinter(std::string ip, int port)
{
	_printers.addPrinterAt(ip, port);
}
