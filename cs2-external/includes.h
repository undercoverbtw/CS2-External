#pragma once

#include <iostream>
#include <thread>
#include <chrono>
#include <Windows.h>
#include <string>
#include <stdio.h>
#include <time.h>

#include "core/memory/memory.h"
#include "features/hack.h"
#include "core/valve-sdk/math/classes/vector.h"
#include "core/ext/consolecolors.h"


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
		cheat::process = std::make_shared<memory>();

		std::cout << red << "[" << currentDateTime() << "] "
			<< white << "Welcome\n";

		std::this_thread::sleep_for(std::chrono::seconds(1));

		system("CLS");

		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << red << "[" << currentDateTime() << "] "
			<< white << "Waiting for cs2.exe\n";

		while (!cheat::process->attach_process_hj("chrome.exe"))
			std::this_thread::sleep_for(std::chrono::seconds(1));

		putchar('\n');
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << red << "------------------------------------------------------\n";

		putchar('\n');
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << red << "[" << currentDateTime() << "] "
			<< white << "Attached to cs2.exe\n";

		putchar('\n');

		do {
			cheat::client = cheat::process->get_module("client.dll");
			cheat::engine = cheat::process->get_module("engine2.dll");
			if (cheat::client.base == 0 || cheat::engine.base == 0) {
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}
		} while (cheat::client.base == 0 || cheat::engine.base == 0);

		if (!cheat::client.base == 0 || !cheat::engine.base == 0)
		{

			std::this_thread::sleep_for(std::chrono::seconds(1));
			std::cout << red << "------------------------------------------------------\n";
			putchar('\n');
			std::this_thread::sleep_for(std::chrono::seconds(2));
			std::cout << red << "[" << currentDateTime() << "] "
				<< white << "Client module found\n";
			putchar('\n');
			std::this_thread::sleep_for(std::chrono::seconds(2));
			std::cout << red << "[" << currentDateTime() << "] "
				<< white << "Engine module found\n";
			putchar('\n');
			std::this_thread::sleep_for(std::chrono::seconds(1));
			std::cout << red << "------------------------------------------------------\n";
			std::this_thread::sleep_for(std::chrono::seconds(1));
			std::cout << red << "[" << currentDateTime() << "] "
				<< white << "Have fun!\n";
			putchar('\n');
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