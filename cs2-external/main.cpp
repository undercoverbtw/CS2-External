#include "includes.h"

int main()
{

	SetConsoleTitle("Undercover");

	chooseyourownname::initialization();

	while (true)
	{
		const uintptr_t local_player = hack::process->read<uintptr_t>(hack::client.base + offsets::local_player);
		int health = hack::process->read<int>(local_player + offsets::health);

		std::cout << red << "Health: " << health << white << std::endl;

		// best lmao
		system("pause");
	}

	return 0;
}



