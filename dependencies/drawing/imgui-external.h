#pragma once
#include "imgui-base.h"

/****************************************************
* Copyright (C)	: Liv
* @file			: OS-ImGui_External.h
* @author		: Liv
* @email		: 1319923129@qq.com
* @version		: 1.0
* @date			: 2023/6/18	11:21
****************************************************/

namespace drawing
{
	class drawing_External : public drawing_Base
	{
	private:
		WindowType Type = NEW;
	public:
		void overlay(std::function<void()> CallBack);
	private:
		void MainLoop();
		bool UpdateWindowData();
		bool CreateMyWindow();

		bool PeekEndMessage();
	};
}