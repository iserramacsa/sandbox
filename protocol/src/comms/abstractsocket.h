#ifndef _ABSTRACT_SOCKET_H
#define _ABSTRACT_SOCKET_H

#include <string>
#include <cstdio>
#include <iostream>

#define DEFAULT_TIMEOUT	1000

typedef void((*OnReceiveDatagram)(const char* rx, int len, void* udata));

class AbstractSocket
{
	public:
		AbstractSocket(){}
		virtual ~AbstractSocket(){}
		virtual bool open() = 0;
		virtual bool disconnect() = 0;
		virtual bool send(const char* tx) = 0;
		virtual bool receive(char& msg, int timeout = DEFAULT_TIMEOUT) = 0;


		void error(const char* msg) // TODO move to log object
		{
			fprintf(stderr, msg);
		}


	protected:
		int _port;
		std::string _ipAddress;

};

class AbstractServerSocket : public AbstractSocket
{
	public:
		virtual ~AbstractServerSocket(){}
		virtual bool listenPort(int port) = 0;

};

class AbstractClientSocket : public AbstractSocket
{
	public:
		virtual ~AbstractClientSocket(){}
		virtual bool connectTo(const char* address, int port) = 0;
//		static OnReceiveDatagram receiveCallback(const char* rx, int len, void* udata);
};

#endif //_ABSTRACT_SOCKET_H
