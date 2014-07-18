// $Id: B2INMessenger.h,v 1.6 2008/08/26 15:00:53 lorsini Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _pt_tcp_B2INMessenger_h
#define _pt_tcp_B2INMessenger_h

#include "b2in/nub/Messenger.h"
#include "pt/Address.h"
#include "pt/tcp/PeerTransportSender.h"
#include "pt/tcp/Channel.h"
#include "toolbox/mem/Reference.h"
#include "b2in/nub/exception/InternalError.h"
#include "b2in/nub/exception/QueueFull.h"
#include "b2in/nub/exception/OverThreshold.h"

namespace pt
{
namespace tcp
{

class PeerTransport;

class B2INMessenger: public b2in::nub::Messenger
{
	public:
	
	B2INMessenger(tcp::PeerTransportSender * pt, pt::Address::Reference destination, pt::Address::Reference local)
		throw(pt::tcp::exception::Exception);

	virtual ~B2INMessenger();
	
	pt::Address::Reference getLocalAddress();
	pt::Address::Reference getDestinationAddress();
	
	void send (toolbox::mem::Reference* msg, xdata::Properties & plist, toolbox::exception::HandlerSignature* handler, void* context) 
			throw (b2in::nub::exception::InternalError, b2in::nub::exception::QueueFull, b2in::nub::exception::OverThreshold);
	private:
	
	pt::tcp::PeerTransportSender * pt_;
	pt::tcp::Channel * channel_;
	pt::Address::Reference destination_;
	pt::Address::Reference local_;
};

}
}

#endif

