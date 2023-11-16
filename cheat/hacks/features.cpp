#include "features.h"
#include "configsystem/config.h"


void features::run()
{

	static DWORD lastTick = 0;
	DWORD currentTick = GetTickCount64();

	if ((GetAsyncKeyState(VK_INSERT) & 0x8000) && currentTick - lastTick >= 150) {
		config::show_menu = !config::show_menu;
		lastTick = currentTick;
	}

	if (config::show_menu)
		menu::setup();

	
}

  


