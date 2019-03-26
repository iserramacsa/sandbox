#ifndef ABSTRACT_SOCKET_H
#define ABSTRACT_SOCKET_H

#include <stdint.h>
#include <string>

namespace MComm {

#define BACKLOG_CONNECTIONS	1

#define MIN_IP_SIZE			7
#define IP_NUM_CHARS		4
#define DEFAULT_BUFF_SIZE	1024

#define UDP_PROTOCOL		"udp"
#define TCP_PROTOCOL		"tcp"

#define DEFAULT_TIMEOUT	10000 // 10 seconds in ms
#define NO_WAIT			0
#define WAIT_FOREVER	-1

	class ISocket
	{
		public:
			enum nSocketType
			{
				UDP_SOCKET = 0,
				TCP_SOCKET
			};
			enum nSocketStatus
			{
				ERROR = -1,
				UNKNOWN = 0,
				CREATED,
				INITIATED,
				BINDED,
				LISTENING,
				CONNECTED,
				READY,
			};

		public:
			ISocket(nSocketType type, int port) {
				_type = type;
				_port  = port;
				_status = UNKNOWN;
			}
			virtual ~ISocket(){}
			virtual bool bind() = 0;
			virtual bool listen() = 0;
			virtual bool connect(const std::string& addr, uint16_t port) = 0;
			virtual bool connect(const std::string& addr, const std::string& port) = 0;
			virtual bool send(const std::string& tx, int timeout = NO_WAIT) = 0;
			virtual bool send(const std::string& tx, const std::string& dest, int timeout = NO_WAIT) = 0;
			virtual bool receive(std::string& rx, int timeout = DEFAULT_TIMEOUT) = 0;
			virtual bool receive(std::string& rx, std::string& addr, int timeout = DEFAULT_TIMEOUT) = 0;
			virtual bool close() = 0;
			virtual bool enableBroadcast() = 0;
			virtual nSocketStatus status() {return _status;}

		protected:
			uint16_t		_port;
			nSocketType		_type;
			nSocketStatus	_status;

			virtual bool init() = 0;

	};
}

#endif //ABSTRACT_SOCKET_H
