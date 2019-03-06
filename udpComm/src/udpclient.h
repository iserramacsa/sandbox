#ifndef _UDP_CLIENT_SOCKET_H
#define _UDP_CLIENT_SOCKET_H
#include "udpsocket.h"

namespace Macsa {
	namespace Comms {
		class UdpClientSocket : public UdpSocket
		{
			public:
				UdpClientSocket(std::string svr = "", int port = 0);
				virtual ~UdpClientSocket();
				virtual bool open();
				virtual bool close();

				virtual bool receiveFrom(std::string &msg, std::string &client);
				virtual bool sendToServer(const std::string &msg);
				void setServer(std::string svr = "", int port = 0);
			protected:
				virtual bool sendTo(const std::string &msg, const std::string &addr);
			private:
				std::string _server;
				struct sockaddr_in _svraddr;
		};
	}
}

#endif
