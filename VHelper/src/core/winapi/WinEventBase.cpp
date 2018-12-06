#include "WinEventBase.h"
#include <src/utils/spdlog/spdlog.h>

#include <iostream>
void core::winapi::WinEventBase::run()
{
	if (!m_hook) {
		spdlog::critical("Hook is not setted");
		return;
	}

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	spdlog::critical("Out of GetMessage");
}

core::winapi::WinEventBase::WinEventBase()
{
}

void core::winapi::WinEventBase::bootRun()
{
	boot();
	run();
}

void core::winapi::WinEventBase::shutdown()
{
	spdlog::debug("Shutdown the Hook");
	UnhookWinEvent(m_hook);
}

