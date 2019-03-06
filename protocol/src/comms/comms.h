#ifndef _COMMS_H
#define _COMMS_H

#include "abstractsocket.h"

class Comms
{
	public:
		Comms();
		~Comms();;
		virtual bool ConnectToServer(std::string ip, int port);
		virtual void send(std::string ip, int port, std::string msg){};


	private:
		AbstractSocket* _socket;

		static OnReceiveDatagram onReceiveData(const char* rx, int len, void* udata);

};

#endif
