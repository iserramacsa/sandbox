#ifndef _M_CLIENT_H
#define _M_CLIENT_H

#include <string>

namespace Macsa {
	namespace Comms {
		class UdpClientSocket;
		class MClient
		{
			public:
				MClient();
				~MClient();
				bool open(const char *svr, int port);
				bool close();

				bool receive(std::string &msg, std::string &client);
				bool receive(std::string &msg);
				bool send(const std::string &msg);

			private:
				UdpClientSocket* udpSocket;
		};
	}
}

#endif
