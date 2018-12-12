#include "ActorModel.h"
#include <thread>

#include <src/utils/spdlog/spdlog.h>
#include <boost/bind.hpp>


ActorModel * ActorModel::getInstance()
{
	static ActorModel* instance;
	if (!instance) {
		instance = new ActorModel();
	}

	return instance;
}

//void ActorModel::post(std::function<void()> message)
//{
//	m_service.post(message);
//}

boost::asio::io_service & ActorModel::service()
{
	return m_service;
}

void ActorModel::run()
{
	spdlog::info("Join run ActorModel");
	while (true)
	{
		try {
			m_service.run();
		}
		catch (...) {
			spdlog::error("A error ocurred on ActorModel");
		}
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	
}

ActorModel::ActorModel()
{
	boost::asio::io_service::work work(m_service);
}
