#ifndef _MCLIENT_H
#define _MCLIENT_H

#include "mprintermanager.h"
#include "mprotocol.h"
#include <string>


class MCLient : public MProtocolClient
{
	public:
		MCLient();
		~MCLient();
		void connectToPrinter(std::string ip, int port);
		int getNumPrinters();
		int getCurrentSelectedPrinter();
		/** Commands **/
		bool getFilesList(int printer, std::vector<std::string>filesList, std::string extensions);
		bool getFilesList(std::vector<std::string>filesList, std::string extensions); //For current selected printer

		bool copyFile(int printer, std::string source, std::string dest);

	private:
		MPrinterManager _printers;
		int _selectedPrinter;
};

#endif
