#include "memory.h"
#include <TlHelp32.h>

Memory::Memory(const char* processName)
{
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	const auto snapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	while (Process32Next(snapShot, &entry))
	{
		if (!strcmp(processName, entry.szExeFile))
		{
			this->process_id = entry.th32ProcessID;
			this->process_module = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->process_id);
			break;
		}

	}

	if (snapShot)
		CloseHandle(snapShot);
}
	


Memory::~Memory()
{
	if (this->process_module)
		CloseHandle(this->process_module);

}

DWORD Memory::GetProcessId()
{
	return this->process_id;
}

HANDLE Memory::GetProcessHandle()
{
	return this->process_module;
}

uintptr_t Memory::GetModuleAdress(const char* moduleName)
{
	MODULEENTRY32 entry;
	entry.dwSize = sizeof(MODULEENTRY32);

	const auto snapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, this->process_id);

	uintptr_t result = 0;

	while (Module32Next(snapShot, &entry))
	{
		if (!strcmp(moduleName, entry.szModule))
		{
			result = reinterpret_cast<uintptr_t>(entry.modBaseAddr);
			break;
		}
	}

	if (snapShot)
		CloseHandle(snapShot);

	return result;
}