#ifndef _MPROTOCOL_H
#define _MPROTOCOL_H

#include <string>
#include "iprotocol.h"

class MCommand;
class MProtocol : public IProtocol
{
	public:
		MProtocol() : IProtocol (){};
		virtual ~MProtocol(){};
		MCommand * getCommand(std::string cmd){};

};

#endif //_MPROTOCOL_H
