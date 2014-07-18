// $Id: PeerTransportAgent.h,v 1.12 2008/07/18 15:27:18 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _pt_PeerTransportAgent_h_
#define _pt_PeerTransportAgent_h_

#include <string>
#include <vector>

#include "pt/PeerTransport.h"
#include "pt/Listener.h"
#include "pt/Messenger.h"
#include "pt/Address.h"
#include "pt/exception/PeerTransportNotFound.h"
#include "pt/exception/NoMessenger.h"
#include "pt/exception/InvalidAddress.h"
#include "pt/exception/DuplicateListener.h"
#include "pt/exception/NoListener.h"


namespace pt
{


class PeerTransportAgent
{
	public:
	
	virtual ~PeerTransportAgent()
	{
	}
	
	//! Returns a list of installed peer transports
	//
	virtual std::vector<pt::PeerTransport*> getPeerTransports() = 0;
		
	//! Add a peer transport. The name of the peer transport is contained by the object passed
	//
	virtual void addPeerTransport(pt::PeerTransport* pt) throw (pt::exception::Exception) = 0;
	
	//! Remove a peer transport. Get the object by calling one of getPeerTransport or getPeerTransports
	//
	virtual void removePeerTransport (pt::PeerTransport* pt) throw (pt::exception::PeerTransportNotFound)  = 0;
	
	//! Retrieve a peer transport according its protocol, service and type (e.g. TCP, I2O, pt::Sender )
	//
	virtual pt::PeerTransport* getPeerTransport (std::string protocol, std::string service, pt::TransportType t) 
		throw (pt::exception::PeerTransportNotFound) = 0;
			
	//! Create an address object by providing a url. To create an address the associated 
	//! peer transport needs to be installed.
	//
	virtual pt::Address::Reference createAddress( const std::string& url, const std::string & service )
		throw (pt::exception::InvalidAddress)  = 0;
		
	virtual pt::Address::Reference createAddress( std::map<std::string, std::string, std::less<std::string> >& address ) 
		throw (pt::exception::InvalidAddress) = 0;
	
	//! Retrieve a messenger by address that can be used to send a message
	//
	virtual pt::Messenger::Reference getMessenger ( pt::Address::Reference destination, pt::Address::Reference local) throw (pt::exception::NoMessenger) = 0;
	
	//! Add a listener for receiving a message on any of the installed peer transports
	//! That offer the specified service. If no matching pt is found, the listener is
	//! still remembered. As soon as a pt with the service becomes available, messages can
	//! be received on this listener.
	//
	virtual void addListener ( pt::Listener* listener) throw (pt::exception::DuplicateListener) = 0; 
	
	//! Remove an installed listener
	//
	virtual void removeListener ( pt::Listener* listener )  throw (pt::exception::NoListener) = 0;
	
	//! Retrieve the installed listener for a service
	//
	virtual pt::Listener* getListener ( const std::string & service) throw (pt::exception::NoListener) = 0;
	
	//! Retrieve all listeners
	//
	virtual std::vector<pt::Listener*> getListeners(const std::string & service) = 0;
	
	//! Remove all installed listeners
	//
	virtual void removeAllListeners() = 0;
	
};

PeerTransportAgent * getPeerTransportAgent();

}

#endif
