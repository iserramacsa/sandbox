#ifndef _M_CLIENT_H
#define _M_CLIENT_H

#include <string>
//#define BCAST	1

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
				bool openBcast(const char *svr,int port);
				bool close();
				bool closeBcast();

				bool receive(std::string &msg, std::string &client);
				bool receive(std::string &msg);
				bool send(const std::string &msg);
				bool sendBcast(const std::string &msg);

			private:
				BcastClientSocket* _udpBcSocket;
				UdpClientSocket* _udpSocket;
		};
	}
}
#endif

