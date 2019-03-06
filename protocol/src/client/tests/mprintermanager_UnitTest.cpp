#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "mprintermanager.h"
#include "mprinter.h"

class MPrinterManager_Mock : public MPrinterManager
{
	public:
		MPrinterManager_Mock() : MPrinterManager(){}
};

class MPrinterManagerUnitTest : public ::testing::Test {
	protected:
		virtual void SetUp() {
		}

		virtual void TearDown() {
		// Code here will be called immediately after each test
		// (right before the destructor).
		}
	protected:
		MPrinterManager_Mock _manager;
};

TEST_F(MPrinterManagerUnitTest, DefaultConstructor)
{
	EXPECT_TRUE(true);
}

TEST_F(MPrinterManagerUnitTest, GetPrinterByIndex_InvalidIndex_ReturnNULL)
{
	std::string ip = "127.0.0.1";
	int port = 9991;
	_manager.addPrinterAt(ip, port);

	MPrinter* printer = _manager.getPrinter(1);
	EXPECT_TRUE(printer == NULL);
}

TEST_F(MPrinterManagerUnitTest, GetPrinterByIndex_validIndex_ReturnValidMPrinter)
{
	std::string ip = "127.0.0.1";
	int port = 9991;
	_manager.addPrinterAt(ip, port);

	MPrinter* printer = _manager.getPrinter(0);
	EXPECT_TRUE(printer->getIpAddress().compare(ip) == 0);
}

TEST_F(MPrinterManagerUnitTest, GetPrinterByIp_InvalidIp_ReturnNULL)
{
	std::string ip = "127.0.0.1";
	int port = 9991;
	_manager.addPrinterAt(ip, port);

	MPrinter* printer = _manager.getPrinter("");
	EXPECT_TRUE(printer == NULL);
}

TEST_F(MPrinterManagerUnitTest, GetPrinterByIp_ValidIp_ReturnValidMPrinter)
{
	std::string ip = "127.0.0.1";
	int port = 9991;
	_manager.addPrinterAt(ip, port);

	MPrinter* printer = _manager.getPrinter(ip);
	EXPECT_TRUE(printer->getIpAddress().compare(ip) == 0);
}
