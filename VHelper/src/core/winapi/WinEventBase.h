#pragma once
#include <Windows.h>

namespace core::winapi {

	class WinEventBase
	{
	public:
		virtual void run();
		virtual void shutdown();
		
		WinEventBase();
		virtual ~WinEventBase();
	protected:
		virtual void boot() = 0;
		virtual void __stdcall winEventProcCallback(
			HWINEVENTHOOK hWinEventHook, 
			DWORD dwEvent,
			HWND hwnd, 
			LONG idObject, 
			LONG idChild, 
			DWORD dwEventThread, 
			DWORD dwmsEventTime
		) = 0;
		
	private:
		HWINEVENTHOOK m_hook;
	};
}

