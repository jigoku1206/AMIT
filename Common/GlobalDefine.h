#pragma once

#define OUTPUT_MAX 65535
#define RET_SUCCESS_STR "Ret=SUCCESS\r\n"
#define RET_FAIL_STR "Ret=FAIL\r\n"

namespace Amit {

	enum AMIT_ERRORCODE
	{
		RET_FAIL,
		RET_SUCCESS,

		RET_PARSE_COMMAND_FAIL,
		RET_COMMAND_KEY_NOT_FOUND,
		RET_NOT_SUPPORTED_COMMNAD,
		RET_NOT_SUPPORTED_FUNCTION,

		RET_GET_VERSION_INFO_FAIL
	};

}