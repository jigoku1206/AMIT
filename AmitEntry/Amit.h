#pragma once

#ifdef AMITENTRY_EXPORTS
#define AMIT_API __declspec(dllexport)
#else
#define AMIT_API __declspec(dllimport)
#endif // !AMITENTRY_EXPORTS



#include "../Common/GlobalDefine.h"
#include "AmitCommandParser.h"