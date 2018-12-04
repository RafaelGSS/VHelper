// VHelper.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <windows.h>
#include <oleacc.h>
#include <thread>

VOID CALLBACK WinEventProcCallback(HWINEVENTHOOK hWinEventHook, DWORD dwEvent, HWND hwnd, LONG idObject, LONG idChild, DWORD dwEventThread, DWORD dwmsEventTime)
{
	auto a = 1;
	std::cout << a;
}

// Global variable.
HWINEVENTHOOK g_hook;

//
// Callback function that handles events.
//
void CALLBACK HandleWinEvent(HWINEVENTHOOK hook, DWORD event, HWND hwnd,
	LONG idObject, LONG idChild,
	DWORD dwEventThread, DWORD dwmsEventTime)
{
	std::cout << "Inside CB" << std::endl;
}

// Initializes COM and sets up the event hook.
void InitializeMSAA()
{
	CoInitialize(NULL);
	g_hook = SetWinEventHook(
		EVENT_OBJECT_FOCUS, EVENT_OBJECT_FOCUS,  // Range of events (4 to 5).
		NULL,                                          // Handle to DLL.
		HandleWinEvent,                                // The callback.
		0, 0,              // Process and thread IDs of interest (0 = all)
		WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS); // Flags.
}


// Unhooks the event and shuts down COM.
//
void ShutdownMSAA()
{
	UnhookWinEvent(g_hook);
	CoUninitialize();
}


int main()
{
	InitializeMSAA();

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}