#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "unixsockets.h"

using ::testing::Return;

class ClientUnixSocket_Mock : public ClientUnixSocket
{
	public:
		ClientUnixSocket_Mock() : ClientUnixSocket(){}
//		virtual bool open(){return false;}
//		virtual bool disconnect(){return true;}
//		virtual bool send(const char* txs){return true;}
//		virtual bool receive(char& rx, int timeout = DEFAULT_TIMEOUT){return true;}
//		virtual bool connectTo(const char* address, int port){return true;}

		MOCK_METHOD2(connectToServer, bool(int, struct sockaddr *));
		virtual bool connectToServer_Unmock(int fd, struct sockaddr *addr){
			return ClientUnixSocket::connectToServer(fd, addr);
		};

};

class ClientUnixSocketUnitTest : public ::testing::Test {
	protected:
		virtual void SetUp() {
		}

		virtual void TearDown() {
		// Code here will be called immediately after each test
		// (right before the destructor).
		}
	protected:
		ClientUnixSocket_Mock unixSocket;
};

TEST_F(ClientUnixSocketUnitTest, DefaultConstructor)
{
	EXPECT_TRUE(true);
}

TEST_F(ClientUnixSocketUnitTest, OpenUnitTest_returnTrue)
{
	bool result = unixSocket.open();
	unixSocket.disconnect();
	EXPECT_TRUE(result);
}

TEST_F(ClientUnixSocketUnitTest, DisconnectUnitTest_returnTrue)
{
	unixSocket.open();
	bool result = unixSocket.disconnect();
	EXPECT_TRUE(result);
}

TEST_F(ClientUnixSocketUnitTest, ConnectToServerValidIp_returnTrue)
{
	EXPECT_CALL(unixSocket, connectToServer).WillRepeatedly(Return(true));
	unixSocket.open();
	bool result =  unixSocket.connectTo("127.0.0.1", 9991);
	unixSocket.disconnect();
	EXPECT_TRUE(result);
}

