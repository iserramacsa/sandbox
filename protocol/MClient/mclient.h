#ifndef _MCLIENT_H
#define _MCLIENT_H

#include "mprintermanager.h"
#include <string>

class MCLient
{
	public:
		MCLient();
		~MCLient();
		void connectToPrinter(std::string ip, int port);

	private:
		MPrinterManager _printers;
};

#endif
