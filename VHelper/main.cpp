#include <src/core/core.hpp>

int main()
{
	core::initializeActor();
	core::initializeWinEvents();
	std::this_thread::sleep_for(std::chrono::seconds(60));
	core::shutdownWinEvents();
	std::this_thread::sleep_for(std::chrono::seconds(60));

	system("pause");
}