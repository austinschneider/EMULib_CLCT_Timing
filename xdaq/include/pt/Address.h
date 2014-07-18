// $Id: Address.h,v 1.6 2008/07/18 15:27:18 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _pt_Address_h_
#define _pt_Address_h_

#include <string>

#include "toolbox/mem/CountingPtr.h"
#include "toolbox/mem/ThreadSafeReferenceCount.h"
#include "toolbox/mem/StandardObjectPolicy.h"

namespace pt
{

//! This class provides the network transport specific information.
//! In general the format of an address takes the form
//! <protocol>:://<network address>/<service name>/<service parameters>
//! A technology specific address class implements the provided interface.
//
class Address
{
	public:
	
	typedef toolbox::mem::CountingPtr<Address, toolbox::mem::ThreadSafeReferenceCount, toolbox::mem::StandardObjectPolicy> Reference;
	
	virtual ~Address() {};
	
	
	//! Retrieve the protocol part of the address, e.g. http
	//
	virtual std::string getProtocol() = 0;
	
	//! Retrieve the service name, e.g. "soap"
	//
	virtual std::string getService() = 0;
	
	//! Get a string representation of the address, e.g. a URL
	//
	virtual std::string toString () = 0;
	
	//! Retrieve additional service parameters
	//
	virtual std::string getServiceParameters() = 0;
	
	//! Address comparison
	virtual bool equals( Reference addressRef ) = 0;
};



}

#endif
