#pragma once
#include <cstdio>
#include <cstdarg>
#include "../Common/GlobalDefine.h"

using namespace std;

namespace Amit
{
	static int WriteOutputMsg(int errorcode, char* output, const char* format, ...)
	{
		va_list args1;
		va_start(args1, format);
		std::vsnprintf(output, OUTPUT_MAX, format, args1);
		va_end(args1);
		return errorcode;
	}

	namespace fnv
	{
		constexpr uint64_t _(uint64_t h, const char* s)
		{
			return (*s == 0) ? h :
				_((h * 1099511628211ull) ^ static_cast<uint64_t>(*s), s + 1);
		}
	}
	static constexpr uint64_t StrToHashCode(const char* s)
	{
		return fnv::_(14695981039346656037ull, s);
	}
	static uint64_t StrToHashCode(const std::string& s)
	{
		return fnv::_(14695981039346656037ull, s.data());
	}

	class AmitCommandSection
	{
	private:
		//unordered_map<string, string> keys;

	public:
		vector<string> batchlines;
		unordered_map<string, string> keys;

		void AddNewKey(string keyname, string keyvalue)
		{
			keys[keyname] = keyvalue;
		}

		int FindKeyValue(const char* paramname, string& paramvalue, char* output_str)
		{
			if (keys.find(paramname) != keys.end()) {
				paramvalue = keys[paramname];
				return RET_SUCCESS;
			}
			else
				return WriteOutputMsg(RET_COMMAND_KEY_NOT_FOUND, output_str, "Value=Cannot find the Parameter: '%s'", paramname);
		}
		int FindKeyValue(const char* paramname, int& paramvalue, char* output_str)
		{
			if (keys.find(paramname) != keys.end()) {
				paramvalue = (keys[paramname].find("0x") != keys[paramname].npos) ? stoi(keys[paramname], nullptr, 16) : stoi(keys[paramname], nullptr, 10);
				return RET_SUCCESS;
			}
			else
				return WriteOutputMsg(RET_COMMAND_KEY_NOT_FOUND, output_str, "Value=Cannot find the Parameter: '%s'", paramname);
		}
		int FindKeyValue(const char* paramname, unsigned int& paramvalue, char* output_str)
		{
			if (keys.find(paramname) != keys.end()) {
				paramvalue = (keys[paramname].find("0x") != keys[paramname].npos) ? stoi(keys[paramname], nullptr, 16) : stoi(keys[paramname], nullptr, 10);
				return RET_SUCCESS;
			}
			else
				return WriteOutputMsg(RET_COMMAND_KEY_NOT_FOUND, output_str, "Value=Cannot find the Parameter: '%s'", paramname);
		}
		int FindKeyValue(const char* paramname, double& paramvalue, char* output_str)
		{
			if (keys.find(paramname) != keys.end()) {
				paramvalue = stod(keys[paramname], nullptr);
				return RET_SUCCESS;
			}
			else
				return WriteOutputMsg(RET_COMMAND_KEY_NOT_FOUND, output_str, "Value=Cannot find the Parameter: '%s'", paramname);
		}
	};

	class AmitLogger
	{

	};

	class CommonFunction
	{
	public:
		int AmitCommonFunctionFlow(AmitCommandSection& cmdsection, char* output_str)
		{

			return WriteOutputMsg(RET_FAIL, output_str, "AmitCommonFunctionFlow!!!\r\n");
		}
	};
}