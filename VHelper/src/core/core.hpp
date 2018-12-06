#pragma once
#include <src/utils/message-passing/ActorModel.h>
#include <src/utils/spdlog/spdlog.h>

#include <src/core/winapi/WinEventBase.h>
#include <src/core/winapi/WinEventKeyboardFocus.h>

#include <oleacc.h>
#include <windows.h>
#include <array>
#include <memory>
#include <thread>
#include <functional>

namespace core {
	
	struct WinHookManager
	{
		std::array<core::winapi::WinEventBase*, 1> m_hooks;

		WinHookManager() {
			m_hooks = std::array<core::winapi::WinEventBase*, 1>{
				new core::winapi::WinEventKeyboardFocus()
			};
		}

		void bootHooks() {
			for (core::winapi::WinEventBase* hook : m_hooks) {
				std::thread(
					std::bind(&core::winapi::WinEventBase::bootRun, hook)
				).detach();
			}
		}

		void unitializeHooks() {
			for (core::winapi::WinEventBase* hook : m_hooks) {
				hook->shutdown();
				delete hook;
				hook = nullptr;
			}
		}
	};

	std::shared_ptr<WinHookManager> getWinHManager()
	{
		static std::shared_ptr<WinHookManager> g_hookM;
		if (!g_hookM)
			g_hookM.reset(new WinHookManager());
	
		return g_hookM;
	}

	void initializeWinEvents() 
	{
		spdlog::info("Initializing WinEvents");
		CoInitialize(NULL);
		getWinHManager()->bootHooks();
	}

	void shutdownWinEvents()
	{
		spdlog::info("Shutdown WinEvents");
		getWinHManager()->unitializeHooks();
		CoUninitialize();
	}

	void initializeActor()
	{
		std::thread(
			std::bind(
				&ActorModel::run,
				ActorModel::getInstance()
			)
		).detach();
	}

}