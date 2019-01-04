#ifndef _COMMS_H
#define _COMMS_H

#include "abstractsocket.h"

class Comms
{
	public:
		Comms();
		~Comms(){};
		void ConnectToServer(std::string ip, int port);


		void send(std::string ip, int port, std::string msg);


	private:
		AbstractSocket* _socket;

		static OnReceiveDatagram onReceiveData(const char* rx, int len, void* udata);

};

#endif
