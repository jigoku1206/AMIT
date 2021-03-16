// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "../Common/GlobalDefine.h"
#include "Amit.h"

using namespace Amit;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

int _stdcall AmitEntry(const char* intputstr, char* outputstr)
{
    int ret = RET_FAIL;
    AmitFunctionLoader funcloader;

	return (RET_SUCCESS == (ret = funcloader.FunctionFlowEntry(intputstr, outputstr))) ?
             WriteOutputMsg(ret, outputstr, RET_SUCCESS_STR"%s", string(outputstr).c_str()) :
             WriteOutputMsg(ret, outputstr, RET_FAIL_STR"%s", string(outputstr).c_str());
}