// $Id: PeerTransport.h,v 1.3 2008/07/18 15:27:14 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _pt_fifo_PeerTransport_h
#define _pt_fifo_PeerTransport_h

#include "pt/PeerTransportSender.h"
#include "pt/PeerTransportReceiver.h"
#include "pt/PeerTransportAgent.h"
#include "i2o/Listener.h"
#include "b2in/nub/Listener.h"
#include "pt/exception/Exception.h"
#include "pt/fifo/I2OMessenger.h"
#include "pt/fifo/PostDescriptor.h"
#include "pt/fifo/B2INMessenger.h"
#include "pt/Address.h"
#include "toolbox/lang/Class.h"

#include "toolbox/mem/Reference.h"
#include "toolbox/rlist.h"

#include "toolbox/BSem.h"
#include "toolbox/task/WorkLoop.h"
#include "toolbox/task/Action.h"

//
// Log4CPLUS
//
#include "log4cplus/logger.h"
#include "log4cplus/consoleappender.h"
#include "log4cplus/socketappender.h"
#include "log4cplus/nullappender.h"
#include "log4cplus/fileappender.h"
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
namespace fifo
{

class PeerTransport: public pt::PeerTransportSender, public pt::PeerTransportReceiver, public toolbox::lang::Class
{
	public:
	
	PeerTransport(Logger & logger) throw (pt::exception::Exception );
	
	~PeerTransport();
	
	//! Enqueue a binary message to the peer transport's work loop. Raise an exception if queue is full
	//
	void post (toolbox::mem::Reference* ref, toolbox::exception::HandlerSignature* handler, void* context, uint32_t signature) 
		throw (pt::exception::Exception );
	
	//! Internal work loop function used to process enqueued post requests
	//
	bool process(toolbox::task::WorkLoop * wl);	
	
	//! Retrieve the type of peer transport (Sender or Receiver or both)
	//
	pt::TransportType getType();
	
	pt::Address::Reference createAddress( const std::string& url, const std::string& service)
		throw (pt::exception::InvalidAddress);
		
	pt::Address::Reference createAddress( std::map<std::string, std::string, std::less<std::string> >& address )
		throw (pt::exception::InvalidAddress);
	
	//! Returns the implemented protocol ("loopback" in this version)
	//
	std::string getProtocol();
	
	//! Retrieve a list of supported services ("i2o" only in this version)
	//
	std::vector<std::string> getSupportedServices();
	
	//! Returns true if a service is supported ("i2o" only in this version), false otherwise
	//
	bool isServiceSupported(const std::string& service );	
	
	//! Retrieve a loopback messenger for the fifo peer transport that allows context internal application communication
	//
	pt::Messenger::Reference getMessenger (pt::Address::Reference destination, pt::Address::Reference local)
		throw (pt::exception::UnknownProtocolOrService);
	
	//! Internal function to add a message processing listener for this peer transport
	//
	void addServiceListener ( pt::Listener* listener ) throw (pt::exception::Exception); 	
	
	//! Internal function to remove a message processing listener for this peer transport
	//
	void removeServiceListener ( pt::Listener* listener ) throw (pt::exception::Exception); 	
	
	//! Internal function to remove all message processing listeners for this peer transport
	//
	void removeAllServiceListeners ();
	
	//! Function to configure this peer transport with a loopback address
	//	
	void config(pt::Address::Reference address) throw (pt::exception::Exception);

	toolbox::mem::Pool * getPool();

	protected:
	
	//! Maximum number of post requests that can be enqueued to this peer transport
	//	
	enum { MaxNoEntries =  10000 };
		
 	toolbox::BSem * sync_;
	toolbox::BSem * mutex_;
	toolbox::rlist<fifo::PostDescriptor> fifo_;
	int pending_;
	
	i2o::Listener* i2oListener_;
	b2in::nub::Listener* b2inListener_;
	pt::Messenger::Reference i2oMessenger_;
	pt::Messenger::Reference b2inMessenger_;
	pt::Address::Reference localI2OAddress_;
	pt::Address::Reference localB2INAddress_;
	toolbox::mem::Pool * pool_ ;
	
	toolbox::task::ActionSignature * process_;
	Logger	logger_;
};
}
}

#endif
