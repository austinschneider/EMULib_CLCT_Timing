// $Id: ApplicationGroup.h,v 1.17 2008/07/18 15:28:02 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdaq_ApplicationGroup_h_
#define _xdaq_ApplicationGroup_h_

#include <set>
#include "xdaq/ApplicationDescriptor.h"
#include "xdaq/ContextDescriptor.h"
#include "xdata/UnsignedInteger.h"

// Includes for exceptions
#include "xdaq/exception/DuplicateTid.h"
#include "xdaq/exception/ApplicationDescriptorNotFound.h"
#include "xdaq/exception/DuplicateApplicationDescriptor.h"

namespace xdaq
{

class ApplicationGroup
{
	public:
	
	virtual ~ApplicationGroup() {}

					
	//! Retrieve list of configurations that belong to host
	//
	virtual std::set<xdaq::ApplicationDescriptor*> getApplicationDescriptors 
	(
		xdaq::ContextDescriptor * context
	) = 0;
	
	//! Retrieve a single application descriptor according to its class name and instance number
	//
	virtual xdaq::ApplicationDescriptor* getApplicationDescriptor
	(
		const std::string & className, 
		xdata::UnsignedIntegerT instance
	)
	throw (xdaq::exception::ApplicationDescriptorNotFound) = 0;
	
	//! Retrieve an application descriptor according to its local identifier within a given context
	//
	virtual xdaq::ApplicationDescriptor* getApplicationDescriptor 
	(
		xdaq::ContextDescriptor * context, 
		xdata::UnsignedIntegerT localId
	)
	throw (xdaq::exception::ApplicationDescriptorNotFound) = 0;
		
	//! Retrieve an application descriptor according to its local identifier within a given context
	//
	virtual bool hasApplicationDescriptor 
	(
		xdaq::ContextDescriptor * context, 
		xdata::UnsignedIntegerT localId
	) = 0;
	
	virtual bool hasApplicationDescriptor 
	(
		xdaq::ApplicationDescriptor* descriptor
	) = 0;
	
	virtual bool hasApplicationDescriptor 
	(
		const std::string & className, 
		xdata::UnsignedIntegerT instance
	) = 0;		
	
	//! Retrieve list of configurations that belong to a class 
	//
	virtual std::set<xdaq::ApplicationDescriptor*> getApplicationDescriptors 
	(
		const std::string & className
	) = 0;
	
	//! Retrieve list of configurations that match an attribute name/value pair 
	//
	virtual std::set<xdaq::ApplicationDescriptor*> getApplicationDescriptors 
	(
		const std::string & attribute,
		const std::string& value
	) = 0;
	
	//! Retrieve set of all configurations in group
	//
	virtual std::set<xdaq::ApplicationDescriptor*> getApplicationDescriptors () = 0;
	
	
	//! Return the name of this group 
	virtual std::string getName() = 0;		
};

}

#endif
