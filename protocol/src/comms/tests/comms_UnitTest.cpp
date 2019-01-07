#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "comms.h"

class Comms_Mock : public Comms
{
	public:
		Comms_Mock() : Comms(){}

};

class CommsUnitTest : public ::testing::Test {
	protected:
		virtual void SetUp() {
		}

		virtual void TearDown() {
		// Code here will be called immediately after each test
		// (right before the destructor).
		}
	private:
		Comms_Mock comms;
};

TEST(CommsUnitTest, DefaultConstructor)
{
	EXPECT_TRUE(true);
}













/***********************************************************************************************
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
*/
