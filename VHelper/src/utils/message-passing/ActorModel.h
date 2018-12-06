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
	

	virtual void post(std::function<void()> message);
	virtual boost::asio::io_service& service();
	
	virtual void run();
	
	ActorModel(ActorModel const&) = delete;
	void operator=(ActorModel const&) = delete;
protected:
	ActorModel();
	
	boost::asio::io_service m_service;
};

