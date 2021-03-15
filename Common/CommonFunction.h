#pragma once
#include <cstdio>
#include <cstdarg>
#include "../Common/GlobalDefine.h"

namespace Amit
{
	static int WriteOutputMsg(AMIT_ERRORCODE errorcode, char* output, const char* format, ...)
	{
		va_list args1;
		va_start(args1, format);
		std::vsnprintf(output, OUTPUT_MAX, format, args1);
		va_end(args1);
		return errorcode;
	}

}