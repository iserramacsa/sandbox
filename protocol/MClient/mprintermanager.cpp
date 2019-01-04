#include "mprintermanager.h"
#include "mprinter.h"

MPrinterManager::MPrinterManager()
{
	printers.clear();
}

void MPrinterManager::addPrinterAt(std::string ip, int port)
{
	if(!printerExist(ip, port)){
		attachPrinter(ip, port);
	}
}

bool MPrinterManager::attachPrinter(std::string ip, int port)
{
	MPrinter * printer = new MPrinter(ip, port);

	if (printer){
		printers.push_back(printer);
	}

	return (printer != NULL);
}

bool MPrinterManager::printerExist(std::string ip, int port)
{
	for (unsigned int i = 0; i < printers.size(); i++){
		if ((printers.at(i)->getIpAddress().compare(ip) == 0) &&
			printers.at(i)->getPort() == port)
		{
			return true;
		}
	}
	return false;
}
