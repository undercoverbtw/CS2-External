#include "hack.h"
#include "../core/memory/offsets.h"
#include "../core/ext/rendering/OS-ImGui_Struct.h"
#include "../core/ext/rendering/imgui/custom.h"
#include "../menu/menu.h"
#include "miscellanous/configsystem.h"

void cheats::run()
{

	// Show menu // thanks tkazer <3
	static std::chrono::time_point LastTimePoint = std::chrono::steady_clock::now();
	auto CurTimePoint = std::chrono::steady_clock::now();

	if (GetAsyncKeyState(VK_INSERT)
		&& CurTimePoint - LastTimePoint >= std::chrono::milliseconds(150))
	{
		// Check key state per 150ms once to avoid loop.
		vars.show_menu = !vars.show_menu;
		LastTimePoint = CurTimePoint;
	}

	if (vars.show_menu)
		menu::render();


	const uintptr_t local_player = cheat::process->read<uintptr_t>(cheat::client.base + offsets::local_player);
	int health = cheat::process->read<int>(local_player + offsets::health);

	//std::cout << red << "Health: " << health << white << std::endl;

}
