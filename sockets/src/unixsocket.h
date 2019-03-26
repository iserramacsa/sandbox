#ifndef UNIX_SOCKET_H
#define UNIX_SOCKET_H

#include "isocket.h"
#include "netinet/in.h"

namespace MComm {
	class UnixSocket : public ISocket
	{
		public:
			UnixSocket(int port, nSocketType type);
			virtual ~UnixSocket();

			virtual bool bind();
			virtual bool listen();
			virtual bool connect(const std::string& addr, uint16_t port);
			virtual bool connect(const std::string& addr, const std::string& port);
			virtual bool send(const std::string& tx, int timeout = NO_WAIT);
			virtual bool send(const std::string& tx, const std::string& dest, int timeout = NO_WAIT);
			virtual bool receive(std::string& rx, int timeout = DEFAULT_TIMEOUT);
			virtual bool receive(std::string& rx, std::string& addr, int timeout = DEFAULT_TIMEOUT);
			virtual bool enableBroadcast();
			virtual bool close();

		protected:
			struct sConnection {
				int			fd;
				sockaddr_in	addr;
			};

		protected:
			virtual bool init();

		private:
			sConnection _local;
			sConnection _remote;


			bool createSocket(int& fd, nSocketType type);
			bool initSocket(struct sockaddr_in& socket, const char *addr, uint16_t port);
			bool initSocket(struct sockaddr_in& socket, const char *addr, const char *port);
			bool setAddress(struct sockaddr_in& socket,  const char *addr = "");
			void clearSocket(struct sockaddr_in& socket);
			bool setSocketOption(int &fd, int optName, int &optValue);
			bool waitForRead(int fd, int timeout);
			bool waitForWrite(int fd, int timeout);
			bool connect(int fd, const struct sockaddr_in& socket);
	};

	class UDPSocket : public UnixSocket
	{
		public:
			UDPSocket(int port);
			virtual ~UDPSocket();

	};
}


#endif //UNIX_SOCKET_H
