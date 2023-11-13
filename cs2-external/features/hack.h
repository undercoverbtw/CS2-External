#include <thread>
#include <cmath>
#include "../memory/memory.h"

namespace cheats
{
	void menu();
	void run();
}

namespace hack {
	inline std::shared_ptr<memory> process;
	inline process_module client;
	inline process_module engine;
}

class config
{
public:

	bool show_menu = true;
};
inline config cfg;