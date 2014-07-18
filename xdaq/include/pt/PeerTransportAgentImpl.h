// $Id: PeerTransportAgentImpl.h,v 1.12 2008/07/18 15:27:18 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _pt_PeerTransportAgentImpl_h_
#define _pt_PeerTransportAgentImpl_h_

#include <vector>
#include <string>

#include "pt/PeerTransportAgent.h"
#include "pt/Messenger.h"
#include "pt/Address.h"
#include "pt/Listener.h"
#include "pt/exception/PeerTransportNotFound.h"

namespace pt
{

class PeerTransportAgentImpl: public pt::PeerTransportAgent
{
	public:
	
	virtual ~PeerTransportAgentImpl();
	
	static PeerTransportAgent * instance();
	
	//! Returns a list of installed peer transports
	//
	std::vector<pt::PeerTransport*> getPeerTransports();

	//! Add a peer transport. The name of the peer transport is contained by the object passed
	//
	void addPeerTransport(pt::PeerTransport* pt) throw (pt::exception::Exception);
	
	//! Remove a peer transport. Get the object by calling one of getPeerTransport or getPeerTransports
	//
	void removePeerTransport (pt::PeerTransport* pt) throw (pt::exception::PeerTransportNotFound);
	
	//! Retrieve a peer transport according its protocol, service and type (e.g. TCP, I2O, pt::Sender )
	//
	pt::PeerTransport* getPeerTransport (std::string protocol, std::string service, pt::TransportType t) 
		throw (pt::exception::PeerTransportNotFound);
	
	//! Create an address object by providing a url. To create an address the associated 
	//! peer transport needs to be installed.
	//
	pt::Address::Reference createAddress( const std::string & url, const std::string & service ) 
		throw (pt::exception::InvalidAddress);
		
	pt::Address::Reference createAddress( std::map<std::string, std::string, std::less<std::string> >& address )
		throw (pt::exception::InvalidAddress);
	
	//! Retrieve a messenger by address that can be used to send a message
	//
	pt::Messenger::Reference getMessenger ( pt::Address::Reference destination, pt::Address::Reference local ) throw (pt::exception::NoMessenger);
	
	//! Add a listener for receiving a message on any of the installed peer transports for a service.
	//! The name of the service is retrieved by pt::Listener::getService().
	//! The listener callback function is invoked on every message received.
	//
	void addListener ( pt::Listener* listener) throw (pt::exception::DuplicateListener); 
	
	//! Remove an installed listener
	//
	void removeListener ( pt::Listener* listener ) throw (pt::exception::NoListener) ;
	
	//! Retrieve the installed listener for a service
	//
	pt::Listener* getListener ( const std::string & service) throw (pt::exception::NoListener);
	
	//! Retrieve all listeners
	//
	std::vector<pt::Listener*> getListeners(const std::string & service);
	
	//! Remove all installed listeners
	//
	void removeAllListeners();
	
	private:
	
	static PeerTransportAgentImpl * instance_;
	std::vector<pt::PeerTransport*> senders_;
	std::vector<pt::PeerTransport*> receivers_;
	std::map<std::string, pt::Listener*, std::less<std::string> > services_;
	
};

}

#endif
