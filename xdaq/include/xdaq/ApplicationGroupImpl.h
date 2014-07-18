// $Id: ApplicationGroupImpl.h,v 1.8 2008/07/18 15:28:02 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdaq_ApplicationGroupImpl_h_
#define _xdaq_ApplicationGroupImpl_h_

#include <set>

#include "toolbox/BSem.h"
#include "xdaq/ApplicationDescriptor.h"
#include "xdaq/ContextDescriptor.h"
#include "xdaq/ApplicationGroup.h"

// Includes for exceptions
#include "xdaq/exception/DuplicateTid.h"
#include "xdaq/exception/ApplicationDescriptorNotFound.h"
#include "xdaq/exception/DuplicateApplicationDescriptor.h"
#include "xdata/UnsignedInteger.h"

namespace xdaq
{

class ApplicationGroupImpl: public xdaq::ApplicationGroup
{
	public:
	
	ApplicationGroupImpl(const std::string & name);
	~ApplicationGroupImpl();

					
	std::set<xdaq::ApplicationDescriptor*> getApplicationDescriptors 
	(
		xdaq::ContextDescriptor * context
	);
	
	//! Retrieve a single application descriptor according to its class name and instance number
	//
	xdaq::ApplicationDescriptor* getApplicationDescriptor 
	(
		const std::string & className, 
		xdata::UnsignedIntegerT instance
	)
	throw (xdaq::exception::ApplicationDescriptorNotFound);
	
	//! Retrieve an application descriptor according to its local identifier within a given context
	//
	xdaq::ApplicationDescriptor* getApplicationDescriptor 
	(
		xdaq::ContextDescriptor * context, 
		xdata::UnsignedIntegerT localId
	)
	throw (xdaq::exception::ApplicationDescriptorNotFound);
	
	//! Retrieve set of configurations that belong to a class 
	//
	std::set<xdaq::ApplicationDescriptor*> getApplicationDescriptors 
	(
		const std::string & className
	);
	
	//! Retrieve list of configurations that match an attribute name/value pair 
	//
	std::set<xdaq::ApplicationDescriptor*> getApplicationDescriptors 
	(
		const std::string & attribute,
		const std::string& value
	);
	
	//! Retrieve an application descriptor according to its local identifier within a given context
	//
	bool hasApplicationDescriptor (xdaq::ContextDescriptor * context, xdata::UnsignedIntegerT localId);
	
	bool hasApplicationDescriptor 
	(
		xdaq::ApplicationDescriptor* descriptor
	);
	
	bool hasApplicationDescriptor 
	(
		const std::string & className, 
		xdata::UnsignedIntegerT instance
	);			
	
	//! Retrieve list of configurations that belong to a class 
	//
	std::set<xdaq::ApplicationDescriptor*> getApplicationDescriptors ();
		
	//! Add an application config
	//
	void addApplicationDescriptor (xdaq::ApplicationDescriptor* descriptor);
	
	//! Return the name of this group 
	std::string getName();	
	
	protected:
	
	std::string name_;
	std::set<xdaq::ApplicationDescriptor*> applicationDescriptors_;
	toolbox::BSem lock_;
};

}

#endif
