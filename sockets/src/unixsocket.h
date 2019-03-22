#ifndef UNIX_SOCKET_H
#define UNIX_SOCKET_H

#include "isocket.h"

namespace MComm {
	class UnixSocket : public ISocket
	{
		public:
			UnixSocket();
			virtual ~UnixSocket();



	};
}


#endif //UNIX_SOCKET_H
