#include <Windows.h>
#include <string>
#include <iostream>
#include <TlHelp32.h>

#include "Hooks.h"

void GetProcessID(const char* Process, DWORD& ProcessID) {
	HANDLE ProcessSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 ProcessEntry;
	ProcessEntry.dwSize = sizeof(PROCESSENTRY32);
	Process32First(ProcessSnapshot, &ProcessEntry);
	do {
		if (!strcmp(ProcessEntry.szExeFile, Process)) {
			ProcessID = ProcessEntry.th32ProcessID;
		}
	} while (Process32Next(ProcessSnapshot, &ProcessEntry));
	CloseHandle(ProcessSnapshot);
}

int main() {
	unsigned long ProcessID;
	char InjectorPath[MAX_PATH];
	char DllPath[MAX_PATH];
	std::string DllName;

	SetConsoleTitleA("LithiumInjector");

	std::cout << "LithiumInjector\n\n";
	std::cout << "Provide DLL name (with .dll): "; std::cin >> DllName;

	DllName.insert(0, "\\");

	GetCurrentDirectoryA(sizeof(InjectorPath), InjectorPath);
	strncpy(DllPath, InjectorPath, sizeof(DllPath));
	strncat(DllPath, DllName.c_str(), sizeof(DllPath));

	GetProcessID("csgo.exe", ProcessID);

	Hooks->Initialize(ProcessID);
	Hooks->RemoveVacHooks();
	Hooks->Inject(DllPath);
	Hooks->RestoreVacHooks();
}