// $Id: Network.h,v 1.8 2008/07/18 15:28:02 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdaq_Network_h_
#define _xdaq_Network_h_

#include <string>
#include <map>
#include "xdaq/Endpoint.h"
#include "xdaq/ContextDescriptor.h"
#include "pt/Address.h"

// Exception includes
#include  "xdaq/exception/AddressMismatch.h"
#include  "xdaq/exception/DuplicateEndpoint.h"
#include  "xdaq/exception/NoEndpoint.h"

namespace xdaq 
{


class Network
{
	public:
	
	Network(const std::string& name, const std::string& protocol);
	
	~Network();
	
	
	// Only one address for the same network on a given host
	//! Create an endpoint from an address, hostId and alias attribute
	//
	void addEndpoint (pt::Address::Reference address, 
				xdaq::ContextDescriptor* context, 
				bool alias)
		throw (xdaq::exception::DuplicateEndpoint, xdaq::exception::AddressMismatch);
		
	void addEndpoint (pt::Address::Reference address, 
				xdaq::ContextDescriptor* context, 
				bool alias,
				bool publish)
		throw (xdaq::exception::DuplicateEndpoint, xdaq::exception::AddressMismatch);
	
	pt::Address::Reference getAddress (xdaq::ContextDescriptor* context) throw (xdaq::exception::NoEndpoint);
	
	std::string getName() const;
	
	std::string getProtocol() const;
	
	xdaq::Endpoint* getEndpoint(xdaq::ContextDescriptor* context) throw (xdaq::exception::NoEndpoint);

	bool isEndpointExisting (xdaq::ContextDescriptor* context) const;
	
	private:
	
	// Endpoints are indexed by context descriptors
	std::map<xdaq::ContextDescriptor*, xdaq::Endpoint*, std::less<xdaq::ContextDescriptor*> > endpoints_;
	std::string name_;
	std::string protocol_;		
};

}

#endif

