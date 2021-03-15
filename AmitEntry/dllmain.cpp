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
    AmitCommandParser cmdparser;
    
    if(RET_SUCCESS != (ret = cmdparser.ParseCommandToCmdMap(intputstr, outputstr))) return ret;
    


    return RET_SUCCESS;
}