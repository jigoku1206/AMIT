#pragma once
#include <cstdio>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include "GlobalDefine.h"

using namespace std;

namespace Amit
{
	struct CmdSection
	{
		CmdSection(string sectionname)
		{
			section_name = sectionname;
		}
		string section_name;
		unordered_map<string, string> cmdmap;
	};

	class AmitCommandParser
	{
	private:


	public:
		vector<CmdSection> cmdcollection;
		vector<string> cmdlines;
		vector<string> batchlines;

		int ParseCommandToCmdMap(char* inputstr, const char* outputstr)
		{
			string cmdstr(inputstr);
			ParseCommandStrToCommandLines(cmdstr);
			cmdlines = RemoveAllCommentString();
			FindCommandSectionNames();



			return RET_SUCCESS;
		}

	private:
		int commandcount = -1;
		//string batchstring;
		bool isBatchArea = false;

		void ParseCommandStrToCommandLines(const string& cmdstr)
		{
			istringstream in(cmdstr);
			string line;
			while (getline(in, line, '\n'))
			{
				RemoveCharacterFromString(line, ' ');
				RemoveCharacterFromString(line, '\r');
				RemoveCharacterFromString(line, '\t');
				cmdlines.push_back(line);
			}
		}
		void RemoveCharacterFromString(string& strline, char removedchar)
		{
			strline.erase(std::remove(strline.begin(), strline.end(), removedchar), strline.end());
		}
		vector<string> RemoveAllCommentString()
		{
			vector<string> new_cmdlines;
			for (auto strline : cmdlines)
			{
				strline = RemoveCommentString(strline);
				if (!strline.empty())
					new_cmdlines.push_back(RemoveCommentString(strline));
			}
			return new_cmdlines;
		}
		string RemoveCommentString(string strline)
		{
			return strline.substr(0, strline.find("//"));
		}
		void FindCommandSectionNames()
		{
			for (auto strline : cmdlines) {
				if (strline.at(0) == '[' && strline.back() == ']') {
					cmdcollection.push_back(CmdSection(strline));
					commandcount++;
				}
				else if (strline.at(0) == '{' || isBatchArea)
				{
					isBatchArea = strline.back() == '}' ? false : true;
					if(isBatchArea)batchlines.push_back(strline);
				}
				else {
					GetCommandKeys(strline);
				}
			}
			if (!batchlines.empty()) batchlines.erase(batchlines.begin());
			
		}
		void GetCommandKeys(string strline)
		{
			string keyname = strline.substr(0, strline.find("="));
			string keyvalue = strline.substr(strline.find("=") + 1, strline.length() - strline.find("="));
			cmdcollection[commandcount].cmdmap[keyname] = keyvalue;
		}

	};


}