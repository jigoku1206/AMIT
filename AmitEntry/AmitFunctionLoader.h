#pragma once

#include "../Common/GlobalDefine.h"
#include "../Common/CommonFunction.h"

using namespace std;
using namespace Amit;

#define CMD(x) StrToHashCode(x)

class AmitFunctionLoader
{
private:
	int ret;
	string command;
	AmitCommandParser cmdparser;

	CommonFunction commonfunc;

	int ExcuteCommandFlow(string command, char* output_str)
	{
		switch (CMD(command))
		{
		case CMD("CommonFunc"):
			return commonfunc.AmitCommonFunctionFlow(cmdparser.cmdsection, output_str);
		case CMD("AmitPlatform"):
			//return commonfunc.AmitCommonFunctionFlow(cmdparser.cmdsection, output_str);
		default:
			return WriteOutputMsg(RET_NOT_SUPPORTED_COMMNAD, output_str, "It's note a supported Command: %s\r\n", command.c_str());
		}
	}

public:
	int FunctionFlowEntry(const char* intputstr, char* output_str)
	{
		if (RET_SUCCESS != (ret = cmdparser.ParseCommandToCmdMap(intputstr, output_str)))
			return ret;

		if(RET_SUCCESS != (ret = cmdparser.cmdsection.FindKeyValue("Command", command, output_str)))
			return ret;

		return ExcuteCommandFlow(command, output_str);
	}


};
