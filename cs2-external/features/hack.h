#include <thread>
#include <cmath>

#include "../core/memory/memory.h"
#include "../core/ext/consolecolors.h"

namespace cheats
{
	void run();
}

namespace cheat {
	inline std::shared_ptr<memory> process;
	inline process_module client;
	inline process_module engine;
}

