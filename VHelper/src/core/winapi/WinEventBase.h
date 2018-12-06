#pragma once
#include <Windows.h>
#include <memory>

namespace core::winapi {
	class WinEventBase : public std::enable_shared_from_this<WinEventBase>
	{
	protected:
		HWINEVENTHOOK m_hook;
	public:
		virtual void boot() = 0;
		virtual void bootRun();

		virtual void shutdown();
		
		virtual void run();

		WinEventBase();
	};
}

