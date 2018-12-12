#include "SpeakerFacade.h"


core::speaker::SpeakerFacade * core::speaker::SpeakerFacade::getInstance()
{
	static SpeakerFacade* instance = nullptr;
	if (!instance)
		instance = new SpeakerFacade();
	
	return instance;
}

void core::speaker::SpeakerFacade::speak(const std::string & msg) const
{
}

void core::speaker::SpeakerFacade::stop() const
{
}

core::speaker::SpeakerFacade::SpeakerFacade()
{
}

core::speaker::SpeakerFacade::~SpeakerFacade()
{
}
