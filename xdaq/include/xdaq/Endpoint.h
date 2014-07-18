// $Id: Endpoint.h,v 1.6 2008/07/18 15:28:02 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdaq_Endpoint_h_
#define _xdaq_Endpoint_h_

#include "xdaq/ContextDescriptor.h"
#include "pt/Address.h"

namespace xdaq 
{

//! Associate and address with a host identifier. If this address is already
//! used in another address, the alias shall be set true.
//! An endpoint is associated with a network and can be retrieved through the Network class.
//
class Endpoint 
{
	public:
	
	//! Create an endpoint for a given context
	//
	Endpoint(pt::Address::Reference address, xdaq::ContextDescriptor* context, bool alias);
	Endpoint(pt::Address::Reference address, xdaq::ContextDescriptor* context, bool alias, bool publish);
	
	//! Retrieve the context to which this endpoint is associated
	//
	xdaq::ContextDescriptor* getContextDescriptor() const;	
	
	//! Retrieve the address that contains the specification of the endpoint
	pt::Address::Reference getAddress() const;
	
	//! If the endpoint is an alias to another endpoint that contains the same address, return true
	//
	bool isAlias() const;
	
	bool publish() const;
	
	void setActive(bool active);
	
	bool isActive() const;
	
	protected:
	
	pt::Address::Reference address_;
	xdaq::ContextDescriptor* context_;
	bool alias_;
	bool publish_;
	bool active_;
};

}



#endif







