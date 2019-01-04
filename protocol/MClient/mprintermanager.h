#ifndef _MPRINTER_MANAGER_H
#define _MPRINTER_MANAGER_H

#include <vector>
#include <string>

class MPrinter;
class MPrinterManager
{
	public:
		MPrinterManager();
		~MPrinterManager();
		void addPrinterAt(std::string ip, int port);
		int getNumPrinters();
		MPrinter * getPrinter(int idx);
		MPrinter * getPrinter(std::string ip);

	private:
		std::vector<MPrinter*> _printers;

		bool attachPrinter(std::string ip, int port);
		bool printerExist(std::string ip, int port);

		inline bool isValid(int idx);
};

#endif //_MPRINTER_MANAGER_H
