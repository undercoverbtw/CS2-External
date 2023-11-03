#include "memory.h"
#include <tlhelp32.h>
#include "../hijacking/hijacking.h"

uint32_t memory::find_process_id_by_process_name(const char* process_name)
{
    std::wstring wide_process_name;
    int wide_char_length = MultiByteToWideChar(CP_UTF8, 0, process_name, -1, nullptr, 0);
    if (wide_char_length > 0)
    {
        wide_process_name.resize(wide_char_length);
        MultiByteToWideChar(CP_UTF8, 0, process_name, -1, &wide_process_name[0], wide_char_length);
    }

    HANDLE h_pid = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    PROCESSENTRY32W process_entry_{};
    process_entry_.dwSize = sizeof(PROCESSENTRY32W);

    uint32_t pid = 0;
    if (Process32FirstW(h_pid, &process_entry_))
    {
        do
        {
            if (!wcscmp(process_entry_.szExeFile, wide_process_name.c_str()))
            {
                pid = process_entry_.th32ProcessID;
                break;
            }
        } while (Process32NextW(h_pid, &process_entry_));
    }
    CloseHandle(h_pid);
    return pid;
}

uint32_t memory::find_process_id_by_window_name(const char* window_name)
{
    DWORD process_id = 0;
    HWND window_handle = FindWindowA(nullptr, window_name);
    if (window_handle)
        GetWindowThreadProcessId(window_handle, &process_id);
    return process_id;
}

HWND memory::get_window_handle_from_process_id(DWORD process_id)
{
    HWND hwnd = NULL;
    do
    {
        hwnd = FindWindowEx(NULL, hwnd, NULL, NULL);
        DWORD pid = 0;
        GetWindowThreadProcessId(hwnd, &pid);
        if (pid == process_id)
        {
            TCHAR window_title[MAX_PATH];
            GetWindowText(hwnd, window_title, MAX_PATH);
            if (IsWindowVisible(hwnd) && window_title[0] != '\0')
            {
                return hwnd;
            }
        }
    } while (hwnd != NULL);
    return NULL; // No main window found for the given process ID
}

bool memory::attach_process(const char* process_name)
{
    this->process_id = find_process_id_by_process_name(process_name);

    if (process_id)
    {
        HMODULE modules[0xFF];
        MODULEINFO module_info;
        DWORD _;

        handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, process_id);

        EnumProcessModulesEx(this->handle, modules, sizeof(modules), &_, LIST_MODULES_64BIT);
        base_client.base = (uintptr_t)modules[0];

        GetModuleInformation(this->handle, modules[0], &module_info, sizeof(module_info));
        base_client.size = module_info.SizeOfImage;

        hwnd = get_window_handle_from_process_id(process_id);

        return true;
    }

    return false;
}

bool memory::attach_process_hj(const char* process_name)
{
    this->process_id = find_process_id_by_process_name(process_name);

    if (process_id)
    {
        HMODULE modules[0xFF];
        MODULEINFO module_info;
        DWORD _;

        // Using Apxaey's handle hijack function to safely open a handle
        handle = hj::HijackExistingHandle(process_id);

        if (!hj::IsHandleValid(handle))
        {
            std::cout << "[cheat] Handle Hijack failed, falling back to OpenProcess method." << std::endl;
            return attach_process(process_name); // Handle hijacking failed, so we fall back to the normal OpenProcess method
        }

        EnumProcessModulesEx(this->handle, modules, sizeof(modules), &_, LIST_MODULES_64BIT);
        base_client.base = (uintptr_t)modules[0];

        GetModuleInformation(this->handle, modules[0], &module_info, sizeof(module_info));
        base_client.size = module_info.SizeOfImage;

        hwnd = get_window_handle_from_process_id(process_id);

        return true;
    }

    return false;
}

bool memory::attach_window(const char* window_name)
{
    this->process_id = find_process_id_by_window_name(window_name);

    if (process_id)
    {
        HMODULE modules[0xFF];
        MODULEINFO module_info;
        DWORD _;

        handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, process_id);

        EnumProcessModulesEx(this->handle, modules, sizeof(modules), &_, LIST_MODULES_64BIT);
        base_client.base = (uintptr_t)modules[0];

        GetModuleInformation(this->handle, modules[0], &module_info, sizeof(module_info));
        base_client.size = module_info.SizeOfImage;

        hwnd = get_window_handle_from_process_id(process_id);

        return true;
    }
    return false;
}

bool memory::update_hwnd()
{
    hwnd = get_window_handle_from_process_id(process_id);
    return hwnd == nullptr;
}

process_module memory::get_module(const char* l_module)
{
    std::wstring wide_module;
    int wide_char_length = MultiByteToWideChar(CP_UTF8, 0, l_module, -1, nullptr, 0);
    if (wide_char_length > 0)
    {
        wide_module.resize(wide_char_length);
        MultiByteToWideChar(CP_UTF8, 0, l_module, -1, &wide_module[0], wide_char_length);
    }

    HANDLE handlemodule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, process_id);
    MODULEENTRY32W module_entry_{};
    module_entry_.dwSize = sizeof(MODULEENTRY32W);

    do
    {
        if (!wcscmp(module_entry_.szModule, wide_module.c_str()))
        {
            CloseHandle(handlemodule);
            return { (DWORD_PTR)module_entry_.modBaseAddr, module_entry_.dwSize };
        }
    } while (Module32NextW(handlemodule, &module_entry_));

    CloseHandle(handlemodule);
    return { 0, 0 };
}

LPVOID memory::allocate(size_t size_in_bytes)
{
    return VirtualAllocEx(this->handle, NULL, size_in_bytes, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
}

uintptr_t memory::find_signature(std::vector<uint8_t> signature)
{
    std::unique_ptr<uint8_t[]> data;
    data = std::make_unique<uint8_t[]>(this->base_client.size);

    if (!ReadProcessMemory(this->handle, (void*)(this->base_client.base), data.get(), this->base_client.size, NULL)) {
        return 0x0;
    }

    for (uintptr_t i = 0; i < this->base_client.size; i++)
    {
        for (uintptr_t j = 0; j < signature.size(); j++)
        {
            if (signature.at(j) == 0x00)
                continue;

            if (*reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(&data[i + j])) == signature.at(j))
            {
                if (j == signature.size() - 1)
                    return this->base_client.base + i;
                continue;
            }
            break;
        }
    }
    return 0x0;
}

uintptr_t memory::find_signature(process_module target_module, std::vector<uint8_t> signature)
{
    std::unique_ptr<uint8_t[]> data;
    data = std::make_unique<uint8_t[]>(0xFFFFFFF);

    if (!ReadProcessMemory(this->handle, (void*)(target_module.base), data.get(), 0xFFFFFFF, NULL)) {
        return NULL;
    }

    for (uintptr_t i = 0; i < 0xFFFFFFF; i++)
    {
        for (uintptr_t j = 0; j < signature.size(); j++)
        {
            if (signature.at(j) == 0x00)
                continue;

            if (*reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(&data[i + j])) == signature.at(j))
            {
                if (j == signature.size() - 1)
                    return this->base_client.base + i;
                continue;
            }
            break;
        }
    }
    return 0x0;
}

uintptr_t memory::find_code_cave(uint32_t length_in_bytes)
{
    std::vector<uint8_t> cave_pattern = {};

    for (uint32_t i = 0; i < length_in_bytes; i++) {
        cave_pattern.push_back(0x00);
    }

    return find_signature(cave_pattern);
}

void memory::close()
{
    CloseHandle(handle);
}
