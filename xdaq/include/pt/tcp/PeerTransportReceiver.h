// $Id: PeerTransportReceiver.h,v 1.6 2008/12/08 08:30:09 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _pt_tcp_PeerTransportReceiver_h
#define _pt_tcp_PeerTransportReceiver_h

#include <string>
#include <vector>

#include "toolbox/mem/Pool.h"
#include "pt/PeerTransportReceiver.h"
#include "pt/exception/Exception.h"
#include "pt/tcp/Address.h"
#include "pt/tcp/ReceiverLoop.h"
#include "xdaq/Object.h"
#include "xdaq/Application.h"

// Log4CPLUS
#include "log4cplus/logger.h"
#include "log4cplus/consoleappender.h"
#include "log4cplus/helpers/appenderattachableimpl.h"
#include "log4cplus/helpers/loglog.h"
#include "log4cplus/helpers/pointer.h"
#include "log4cplus/spi/loggingevent.h"
#include "log4cplus/layout.h"

using namespace log4cplus;
using namespace log4cplus::helpers;
using namespace log4cplus::spi;

namespace pt
{
namespace tcp
{

//! There is only one peer transport receiver. It has a number of ReceiverLoop
//! objects, one per receiver port
//
class PeerTransportReceiver: public pt::PeerTransportReceiver, xdaq::Object
{
	public:
	
	PeerTransportReceiver
	(
		xdaq::Application* app,
		bool autoSize,
		xdata::UnsignedLongT maxPacketSize,
		xdata::UnsignedInteger32T maxClients
	);
	
	~PeerTransportReceiver();
	
	pt::TransportType getType();
	
	pt::Address::Reference createAddress( const std::string& url, const std::string& service )
		throw (pt::exception::InvalidAddress);
	
	pt::Address::Reference 
	createAddress( std::map<std::string, std::string, std::less<std::string> >& address )
		throw (pt::exception::InvalidAddress);
	
	void addServiceListener (pt::Listener* listener) throw (pt::exception::Exception);
	void removeServiceListener (pt::Listener* listener ) throw (pt::exception::Exception);
	void removeAllServiceListeners();
	
	std::string getProtocol();
	
	std::vector<std::string> getSupportedServices();	

	bool isServiceSupported(const std::string& service );
	
	void config (pt::Address::Reference address) throw (pt::exception::Exception);
	void start() throw (pt::exception::Exception);
	void stop() throw (pt::exception::Exception);
	
	void setPool(toolbox::mem::Pool * pool);
	void setMaxPacketSize(xdata::UnsignedLongT maxPacketSize );
	void setAutoSize(xdata::BooleanT autoSize );
	void setMaxClients(xdata::UnsignedInteger32T maxPacketSize );
		
	std::string getHostByInterface(const std::string & interface)
		throw (pt::exception::InvalidAddress);
	std::string getHostBySubnet(const std::string & subnet)
		throw (pt::exception::InvalidAddress);
	
	protected:
	
	xdata::BooleanT autoSize_;
	xdata::UnsignedLongT maxPacketSize_;	
	xdata::UnsignedInteger32T maxClients_;			
	std::vector<tcp::ReceiverLoop*> loop_;
	toolbox::mem::Pool * pool_;
};

}
}

#endif
