#pragma once

#include "framework.h"
#include <stdio.h>
#include <windows.h>
#include <psapi.h>
#include <wchar.h>
#include <easylogging++.h>


/*F+F+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Function: ConfigureLoggers()

  Summary:  Configures each loggers with default settings.

  Args:     void

  Returns:  void
-----------------------------------------------------------------F-F*/
void ConfigureLoggers(const char* szcLogFileFullName);

/*F+F+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Function: GetProcessByWindowName()

  Summary:  Searches for process with given windows name and returns it.

  Args:     wszcWindowName - name of desired window.

  Returns:  `HANDLE` to found process. If function fails, it returns NULL.
-----------------------------------------------------------------F-F*/
HANDLE GetProcessByWindowName(const WCHAR* wszcWindowName);

/*F+F+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Function: GetProcessTargetModule()

  Summary:  Searches for module with given name within given proces.

  Args:     hProcess - `HANDLE` to process.
			wszcTargetModuleName - name of desired module.

  Returns:  `HMODULE` to found module. If function fails, it returns NULL.
-----------------------------------------------------------------F-F*/
HMODULE GetProcessTargetModule(HANDLE hProcess, const WCHAR* wszcTargetModuleName);

/*F+F+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Function: GetProcessTargetModuleBase()
  Summary:  

  Args:    

  Returns:  `LPVOID` to module base. Basically it is the same pointer
			as `hTargetModule`.
-----------------------------------------------------------------F-F*/
LPVOID GetProcessTargetModuleBase(HANDLE hProcess, HMODULE hTargetModule);
