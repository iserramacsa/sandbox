#include "mprintermanager.h"
#include "mprinter.h"

MPrinterManager::MPrinterManager()
{
	_printers.clear();
}

void MPrinterManager::addPrinter(std::string ip, int port)
{
	if(!printerExist(ip, port)){
		attachPrinter(ip, port);
	}
}

int MPrinterManager::getNumPrinters()
{
	return _printers.size();
}

MPrinter *MPrinterManager::getPrinter(int idx)
{
	if(isValid(idx)){
		return _printers.at(idx);
	}
	return NULL;
}

MPrinter * MPrinterManager::getPrinter(std::string ip)
{
	for (unsigned int i = 0; i < _printers.size(); i++){
		if (_printers.at(i)->getIpAddress().compare(ip) == 0)
		{
			return _printers.at(i);
		}
	}
	return NULL;
}

bool MPrinterManager::attachPrinter(std::string ip, int port)
{
	MPrinter * printer = new MPrinter(ip, port);

	if (printer){
		_printers.push_back(printer);
	}

	return (printer != NULL);
}

bool MPrinterManager::printerExist(std::string ip, int port)
{
	for (unsigned int i = 0; i < _printers.size(); i++){
		if ((_printers.at(i)->getIpAddress().compare(ip) == 0) &&
			_printers.at(i)->getPort() == port)
		{
			return true;
		}
	}
	return false;
}

bool MPrinterManager::isValid(int idx)
{
	return (idx >= 0 && idx < static_cast<int>(_printers.size()));
}
