#include "includes.h"
#include <OS-ImGui_Exception.hpp>
#include <OS-ImGui.h>

int main()
{

	auto io = ImGui::GetStyle();

	io.WindowBorderSize = 0;

	SetConsoleTitleA("Undercover");

	chooseyourownname::initialization();

	// best lmao
	
	try
	{
		Gui.AttachAnotherWindow("Counter-Strike 2", "SDL_app", cheats::run);
	}
	catch (OSImGui::OSException& e)
	{
		std::cout << e.what() << std::endl;
	}

	// sleep for fix

	return 0;
}



