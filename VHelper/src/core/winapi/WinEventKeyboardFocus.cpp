#include "WinEventKeyboardFocus.h"

#include <src/utils/spdlog/spdlog.h>
#include <src/utils/message-passing/ActorModel.h>

#include <functional>
#include <iostream>
#include <oleacc.h>
#include <Windows.h>

core::winapi::WinEventKeyboardFocus::WinEventKeyboardFocus()
{
}

void core::winapi::WinEventKeyboardFocus::boot()
{
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
	IAccessible* pAcc = NULL;
	VARIANT varChild;
	HRESULT hr = AccessibleObjectFromEvent(hwnd, idObject, idChild, &pAcc, &varChild);

	if ((hr == S_OK) && (pAcc != NULL))
	{
		BSTR pNameT;
		
		pAcc->get_accName(varChild, &pNameT);
		std::wstring ws(pNameT, SysStringLen(pNameT));
	}
}
