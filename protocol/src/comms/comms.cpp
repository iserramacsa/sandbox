#include "comms.h"
#if __linux
	#include "unixsockets.h"
#endif

#include "unistd.h" // tmp

Comms::Comms()
{

#if __linux
	_socket = new ClientUnixSocket();
#elif __WIN32__
	_socket = new ClientWin32Socket();
#endif


}

void Comms::ConnectToServer(std::string ip, int port)
{

}

OnReceiveDatagram Comms::onReceiveData(const char *rx, int len, void *udata)
{
	Comms * self = static_cast<Comms*>(udata);

	if (self){
		write(1, rx, len);
	}

	return 0;
}
