#pragma once
#include <src/core/winapi/WinEventBase.h>

namespace core::winapi {
	class WinEventKeyboardFocus : public WinEventBase
	{
	public:
		WinEventKeyboardFocus();
		
		virtual void boot() override;

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

