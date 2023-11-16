#pragma once
#include "imguii.h"

namespace drawing
{
    void drawing::text(std::string text, Vector2 pos, ImColor color, float font_size, bool keep_center)
    {
        if (!keep_center)
        {
            ImGui::GetBackgroundDrawList()->AddText(ImGui::GetIO().Fonts->Fonts[2], font_size, pos.ToImVector2(), color, text.c_str());
        }
        else
        {
            float text_width = ImGui::GetFont()->CalcTextSizeA(font_size, FLT_MAX, 0.f, text.c_str()).x;
            ImVector2 pos_ = { pos.x - text_width / 2, pos.y };
            ImGui::GetBackgroundDrawList()->AddText(ImGui::GetIO().Fonts->Fonts[2], font_size, pos_, color, text.c_str());
        }
    }

    void drawing::stroke_text(std::string text, Vector2 pos, ImColor color, float font_size, bool keep_center)
    {
        this->text(text, Vector2(pos.x - 1, pos.y + 1), ImColor(0, 0, 0), font_size, keep_center);
        this->text(text, Vector2(pos.x - 1, pos.y - 1), ImColor(0, 0, 0), font_size, keep_center);
        this->text(text, Vector2(pos.x + 1, pos.y + 1), ImColor(0, 0, 0), font_size, keep_center);
        this->text(text, Vector2(pos.x + 1, pos.y - 1), ImColor(0, 0, 0), font_size, keep_center);
        this->text(text, pos, color, font_size, keep_center);
    }
}