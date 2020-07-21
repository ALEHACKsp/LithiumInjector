#include <Windows.h>

#include "Hooks.h"

#define Size sizeof(char) * 6

bool cHooks::Initialize(unsigned long ID) {
	this->ProcessID = ID;
	this->ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, 0, this->ProcessID);

	return true;
}

bool cHooks::Inject(char DllPath[]) {
	void* LoadLib		= GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
	void* Allocation	= VirtualAllocEx(this->ProcessHandle, 0, strlen(DllPath), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

	WriteProcessMemory(this->ProcessHandle, Allocation, DllPath, strlen(DllPath), 0);
	CreateRemoteThread(this->ProcessHandle, 0, 0, (LPTHREAD_START_ROUTINE)LoadLib, (LPVOID)Allocation, 0, 0);
	CloseHandle(this->ProcessHandle);

	return true;
}

bool cHooks::RemoveVacHooks() {
	RemoveHook("LoadLibraryExW",	"kernel32",		this->PreviousBytes[0]);
	RemoveHook("VirtualAlloc",		"kernel32",		this->PreviousBytes[1]);
	RemoveHook("FreeLibrary",		"kernel32",		this->PreviousBytes[2]);
	RemoveHook("LoadLibraryExA",	"kernel32",		this->PreviousBytes[3]);
	RemoveHook("LoadLibraryW",		"kernel32",		this->PreviousBytes[4]);
	RemoveHook("LoadLibraryA",		"kernel32",		this->PreviousBytes[5]);
	RemoveHook("VirtualAllocEx",	"kernel32",		this->PreviousBytes[6]);
	RemoveHook("LdrLoadDll",		"ntdll",		this->PreviousBytes[7]);
	RemoveHook("NtOpenFile",		"ntdll",		this->PreviousBytes[8]);
	RemoveHook("VirtualProtect",	"kernel32",		this->PreviousBytes[9]);
	RemoveHook("CreateProcessW",	"kernel32",		this->PreviousBytes[10]);
	RemoveHook("CreateProcessA",	"kernel32",		this->PreviousBytes[11]);
	RemoveHook("VirtualProtectEx",	"kernel32",		this->PreviousBytes[12]);
	RemoveHook("FreeLibrary",		"KernelBase",	this->PreviousBytes[13]);
	RemoveHook("LoadLibraryExA",	"KernelBase",	this->PreviousBytes[14]);
	RemoveHook("LoadLibraryExW",	"KernelBase",	this->PreviousBytes[15]);
	RemoveHook("ResumeThread",		"KernelBase",	this->PreviousBytes[16]);

	return true;
}

bool cHooks::RestoreVacHooks() {
	RestoreHook("LoadLibraryExW",	"kernel32",		this->PreviousBytes[0]);
	RestoreHook("VirtualAlloc",		"kernel32",		this->PreviousBytes[1]);
	RestoreHook("FreeLibrary",		"kernel32",		this->PreviousBytes[2]);
	RestoreHook("LoadLibraryExA",	"kernel32",		this->PreviousBytes[3]);
	RestoreHook("LoadLibraryW",		"kernel32",		this->PreviousBytes[4]);
	RestoreHook("LoadLibraryA",		"kernel32",		this->PreviousBytes[5]);
	RestoreHook("VirtualAllocEx",	"kernel32",		this->PreviousBytes[6]);
	RestoreHook("LdrLoadDll",		"ntdll",		this->PreviousBytes[7]);
	RestoreHook("NtOpenFile",		"ntdll",		this->PreviousBytes[8]);
	RestoreHook("VirtualProtect",	"kernel32",		this->PreviousBytes[9]);
	RestoreHook("CreateProcessW",	"kernel32",		this->PreviousBytes[10]);
	RestoreHook("CreateProcessA",	"kernel32",		this->PreviousBytes[11]);
	RestoreHook("VirtualProtectEx",	"kernel32",		this->PreviousBytes[12]);
	RestoreHook("FreeLibrary",		"KernelBase",	this->PreviousBytes[13]);
	RestoreHook("LoadLibraryExA",	"KernelBase",	this->PreviousBytes[14]);
	RestoreHook("LoadLibraryExW",	"KernelBase",	this->PreviousBytes[15]);
	RestoreHook("ResumeThread",		"KernelBase",	this->PreviousBytes[16]);

	return true;
}

bool cHooks::RemoveHook(const char* FunctionName, const char* ModuleName, char* PreviousBytes) {
	char* OriginalHookBytes[6];
	char* OriginalFunctionBytes[6];
	void* FunctionAddress = GetProcAddress(LoadLibraryA(ModuleName), FunctionName);
	
	ReadProcessMemory(this->ProcessHandle, FunctionAddress, OriginalHookBytes, Size, 0);
	memcpy_s(PreviousBytes, Size, OriginalHookBytes, Size);
	memcpy_s(OriginalFunctionBytes, Size, FunctionAddress, Size);

	return WriteProcessMemory(this->ProcessHandle, FunctionAddress, OriginalFunctionBytes, Size, 0);
}

bool cHooks::RestoreHook(const char* FunctionName, const char* ModuleName, char* PreviousBytes) {
	void* FunctionAddress = GetProcAddress(LoadLibraryA(ModuleName), FunctionName);
	return WriteProcessMemory(this->ProcessHandle, FunctionAddress, PreviousBytes, Size, 0);
}

cHooks* Hooks = new cHooks();