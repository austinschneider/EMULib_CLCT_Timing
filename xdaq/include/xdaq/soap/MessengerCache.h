// $Id: MessengerCache.h,v 1.3 2008/07/18 15:28:04 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdaq_soap_MessengerCache_h_
#define _xdaq_soap_MessengerCache_h_

#include "toolbox/net/UUID.h"
#include "xdaq/ApplicationContext.h"
#include "xdaq/ApplicationGroup.h"
#include "pt/Messenger.h"
#include "pt/PeerTransportAgent.h"
#include "xdaq/exception/MessengerCreationFailed.h"
#include "xdaq/ApplicationDescriptor.h"

#include "toolbox/BSem.h"

namespace xdaq 
{
namespace soap 
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
		xdaq::ApplicationDescriptor & from, 
		xdaq::ApplicationDescriptor & to
	)
	throw (xdaq::exception::Exception);
	
	//!
	//
	pt::Messenger::Reference getMessenger
	(
		xdaq::ApplicationDescriptor & from, 
		xdaq::ApplicationDescriptor & to
	) 
	throw ( xdaq::exception::MessengerCreationFailed);
	
	protected:
	
	std::map<toolbox::net::UUID, std::map<toolbox::net::UUID, pt::Messenger::Reference> > messengers_;	
	toolbox::BSem lock_;
};

}
}
#endif







