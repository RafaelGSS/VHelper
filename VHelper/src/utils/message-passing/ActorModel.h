#pragma once
#include <boost/asio/io_service.hpp>

#include <memory>
#include <functional>
#include <stdarg.h>  
#include <cstdarg>

class ActorModel
{
public:
	static ActorModel* getInstance();
	

	//virtual void post(std::function<void()> message);
	
	template <typename T>
	void post(T func);

	virtual boost::asio::io_service& service();
	
	virtual void run();
	
	ActorModel(ActorModel const&) = delete;
	void operator=(ActorModel const&) = delete;
protected:
	ActorModel();
	
	boost::asio::io_service m_service;
};

template<typename T>
inline void ActorModel::post(T func)
{
	m_service.post(func);
}
