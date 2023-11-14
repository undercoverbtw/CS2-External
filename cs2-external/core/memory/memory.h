#ifndef _PPROCESS_HPP_
#define _PPROCESS_HPP_

#include <vector>
#include <math.h>
#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include <iostream>
#include <Psapi.h> 

struct process_module
{
    uintptr_t base, size;
};

class memory
{
public:
    DWORD process_id; // process id
    HANDLE handle; // handle to process
    HWND hwnd; // window handle
    process_module base_client;

public:
    bool attach_process(const char* process_name);
    bool attach_process_hj(const char* process_name);
    void close();

public:
    process_module get_module(const char* module_name);
    LPVOID allocate(size_t size_in_bytes);
    uintptr_t find_code_cave(uint32_t length_in_bytes);
    uintptr_t find_signature(std::vector<uint8_t> signature);
    uintptr_t find_signature(process_module target_module, std::vector<uint8_t> signature);

    template<class T>
    uintptr_t read_offset_from_signature(std::vector<uint8_t> signature, uint8_t offset) // offset example: "FF 05 ->22628B01<-" offset is 2
    {
        uintptr_t pattern_address = this->find_signature(signature);
        if (!pattern_address)
            return 0x0;

        T offset_value = this->read<T>(pattern_address + offset);
        return pattern_address + offset_value + offset + sizeof(T);
    }

    bool read_raw(uintptr_t address, void* buffer, size_t size)
    {
        SIZE_T bytesRead;
        if (ReadProcessMemory(this->handle, reinterpret_cast<LPCVOID>(address), buffer, size, &bytesRead))
        {
            return bytesRead == size;
        }
        return false;
    }

    template<class T>
    void write(uintptr_t address, T value)
    {
        WriteProcessMemory(handle, (void*)address, &value, sizeof(T), 0);
    }

    template<class T>
    T read(uintptr_t address)
    {
        T buffer{};
        ReadProcessMemory(handle, (void*)address, &buffer, sizeof(T), 0);
        return buffer;
    }

    void write_bytes(uintptr_t addr, std::vector<uint8_t> patch)
    {
        WriteProcessMemory(handle, (void*)addr, &patch[0], patch.size(), 0);
    }

    uintptr_t read_multi_address(uintptr_t ptr, std::vector<uintptr_t> offsets)
    {
        uintptr_t buffer = ptr;
        for (int i = 0; i < offsets.size(); i++)
            buffer = this->read<uintptr_t>(buffer + offsets[i]);

        return buffer;
    }

    template <typename T>
    T read_multi(uintptr_t base, std::vector<uintptr_t> offsets) {
        uintptr_t buffer = base;
        for (int i = 0; i < offsets.size() - 1; i++)
        {
            buffer = this->read<uintptr_t>(buffer + offsets[i]);
        }
        return this->read<T>(buffer + offsets.back());
    }

private:
    uint32_t find_process_id_by_process_name(const char* process_name);
    uint32_t find_process_id_by_window_name(const char* window_name);
    HWND get_window_handle_from_process_id(DWORD ProcessId);
};

#endif
