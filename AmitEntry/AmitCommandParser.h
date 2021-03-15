#pragma once

#ifdef AMITENTRY_EXPORTS
#define AMIT_API __declspec(dllexport)
#else
#define AMIT_API __declspec(dllimport)
#endif // !AMITENTRY_EXPORTS


#include <cstdio>
#include <cstdarg>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include "../Common/GlobalDefine.h"
#include "../Common/CommonFunction.h"

using namespace std;

namespace Amit
{
	class AmitCommandParams
	{
	private:
		unordered_map<string, string> params;

	public:
		void AddNewParam(string keyname, string keyvalue)
		{
			params[keyname] = keyvalue;
		}

		int FindParamValue(const char* paramname, string& paramvalue, char* output_str)
		{
			if (params.find(paramname) != params.end()) {
				paramvalue = params[paramname];
				return RET_SUCCESS;
			}
			else
				return WriteOutputMsg(RET_COMMAND_KEY_NOT_FOUND, output_str, "Value=Cannot find the Parameter: '%s'", paramname);
		}
	};

	class AMIT_API AmitCommandParser
	{
	private:
		int ret = -1;

	public:
		unordered_map<string, string> cmdmap;
		vector<string> cmdlines;
		vector<string> batchlines;

		int ParseCommandToCmdMap(const char* inputstr, char* outputstr);

	private:
		int commandcount = -1;
		bool isBatchArea = false;

		void ParseCommandStrToCommandLines(const string& cmdstr);
		void RemoveCharacterFromString(string& strline, char removedchar);
		void RemoveSpecificCharacters(string& strline);
		void RemoveAllCommentString(vector<string>& cmdlines);
		string RemoveCommentString(string strline);
		int ParseCommandSectionArea(char* output);
		bool IsCommandSection(string strline);
		bool IsBatchCommandArea(string strline);
		bool IsCommandKeys(string strline);
		void GetBatchCommands(string strline);
		void GetCommandKeys(string strline);
	};
}