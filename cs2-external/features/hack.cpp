#include "hack.h"
#include "../ext/rendering/OS-ImGui_Struct.h"
#include "../ext/consolecolors.h"
#include "../ext/rendering/imgui/custom.h"




void cheats::menu()
{

	ImGui::StyleColorsDark();
	ImGui::SetNextWindowSize(ImVec2(500, 300));
	ImGui::Begin("##Menu", NULL);
	{


	}
	ImGui::End();
}




void cheats::run()
{

	// Show menu // thanks tkazer <3
	static std::chrono::time_point LastTimePoint = std::chrono::steady_clock::now();
	auto CurTimePoint = std::chrono::steady_clock::now();

	if (GetAsyncKeyState(VK_INSERT)
		&& CurTimePoint - LastTimePoint >= std::chrono::milliseconds(150))
	{
		// Check key state per 150ms once to avoid loop.
		cfg.show_menu = !cfg.show_menu;
		LastTimePoint = CurTimePoint;
	}

	if (cfg.show_menu)
		menu();


	//const uintptr_t local_player = hack::process->read<uintptr_t>(hack::client.base + offsets::local_player);
	//int health = hack::process->read<int>(local_player + offsets::health);

	//std::cout << red << "Health: " << health << white << std::endl;

}
