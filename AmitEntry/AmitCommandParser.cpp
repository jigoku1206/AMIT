#include "pch.h"
#include "Amit.h"

using namespace Amit;


int AMIT_API AmitCommandParser::ParseCommandToCmdMap(const char* inputstr, char* outputstr)
{
	string cmdstr(inputstr);
	ParseCommandStrToCommandLines(cmdstr);
	RemoveAllCommentString(cmdlines);
	return ParseCommandSectionArea(outputstr);
}

void AMIT_API AmitCommandParser::ParseCommandStrToCommandLines(const string& cmdstr)
{
	istringstream in(cmdstr);
	string line;

	while (getline(in, line, '\n'))
	{
		RemoveSpecificCharacters(line);
		cmdlines.push_back(line);
	}
}
void AMIT_API AmitCommandParser::RemoveCharacterFromString(string& strline, char removedchar)
{
	strline.erase(std::remove(strline.begin(), strline.end(), removedchar), strline.end());
}
void AMIT_API AmitCommandParser::RemoveSpecificCharacters(string& strline)
{
	char specificletter[]{ ' ', '\r', '\t' };

	for (auto letter : specificletter)
		RemoveCharacterFromString(strline, letter);
}
void AMIT_API AmitCommandParser::RemoveAllCommentString(vector<string>& cmdlines)
{
	vector<string> new_cmdlines;
	for (auto strline : cmdlines)
	{
		strline = RemoveCommentString(strline);
		if (!strline.empty())
			new_cmdlines.push_back(strline);
	}
	cmdlines = new_cmdlines;
}
string AMIT_API AmitCommandParser::RemoveCommentString(string strline)
{
	return strline.substr(0, strline.find("//"));
}
int AMIT_API AmitCommandParser::ParseCommandSectionArea(char* output)
{
	for (auto strline : cmdlines) {
		if (IsCommandSection(strline))	continue;
		else if (IsBatchCommandArea(strline))	GetBatchCommands(strline);
		else if (IsCommandKeys(strline))	GetCommandKeys(strline);
		else
			return WriteOutputMsg(RET_PARSE_COMMAND_FAIL, output, "Parse Command Fail\r\n");
	}
	if (!cmdsection.batchlines.empty()) cmdsection.batchlines.erase(cmdsection.batchlines.begin());

	return WriteOutputMsg(RET_SUCCESS, output, "Parse Command PASS\r\n");
}
bool AMIT_API AmitCommandParser::IsCommandSection(string strline)
{
	return strline.at(0) == '[' && strline.back() == ']' ? true : false;
}
bool AMIT_API AmitCommandParser::IsBatchCommandArea(string strline)
{
	return strline.at(0) == '{' || isBatchArea ? true : false;
}
bool AMIT_API AmitCommandParser::IsCommandKeys(string strline)
{
	return strline.find("=") != strline.npos ? true : false;
}
void AMIT_API AmitCommandParser::GetBatchCommands(string strline)
{
	isBatchArea = strline.back() == '}' ? false : true;
	if (isBatchArea)cmdsection.batchlines.push_back(strline);
}
void AMIT_API AmitCommandParser::GetCommandKeys(string strline)
{
	string keyname = strline.substr(0, strline.find("="));
	string keyvalue = strline.substr(strline.find("=") + 1, strline.length() - strline.find("="));
	cmdsection.AddNewKey(keyname, keyvalue);
}
