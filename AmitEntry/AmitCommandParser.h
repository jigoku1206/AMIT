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
	class AMIT_API AmitCommandParser
	{
	public:
		AmitCommandSection cmdsection;
		vector<string> cmdlines;

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