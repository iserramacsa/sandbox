#ifndef _UDP_SERVER_SOCKET_H
#define _UDP_SERVER_SOCKET_H
#include "udpsocket.h"

namespace Macsa {
	namespace Comms {
		class UdpServerSocket : public UdpSocket
		{
			public:
				UdpServerSocket(int port);
				virtual ~UdpServerSocket();
				virtual bool open();

				virtual bool receiveFrom(std::string &msg, std::string &addr);
				virtual bool sendTo(const std::string &msg, const std::string &addr);
		};
	}
}

#endif
