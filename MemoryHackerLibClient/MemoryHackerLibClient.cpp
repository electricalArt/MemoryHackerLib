// MemoryHackerLibClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <MemoryHacker.h>
#include <assert.h>

PDWORD32 GetGameMoneyPointer(HANDLE hGameProcess, HMODULE hTargetModule)
{
    //  [[0x017EECB8 + 0x60] + 0xA90] + 0x4
    SIZE_T cbRead = 0;
    DWORD32 dwMoney = 0;
    DWORD32 dwBuff = (DWORD32)((LPBYTE)hTargetModule + 0x017EECB8 + 0x60);
    ReadProcessMemory(hGameProcess,
        (LPCVOID)dwBuff,
        &dwBuff,
        4,
        &cbRead);
    LOG(INFO) << "[0x017EECB8 + 0x60]: " << std::hex << dwBuff;
    ReadProcessMemory(hGameProcess,
        (LPCVOID)(dwBuff + 0xA90),
        &dwBuff,
        4,
        &cbRead);
    LOG(INFO) << "[[0x017EECB8 + 0x60] + 0xA90]: " << std::hex << dwBuff;
    dwBuff += 0x4;
    LOG(INFO) << "[[0x017EECB8 + 0x60] + 0xA90] + 0x4: " << std::hex << dwBuff;
    ReadProcessMemory(hGameProcess,
        (LPCVOID)(dwBuff),
        &dwMoney,
        4,
        &cbRead);
    LOG(INFO) << "dwMoney: " << std::dec << dwMoney;

    return (PDWORD32)dwBuff;
}

// Writes new value to the `Money` memory.
void SetGameMoney(HANDLE hGameProcess, PDWORD32 lpMoney, DWORD32 dwNewMoneyValue)
{
    LOG(INFO) << "New `Money` value: " << dwNewMoneyValue;
    SIZE_T cbWritten = 0;
    WriteProcessMemory(hGameProcess,
        (LPVOID)(lpMoney),
        &dwNewMoneyValue,
        4,
        &cbWritten);
    LOG(INFO) << "cbWritten: " << cbWritten;
}

int main()
{
	ConfigureLoggers("C:\\Users\\musli\\AppData\\Local\\Temp\\MemoryHackerLibClient.log");

	HANDLE hWesnothProcess = GetProcessByWindowName(L"The Battle for Wesnoth - 1.14.9");
    assert(hWesnothProcess);

    PDWORD32 pMoney = GetGameMoneyPointer(hWesnothProcess, NULL);
    SetGameMoney(hWesnothProcess, pMoney, 5000);

	return 0;
}
