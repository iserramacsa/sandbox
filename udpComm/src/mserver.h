#ifndef _M_SERVER_H
#define _M_SERVER_H

#include <string>

namespace Macsa {
	namespace Comms {
		class BCastServerSocket;
		class UdpServerSocket;
		class MServer
		{
			public:
				MServer();
				~MServer();
				bool open(int port);
				bool close();
				bool isOpened();

				bool receive(std::string &msg, std::string &client);
				bool receive(std::string &msg);
				bool send(std::string &msg, const std::string &client);

			private:
				UdpServerSocket* udpSocket;
		};
	}
}

#endif
