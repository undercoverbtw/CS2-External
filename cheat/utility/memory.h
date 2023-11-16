#pragma once
#include "../includes.h"

class Memory
{
private:
	DWORD process_id = 0; // id of proccess
	HANDLE process_module = NULL; // handle to process

public:
	Memory(const char* processName);
	~Memory();

	DWORD GetProcessId();
	HANDLE GetProcessHandle();

	uintptr_t GetModuleAdress(const char* moduleName);

	template <typename T>
	T Read(uintptr_t adress)
	{
		T value;
		ReadProcessMemory(this->process_module, (LPCVOID)adress, &value, sizeof(T), NULL);
		return value;
	}
	
	template <typename T>
	bool Write(uintptr_t adress, T value)
	{
		return WriteProcessMemory(this->process_module, (LPVOID)adress, &value, sizeof(T), NULL);
	}

};

