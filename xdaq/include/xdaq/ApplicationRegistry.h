// $Id: ApplicationRegistry.h,v 1.9 2008/07/18 15:28:02 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdaq_ApplicationRegistry_h_
#define _xdaq_ApplicationRegistry_h_

#include <map>
#include <string>
#include <list>

#include "xdaq/ApplicationContext.h"
#include "xdaq/ApplicationDescriptor.h"
#include "xdaq/Application.h"
#include "xdaq/exception/ApplicationInstantiationFailed.h"
#include "xdaq/exception/ApplicationNotFound.h"
#include "xdata/UnsignedInteger.h"

namespace xdaq 
{

class ApplicationRegistry
{
	public:
	
	ApplicationRegistry
	(
		xdaq::ApplicationContext * context
	);
	
	//! Remove a registered XDAQ application from the run-time environment. This does not delete the application
	//
	void destroyApplication 
	(
		xdata::UnsignedIntegerT localId
	) 
	throw (xdaq::exception::ApplicationNotFound);
	
	//! Retrieve an application by tid
	//
	xdaq::Application * getApplication
	(
		xdata::UnsignedIntegerT localId
	) 
	throw (xdaq::exception::ApplicationNotFound);
	
	//! Instantiate an application object and return a non-mutable pointer to the newly created application. 
	//
	xdaq::Application* instantiateApplication 
	(
		xdaq::ApplicationDescriptor* descriptor
	) 
	throw (xdaq::exception::ApplicationInstantiationFailed);
	
	//! Find first object instance for class name
	//
	xdaq::Application* getFirstApplication
	(
		const std::string & className
	) 
	throw (xdaq::exception::ApplicationNotFound);
	
	//! Find first object instance for class name
	//
	xdaq::Application* getApplication
	(
		const std::string & className, 
		xdata::UnsignedIntegerT instance
	) 
	throw (xdaq::exception::ApplicationNotFound);
	
	//! Find applications that match a given attribute value
	//
	std::vector<xdaq::Application*> getApplications
	(
		const std::string & attribute, 
		const std::string & value
	);
	
	//! Get all instantiated applications
	//
	std::list<xdaq::Application*> getApplications();


	private:
	
	std::map <xdata::UnsignedIntegerT, xdaq::Application*,  std::less <xdata::UnsignedIntegerT> > applications_;
	xdaq::ApplicationContext* context_;
};

}


#endif
