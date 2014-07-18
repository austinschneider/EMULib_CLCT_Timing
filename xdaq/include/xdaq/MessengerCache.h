// $Id: MessengerCache.h,v 1.9 2008/07/18 15:28:02 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdaq_MessengerCache_h_
#define _xdaq_MessengerCache_h_

#include "xdaq/ApplicationContext.h"
#include "xdaq/ApplicationGroup.h"
#include "xdaq/NetGroup.h"
#include "xdaq/Network.h"
#include "xdaq/RoutingTable.h"
#include "pt/Messenger.h"
#include "pt/PeerTransportAgent.h"
#include "xdaq/exception/MessengerCreationFailed.h"
#include "xdaq/ApplicationDescriptor.h"

#include "toolbox/BSem.h"

namespace xdaq 
{

//! This class maintains a cache of messenger pointers for fast access to 
//! the messenger by giving a source and destination tid.
//
class MessengerCache 
{
	xdaq::ApplicationContext* context_;

	public:

	MessengerCache (xdaq::ApplicationContext* context);
	
	//!
	//
	void invalidate 
	(
		xdaq::ApplicationDescriptor* from, 
		xdaq::ApplicationDescriptor* to
	)
	throw (xdaq::exception::Exception);
	
	//!
	//
	pt::Messenger* getMessenger
	(
		xdaq::ApplicationDescriptor* from, 
		xdaq::ApplicationDescriptor* to
	) 
	throw ( xdaq::exception::MessengerCreationFailed);
	
	protected:
	
	std::vector<pt::Messenger::Reference> messengerReferences_;
	std::map<xdaq::ApplicationDescriptor*, std::map<xdaq::ApplicationDescriptor*, pt::Messenger*> > messengers_;	
	toolbox::BSem lock_;
};

}

#endif







