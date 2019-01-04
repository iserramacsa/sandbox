#ifndef _UNIX_SOCKET_H
#define _UNIX_SOCKET_H

#include "abstractsocket.h"

class ClientUnixSocket : public AbstractClientSocket
{
	public:
		ClientUnixSocket();
		virtual ~ClientUnixSocket();
		virtual bool open();
		virtual bool disconnect();
		virtual bool send(const char* tx);
		virtual bool receive(char& rx, int timeout = DEFAULT_TIMEOUT);
		virtual bool connectTo(const char* address, int port);

	private:
		bool _opened;
		bool _connected;
		int _socketFd;
};


// TODO
class ServerUnixSocket : public AbstractServerSocket
{
	public:
		ServerUnixSocket();
		virtual ~ServerUnixSocket();
		virtual bool open();
		virtual bool disconnect();
		virtual bool send(const char* tx);
		virtual bool receive(char& rx, int timeout = DEFAULT_TIMEOUT);
		virtual bool listenPort(int port);

	private:
		bool _opened;
		bool _connected;
		int _socketFd;
};

#endif //_UNIX_SOCKET_H

