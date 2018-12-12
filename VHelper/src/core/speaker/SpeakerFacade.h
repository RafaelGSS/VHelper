#pragma once
// This method is a facade for Speaker and SAPI
#include <string>

namespace core::speaker {
	class SpeakerFacade
	{
	public:
		static SpeakerFacade* getInstance();

		void speak(const std::string& msg) const;
		void stop() const;
	private:
		SpeakerFacade();
		~SpeakerFacade();
	};
}

