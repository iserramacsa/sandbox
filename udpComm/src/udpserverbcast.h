#ifndef _UDP_BROADCAST_SOCKET_H
#define _UDP_BROADCAST_SOCKET_H

#include "udpsocket.h"

namespace Macsa {
	namespace Comms {
		class BCastServerSocket : UdpSocket
		{
			public:
				BCastServerSocket(std::string svr = "", int port = 0);
				virtual ~BCastServerSocket();
				virtual bool open();
				virtual bool close();
				virtual bool receiveFrom(std::string &msg, std::string &addr);
				virtual bool sendTo(std::string &msg, const std::string &addr);

			private:
				std::string _bcastAddr;
		};
	}
}

#endif
