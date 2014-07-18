// $Id: MessengerCache.h,v 1.3 2008/07/18 15:27:53 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _ws_service_MessengerCache_h_
#define _ws_service_MessengerCache_h_

#include "toolbox/net/UUID.h"
#include "ws/addressing/EndpointReference.h"
#include "pt/Messenger.h"
#include "pt/PeerTransportAgent.h"
#include "xdaq/exception/MessengerCreationFailed.h"

#include "toolbox/BSem.h"

namespace ws 
{
namespace service 
{

//! This class maintains a cache of messenger pointers for fast access to 
//! the messenger by giving a source and destination tid.
//
class MessengerCache 
{
	public:

	MessengerCache ();
	
	//!
	//
	void invalidate 
	(
		ws::addressing::EndpointReference & from, 
		ws::addressing::EndpointReference & to
	)
	throw (xdaq::exception::Exception);
	
	//!
	//
	pt::Messenger::Reference getMessenger
	(
		ws::addressing::EndpointReference & from, 
		ws::addressing::EndpointReference & to
	) 
	throw ( xdaq::exception::MessengerCreationFailed);
	
	protected:
	
	std::map<toolbox::net::UUID, std::map<toolbox::net::UUID, pt::Messenger::Reference> > messengers_;	
	toolbox::BSem lock_;
};

}
}
#endif







