#pragma once
#include <string>
//#include "Speaker.h"

namespace core::speaker {
	class SpeakerFacade
	{
	public:
		static SpeakerFacade* getInstance();

		void speak(const std::string& msg) const;
		void stop() const;

		void release();
	private:
		//Speaker* m_spk;

		SpeakerFacade();
		~SpeakerFacade();
	};
}

