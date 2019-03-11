#ifndef _M_CLIENT_H
#define _M_CLIENT_H

#include <string>
#define BCAST	1
namespace Macsa {
	namespace Comms {
		class BcastClientSocket;
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
#if BCAST
				BcastClientSocket* _udpSocket;
#else
				UdpClientSocket* _udpSocket;
#endif
		};
	}
}

#endif
