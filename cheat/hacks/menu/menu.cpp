#include "menu.h"
#include "../../../dependencies/drawing/more/imgui.h"
#include <Windows.h>
void menu::setup()
{
	ImGui::StyleColorsDark();

	ImGui::SetNextWindowSize(ImVector2(600, 400), ImGuiCond_Once);

	ImGui::Begin("", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
	{

		// your menu here

	}
	ImGui::End();
}


