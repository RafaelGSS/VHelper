// VHelper.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <src/core/winapi/WinEventKeyboardFocus.h>

int main()
{
	// Using WinEventKeyboardFocus
	auto p = core::winapi::WinEventKeyboardFocus();
	p.boot();
	p.run();

	system("pause");
}