#ifndef _MPROTOCOL_H
#define _MPROTOCOL_H

#include <string>

class MCommand;
class MProtocolClient
{
	public:
		MProtocolClient();
		~MProtocolClient();
		MCommand * getCommand(std::string cmd);

};

#endif //_MPROTOCOL_H
