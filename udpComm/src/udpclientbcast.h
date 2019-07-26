#ifndef _UDP_BROADCAST_CLIENT_SOCKET_H
#define _UDP_BROADCAST_CLIENT_SOCKET_H
#include "udpsocket.h"

namespace Macsa {
	namespace Comms {
		class BcastClientSocket : public UdpSocket
		{
			public:
				BcastClientSocket(std::string svr = "", int port = 0);
				virtual ~BcastClientSocket();
				virtual bool open();

				virtual bool receiveFrom(std::string &msg, std::string &client);
				virtual bool sendTo(const std::string &msg, const std::string &addr);

			private:
				std::string _server;
				int _port;
		};
	}
}

#endif
