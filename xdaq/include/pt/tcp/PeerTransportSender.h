// $Id: PeerTransportSender.h,v 1.10 2008/08/26 15:00:53 lorsini Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _pt_tcp_PeerTransportSender_h
#define _pt_tcp_PeerTransportSender_h

#include <vector>
#include <map>
#include <string>

#include "pt/PeerTransportSender.h"
#include "pt/PeerTransportReceiver.h"
#include "pt/PeerTransportAgent.h"
#include "toolbox/squeue.h"
#include "pt/tcp/Channel.h"
#include "pt/tcp/PostDescriptor.h"
#include "toolbox/mem/Reference.h"
#include "i2o/Messenger.h"
#include "toolbox/Task.h"
#include "xdaq/Object.h"
#include "xdaq/Application.h"
#include "xdata/Properties.h"
#include "xdata/InfoSpaceFactory.h"
#include "xdata/UnsignedInteger32.h"
#include "xdata/Double.h"
#include "pt/tcp/Transmitter.h"
#include "pt/tcp/exception/QueueFull.h"
#include "pt/tcp/exception/OverThreshold.h"
#include "pt/tcp/exception/NotActive.h"
namespace pt 
{
namespace tcp
{

class PeerTransportSender: public pt::PeerTransportSender, public toolbox::Task, public xdaq::Object
{
	public:
	
	PeerTransportSender(xdaq::Application* app, size_t qsize);
	virtual ~PeerTransportSender();
	
	pt::TransportType getType();
	
	pt::Address::Reference createAddress( const std::string& url, const std::string& service )
		throw (pt::exception::InvalidAddress);
	
	pt::Address::Reference createAddress( std::map<std::string, std::string, std::less<std::string> >& address )
		throw (pt::exception::InvalidAddress);
	
	std::string getProtocol();
	
	std::vector<std::string> getSupportedServices();	

	bool isServiceSupported(const std::string& service );
	
	pt::Messenger::Reference getMessenger (pt::Address::Reference destination, pt::Address::Reference local)
		throw (pt::exception::UnknownProtocolOrService);
	
	//! sender loop service routine, run in a thread
	int svc();
	
	//! queue a request for send
	void post(toolbox::mem::Reference * ref, 
			tcp::Channel * channel, 
			toolbox::exception::HandlerSignature * handler, 
			void * context, uint32_t signature, const ConnectionType & connection)
		throw (pt::tcp::exception::QueueFull, pt::tcp::exception::OverThreshold,  pt::tcp::exception::NotActive);
		
	void setPool(toolbox::mem::Pool * pool);
	toolbox::mem::Pool * getPool();
	
	void start();
	void stop();
	
	pt::tcp::Channel * createChannel(pt::Address::Reference destination, pt::Address::Reference local)
		 throw (pt::tcp::exception::Exception);
;
	bool hasChannel(pt::tcp::Channel * channel);
	void destroyChannel(pt::tcp::Channel * channel);



	
	private:
	
		toolbox::squeue<tcp::PostDescriptor> outputQueue_;
		bool activated_;
		bool done_;
		uint32_t sequence_;
		uint16_t identification_;
		toolbox::mem::Pool * pool_;
		toolbox::BSem channelMutex_;
		std::set<pt::tcp::Channel*> channels_;
		
		// Monitoring Variables
		xdata::InfoSpace* 		monitorInfoSpace_;
		xdata::UnsignedInteger32	sentMessages_;
		xdata::Double			kiloBytesSent_;
		xdata::Double			sendTime_;		
};

}
}

#endif
