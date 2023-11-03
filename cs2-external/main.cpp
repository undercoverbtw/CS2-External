#include "hijacking/hijacking.h"
#include <Windows.h>



int main()
{
	

	while (true)
	{
		auto process = hj::GetPID("cs2.exe");


		HANDLE hijacked = hj::HijackExistingHandle(process);

	}

}



