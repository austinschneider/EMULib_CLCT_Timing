// $Id: I2OMessenger.h,v 1.2 2008/07/18 15:27:20 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _pt_tcp_I2OMessenger_h
#define _pt_tcp_I2OMessenger_h

#include "i2o/Messenger.h"
#include "pt/Address.h"
#include "pt/tcp/PeerTransportSender.h"
#include "pt/tcp/Channel.h"
#include "toolbox/mem/Reference.h"

namespace pt
{
namespace tcp
{

class PeerTransport;

class I2OMessenger: public i2o::Messenger
{
	public:
	
	I2OMessenger(tcp::PeerTransportSender * pt, pt::Address::Reference destination, pt::Address::Reference local);
	virtual ~I2OMessenger();
	
	pt::Address::Reference getLocalAddress();
	pt::Address::Reference getDestinationAddress();
	
	void send (toolbox::mem::Reference* msg, toolbox::exception::HandlerSignature* handler, void* context) 
		throw (pt::exception::Exception);
	
	private:
	
	pt::tcp::PeerTransportSender * pt_;
	pt::tcp::Channel * channel_;
	pt::Address::Reference destination_;
	pt::Address::Reference local_;
};

}
}

#endif

