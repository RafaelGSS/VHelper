#define _WIN32_WINNT 0x0501
#include <src/core/core.hpp>
#include <iostream>
#include <src/core/speaker/SpeakerFacade.h>


int main()
{
	core::initializeActor();
	core::initializeWinEvents();
	std::this_thread::sleep_for(std::chrono::seconds(60));
	core::shutdownWinEvents();
	std::this_thread::sleep_for(std::chrono::seconds(60));

	system("pause");
}