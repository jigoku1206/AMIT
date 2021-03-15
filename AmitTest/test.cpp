#include "pch.h"
#include "Amit.h"

using namespace testing;
using namespace Amit;

class AmitCommandParserTest : public Test
{
public:
	int ret = 0;
	AmitCommandParser cmdparser;
	char output[65535]{ 0 };

	void SetUp() override
	{

	}
};

TEST_F(AmitCommandParserTest, ReadCommandLines) {

	ret = cmdparser.ParseCommandToCmdMap("[GetAmitVersion]\r\nCommand=Amit\r\n \
										Func=AmitVersion\r\n", output);

	ASSERT_EQ(cmdparser.cmdlines.size(), 3);
}

TEST_F(AmitCommandParserTest, FindCommandSections) {

	ret = cmdparser.ParseCommandToCmdMap("[GetAmitVersion]\r\nCommand=Amit\r\n\
										Func=AmitVersion\r\n", output);

	ASSERT_EQ(cmdparser.cmdcollection.size(), 1);
}

TEST_F(AmitCommandParserTest, AddCommandParams) {

	ret = cmdparser.ParseCommandToCmdMap("[GetAmitVersion]\r\nCommand=Amit\r\n\
										Func=AmitVersion\r\n", output);

	ASSERT_EQ(cmdparser.cmdcollection[0].cmdmap["Command"], "Amit");
	ASSERT_EQ(cmdparser.cmdcollection[0].cmdmap["Func"], "AmitVersion");
}

TEST_F(AmitCommandParserTest, RemoveSpecicCharacters) {

	ret = cmdparser.ParseCommandToCmdMap("[GetAmitVersion]\r\nCommand=Amit\r\n   \
										Func=  \tAmitVersion\r\n", output);

	ASSERT_EQ(cmdparser.cmdcollection[0].cmdmap["Command"], "Amit");
	ASSERT_EQ(cmdparser.cmdcollection[0].cmdmap["Func"], "AmitVersion");
}

TEST_F(AmitCommandParserTest, RemoveCommentString) {

	ret = cmdparser.ParseCommandToCmdMap("[GetAmitPlatformDeviceInfo]\r\n//ThisIsComment1\r\n \
										Command=AmitPlatform   \t//ThisIsComment2\r\n \
										Func=GetDeviceInfo\r\n", output);

	ASSERT_EQ(cmdparser.cmdcollection[0].cmdmap.size(), 2);
	ASSERT_EQ(cmdparser.cmdcollection[0].cmdmap["Command"], "AmitPlatform");
	ASSERT_EQ(cmdparser.cmdcollection[0].cmdmap["Func"], "GetDeviceInfo");
}

TEST_F(AmitCommandParserTest, ParseBatchCommandArea) 
{
	ret = cmdparser.ParseCommandToCmdMap("[GetAmitPlatformDeviceInfo]\r\n//ThisIsComment1\r\n \
										Command=BatchRun//ThisIsComment2\r\n \
										{\r\nReg, 0x0100,  0x00\r\n}\r\n\r\n", output);

	ASSERT_EQ(cmdparser.batchlines.size(), 1);

}