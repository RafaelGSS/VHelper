#include "WinEventBase.h"

#include <src/utils/spdlog/spdlog.h>


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

void core::winapi::WinEventBase::shutdown()
{
	spdlog::debug("Shutdown the Hook");
	UnhookWinEvent(m_hook);
	CoUninitialize();
}

core::winapi::WinEventBase::WinEventBase()
{
}

core::winapi::WinEventBase::~WinEventBase()
{
}
