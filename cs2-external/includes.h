#pragma once

#include <iostream>
#include <thread>
#include <chrono>
#include <Windows.h>
#include <string>
#include <stdio.h>
#include <time.h>

#include "memory/memory.h"
#include "features/hack.h"
#include "classes/vector.hpp"
#include "extern/consolecolors.h"

namespace chooseyourownname
{
	const std::string currentDateTime() {
		time_t now = time(0);
		struct tm tstruct;
		char buf[80];
		tstruct = *localtime(&now);
		// Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
		// for more information about date/time format
		strftime(buf, sizeof(buf), "%X", &tstruct);

		return buf;
	}
	inline void initialization()
	{
		hack::process = std::make_shared<memory>();

		std::cout << red << "[" << currentDateTime() << "] "
			<< white << "Welcome\n";

		std::this_thread::sleep_for(std::chrono::seconds(1));

		system("CLS");

		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << red << "[" << currentDateTime() << "] "
			<< white << "Waiting for cs2.exe\n";

		while (!hack::process->attach_process_hj("cs2.exe"))
			std::this_thread::sleep_for(std::chrono::seconds(1));

		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << red << "------------------------"
			<< white << "Attaching to cs2" << red << "------------------------------\n";

		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << red << "[" << currentDateTime() << "] "
			<< white << "Attached to cs2.exe\n";


		do {
			hack::client = hack::process->get_module("client.dll");
			hack::engine = hack::process->get_module("engine2.dll");
			if (hack::client.base == 0 || hack::engine.base == 0) {
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}
		} while (hack::client.base == 0 || hack::engine.base == 0);

		if (!hack::client.base == 0 || !hack::engine.base == 0)
		{

			std::this_thread::sleep_for(std::chrono::seconds(1));
			std::cout << red << "------------------------"
				<< white << "Searching for modules" << red << "------------------------------\n";

			std::this_thread::sleep_for(std::chrono::seconds(2));
			std::cout << red << "[" << currentDateTime() << "] "
				<< white << "Client module found\n";

			std::this_thread::sleep_for(std::chrono::seconds(2));
			std::cout << red << "[" << currentDateTime() << "] "
				<< white << "Engine module found\n";

			std::this_thread::sleep_for(std::chrono::seconds(1));
			std::cout << red << "------------------------"
				<< white << "Made by Undercover" << red << "------------------------------\n";

			std::this_thread::sleep_for(std::chrono::seconds(1));
			std::cout << red << "[" << currentDateTime() << "] "
				<< white << "Have fun!\n";

			std::this_thread::sleep_for(std::chrono::seconds(1));
			std::cout << red << "------------------------"
				<< white << "Debug logs" << red << "------------------------------\n";
			
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		else
		{
			std::this_thread::sleep_for(std::chrono::seconds(2));
			std::cout << red << "[" << currentDateTime() << "] "
				<< white << "No modules find. Are you sure cs2 is running?\n";
		}
	}

}

namespace offsets {
	inline std::ptrdiff_t local_player = 0x16B9388;
	inline std::ptrdiff_t entity_list = 0x17ADAE0;
	inline std::ptrdiff_t view_matrix = 0x1899070;


	inline std::ptrdiff_t vec_abs_origin = 0xC8;
	inline std::ptrdiff_t game_scene_node = 0x310;
	inline std::ptrdiff_t name = 0xC18;
	inline std::ptrdiff_t health = 0x32C;
	inline std::ptrdiff_t player_pawn = 0x7BC;
	inline std::ptrdiff_t sanatized_name = 0x720;
	inline std::ptrdiff_t team_num = 0x3BF;

	inline std::ptrdiff_t vec_origin = 0x1224;
}