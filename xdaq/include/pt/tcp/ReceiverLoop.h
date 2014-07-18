// $Id: ReceiverLoop.h,v 1.11 2008/12/08 08:30:09 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _pt_tcp_ReceiverLoop_h_
#define _pt_tcp_ReceiverLoop_h_

#include <vector>
#include <sys/poll.h>

#include "pt/tcp/Address.h"
#include "pt/tcp/Channel.h"
#include "pt/tcp/exception/Exception.h"
#include "pt/tcp/exception/ConnectionReset.h"
#include "pt/tcp/exception/ReceiveError.h"
#include "pt/Listener.h" 
#include "i2o/Listener.h" 
#include "b2in/nub/Listener.h" 
#include "pt/tcp/Netfilter.h"
#include "toolbox/mem/MemoryPoolFactory.h"
#include "toolbox/mem/Pool.h"
#include "toolbox/task/WorkLoop.h"
#include "toolbox/lang/Class.h"

#include "xdata/UnsignedLong.h"
#include "xdata/UnsignedInteger32.h"
#include "xdata/Double.h"
#include "xdata/InfoSpaceFactory.h"
#include "xdata/Boolean.h"
#include "xdata/String.h"
#include "xdaq/Object.h"

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

class ReceiverLoop:  public pt::tcp::Channel, public toolbox::lang::Class, xdaq::Object
{
	enum { MaxNoChannels = 1024 };

	public:
	
	ReceiverLoop(pt::Address::Reference address, xdaq::Object* obj) 
		throw (pt::tcp::exception::Exception);
	
	~ReceiverLoop();
		
	// override channel receive
	size_t receive(char * buf ,size_t len ) throw (pt::tcp::exception::ReceiveError, pt::tcp::exception::ConnectionReset);
	
	void send(const char * buf, size_t len) throw (pt::tcp::exception::Exception);
	
	void disconnect() throw (pt::tcp::exception::Exception);
	
	void connect() throw (pt::tcp::exception::Exception); 
	
	void close() throw (pt::tcp::exception::Exception);
	
	//! work loop job routine
	bool process(toolbox::task::WorkLoop * wl);

	//! Get the address of this receiver (can be casted to a tcp::Address&)
	pt::Address::Reference getAddress();
	
	void addServiceListener (pt::Listener* listener);
	void removeServiceListener (pt::Listener* listener);
	void removeAllServiceListeners();
	
	void setPool(toolbox::mem::Pool * pool);
	void setMaxPacketSize(xdata::UnsignedLongT maxPacketSize );
	void setAutoSize(xdata::BooleanT autoSize );
	
	//! Set the maximum number of open sockets from which to receive
	//
	void setMaxClients( xdata::UnsignedInteger32T maxClients );
	
	void activate() throw (pt::tcp::exception::Exception);
	void cancel();
	
	private:
	
	int accept(std::string & originator, uint16_t & port) throw (pt::tcp::exception::Exception);
	
	bool isConnected() throw (pt::tcp::exception::Exception);
	bool isActive() throw (pt::tcp::exception::Exception);
	
	void onRequest() throw (pt::tcp::exception::Exception);
	
	void safeReceive(char * buf, size_t len) throw (pt::tcp::exception::ReceiveError, pt::tcp::exception::ConnectionReset);
	pt::Address::Reference getOriginatorAddress();

	pt::Address::Reference  address_; // reference counted pt address
	fd_set fdset_;
	fd_set allset_;
	int timeout_;
	bool done_;
	bool stop_;
	int maxfd_;
	int current_; // currently active file descriptor
	int listenfd_;
	int accepted_;
	int nochannels_;
	int nready_;
	xdata::BooleanT autoSize_; // use variable size allocation of incoming messages
	xdata::UnsignedLongT maxPacketSize_; // if autoSize_ is true, then this package size is always used for receiving packets. Otherwise it is an upper limit
	
	i2o::Listener* listener_;
	b2in::nub::Listener* b2inListener_;
	toolbox::mem::Pool * pool_;
	toolbox::mem::MemoryPoolFactory * manager_;
	toolbox::task::ActionSignature* process_;		
	std::vector<pt::Address::Reference> originators_;
	std::vector<std::string> originatorsURL_;
	pt::tcp::Netfilter netFilter_;
		
	bool deadBand_;
	
	// Monitoring Variables
	xdata::InfoSpace * 		monitorInfoSpace_;
	xdata::UnsignedInteger32	receivedMessages_;
	xdata::Double			kiloBytesReceived_;
	xdata::Double 			receiveTime_;
	xdata::String			endpointURL_;
	
	struct pollfd* clients_; // dynamically allocated list of client file descriptors depending on the system size limitation
	int maxClients_;
};

}
}
#endif
