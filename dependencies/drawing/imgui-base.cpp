#include "imgui-base.h"
#include <more/bytes.hpp>
/****************************************************
* Copyright (C)	: Liv
* @file			: OS-ImGui_Base.cpp
* @author		: Liv
* @email		: 1319923129@qq.com
* @version		: 1.0
* @date			: 2023/6/18	11:21
****************************************************/

namespace drawing
{
    bool drawing_Base::InitImGui(ID3D11Device* device, ID3D11DeviceContext* device_context)
    {
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        (void)io;


        ImFontConfig font_config;


        static const ImWchar ranges[] = {

           0x0020, 0x00FF, // Basic Latin + Latin Supplement
           0x0400, 0x052F, // Cyrillic + Cyrillic Supplement
           0x2DE0, 0x2DFF, // Cyrillic Extended-A
           0xA640, 0xA69F, // Cyrillic Extended-B
           0xE000, 0xE226, // icons
           0,
        };

        font_config.GlyphRanges = ranges;

        io.Fonts->AddFontFromMemoryTTF(font_medium_binary, sizeof font_medium_binary, 15, &font_config, ranges);

        ImGui_ImplWin32_Init(Window.hWnd);

        ImGui_ImplDX11_Init(device, device_context);

        return true;

    }

    void drawing_Base::CleanImGui()
    {
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();

        g_Device.CleanupDeviceD3D();
        DestroyWindow(Window.hWnd);
        UnregisterClassA(Window.ClassName.c_str(), Window.hInstance);
    }

    std::wstring drawing_Base::StringToWstring(std::string& str)
    {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        return converter.from_bytes(str);
    }

}
