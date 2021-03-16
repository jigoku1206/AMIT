#include "pch.h"
#include "Amit.h"

using namespace testing;
using namespace Amit;

#pragma region AmitCommandParserTest
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

	ASSERT_EQ(cmdparser.cmdsection.keys["Command"], "Amit");
	ASSERT_EQ(cmdparser.cmdsection.keys["Func"], "AmitVersion");
}

TEST_F(AmitCommandParserTest, RemoveSpecificCharacters) {

	ret = cmdparser.ParseCommandToCmdMap("[GetAmitVersion]\r\nCommand=Amit\r\n   \
										Func=  \tAmitVersion\r\n", output);

	ASSERT_EQ(cmdparser.cmdsection.keys["Command"], "Amit");
	ASSERT_EQ(cmdparser.cmdsection.keys["Func"], "AmitVersion");
}

TEST_F(AmitCommandParserTest, RemoveCommentString) {

	ret = cmdparser.ParseCommandToCmdMap("[GetAmitPlatformDeviceInfo]\r\n//ThisIsComment1\r\n \
										Command=AmitPlatform   \t//ThisIsComment2\r\n \
										Func=GetDeviceInfo\r\n", output);

	ASSERT_EQ(cmdparser.cmdsection.keys.size(), 2);
	ASSERT_EQ(cmdparser.cmdsection.keys["Command"], "AmitPlatform");
	ASSERT_EQ(cmdparser.cmdsection.keys["Func"], "GetDeviceInfo");
}

TEST_F(AmitCommandParserTest, ParseBatchCommandArea) 
{
	ret = cmdparser.ParseCommandToCmdMap("[GetAmitPlatformDeviceInfo]\r\n//ThisIsComment1\r\n \
										Command=BatchRun//ThisIsComment2\r\n \
										{\r\nReg, 0x0100,  0x00\r\nReg, 0x0200,  0x01\r\n}\r\n\r\n", output);

	ASSERT_EQ(cmdparser.cmdsection.batchlines.size(), 2);
	ASSERT_EQ(cmdparser.cmdsection.batchlines[1], "Reg,0x0200,0x01");
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

	ASSERT_EQ(cmdparser.cmdsection.keys["Command"], "AmitPlatform");
	ASSERT_EQ(cmdparser.cmdsection.keys["Func"], "GetDeviceInfo");

}
#pragma endregion

#pragma region AmitCommandMapTest
class AmitCommandMapTest : public Test
{
public:
	int ret = 0;
	AmitCommandSection cmdsection;
	char output[65535]{ 0 };

	void SetUp() override
	{
		cmdsection.AddNewKey("Command", "Amit");
	}
};

TEST_F(AmitCommandMapTest, AddSameKeyNameToCommandSection)
{
	string paramvalue;
	cmdsection.AddNewKey("Command", "NewAmit");
	ret = cmdsection.FindKeyValue("Command", paramvalue, output);
	ASSERT_NE(paramvalue, "Amit");
	ASSERT_EQ(paramvalue, "NewAmit");
}

TEST_F(AmitCommandMapTest, FindStringParamValue)
{
	string paramvalue;
	ret = cmdsection.FindKeyValue("Command", paramvalue, output);

	ASSERT_EQ(paramvalue, "Amit");
}

TEST_F(AmitCommandMapTest, FindIntegerParamValue)
{
	int paramvalue;
	cmdsection.AddNewKey("IntParam", "123");
	ret = cmdsection.FindKeyValue("IntParam", paramvalue, output);

	ASSERT_EQ(paramvalue, 123);
}

TEST_F(AmitCommandMapTest, FindHexParamValue)
{
	int paramvalue;
	cmdsection.AddNewKey("HexParam", "0x0016");
	ret = cmdsection.FindKeyValue("HexParam", paramvalue, output);

	ASSERT_EQ(paramvalue, 0x16);
}

TEST_F(AmitCommandMapTest, FindUnsignedIntegerParamValue)
{
	unsigned int paramvalue;
	cmdsection.AddNewKey("IntParam2", "0x0032");
	ret = cmdsection.FindKeyValue("IntParam2", paramvalue, output);
	ASSERT_EQ(paramvalue, 0x032);
}

TEST_F(AmitCommandMapTest, FindDoubleParamValue)
{
	double paramvalue;
	cmdsection.AddNewKey("HexParam", "1.000001");
	ret = cmdsection.FindKeyValue("HexParam", paramvalue, output);

	ASSERT_EQ(paramvalue, 1.000001);
}
#pragma endregion

#pragma region AmitFunctionLoaderTest
class AmitFunctionLoaderTest : public Test
{
public:
	int ret = 0;
	AmitFunctionLoader funcloader;
	char output[65535]{ 0 };
	//AmitCommandSection cmdsection;

	void SetUp() override
	{
		//cmdsection.AddNewKey("Command", "NotSupported");
		//cmdsection.AddNewKey("Function", "GetAmitVersion");
	}
};

TEST_F(AmitFunctionLoaderTest, SetAInvalidCommand)
{
	ret = funcloader.FunctionFlowEntry("Command=NotSupported\r\n", output);

	ASSERT_EQ(ret, RET_NOT_SUPPORTED_COMMNAD) << output;
}

#pragma endregion