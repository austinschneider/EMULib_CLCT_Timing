// $Id: I2OMessenger.h,v 1.1 2007/03/31 14:23:32 mpieri Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2004, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _atcp_I2OMessenger_h
#define _atcp_I2OMessenger_h

#include "pt/atcp/ATCP.h" //ADDEDATCP

#include "i2o/Messenger.h"
#include "pt/Address.h"
#include "pt/atcp/PeerTransportSender.h"
#include "pt/atcp/Channel.h"
#include "toolbox/mem/Reference.h"

// Log4CPLUS
#include "log4cplus/logger.h"
#include "log4cplus/consoleappender.h"
#include "log4cplus/helpers/appenderattachableimpl.h"
#include "log4cplus/helpers/loglog.h"
#include "log4cplus/helpers/pointer.h"
#include "log4cplus/spi/loggingevent.h"
#include "log4cplus/layout.h"

using namespace std;
using namespace log4cplus;
using namespace log4cplus::helpers;
using namespace log4cplus::spi;

namespace pt {
namespace atcp
{

class PeerTransport;

class I2OMessenger: public i2o::Messenger
{
	public:
	
	I2OMessenger(pt::atcp::PeerTransportSender * pt, pt::Address::Reference destination, pt::Address::Reference local, xdata::UnsignedInteger32T queueSize, Logger& logger) throw (pt::atcp::exception::Exception);
	virtual ~I2OMessenger();
	
	pt::Address::Reference getLocalAddress();
	pt::Address::Reference getDestinationAddress();
	
	void send (toolbox::mem::Reference* msg, toolbox::exception::HandlerSignature* handler, void* context) 
		throw (pt::exception::Exception);
	
	//! Get the channel
	pt::atcp::Channel * getChannel(); //ADDEDATCP
	
	private:
	
	pt::atcp::PeerTransportSender * pt_;
	pt::atcp::Channel * channel_;
	pt::Address::Reference destination_;
	pt::Address::Reference local_;

	Logger logger_;
};

}


}
#endif

