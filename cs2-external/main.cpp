#include <iostream>
#include <thread>
#include <chrono>
#include <Windows.h>

#include "memory/memory.h"
#include "features/hack.h"
#include "classes/vector.hpp"



namespace offsets {
	inline std::ptrdiff_t dwLocalPlayer = 0x16B6320;
	inline std::ptrdiff_t dwEntityList = 0x17AA8E8;
	inline std::ptrdiff_t dwViewMatrix = 0x1899070;


	inline std::ptrdiff_t m_vecAbsOrigin = 0xC8;
	inline std::ptrdiff_t m_pGameSceneNode = 0x310;
	inline std::ptrdiff_t m_szName = 0xC18;
	inline std::ptrdiff_t m_iHealth = 0x32C;
	inline std::ptrdiff_t m_hPlayerPawn = 0x7BC;
	inline std::ptrdiff_t m_sSanitizedPlayerName = 0x720;
	inline std::ptrdiff_t m_iTeamNum = 0x3BF;

	inline std::ptrdiff_t m_vecOrigin = 0x1224;
}


int main()
{

	SetConsoleTitle("cs2-external");

	hack::process = std::make_shared<memory>();

	std::cout << "[cheat] Waiting for cs2.exe..." << std::endl;

	while (!hack::process->attach_process_hj("cs2.exe"))
		std::this_thread::sleep_for(std::chrono::seconds(1));

	std::cout << "[cheat] Attached to cs2.exe\n" << std::endl;


	do {
		hack::client = hack::process->get_module("client.dll");
		hack::engine = hack::process->get_module("engine2.dll");
		if (hack::client.base == 0 || hack::engine.base == 0) {
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	} while (hack::client.base == 0 || hack::engine.base == 0);



	while (true)
	{

		const uintptr_t localPlayer = hack::process->read<uintptr_t>(hack::client.base + offsets::dwLocalPlayer);

		auto health = hack::process->read<int>(localPlayer + offsets::m_iHealth);

		std::cout << "Health: " << health << std::endl;

		Sleep(500);
	}


	return 0;
}



