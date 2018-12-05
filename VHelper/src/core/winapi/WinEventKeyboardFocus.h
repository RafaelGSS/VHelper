#pragma once
#include <Windows.h>

namespace core::winapi {
	class WinEventKeyboardFocus
	{
	private:
		HWINEVENTHOOK m_hook;

	public:
		WinEventKeyboardFocus();
		
		virtual void run();
		virtual void shutdown();

		virtual void boot();
		static void __stdcall winEventProcCallback(
			HWINEVENTHOOK hWinEventHook,
			DWORD dwEvent,
			HWND hwnd,
			LONG idObject,
			LONG idChild,
			DWORD dwEventThread,
			DWORD dwmsEventTime
		);
	};
}

