#pragma once
#include <string>
#include "TextSpeaker.h"

namespace core::speaker {
	class SpeakerFacade
	{
	public:
		static SpeakerFacade* getInstance();

		void speak(const std::string& msg) const;
		void stop() const;

		void release();
	private:
		gds::CTextSpeaker* m_spk;

		SpeakerFacade();
		~SpeakerFacade();
	};
}

