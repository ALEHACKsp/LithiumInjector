#pragma once

class cHooks {
public:
	bool Initialize(unsigned long);
	bool Inject(char[]);

	bool RemoveVacHooks();
	bool RestoreVacHooks();

private:
	bool RemoveHook(const char*, const char*, char*);
	bool RestoreHook(const char*, const char*, char*);

	char PreviousBytes[17][6];
	void* ProcessHandle = 0;
	unsigned long ProcessID = 0;
};

extern cHooks* Hooks;