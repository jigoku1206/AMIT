#pragma once

#define OUTPUT_MAX 65535

namespace Amit {

	enum AMIT_ERRORCODE
	{
		RET_FAIL,
		RET_SUCCESS,

		RET_PARSE_COMMAND_FAIL,
		RET_COMMAND_KEY_NOT_FOUND
	};

}