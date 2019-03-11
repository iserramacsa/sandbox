#ifndef _UDP_BROADCAST_CLIENT_SOCKET_H
#define _UDP_BROADCAST_CLIENT_SOCKET_H
#include "udpclient.h"

namespace Macsa {
	namespace Comms {
		class BcastClientSocket : public UdpClientSocket
		{
			public:
				BcastClientSocket(std::string svr = "", int port = 0);
				virtual ~BcastClientSocket();
				virtual bool open();
			private:
		};
	}
}

#endif
