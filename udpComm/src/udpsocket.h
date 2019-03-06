#ifndef _UDP_SOCKET_H
#define _UDP_SOCKET_H

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <string>

namespace Macsa {
	namespace Comms {
		class UdpSocket {
			public:
				UdpSocket();
				virtual ~UdpSocket();
				virtual bool isOpened();
				virtual int port();
				virtual bool open()  = 0;
				virtual bool close();
				virtual bool receiveFrom(std::string &msg, std::string &addr)  = 0;
				virtual bool sendTo(const std::string &msg, const std::string &addr) = 0;

			protected:
				int  _fdSocket;
				int  _port;
				bool _opened;

				bool createSocket(int& fd, int type = SOCK_DGRAM, int protocol = IPPROTO_UDP);
				bool initSocket(struct sockaddr_in& socket,  const char *addr = "", const char *port = "");
				bool initSocket(struct sockaddr_in& socket,  const char *addr = "", short port = 0);
				bool bindSocket(int &fd, struct sockaddr_in& socket);
				bool setSocketOption(int &fd, int optName, int &optValue);
				void clearSocket(struct sockaddr_in& socket);

			private:
				bool setAddress(struct sockaddr_in& socket,  const char *addr = "");

		};
	}
}

#endif
