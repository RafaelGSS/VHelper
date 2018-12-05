#include "WinEventKeyboardFocus.h"

#include <src/utils/spdlog/spdlog.h>
#include <functional>

core::winapi::WinEventKeyboardFocus::WinEventKeyboardFocus()
{
}

void core::winapi::WinEventKeyboardFocus::run()
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

void core::winapi::WinEventKeyboardFocus::shutdown()
{
	spdlog::debug("Shutdown the Hook");
	UnhookWinEvent(m_hook);
	CoUninitialize();
}

void core::winapi::WinEventKeyboardFocus::boot()
{
	CoInitialize(NULL);
	m_hook = SetWinEventHook(
		EVENT_OBJECT_FOCUS, EVENT_OBJECT_FOCUS,  // Range of events (4 to 5).
		NULL,                                          // Handle to DLL.
		&core::winapi::WinEventKeyboardFocus::winEventProcCallback,
		0, 0,              // Process and thread IDs of interest (0 = all)
		WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS); // Flags.
}

void __stdcall core::winapi::WinEventKeyboardFocus::winEventProcCallback(
	HWINEVENTHOOK hWinEventHook, 
	DWORD dwEvent,
	HWND hwnd,
	LONG idObject, 
	LONG idChild, 
	DWORD dwEventThread, 
	DWORD dwmsEventTime
){
	spdlog::info("New event!");
}
