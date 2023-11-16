#pragma once
#include "imgui-struct.h"
#include <iostream>
#include <string>
#include <functional>
#include <codecvt>
#include <vector>
#include <dwmapi.h>
#pragma comment(lib,"dwmapi.lib")


namespace drawing
{
	class D3DDevice
	{
	public:
		ID3D11Device* g_pd3dDevice = nullptr;
		ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
		IDXGISwapChain* g_pSwapChain = nullptr;
		ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;
#ifdef _CONSOLE
		bool CreateDeviceD3D(HWND hWnd);
		void CleanupDeviceD3D();
		void CreateRenderTarget();
		void CleanupRenderTarget();
#endif
	};

	static D3DDevice g_Device;

	enum WindowType
	{
		NEW,
		ATTACH
	};

	class WindowData
	{
	public:
		HWND  hWnd = NULL;
		HINSTANCE hInstance = nullptr;
		std::string Name;
		std::wstring wName;
		std::string ClassName;
		std::wstring wClassName;
		Vector2 Pos;
		Vector2 Size;
		ImColor BgColor{ 255, 255, 255 };
	};

	class drawing_Base
	{
	public:
		std::function<void()> CallBackFn = nullptr;
		bool EndFlag = false;

	public:

		WindowData Window;
		WindowData DestWindow;
	public:

		virtual void Quit() { EndFlag = true; };
	public:
		virtual bool CreateMyWindow() = 0;
		virtual void MainLoop() {};
		bool InitImGui(ID3D11Device* device, ID3D11DeviceContext* device_context);
		void CleanImGui();
		std::wstring StringToWstring(std::string& str);
	};
}