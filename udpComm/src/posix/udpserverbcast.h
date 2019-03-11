#ifndef _UDP_BROADCAST_SOCKET_H
#define _UDP_BROADCAST_SOCKET_H

#include "udpserver.h"

namespace Macsa {
	namespace Comms {
		class BCastServerSocket : public UdpServerSocket
		{
			public:
				BCastServerSocket(std::string svr = "", int port = 0);
				virtual ~BCastServerSocket();
				virtual bool open();

			private:
				std::string _bcastAddr;
		};
	}
}

#endif
