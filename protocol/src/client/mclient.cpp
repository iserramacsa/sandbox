#include "mclient.h"
#include "unixsockets.h"
#include "mprinter.h"


MCLient::MCLient()
{
//	_socket = new ClientUnixSocket();
//	_comm = new Comms(*_socket);

	_selectedPrinter = -1;

}
MCLient::~MCLient()
{

}

void MCLient::connectToPrinter(std::string ip, int port)
{
	_printers.addPrinter(ip, port);
}

int MCLient::getNumPrinters()
{
	return _printers.getNumPrinters();
}

int MCLient::getCurrentSelectedPrinter()
{
	return _selectedPrinter;
}

bool MCLient::getFilesList(int printer, std::vector<std::string> filesList, std::string extensions)
{
	if (printer >= 0 && printer < getNumPrinters()) {
		MPrinter* mprinter = _printers.getPrinter(printer);
		if(mprinter){
			//		mprinter->getFilesList(filesList, extensions);
		}
	}

	return false;
}

bool MCLient::getFilesList(std::vector<std::string> filesList, std::string extensions)
{
	return getFilesList(_selectedPrinter, filesList, extensions);
}
