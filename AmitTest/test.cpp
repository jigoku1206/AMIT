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
};

TEST_F(AmitCommandParserTest, ReadCommandLines) {

	ret = cmdparser.ParseCommandToCmdMap("[GetAmitVersion]\r\nCommand=Amit\r\n \
										Func=AmitVersion\r\n", output);

	ASSERT_EQ(cmdparser.cmdlines.size(), 3);
}

TEST_F(AmitCommandParserTest, AddCommandParams) {

	ret = cmdparser.ParseCommandToCmdMap("[GetAmitVersion]\r\nCommand=Amit\r\n\
										Func=AmitVersion\r\n", output);

	ASSERT_EQ(cmdparser.cmdmap["Command"], "Amit");
	ASSERT_EQ(cmdparser.cmdmap["Func"], "AmitVersion");
}

TEST_F(AmitCommandParserTest, RemoveSpecificCharacters) {

	ret = cmdparser.ParseCommandToCmdMap("[GetAmitVersion]\r\nCommand=Amit\r\n   \
										Func=  \tAmitVersion\r\n", output);

	ASSERT_EQ(cmdparser.cmdmap["Command"], "Amit");
	ASSERT_EQ(cmdparser.cmdmap["Func"], "AmitVersion");
}

TEST_F(AmitCommandParserTest, RemoveCommentString) {

	ret = cmdparser.ParseCommandToCmdMap("[GetAmitPlatformDeviceInfo]\r\n//ThisIsComment1\r\n \
										Command=AmitPlatform   \t//ThisIsComment2\r\n \
										Func=GetDeviceInfo\r\n", output);

	ASSERT_EQ(cmdparser.cmdmap.size(), 2);
	ASSERT_EQ(cmdparser.cmdmap["Command"], "AmitPlatform");
	ASSERT_EQ(cmdparser.cmdmap["Func"], "GetDeviceInfo");
}

TEST_F(AmitCommandParserTest, ParseBatchCommandArea) 
{
	ret = cmdparser.ParseCommandToCmdMap("[GetAmitPlatformDeviceInfo]\r\n//ThisIsComment1\r\n \
										Command=BatchRun//ThisIsComment2\r\n \
										{\r\nReg, 0x0100,  0x00\r\nReg, 0x0200,  0x01\r\n}\r\n\r\n", output);

	ASSERT_EQ(cmdparser.batchlines.size(), 2);
	ASSERT_EQ(cmdparser.batchlines[1], "Reg,0x0200,0x01");
}

TEST_F(AmitCommandParserTest, AvoidInvalidCommand)
{
	ret = cmdparser.ParseCommandToCmdMap("PP123=1dsvv\r\nasfd156\tasdfdszv\r\n\r\n", output);

	ASSERT_EQ(ret, RET_PARSE_COMMAND_FAIL);
}

TEST_F(AmitCommandParserTest, WithoutSectionCommand)
{
	ret = cmdparser.ParseCommandToCmdMap("Command=AmitPlatform \t//ThisIsComment2\r\n \
										Func=GetDeviceInfo\r\n", output);

	ASSERT_EQ(cmdparser.cmdmap["Command"], "AmitPlatform");
	ASSERT_EQ(cmdparser.cmdmap["Func"], "GetDeviceInfo");

}

class AmitCommandMapTest : public Test
{
public:
	int ret = 0;
	AmitCommandParams cmdparams;
	char output[65535]{ 0 };

	void SetUp() override
	{
		cmdparams.AddNewParam("Command", "Amit");
	}
};

TEST_F(AmitCommandMapTest, FindStringParamValue)
{
	string paramvalue;
	ret = cmdparams.FindParamValue("Command", paramvalue, output);

	ASSERT_EQ(paramvalue, "Amit");
}