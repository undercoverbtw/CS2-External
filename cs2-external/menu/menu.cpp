#include "../core/ext/rendering/OS-ImGui_Struct.h"
#include "../core/ext/rendering/imgui/custom.h"
#include "menu.h"



void menu::render()
{
	ImGui::StyleColorsDark(); // go to the definition and you can choose colors
	ImGui::SetNextWindowSize(ImVec2(500, 300)); // menu size
	ImGui::Begin("##Menu", NULL); // imgui start. dont forget end.
	{

		// your menu here. checkboxes, etc.

	}
	ImGui::End(); // as i said dont forget end.
}
