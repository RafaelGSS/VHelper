#include "SpeakerFacade.h"
#include <iostream>

#include <src/utils/func.hpp>


core::speaker::SpeakerFacade * core::speaker::SpeakerFacade::getInstance()
{
	static SpeakerFacade* instance = nullptr;
	if (!instance)
		instance = new SpeakerFacade();
	
	return instance;
}

void core::speaker::SpeakerFacade::speak(const std::string & msg) const
{
	auto converted = utils::string2WStr(msg);
	LPCWSTR phrase = converted.c_str();

	//m_spk->speakMessage(phrase);
}

void core::speaker::SpeakerFacade::stop() const
{
	//m_spk->pause();
}

void core::speaker::SpeakerFacade::release()
{
	//delete m_spk;
	//m_spk = nullptr;
}

core::speaker::SpeakerFacade::SpeakerFacade() /*: m_spk(new Speaker())*/
{
}

core::speaker::SpeakerFacade::~SpeakerFacade()
{
	/*if (m_spk) {
		release();
	}*/
}
