// MemoryHackerLib.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"
#include "MemoryHacker.h"
#include <easylogging++.h>

HANDLE GetProcessByWindowName(const WCHAR* wszcWindowName)
{
    // Find our `Game` window. Depending on your language settings, this might be different.
    HWND hGameWindow = FindWindowW(NULL, wszcWindowName);
    // Get the process id for the `Game` process. GetWindowThreadProcessId() does not return a process id, but
    // rather fills a provided variable with its value, hence the &.
    DWORD dwGameProcessId = 0;
    GetWindowThreadProcessId(hGameWindow, &dwGameProcessId);
    // Open our `Game` process. PROCESS_ALL_ACCESS means we can both read and write to the process. However,
    // it also means that this program must be executed as an administrator to work.
    HANDLE hGameProcess = OpenProcess(PROCESS_ALL_ACCESS, true, dwGameProcessId);

    LOG(INFO) << "dwGameProcessId: " << dwGameProcessId;
    LOG(INFO) << "hGameProcess: " << hGameProcess;
    return hGameProcess;
}


HMODULE GetProcessTargetModule(HANDLE hProcess, const WCHAR* wszcTargetModuleName)
{
	HMODULE hModules[1024];
	DWORD cbNeeded = 0;
	if (EnumProcessModules(
			hProcess,
			hModules,
			sizeof(hModules),
			&cbNeeded ) == 0) {
        LOG(ERROR) << "EnumProcessModules() fail";
        return NULL;
    }

    unsigned int cuFoundModules = cbNeeded / sizeof(HMODULE);
    HMODULE hTargetModule = NULL;
    for (int i = 0; i < cuFoundModules; i++)
    {
        WCHAR wszModuleName[1024];
        GetModuleBaseNameW(
            hProcess,
            hModules[i],
            wszModuleName,
            1024
        );
        LOG(TRACE) << "Found module: " << wszModuleName;
        if (wcscmp(wszModuleName, wszcTargetModuleName) == 0)
        {
            hTargetModule = hModules[i];
            break;
        }
    }
    LOG(INFO) << "hTargetModule: " << hTargetModule;
    LOG_IF(hTargetModule == NULL, ERROR) << "Target module is not found";
    return hTargetModule;
}

LPVOID GetProcessTargetModuleBase(HANDLE hProcess, HMODULE hTargetModule)
{
    MODULEINFO targetModuleInfo;
    GetModuleInformation(
        hProcess,
        hTargetModule,
        &targetModuleInfo,
        sizeof(targetModuleInfo));
    LPVOID lpTargetModuleEntryPoint = targetModuleInfo.EntryPoint;

    LOG(INFO) << "lpTargetModuleEntryPoint: " << lpTargetModuleEntryPoint;
    LOG_IF(hTargetModule == NULL, ERROR) << "hTargetModule is NULL";
    return targetModuleInfo.EntryPoint;
}

