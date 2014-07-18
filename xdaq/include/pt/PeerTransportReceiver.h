// $Id: PeerTransportReceiver.h,v 1.8 2008/07/18 15:27:18 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _pt_PeerTransportReceiver_h
#define _pt_PeerTransportReceiver_h

#include <string>
#include <vector>

#include "pt/Listener.h"
#include "pt/Address.h"
#include "pt/PeerTransport.h"
#include "pt/exception/Exception.h"

#include <map>

namespace pt
{

//! Interface for a transport receiver class.
//! A concrete peer transport implementation needs
//! to implement this interface.
//
class PeerTransportReceiver: public virtual pt::PeerTransport
{
	public:
	
	virtual ~PeerTransportReceiver();
	
	//! Add a multiple listeners, one for each service type supported
	//
	virtual void addServiceListener ( pt::Listener* listener ) throw (pt::exception::Exception); 
	
	//! Remove an installed listener
	//
	virtual void removeServiceListener (pt::Listener* listener ) throw (pt::exception::Exception);
	
	//! Remove all installed listener
	//
	virtual void removeAllServiceListeners();
	
	//! Check if a listener for a service exists
	//
	virtual bool isExistingListener (std::string service);
	
	//! Retrieve the installed listener for a service
	//
	virtual pt::Listener* getListener (std::string service) throw (pt::exception::Exception);

	//! Add a new receiver address. Configuration is implementation dependent
	//
	virtual void config (pt::Address::Reference address) throw (pt::exception::Exception) = 0;
	
	private:
	
	std::map<std::string, pt::Listener*, std::less<std::string> > listeners_;
	
};

}

#endif
