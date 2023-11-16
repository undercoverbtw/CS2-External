#pragma once
#include "imgui-external.h"
/****************************************************
* Copyright (C)	: Liv
* @file			: OS-ImGui.h
* @author		: Liv
* @email		: 1319923129@qq.com
* @version		: 1.0
* @date			: 2023/9/17	11:25
****************************************************/

namespace drawing
{
	class drawing : public drawing_External, public Singleton<drawing>


	{
	public:
		// 文本
		void text(std::string Text, Vector2 Pos, ImColor Color, float FontSize = 15, bool KeepCenter = false);
		// 描边文本
		void stroke_text(std::string Text, Vector2 Pos, ImColor Color, float FontSize = 15, bool KeepCenter = false);
		
	};
}

inline drawing::drawing& render = drawing::drawing::get();